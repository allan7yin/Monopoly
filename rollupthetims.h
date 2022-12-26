#ifndef ROLLUPTHETIMSCUP_H
#define ROLLUPTHETIMSCUP_H

#include <vector>

class Player;

class RollUpTheTims{
    static int maxNumOfCups;
    static std::vector<Player *> owners;
    static int currNumOfCups;

    public:
        static void giveCup(Player * p); // adds player to an empty slot in owners
        static void removeCup(Player * p); // removes the first instance of the player that points to the same address
        static int numOfCups(Player * p); // return number of cups that the player has
        static bool canGiveCup();
};


#endif
