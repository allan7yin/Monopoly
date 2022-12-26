#include "gototimsaction.h"

#include "Player.h"
#include <string>

void GoToTimsAction::actionOnSquare(Player * p){
    // move the player to the tims
    
    // the location of the square in the board's vector
    const std::string TIMS_SQUARE = "DC TIMS LINE";
    p->move(TIMS_SQUARE);
    //p->setInJail(true);
}
