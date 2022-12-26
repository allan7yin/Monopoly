#include "slc.h"

Slc::Slc(std::string name, int position):
    Chance{this->generateActionDeck()},
    NonProperties(name, position, nullptr)
{
    setAction(pickAction());
}

std::vector<Action *> Slc::generateActionDeck(){
    std::vector<Action *> actionsDeck;
    
    // -3 and +1 spaces
    for(int i = 0; i < 3; i++){
        Action * action = SLCActionsFactory::createAction("-3");
        actionsDeck.emplace_back(action);
        action = SLCActionsFactory::createAction("1");
        actionsDeck.emplace_back(action);
    }

    // -2, -1 and +2  and +3 spaces
    for(int i = 0; i < 4; i++){
        Action * action =  SLCActionsFactory::createAction("-2");
        actionsDeck.emplace_back(action);
        action =  SLCActionsFactory::createAction("-1");
        actionsDeck.emplace_back(action);
        action =  SLCActionsFactory::createAction("1");
        actionsDeck.emplace_back(action);
        action =  SLCActionsFactory::createAction("3");
        actionsDeck.emplace_back(action);
    }

    //dc tims and osap
    for(int i = 0; i < 1; i++) {
        Action * action =  SLCActionsFactory::createAction("DC Tims Line");
        actionsDeck.emplace_back(action);
        action =  SLCActionsFactory::createAction("COLLECT OSAP");
        actionsDeck.emplace_back(action);
    }


    // shuffle
    actionsDeck = shuffleDeck(actionsDeck);
    return actionsDeck;
}

void Slc::actionOnSquare(Player * p){
    setAction(pickAction());
    NonProperties::actionOnSquare(p);
    if(getAction() != Chance::TimsAction){
        discardPile.emplace_back(getAction());
    }
    setAction(nullptr);
}

Slc::~Slc() {
    delete action;
    action = nullptr;
}
