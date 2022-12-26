#ifndef OWNABLEFACTORY_H_
#define OWNABLEFACTORY_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Ownable;
enum class OwnableType;
class Player;

class OwnableFactory {
	map<string, vector<int>> buildinfo;
	map<string, OwnableType> buildpay;
public:
	OwnableFactory();
	Ownable* createOwnable(string name, int position);
};

#endif /* OWNABLEFACTORY_H_ */
