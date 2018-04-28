#ifndef DECK_HH
#define DECK_HH

#include "card.hh"

#include <algorithm>
#include <deque>
#include <vector>

#include <thread>
#include <chrono>

class Deck
{
public:
    Deck();
    ~Deck();

    void shuffle();

    void start();

    void skipNext();

    void setSkip(bool state);

    void addForNext(unsigned amount);

    void setNextColor(Color color);

    void setColorAssigned(bool state);

    void putToDeck(std::vector<Card*> cards);

    bool needToSkip();

    unsigned cardsToTake();

    void firstTop();

    bool getColorAssigned();

    std::vector<Card*> pick(unsigned amount);

    Card* getTop() const;

    std::deque<Card*> getDeck() const;

    Color getNextColor();

    unsigned size() const;

private:
    void getTrash();

    bool skip_;
    unsigned takeAmount_;
    bool colorAssigned_;
    Color nextColor_;

    Card* top_;

    std::deque<Card*> deck_;
    std::vector<Card*> trashed_;
    std::vector<Card*> ptrVector_;

};

#endif // DECK_HH
