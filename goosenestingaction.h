//
//  goosenestingaction.h
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef goosenestingaction_h
#define goosenestingaction_h

#include "action.h"

class Player;

class GooseNestingAction: public Action{
    void actionOnSquare(Player * p);
};

#endif /* goosenestingaction_h */
