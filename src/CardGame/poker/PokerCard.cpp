
#include "PokerCard.h"
#include <stdio.h>
#include "Utils.h"

std::string PokerCard::PokerTypeToStr[6] = {"♠", "♥", "♣","♦", "大", "小"};
std::string PokerCard::PokerNumberToStr[14] = {
        "王","A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
};

PokerCard::PokerCard(PokerType type, PokerNumber number){
        this->type = type;
        this->number = number;
}

PokerCard::~PokerCard(){
}

PokerType PokerCard::getType() const {
        return type;
}
PokerNumber PokerCard::getNumber() const {
        return number;
}

// use to find straight
PokerNumber PokerCard::getNextNumber() const {
        if(number == _3) return _4;
        else if(number == _4) return _5;
        else if(number == _5) return _6;
        else if(number == _6) return _7;
        else if(number == _7) return _8;
        else if(number == _8) return _9;
        else if(number == _9) return _10;
        else if(number == _10) return J;
        else if(number == J) return Q;
        else if(number == Q) return K;
        else if(number == K) return A;
        else if(number == A) return _2;
        else return JOKER;
}

bool PokerCard::isRed() const {
        if (type == HEART ||
            type == DIAMOND ||
            type == RED
            ) return true;
        else return false;
}

void PokerCard::print() const {
        printf("%s%s",
               PokerTypeToStr[type].c_str(),
               PokerNumberToStr[number].c_str()
               );
}
void PokerCard::colorPrint() const {
        if(isRed()) printf(PRINT_RED);
        this->print();
        if(isRed()) printf(PRINT_END);
}
