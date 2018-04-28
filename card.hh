#ifndef CARD_HH
#define CARD_HH

enum Color {blue, red, yellow, green, black};

struct Card {
    Color color;
    unsigned value;
};

const unsigned PLUS2 = 10;
const unsigned BLOCK = 11;
const unsigned SWITCH = 12;

const Card PLUS4 = {black, 13};
const Card JOKER = {black, 14};

const unsigned SPECIALS[3] = {PLUS2, BLOCK, SWITCH};
const Card SUPERS[2] = {PLUS4, JOKER};

#endif // CARD_HH
