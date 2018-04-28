#include "deck.hh"

Deck::Deck():
    skip_(false),
    takeAmount_(0),
    colorAssigned_(false),
    nextColor_(Color::yellow),
    top_(nullptr),
    deck_(0),
    trashed_(0),
    ptrVector_(0)
{
    Card *card = nullptr;

    // Add zero cards (only 1 per color)
    Color colors[4] = {blue, red, yellow, green};

    for (auto color : colors) {
        card = new Card{color, 0};
        deck_.push_back(card);
        ptrVector_.push_back(card);
    }

    // Add other regular cards
    for (unsigned i = 0; i <= 3; ++i) {

        for (unsigned j = 1; j <= 12; ++j) {

            for (unsigned x = 0; x < 2; ++x) {

                switch (i) {
                case 0:
                    card = new Card{blue, j};
                    break;
                case 1:
                    card = new Card{red, j};
                    break;
                case 2:
                    card = new Card{yellow, j};
                    break;
                case 3:
                    card = new Card{green, j};
                    break;
                }
                deck_.push_back(card);
                ptrVector_.push_back(card);
            }
        }
    }

    for (unsigned i = 0; i < 4; ++i) {
        card = new Card(JOKER);
        deck_.push_back(card);
        ptrVector_.push_back(card);
        card = new Card(PLUS4);
        deck_.push_back(card);
        ptrVector_.push_back(card);
    }
}

Deck::~Deck()
{
    for (auto n : ptrVector_) {
        delete n;
    }
}

void Deck::shuffle()
{
    if (size() > 1) {
        std::random_shuffle(deck_.begin(), deck_.end());
    }
}

void Deck::skipNext()
{
    skip_ = true;
}

void Deck::setSkip(bool state)
{
    skip_ = state;
}

void Deck::addForNext(unsigned amount)
{
    takeAmount_ += amount;
}

void Deck::setNextColor(Color color)
{
    nextColor_ = color;
    colorAssigned_ = true;
}

void Deck::setColorAssigned(bool state)
{
    colorAssigned_ = state;
}

void Deck::putToDeck(std::vector<Card *> cards)
{
    // Trash previous top
    trashed_.push_back(top_);

    // Trash everything else than card coming to top
    for (auto it = cards.begin(); it != cards.end() - 1; ++it) {
        trashed_.push_back(*it);
    }
    // Put last added to top
    top_ = cards[cards.size()-1];
}

bool Deck::needToSkip()
{
    if (skip_) {
        skip_ = false;
        return true;
    }
    return false;
}

unsigned Deck::cardsToTake()
{
    return takeAmount_;
}

void Deck::firstTop()
{
    while (1) {
        Card* card = deck_.front();

        if (card->color == black) {
            deck_.push_back(card);
            deck_.pop_front();
            continue;
        }
        else {
            top_ = card;
            break;
        }
    }
}

bool Deck::getColorAssigned()
{
    return colorAssigned_;
}

Card *Deck::getTop() const
{
    return top_;
}

std::deque<Card *> Deck::getDeck() const
{
    return deck_;
}

Color Deck::getNextColor()
{
    return nextColor_;
}

std::vector<Card *> Deck::pick(unsigned amount)
{
    // Not enough cards in deck
    if (size() < amount) {
        // Get more cards from trash
        getTrash();
    }

    std::vector<Card*> toHand(0);

    for (unsigned i = 0; i < amount; ++i) {
        toHand.push_back(deck_.front());
        deck_.pop_front();
    }

    takeAmount_ = 0;
    return toHand;
}

unsigned Deck::size() const
{
    return deck_.size();
}

void Deck::getTrash()
{
    // Mix trashed cards and add back to deck
    std::random_shuffle(trashed_.begin(), trashed_.end());
    for (auto a : trashed_) {
        deck_.push_back(a);
    }
    trashed_.clear();
}
