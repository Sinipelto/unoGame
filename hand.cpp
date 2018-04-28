#include "hand.hh"

Hand::Hand(Deck *deck):
    deck_(deck),
    hand_(0)
{
}

void Hand::addToHand(std::vector<Card *> cards)
{
    for (auto c : cards) {
        hand_.push_back(c);
    }
}

std::vector<Card *> Hand::getHand()
{
    return hand_;
}

unsigned Hand::handSize()
{
    return hand_.size();
}

bool Hand::insertToDeck()
{
    std::vector<Card *> colorMatch;
    std::vector<Card *> valueMatch;
    std::vector<Card *> result;

    Card* onTop = deck_->getTop();

    Color targetColor = onTop->color;

    if (deck_->getColorAssigned()) {
        targetColor = deck_->getNextColor();
    }

    unsigned count = 0;

    for (auto it = hand_.begin(); it != hand_.end(); ++it) {
        if ((*it)->color == targetColor) {
            colorMatch.push_back(*it);
            hand_.erase(it);
            break;
        }
    }

    if (colorMatch.size() > 0) {
        for (auto card : hand_) {
            if (card->value == colorMatch[0]->value) {
                colorMatch.push_back(card);
            }
        }
    }

    for (auto card : hand_) {
        if (card->value == onTop->value) {
            valueMatch.push_back(card);
            ++count;
        }
    }

    if (valueMatch.size() <= 0 && colorMatch.size() <= 0) {
        return false;
    }

    if (valueMatch.size() > colorMatch.size()) {
        hand_.push_back(colorMatch[0]); // Return color matched card
        // Remove matching cards from hand
        for (auto m : valueMatch) {
            for (auto it = hand_.begin(); it != hand_.end(); ++it) {
                if (*it == m) {
                    hand_.erase(it);
                    break;
                }
            }
        }
        deck_->putToDeck(valueMatch);
        result = valueMatch;
    }

    else {
        for (auto m : colorMatch) {
            for (auto it = hand_.begin(); it != hand_.end(); ++it) {
                if (*it == m) {
                    hand_.erase(it);
                }
            }
        }
        deck_->putToDeck(colorMatch);
        result = colorMatch;
    }

    for (unsigned num : SPECIALS) {
        if (result[0]->value == num) {
            for (unsigned i = 0; i < colorMatch.size(); ++i) {
                switch (num) {
                case PLUS2:
                    deck_->addForNext(2);
                    break;
                case BLOCK:
                    deck_->skipNext();
                    break;
                case SWITCH:
                    // Should be: change direction
                    deck_->skipNext();
                    break;
                }
            }
        }
    }

    const unsigned num = result[0]->value;

    switch (num) {
    case 13: // PLUS4
        deck_->addForNext(4);
        break;
    case 14: // JOKER
        // Replace with user-defined color
        deck_->setNextColor(Color::green);
        break;
    }

    deck_->setColorAssigned(false);
    return true;
}
