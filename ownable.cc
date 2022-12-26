#include <iostream>
#include <vector>
#include <string>
#include "ownable.h"
#include "Player.h"
using namespace std;

Ownable::Ownable(string name, int position, int bprice, int rprice, OwnableType buildtype) : Building{name, position}, Asset(nullptr, false, bprice), isMortgage{false}, rentPrice{rprice}, buildtype{buildtype}, blockSize{0} {
    vector<Ownable*> myOwn;
    propertyBlock = myOwn;
    numImprovements = 0;
}

void Ownable::addToBlock(Ownable* myOwn) {
	propertyBlock.emplace_back(myOwn);
	blockSize += 1;
}

void Ownable::trade(Asset *other) {
    Player *temp = getOwner();
    this->setOwner(other->getOwner());
    other->setOwner(temp);
}

bool Ownable::ownBlock() {
	for (int i = 0; i < blockSize; i++) {
		if (propertyBlock[i]->getOwner() != getOwner()) {
			return false;
		}
	}
	return true;
}

OwnableType Ownable::getType(){
    return buildtype;
}

int Ownable::otherBlock() {
    int counter = 0;
    for (int i = 0; i < blockSize; i++) { // calculates how many other buildings in the block that the owner owns
        if (propertyBlock[i]->getOwner() == getOwner()) {
            counter += 1;
        }
    }
    return counter;
}

void Ownable::toggleMortgage() {
	isMortgage = !(isMortgage);
}

bool Ownable::checkMortgage() {
	return isMortgage;
}

int Ownable::getRentPrice() {
	return rentPrice;
}

int Ownable::getSize() {
	return blockSize;
}

void Ownable::actionOnSquare(Player* p) {
    Player* propOwner = getOwner();
    if (checkOwned() && (owner->getName() != "Bank")) { // if building is owned then player has to pay rent to owner
        
        if (propOwner == p) {
            return;
        } // if the owner landed on their own property, nothing happens
        
        if (checkMortgage()) {
            return;
        } // if the building is mortgaged then there is no need to pay rent
        
        int tuitionPrice = 0;
        if (buildtype == OwnableType::Improvable) {
            tuitionPrice = getRentPrice(); // 998, 878
            if (ownBlock() && numImprovements == 0) {
                tuitionPrice *= 2;
            } // if a monopoly block is owned then double tuition
        } else if (buildtype == OwnableType::Residence) {
            int counter = otherBlock(); // how many other buildings in block owned
            tuitionPrice = getRentPrice(); // tuition price if only one residence is owned (should be 25)
            for (int i = 0; i < counter; i++) { // for each extra residence the owner owns, the tuition price is doubled
                tuitionPrice *= 2;
            }
        } else if (buildtype == OwnableType::Gym) {
            int counter = otherBlock();
            tuitionPrice = p->roll(); // tuition price is calculated by rolling two dice and adding up the sum
            if (counter == 1) {
                tuitionPrice *= 10;
            } // fee is 10 times the sum of the dice if own both gyms
            else {
                tuitionPrice *= 4;
            } // fee is 4 times the sum of the dice of only own one gym
        }
        
        if (p->getCash() >= tuitionPrice) { // checks if player's cash is more than the tuition price
            p->subCash(tuitionPrice);
            propOwner->addCash(tuitionPrice);
            cout << "The player has payed the required tuition price." << endl;
        } else { // if player's cash is less than the tuition price, they need to get more cash
            cout << "Get more cash to pay the tuition price." << endl;
            p->getMoreCash(); // player only has one chance to get more cash
            if (p->getCash() < tuitionPrice) { // if the player's cash is still less than tuition price, they go bankrupt and transfer assets
                p->bankrupt(propOwner); // when bankrupt, the player transfers all assets to the owner
                cout << "The player has now gone bankrupt." << endl;
                return;
            } else { // if the player's cash is now greater than or equal the tuition price, they pay it off
                p->subCash(tuitionPrice);
                propOwner->addCash(tuitionPrice);
                cout << "The player has payed the required tuition price."
                        << endl;
            }
        }
        
    } else { // if building is not owned then player has option to buy the Ownable
        char response;
        cout << "=>+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "You are able to purchase the building!" << endl;
        while (true) { // while loop to ensure that player enters a valid choice

            cout << "Would you like to buy " << name <<  " for $" << getValue() << "? (Y/N)" << endl;
            cout << "Your resonse: " << endl;
            cin >> response;
            if (response == 'Y' || response == 'y') {
                if (p->getCash() >= getValue()) { // if the player has enough cash then they can buy the Ownable
                    p->subCash(getValue());
                    setOwner(p); // set the owner of the Ownable to the player
                    p->addProperty(this); // adds the Ownable to the list of Ownables that the player owns
                    cout << p->getName() <<  " has bought " << getName() << "!"
                            << endl;
                    break;
                } else {
                    cout << "Get more cash and try again." << endl;
                    bool cond = p->getMoreCash(); // the player can now get more cash before deciding to buy the Ownable again
                    if (cond) {
                        // means Player chose to dropout
                        p->bankrupt(propOwner); // should be to bank
                        cout << p->getName() << " has dropped out." << endl;
                        return;
                    }
                }
            } else if (response == 'N' || response == 'n') {
                p->auction(this);
                break;
            } else {
                cout << "Please enter a valid answer (Y/N)" << endl;
            }
        }
    }
}

void Ownable::saveData(ofstream &out) {
    // here, we print the player's data into the ostream reference (which is the save file)
    out << name << " " << owner->getName() << " "<< numImprovements << endl;
}

int Ownable::getNumImprovements() {
    return numImprovements;
}

bool Ownable::isImprovable() {
    return (buildtype == OwnableType::Improvable);
}

void Ownable::addImprovement() {
    numImprovements++;
}

void Ownable::subImprovement() {
    numImprovements--;
}


void Ownable::setRentPrice(int num) {
    rentPrice = num;
}

