#ifndef _NEEDLESHALL_H
#define _NEEDLESHALL_H

#include "nonproperties.h"
#include "needleshallactionsfactory.h"
#include "chance.h"

class Action;
class Player;

class NeedlesHall: public NonProperties, public Chance{
public:
    NeedlesHall(std::string name, int position);
    void actionOnSquare(Player * p) override;
    std::vector<Action *> generateActionDeck() override;
    //~NeedlesHall();
};

#endif
