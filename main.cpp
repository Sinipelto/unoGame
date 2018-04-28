#include "deck.hh"
#include "hand.hh"

#include <iostream>

using namespace std;

using CardDeque = std::deque<Card*>;
using CardVector = std::vector<Card*>;

std::string enumToString(Color value) {
    switch (value) {
    case blue:
        return "blue";
    case green:
        return "green";
    case red:
        return "red";
    case yellow:
        return "yellow";
    case black:
        return "special";
    }
    return "NULL";
}

template <typename T>
void printContainer(const T &container) {
    cout << "{ ";

    for (unsigned i = 0; i < container.size(); ++i) {
        auto result = dynamic_cast<Card*>(container[i]);
        cout << enumToString(result->color) << ":" << result->value << " ";
    }

    cout << "}";
    cout << endl << endl;
}

void playTurn(Hand *hand, Deck *deck) {
    if (deck->cardsToTake() > 0) {
        hand->addToHand(deck->pick(deck->cardsToTake()));
    }

    if (deck->needToSkip()) {
        deck->setSkip(false); // Stop skipping
        return;
    }

    if (!hand->insertToDeck()) {
        // Pick one from deck and try again
        hand->addToHand(deck->pick(1));
        hand->insertToDeck();
    }
}

int main()
{
    Deck *deck = new Deck();
    Hand *hand1 = new Hand(deck), *hand2 = new Hand(deck);

    cout << deck->size() << endl;

    deck->shuffle();
//    printContainer<CardDeque>(deck->getDeck());

    cout << "DEBUG1" << endl;
    hand1->addToHand(deck->pick(7));
    hand2->addToHand(deck->pick(7));

    cout << "DEBUG2"<< endl;
    deck->firstTop();

//    printContainer<CardVector>(hand1->getHand());
//    printContainer<CardVector>(hand2->getHand());

    bool turn = true;
    unsigned turnCount = 0;

    cout << "DEBUG3" << endl;

    while (hand1->handSize() > 0 && hand2->handSize() > 0) {
        printContainer<std::vector<Card*>>(hand1->getHand());
        printContainer<std::vector<Card*>>(hand2->getHand());

        if (turn) {
            playTurn(hand1, deck);
            turn = !turn;
        }
        else {
            playTurn(hand2, deck);
            turn = !turn;
        }
        ++turnCount;
    }

    if (hand1->handSize() == 0) {
        cout << "Winner: player 1" << endl;
    }
    else if (hand2->handSize() == 0) {
        cout << "Winner: player 2" << endl;
    }

    delete deck;
    delete hand1;
    delete hand2;
    return 0;
}
