#include "nonpropertiesactionsfactory.h"

class Action;
#include "coopfeeaction.h"
#include "tuitionaction.h"
#include "goosenestingaction.h"
#include "gototimsaction.h"
#include "osapaction.h"
#include "dctimslineaction.h"

Action * NonPropertiesActionsFactory::createAction(std::string type){
    Action * action = nullptr;
    if (type == "COOP FEE") {
        action = new CoopFeeAction();
    } else if (type == "TUITION") {
        action = new TuitionAction();
    } else if (type == "Goose Nesting") {
        action = new GooseNestingAction();
    } else if (type == "GO TO TIMS") {
        action = new GoToTimsAction();
    } else if (type == "COLLECT OSAP") {
    action = new OSAPAction();
    } else if (type == "DC Tims Line") {
        action = new DCTimsLineAction();
    }
    
    return action;
}
