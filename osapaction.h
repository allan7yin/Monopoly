//
//  osapaction.h
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef osapaction_h
#define osapaction_h


#include "action.h"

class Player;

class OSAPAction: public Action{
    void actionOnSquare(Player * p);
};

#endif /* osapaction_h */
