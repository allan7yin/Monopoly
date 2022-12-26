//
//  dctimsaction.h
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef dctimslineaction_h
#define dctimslineaction_h

#include "action.h"

class Player;

class DCTimsLineAction: public Action{
    void actionOnSquare(Player * p);
};


#endif /* dctimslineaction_h */
