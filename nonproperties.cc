#include "nonproperties.h"
#include "action.h"

NonProperties::NonProperties(std::string name, int position, Action * action):
    Building{name, position},
    action{action}
{}


void NonProperties::actionOnSquare(Player * p){
    action->actionOnSquare(p);
}

void NonProperties::setAction(Action * newAction){
    action = newAction;
}

void NonProperties::saveData(std::ofstream &out) {
    // nothing happens for now
}

Action * NonProperties::getAction(){
    return action;
}

int NonProperties::getNumImprovements() {
    return 0;
}

bool NonProperties::isImprovable() {
    return false;
}


