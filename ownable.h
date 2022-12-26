#ifndef OWNABLE_H_
#define OWNABLE_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "building.h"
#include "Asset.h"
using namespace std;

class Player;
enum class OwnableType { Gym, Residence, Improvable };

class Ownable : public Building, public Asset {
	bool isMortgage;
	int blockSize;
    OwnableType buildtype;
	vector<Ownable*> propertyBlock;
    int numImprovements;
    
protected:
    int rentPrice;
public:
	Ownable(string name, int position, int bprice, int rprice, OwnableType buildtype);
	void addToBlock(Ownable* myOwn);
	bool ownBlock();
    int otherBlock();
	void toggleMortgage();
	bool checkMortgage();
	int getRentPrice();
    void setRentPrice(int num);
	int getSize();
    OwnableType getType();
    void trade(Asset *other) override;
    void actionOnSquare(Player*) override;
    void saveData(std::ofstream &out) override;
    int getNumImprovements() override;
    void addImprovement();
    void subImprovement();
    bool isImprovable() override;
};

#endif /* OWNABLE_H_ */
