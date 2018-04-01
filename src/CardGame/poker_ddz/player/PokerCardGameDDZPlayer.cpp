#include "PokerCardGameDDZPlayer.h"
#include "PokerCardGameDDZInfo.h"
#include "PokerCardGameDDZEventList.h"
#include "EventTagList.h"
#include "PokerCardGameDDZUtils.h"
#include <sstream>
#include "PlayCardsAction.h"
#include "PokerCard.h"

PokerCardGameDDZPlayer::PokerCardGameDDZPlayer(int id, std::string name) {
        this->id =id;
        this->name = name;
        this->dz_player = NULL;
}

PokerCardGameDDZPlayer::~PokerCardGameDDZPlayer() {
}

void PokerCardGameDDZPlayer::regist(EventQueue * q) {
        this->addTag(EVENT_TAG_GAME_PROCESS);
        this->addTag(EVENT_TAG_PLAYER_ACTION);
        q->addListener(this);
}

enum DDZCardGroupSet {
        STRAIGHT,
        SINGLE_CARD,
        PAIR_OF_CARDS,
        THREE_CARDS,
        FOUR_CARDS,
        DOUBLE_JOKER,
};

void getAllCardsSet(std::vector<Card*> &c, std::vector<std::vector<CardGroup> >& res) {
        // get all single/pair/three/four cards
        int st = 0;
        int ed = 1;
        while(st<c.size()) {
                while(ed<c.size() && ((PokerCard*)c[ed-1])->getNumber() == ((PokerCard*)c[ed])->getNumber()) {
                        ed++;
                }
                CardGroup g;
                for(int i=st; i<ed; i++) {
                        g.add(c[i]);
                }
                if(ed-st == 2 && ((PokerCard*)c[st])->getNumber() == JOKER) {
                        res[DOUBLE_JOKER].push_back(g);
                } else {
                        res[ed-st].push_back(g);
                }
                st = ed++;
        }

        // get all straight
        st = 0;
        ed = 1;
        while(st<c.size()) {
                while(ed<c.size() &&
                      ((PokerCard*)c[ed-1])->getNextNumber() == ((PokerCard*)c[ed])->getNumber() &&
                      ((PokerCard*)c[ed])->getNumber()  != _2 &&
                      ((PokerCard*)c[ed])->getNumber()  != JOKER
                      ) {
                        ed++;
                }
                if(ed-st>=5) {
                        CardGroup g;
                        for(int i=st; i<ed; i++) {
                                g.add(c[i]);
                        }
                        res[0].push_back(g);
                }
                st = ed++;
        }
}

CardGroup PokerCardGameDDZPlayer::think() {
        //if(last_useful_play_card_info.player == this) {
        std::vector<Card*> c = this->cards.getVector();
        std::vector<std::vector<CardGroup> > cards_set(6);
        getAllCardsSet(c, cards_set);
        CardGroup g;
        // if (last_useful_play_card_info.player == this ||
        //     last_useful_play_card_info.player == NULL
        //     ) {
        if(cards_set[THREE_CARDS].size() > 0) {
                g.add(cards_set[THREE_CARDS][0]);
                if(cards_set[SINGLE_CARD].size() > 0) {
                        g.add(cards_set[SINGLE_CARD][0]);
                } else if(cards_set[PAIR_OF_CARDS].size() > 0) {
                        g.add(cards_set[PAIR_OF_CARDS][0]);
                }
        } else if(cards_set[STRAIGHT].size() > 0) {
                g.add(cards_set[STRAIGHT][0]);
        } else if(cards_set[PAIR_OF_CARDS].size() > 0) {
                g.add(cards_set[PAIR_OF_CARDS][0]);
        } else if(cards_set[SINGLE_CARD].size() > 0) {
                g.add(cards_set[SINGLE_CARD][0]);
        } else if(cards_set[FOUR_CARDS].size() > 0) {
                g.add(cards_set[FOUR_CARDS][0]);
        }else if(cards_set[DOUBLE_JOKER].size() > 0) {
                g.add(cards_set[DOUBLE_JOKER][0]);
        }
        // } else {
        //
        // }
        return g;
}

void PokerCardGameDDZPlayer::process(Event* e, EventQueue* q) {
        std::string name=e->getName();
        if (name == EVENT_DZ_ASK_TO_BE) {
                Player * player = (Player *)(e->getData());
                if(player == this) {
                        std::ostringstream str;
                        Event * e;
                        // TODO: Decide if to be dz
                        if(rand()%2 == 0) {
                                e = new Event(EVENT_DZ_TO_BE);
                                str << player->getName() << " answered YES";
                        } else {
                                e = new Event(EVENT_DZ_NOT_TO_BE);
                                str << player->getName() << " answered NO";
                        }

                        e->setExplanation(str.str());
                        e->addTag(EVENT_TAG_PLAYER_ACTION);
                        e->setData(player);
                        q->push(e);
                }
        } else if(name == EVENT_DZ_CLAIM) {
                Player * player = (Player *)(e->getData());
                this->dz_player = player;
                this->last_useful_play_card_info.player = NULL;
        } else if(name == EVENT_DZ_SHOW_3_CARDS) {
                CardGroup * cards = (CardGroup*) (e->getData());
                if(this->dz_player == this) {
                        this->cards.add(*cards);
                        this->cards.sort(handCardComparator);
                        printf("Player %s: ", this->name.c_str());
                        this->cards.print(); puts("");
                }
        } else if(name == EVENT_ASK_TO_PLAY) {
                Player * player = (Player*) (e->getData());
                if(player == this) {
                        std::ostringstream str;
                        str << this->name << " is going to play some cards";
                        Event * e = new Event(EVENT_READY_TO_PLAY_CARDS);
                        e->setExplanation(str.str());
                        e->addTag(EVENT_TAG_PLAYER_ACTION);
                        e->setData(this);
                        q->push(e);

                        CardGroup g = this->think();

                        PlayCardsAction * action = new PlayCardsAction(g);
                        e = new Event(EVENT_PLAY_CARDS);
                        e->setExplanation("Playing cards");
                        e->addTag(EVENT_TAG_PLAYER_ACTION);
                        e->setData(action);
                        q->push(e);
                }
        } else if (name == EVENT_READY_TO_PLAY_CARDS) {
                Player * curr_player = (Player*) (e->getData());
                this->curr_player = curr_player;
        } else if (name == EVENT_PLAY_CARDS) {
                PlayCardsAction * action = (PlayCardsAction*) (e->getData());
                if(this->curr_player == this) {
                        action->playBy(this);
                        printf("%s: now ", this->name.c_str());
                        this->cards.print(); puts("");
                        if(this->cards.size() == 0) {
                                Event * e = new Event(EVENT_FINISH_ALL_CARD);
                                e->addTag(EVENT_TAG_PLAYER_ACTION);
                                q->push(e);
                        } else {
                                Event * e = new Event(EVENT_PLAY_CARDS_DONE);
                                e->addTag(EVENT_TAG_PLAYER_ACTION);
                                q->push(e);
                        }
                }
                if (action->getCards().size()) {
                        this->last_useful_play_card_info.player = this->curr_player;
                        this->last_useful_play_card_info.cards = action->getCards();
                }
        }
}
