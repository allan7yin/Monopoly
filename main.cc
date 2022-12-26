//
//  main.cpp
//  Watopoly
//
//  Created by w375liu on 2022-07-22.
//

#include "Game.h"
#include <fstream>

// would be helpful to define some "helper" functions to help test code
//  - printing the properties a player owns, number of cash, number of properties, location player is on, ...
//  - printing the the number of improvements a property has, # of players on it

int main(int argc, const char * argv[]) {
    // ./watapoly testing
    if(argc == 2 && string(argv[1]) == "-testing"){
        //testing dice
        Game *Watopoly = new Game{true};
        Watopoly->play();
        delete Watopoly;
    }
    
    // ./watapoly -load savefile
    else if(argc == 3 && string(argv[1]) == "-load"){
        Game *Watopoly = new Game{false};
        ifstream gameFile (argv[2]);
        Watopoly->load(gameFile);
        delete Watopoly;
    }
    else{
        Game *Watopoly = new Game{false};
        Watopoly->play();
        delete Watopoly;
    }
    return 0;
}
