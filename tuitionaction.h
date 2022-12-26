//
//  tuitionaction.h
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef tuitionaction_h
#define tuitionaction_h

#include "action.h"

class Player;

class TuitionAction: public Action{
    void actionOnSquare(Player * p);
};



#endif /* tuitionaction_h */
