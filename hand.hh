#ifndef HAND_HH
#define HAND_HH

#include "deck.hh"

class Hand
{
public:
    Hand(Deck *deck);

    void addToHand(std::vector<Card*> cards);

    std::vector<Card*> takeFromHand(std::vector<Card*> cards);

    std::vector<Card*> getHand();

    unsigned handSize();

    void sortHand();

    bool insertToDeck();

private:
    Deck *deck_;
    std::vector<Card*> hand_;

};

#endif // HAND_HH
