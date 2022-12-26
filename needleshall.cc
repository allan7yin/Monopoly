#include "needleshall.h"

NeedlesHall::NeedlesHall(std::string name, int position):
    Chance{this->generateActionDeck()},
    NonProperties(name, position, nullptr)
{
    setAction(pickAction());
}

std::vector<Action *> NeedlesHall::generateActionDeck(){
    std::vector<Action *> actionsDeck;
    // build a deck of actions that match the probability given

    // -200 and 200
    for(int i = 0; i < 1; i++){
        Action * action =  NeedlesHallActionsFactory::createAction(-200);
        actionsDeck.emplace_back(action);
        action =  NeedlesHallActionsFactory::createAction(200);
        actionsDeck.emplace_back(action);
    }

    // -100 and +100
    for(int i = 0; i < 2; i++){
        Action * action =  NeedlesHallActionsFactory::createAction(-100);
        actionsDeck.emplace_back(action);
        action =  NeedlesHallActionsFactory::createAction(100);
        actionsDeck.emplace_back(action);
    }

    // -50 and +50
    for(int i = 0; i < 3; i++){
        Action * action =  NeedlesHallActionsFactory::createAction(-50);
        actionsDeck.emplace_back(action);
        action =  NeedlesHallActionsFactory::createAction(50);
        actionsDeck.emplace_back(action);
    }

    // 25
    for(int i = 0; i < 6; i++){
        Action * action =  NeedlesHallActionsFactory::createAction(25);
        actionsDeck.emplace_back(action);
    }

    // shuffle
    actionsDeck = shuffleDeck(actionsDeck);
    return actionsDeck;
}


void NeedlesHall::actionOnSquare(Player * p){
    setAction(pickAction());
    NonProperties::actionOnSquare(p);
    if(getAction() != Chance::TimsAction){
        discardPile.emplace_back(getAction());
    }
    setAction(nullptr);
}

//NeedlesHall::~NeedlesHall() {}
