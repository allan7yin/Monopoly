#include "slcaction.h"
#include "Player.h"
#include <string>

class Player;
#include "building.h"

void SLCAction::actionOnSquare(Player * p){
    // move the player to the tims
    if (position == "GO TO TIMS" && p->getBoardPosition() == 3) { // the only SLC that will not cross OSAP when moving to DC Tims Line
        p->move("-32"); // we simulate this by moing backwards, since moving backwards will never earn OSAP money
    } else {
        p->move(position);
    }
}
