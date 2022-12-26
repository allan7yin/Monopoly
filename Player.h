//
//  Player.hpp
//  A5
//
//  Created by Allan Yin on 2022-07-20.
//

#ifndef Player_hpp
#define Player_hpp

#include <vector>
#include <string>
#include <fstream>


using namespace std;

class Ownable;
class Improvable;
class Board;
class Building;
class Asset;
class Die;

class Player {
    string name;
    char symbol;
    int position;
    
    int totalMoney; // sum of the Money Vector

    bool inLine = false;
    int turnsInLine = 0;
    
    Board *board;
    Player *Bank;
    Ownable *is_owned(string name);
    Player *valid_player(string name);
    
    Die *die;
    void mortgage(Ownable *other);
    void unmortgage(Ownable *other);
    
public:
    vector<Ownable *> myProperties;
    Player(string name, char symbol, int position, int totalMoney, vector<Ownable *> myProperties, Board *board, Player *Bank, Die *die);
    void setBoard(Board *b);
    bool isOwned(string name);
    string getName();
    char getSymbol();
    
    Building *getPosition();
    int getBoardPosition();
    
    void move(string increment);
    void move(bool forward);
    
    void mortgage(string buildName);
    void unmortgage(string buildName);
    
    void buyImprovement(Improvable * i);
    void sellImprovement(Improvable * i);

    void addCash(int amount) {
        totalMoney+=amount;
    }
    
    void bankrupt(Player *p);
    
    
    int getCash() {
        return totalMoney;
    }
    
    void subCash(int amount) {
        totalMoney-=amount;
    }

    void setInLine(bool inLine);

    bool getInLine();

    void setTurnsInLine(int n);

    int getTurnsInLine();
    
    int netWorth();
    
    int playerTotalValue();
    
    bool getMoreCash();
    
    void auction(Ownable *myOwn);
    
    void request_trade();
    void trade(string ob1, string ob2, Player *p);
    void addProperty(Ownable *o);
    int roll();
    
    void saveData(ofstream &out);
    void displayAssets();
};



#endif /* Player_hpp */

