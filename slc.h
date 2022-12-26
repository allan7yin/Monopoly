#ifndef SLC_H
#define SLC_H

#include "nonproperties.h"
#include "chance.h"
#include "slcactionsfactory.h"

class Action;
class Player;

class Slc: public NonProperties, public Chance{
public:
    Slc(std::string name, int position);
    void actionOnSquare(Player * p) override;
    std::vector<Action *> generateActionDeck() override;
     ~Slc();

};

#endif
