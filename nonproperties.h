#ifndef _NONPROPERTIES_H
#define _NONPROPERTIES_H

#include "building.h"
#include <fstream>

class Action;
class Player;

class NonProperties: public Building {
protected:
    Action *action;
public:
    virtual void actionOnSquare(Player * p) override; // no need for this, if ur gunna make this virtual and override, just make it virtual and override in the derived classes of nonproperties
    NonProperties(std::string name, int position, Action * action);
    void setAction(Action * newAction);
    void saveData(std::ofstream &out) override;
    Action * getAction();
    int getNumImprovements() override;
    bool isImprovable() override;

    virtual ~NonProperties() {
        delete action;
        //action = nullptr;
    }
};

#endif
