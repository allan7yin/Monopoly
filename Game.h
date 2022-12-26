//
//  Game.hpp
//  Assignment5
//
//  Created by Allan Yin on 2022-07-23.
//


#ifndef Game_hpp
#define Game_hpp

#include <istream>
#include <vector>

class Board;
class Player;

using namespace std;

class Game {
    bool testing;
    void runGame(Board * game, vector<Player *> players); //run the main game component
    
public:
    Game(bool testing);
    void play(); // runs the Watopoly game from the beginning
    void load(ifstream & in); // loads the monopoly game from a savefile
};

#endif /* Game_hpp */
