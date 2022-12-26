//
//  Board.hpp
//  A5
//
//  Created by Allan Yin on 2022-07-20.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include "Player.h"
#include "building.h"
#include "Subject.h"
#include <utility>
#include <map>

using namespace std;

class Player;
class Building;
class Die;
struct ImprovementData;

class Board: public Subject {
    vector<Building *> theBoard; // LENGTH 40
    // above is owns-a relationship, aggregation
    vector<Player *> players; // array of players who are active in the game
    Player *curPlayer; // pointer to the current player
    Die *die;
    Player *Bank;
    //bool DemoMode; -> we can set this up later
    vector<ImprovementData *> table; // destory when board is detroyed
    vector<Ownable *> ownables;
    
public:
    void popPlayer(Player *p);
    void setCurPlayer(Player * other);
    // constructor for board object
    Board(vector<Player *> players, Die *die, vector<string> squareNames, vector<string> buildingTypes, Player *Bank);
    
    // overloaded constructor that takes in additional info
    Board(map<string, pair<string, int>> & buildingInfo, Die *die, vector<Player *> players, vector<string> squareNames, vector<string> buildingTypes, Player *Bank);
    
    // rolls the die, returns an integer of the sum
    pair<bool, int> roll(int numOfDoubles = 0);
    // for testing
    pair<bool, int> roll(int first, int second, int numOfDoubles = 0);
    
    // moves player forward in a fixed amount of spaces
    void move_player(string increment); // for jump squares like "go to tims line"
    void move_player(int increment); // for normal movement on board
    
    // performs all actions possible for player on the square, given game state
    void actions();
    
    // skips the current player's turn and moves onto the next player in line
    void next();

    // requests a trade between current player and *p, can be accepted or denied
    // if accepted, trade will be executed in Player class 
    void trade();
    
    // improves an academic building
    void improve(string name);
    void sell_improvement(string name);
    
    // mortgages an academic building
    void mortgage();
    
    // unmortgages an acadmeic building
    void unmortgage();
    
    // current player has declared bankrupcy, a set of actions are now allowed
    void bankrupt();
    
    // prints the current player's assets
    void display_assets();
    
    // prints all assets of all players in the game
    void all_player_assets();
    
    void display_all();
    
    int getPlayerWorth();
    
    void save(ofstream & out);
    
    void attach(Observer *ob) override;
    void notifyobservers() override;
    
    
    ~Board();
    friend class Player;
    friend class TextDisplay;
};


#endif /* Board_hpp */

