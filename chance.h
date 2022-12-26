#ifndef _CHANCE_H
#define _CHANCE_H

class Action;

#include "rollupthetims.h"
#include "rollupthetimsaction.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Chance{

    protected:
        std::vector<Action *> actionsDeck; // holds the deck of actions that can be drawn
        std::vector<Action *> discardPile;

        virtual std::vector<Action *> generateActionDeck() = 0;
        int randomPercentage();
        Action * pickAction();
        std::vector<Action *> shuffleDeck(std::vector<Action *> deck);
    public:
        Chance(std::vector<Action *> actionsDeck);
        static RollUpTheTimsAction * TimsAction;
        virtual ~Chance();
    
};

// want a way of generating the actions
// want a way of picking the actions

#endif
