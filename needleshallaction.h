//
//  needleshallaction.h
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef needleshallaction_h
#define needleshallaction_h

#include "action.h"
class Player;

class NeedlesHallAction: public Action{
    
    public:
        int money;

    void actionOnSquare(Player * p);
};

#endif /* needleshallaction_h */
