#include "slcactionsfactory.h"

class Action;
#include "slcaction.h"
#include <string>


Action * SLCActionsFactory::createAction(std::string position){
    //SLCAction * action;
    SLCAction * action = new SLCAction();
    action->position = position; 
    return action;
}
