//
//  die.cpp
//  Watopoly
//
//  Created by w375liu on 2022-07-22.
//

#include "die.h"
#include <iostream>

Die::Die(int maxValue): maxValue{maxValue} {}

int Die::roll(){
  return (1 + (std::chrono::system_clock::now().time_since_epoch().count() % maxValue));
}
