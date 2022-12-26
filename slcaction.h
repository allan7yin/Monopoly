//
//  slcaction.h
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef slcaction_h
#define slcaction_h

#include "action.h"
#include <string>

class Player;

class SLCAction: public Action{
    public:
        std::string position; // where to move player

    void actionOnSquare(Player * p);
};

#endif /* slcaction_h */
