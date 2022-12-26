#include "rollupthetimsaction.h"
#include "rollupthetims.h"

class Player;

void RollUpTheTimsAction::actionOnSquare(Player * p){
    // gives the player a roll up the rims cup
   RollUpTheTims::giveCup(p);
}

