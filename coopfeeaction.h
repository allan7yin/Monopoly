//
//  coopfeeaction.h
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef coopfeeaction_h
#define coopfeeaction_h

#include "action.h"

class Player;

class CoopFeeAction:  public Action{
    void actionOnSquare(Player * p);
};


#endif /* coopfeeaction_h */
