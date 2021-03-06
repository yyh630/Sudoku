#include "PlayCardsAction.h"
#include "Utils.h"

PlayCardsAction::PlayCardsAction(CardGroup cards) {
        this->cards = cards;
}

PlayCardsAction::~PlayCardsAction() {
}

std::string PlayCardsAction::getName() {
        return "PlayCardsAction";
}


void PlayCardsAction::playBy(Player* p) const {
        p->eraseCards(this->cards);
        printf("PlayCardsAction: ");
        printf(PRINT_YELLOW); this->cards.print();  printf(PRINT_END);
        printf(" (%s)", p->getName().c_str());

        puts("");
}

void PlayCardsAction::inversePlayBy(Player* p) const {
        p->addCards(this->cards);
        printf("PlayCardsAction: %s withdraw ", p->getName().c_str());
        this->cards.print();
        puts("");
}

CardGroup PlayCardsAction::getCards() {
        return cards;
}
