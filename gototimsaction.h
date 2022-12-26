//
//  gototimsaction.h
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef gototimsaction_h
#define gototimsaction_h

#include "action.h"

class Player;

class GoToTimsAction: public Action{
    void actionOnSquare(Player * p);
};

#endif /* gototimsaction_h */
