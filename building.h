#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <fstream>

class Action;
class Ownable;
class Player;

class Building {
protected:
    std::string name;
    int position;
public:
    Building(std::string name, int position);
    std::string getName();
    virtual void actionOnSquare(Player *p) = 0;
    virtual void saveData(std::ofstream &out) = 0;
    virtual int getNumImprovements() = 0;
    virtual bool isImprovable() = 0;
    virtual ~Building() = default;
    
};

#endif
