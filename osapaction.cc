#include "osapaction.h"
#include "Player.h"

class Player;

void OSAPAction::actionOnSquare(Player * p){
    // adds 200 to the player

    // we play with house rules here
    const int OSAP_MONEY = 200;
    p->addCash(OSAP_MONEY);
}
