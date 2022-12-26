#include "chance.h"

#include "rollupthetimsaction.h"
#include "rollupthetims.h"

Chance::Chance(std::vector<Action *> actionsDeck):
    actionsDeck{actionsDeck}
{}

RollUpTheTimsAction * Chance::TimsAction = new RollUpTheTimsAction();

Action * Chance::pickAction(){
    //  roll up the rim action is 1% and only occurs if we can give cup
    if(randomPercentage() == 0 && RollUpTheTims::canGiveCup()){
        return TimsAction;
    }
    else{
        // the actionsDeck is empty, so all the cards are in the discardPile
        if(actionsDeck.size() == 0){
            swap(actionsDeck, discardPile);

            // shuffle the deck
            actionsDeck = shuffleDeck(actionsDeck);
        }
        Action * temp = actionsDeck.back();
        actionsDeck.pop_back();

        return temp;
    }
}

std::vector<Action *> Chance::shuffleDeck(std::vector<Action *> deck){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    shuffle(deck.begin(), deck.end(), rng);
    return deck;
}

int Chance::randomPercentage(){
    return std::chrono::system_clock::now().time_since_epoch().count() % 100;
}

Chance::~Chance() {
    delete TimsAction;
    TimsAction = nullptr;
    for (auto i: actionsDeck) {
        delete i;
        i = nullptr;
    }
    
    for (auto i: discardPile) {
        delete i;
        i = nullptr;
    }
}
