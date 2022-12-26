//
//  Cash.cpp
//  Assignment5
//
//  Created by Allan Yin on 2022-07-22.
//

#include "Cash.h"

void Cash::trade(Asset *other) {
    other->trade(this);
}
