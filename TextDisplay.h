//
//  TextDisplay.hpp
//  Assignment5
//
//  Created by Allan Yin on 2022-07-24.
//

#ifndef TextDisplay_hpp
#define TextDisplay_hpp
#include "Observer.h"

class Board;

class TextDisplay: public Observer {
public:
    TextDisplay(Subject *board); // constructor
    void notify(Board *whoNotified) override;
};

#endif /* TextDisplay_hpp */


