#include "coopfeeaction.h"
#include "action.h"
#include "Player.h"

class Player;


void CoopFeeAction::actionOnSquare(Player * p){
    // coop fee square action
    const int COOPFEE = 150;
    p->subCash(COOPFEE);
}
