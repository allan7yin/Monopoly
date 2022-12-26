#include "rollupthetims.h"

int RollUpTheTims::maxNumOfCups = 4;
int RollUpTheTims::currNumOfCups = 0;
std::vector<Player *> RollUpTheTims::owners = std::vector<Player *>(maxNumOfCups);


void RollUpTheTims::giveCup(Player * p){
    if(canGiveCup()){
        // we can find a spot for the player
        
        // the current number of cups is less than the size of the vector
        // thus we can find place to add the player in the vector
        currNumOfCups++;
        for(int i = 0; i < maxNumOfCups; i++){
            if(owners[i] == nullptr){
                owners[i] = p;
                return;
            }
        }
    }
}

void RollUpTheTims::removeCup(Player * p){
    for(int i = 0; i < maxNumOfCups; i++){
        if(owners[i] == p){
            owners[i] = nullptr;
            currNumOfCups--;
            return;
        }
    }
}

int RollUpTheTims::numOfCups(Player * p){
    int counter = 0;
    for(int i = 0; i < maxNumOfCups; i++){
        if(owners[i] != nullptr && owners[i] == p){
            counter++;
        }
    }
    return counter;
}


bool RollUpTheTims::canGiveCup(){
    return (currNumOfCups + 1 < maxNumOfCups);
}

