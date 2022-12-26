//
//  rollupthetims.h
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef rollupthetims_h
#define rollupthetims_h

#include "action.h"

class Player;


class RollUpTheTimsAction: public Action{
    void actionOnSquare(Player * p);
};


#endif /* rollupthetims_h */
