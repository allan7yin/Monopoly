#include "needleshallactionsfactory.h"

#include "needleshallaction.h"

Action * NeedlesHallActionsFactory::createAction(int money){
    NeedlesHallAction * action = new NeedlesHallAction();
    action->money = money; 
    return action;
}
