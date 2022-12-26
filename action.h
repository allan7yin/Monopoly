//
//  action.hpp
//  A5
//
//  Created by j446zhao on 2022-07-23.
//

#ifndef ACTION_H
#define ACTION_H

class Player;

class Action {
public:
    virtual void actionOnSquare(Player * p) = 0; // action to take place when the player lands on the square
    virtual ~Action() = default;
};

#endif
