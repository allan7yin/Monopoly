#include "needleshallaction.h"
#include "Player.h"


class Player;


void NeedlesHallAction::actionOnSquare(Player * p){
    // give player money
    p->addCash(money);
}
