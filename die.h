//
//  die.h
//  Watopoly
//
//  Created by w375liu on 2022-07-22.
//

#ifndef die_h
#define die_h

#include <algorithm>
#include <random>
#include <chrono>

class Die {
    int maxValue;
public:
    Die(int maxValue);
    int roll();
};

#endif /* die_h */
