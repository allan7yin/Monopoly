//
//  Board.cpp
//  A5
//
//  Created by Allan Yin on 2022-07-20.
//

#include "Board.h"
#include "die.h"
#include "ownablefactory.h"
#include "nonpropertiesfactory.h"
#include "nonproperties.h"
#include "ImprovementData.h"
#include "ownable.h"
#include "Observer.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <utility>
#include <map>


using namespace std;

void Board::popPlayer(Player *p) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i] == p) {
            // remove it
            players.erase(players.begin() + i);
        }
    }
}

void Board::setCurPlayer(Player *other) {
    curPlayer = other;
}

// constructor for Board
Board::Board(vector<Player *> players, Die *die, vector<string> squareNames, vector<string> buildingTypes, Player *Bank): die{die}, players{players}, Bank{Bank} {
    // now, we need to create building objects
    // we have been given the names of each building, type of each building, and now call on the respective factories to return an object
    for (int i = 0; i < 40; i++) {
        if (buildingTypes[i] == "Ownable") {
            OwnableFactory of;
            
            // for now, we will manually construct the ownable ojects, will use factory when done
            Ownable *member = of.createOwnable(squareNames[i], i);
            theBoard.emplace_back(member);
            member->setOwner(Bank);
            ownables.emplace_back(member);
            
            // for now, before read in file is fully implemented, we will do this with a sample vector of 10 objects
        } else {
            // same thing as above, we use a small scalaed down verison of the vector for now
            theBoard.emplace_back(NonPropertiesFactory::createNonProperties(squareNames[i], i));
        }
    }
    
    // by this point, the vector<Building *> theBoard, vector has been initialized
    // now, we take the time to add the board's pointer to each player
    for (int i = 0; i < players.size(); i++) {
        players[i]->setBoard(this);
    }

    ifstream improvementsFile;
    improvementsFile.open("Improvements.txt");
    // now, we make a ImprovableData table and pass its pointer to baord
    map<string, string> academicBuildings; // maps each building name to its block
    vector<string> academicNames;
    for (int i = 0; i < 22; i++) {
        // now, we read in from the file and store a line into an entry object
        ImprovementData *entry = new ImprovementData;
        string name;
        improvementsFile >> name;
        entry->name = name;
       // academicNames.emplace_back(name);
        string monopolyblock;
        improvementsFile >> monopolyblock;
        entry->monpoly = monopolyblock;
        academicBuildings[name] = monopolyblock;
        int pcost;
        improvementsFile >> pcost;
        entry->purchaseCost = pcost;
        int icost;
        improvementsFile >> icost;
        entry->improvementCost = icost;
        
        // now, we loop and read in tuition changes
        for (int i = 0; i < 6; i++) {
            int num;
            improvementsFile >> num;
            entry->improvedTuition.emplace_back(num);
        }

        table.emplace_back(entry);
    }
    
    // we need a vecotr of the pointers to all of the ownable objects
    for (int i = 0; i < academicBuildings.size(); i++) {
        for (int j = 0; j < academicBuildings.size(); j++) {
            if ((academicBuildings[ownables[i]->getName()] == academicBuildings[ownables[j]->getName()]) && (i != j)) {
                // they share the same monopoly block
                ownables[i]->addToBlock(ownables[j]);
            }
        }
    }
    
    // now, the table of improvement data is initialized
    improvementsFile.close();
}

pair<bool, int> Board::roll(int first, int second, int numOfDoubles){
    int moveCount = first + second;
    if(first == second){
        numOfDoubles++;
        cout << numOfDoubles << endl;
        if(numOfDoubles == 3){
            // go to jail
            string jail = "DC Tims Line";
            curPlayer->move(jail);
            curPlayer->setInLine(true);
            //curPlayer->setTurnsInLine(1);
            return pair<bool, int>(false, 0);
        }
    }
    
    for (int i = 0; i < moveCount; i++) {
        curPlayer->move(true);
        if (curPlayer->getPosition()->getName() == "COLLECT OSAP") {
            curPlayer->addCash(200);
        }
    }
    theBoard[curPlayer->getBoardPosition()]->actionOnSquare(curPlayer);
    notifyobservers();
    
    return pair<bool, int>(first == second, numOfDoubles);
}

// each player starts at position 0, each building will have vector of players on it
pair<bool, int> Board::roll(int numOfDoubles) {
    int first_roll = die->roll();
    int second_roll = die->roll();
    
    if(first_roll == second_roll){
        cout << numOfDoubles << endl;
        numOfDoubles++;
        if(numOfDoubles == 3){
            // go to jail
            curPlayer->move("DC Tims Line");
            curPlayer->setInLine(true);
            //curPlayer->setTurnsInLine(1);
            return pair<bool, int>(false, 0);
        }

    }
    
    int moveCount = first_roll + second_roll;
    for (int i = 0; i < moveCount; i++) {
        curPlayer->move(true);
        if (curPlayer->getPosition()->getName() == "COLLECT OSAP") {
            curPlayer->addCash(200);
        }
    }
    
    theBoard[curPlayer->getBoardPosition()]->actionOnSquare(curPlayer);

    notifyobservers();
    

    return pair<bool, int>(first_roll == second_roll, numOfDoubles);
}

// these two moves are for NON-PROP
void Board::move_player(string increment) {
    curPlayer->move(increment);
}

void Board::move_player(int increment) {
    for (int i = 0; i < increment; i++) {
        curPlayer->move(true);
    }
}

void Board::actions() {
    theBoard[curPlayer->getBoardPosition()]->actionOnSquare(curPlayer);
}

void Board::trade() {
    curPlayer->request_trade();
}

void Board::improve(string name){
    Ownable *temp;
    if (curPlayer->isOwned(name)) {
        // find pointer to the object
        for (auto i: curPlayer->myProperties) {
            if (i != nullptr && i->getName() == name) {
                temp = i;
            }
        }
        
        if (!(temp->ownBlock())) {
            cout << "Invalid: Player does not own the monopoly block" << endl;
            return;
        }
        
        if (temp->getNumImprovements() == 5) {
            cout << "Invalid. The maximum number of improvements have already been applied this building." << endl;
            return;
        }
        
        // now, we can determine if it is improvable
        
        if (temp->isImprovable()) {
            // so. we own the building, it is improvable, now we check if our money is enough
            
            // we need to find the location in the improvmens table
            for (auto i: table) {
                if (temp->getName() == i->name) { // means matches, we now can open i for the right info}
                    // we want to access the numImporvemnts + 1, column
                    curPlayer->subCash(i->improvementCost);
                    temp->addImprovement(); // increments number of improvement son the building
                    temp->setRentPrice(i->improvedTuition[temp->getNumImprovements()]);
                }
            }
        }
        
    }
}

void Board::sell_improvement(string name) {
    Ownable *temp;
    if (curPlayer->isOwned(name)) {
        // find pointer to the object
        for (auto i: curPlayer->myProperties) {
            if (i != nullptr && i->getName() == name) {
                temp = i;
            }
        }
        
        if (temp->getNumImprovements() == 0) {
            cout << "Invalid. The building has not been improved." << endl;
            return;
        }
        
        // now, we can determine if it is can sell
        
        if (temp->isImprovable()) {
            // so. we own the building, it is improvable, now we check if our money is enough
            
            // we need to find the location in the improvmens table
            for (auto i: table) {
                if (temp->getName() == i->name) { // means matches, we now can open i for the right info}
                    // we want to access the numImporvemnts + 1, column
                    curPlayer->addCash(i->improvementCost);
                    temp->subImprovement(); // increments number of improvement son the building
                    temp->setRentPrice(i->improvedTuition[temp->getNumImprovements()]);
                }
            }
        }
        
    }
}

void Board::mortgage() {
    // now, we need to read in what property the player wishes to mortgage
    string readIn;
    cin >> readIn;
    
    curPlayer->mortgage(readIn);
}

void Board::unmortgage() {    
    string readIn;
    cin >> readIn;
    
    curPlayer->unmortgage(readIn);
}

// current player has declared bankrupcy, a set of actions are now allowed
void Board::bankrupt() {
    // so, first
}

int Board::getPlayerWorth() {
    return curPlayer->netWorth();
}

void Board::display_assets() {
    curPlayer->displayAssets();
}

void Board::display_all() {
    for (auto i: players) {
        cout << "=> ---------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "=> " << i->getName() << " assets:" << endl;
        i->displayAssets();
    }
}

void Board::save(ofstream & out){
    out << players.size() << endl;
    for(auto i: players){
        i->saveData(out);
    }
    
    for(int i = 0; i < 40; i++){
        theBoard[i]->saveData(out);
    }
}

void Board::attach(Observer *ob){
    observers.emplace_back(ob); // ob attatched to vector of observers
}

void Board::notifyobservers() {
    for (auto i: observers) {
        i->notify(this);
    }
}

// overloaded constructor
Board::Board(map<string, pair<string, int>> & buildingInfo, Die *die, vector<Player *> players, vector<string> squareNames, vector<string> buildingTypes, Player *Bank): die{die}, players{players}
{
    for (int i = 0; i < 40; i++) {
        if (buildingTypes[i] == "Ownable") {
            OwnableFactory of;
            
            // builds the building and finds the owner-
            Ownable *member = of.createOwnable(squareNames[i], i);
            theBoard.emplace_back(member);
            member->setOwner(Bank);
            for(auto p: players){
                if(p->getName() == buildingInfo[squareNames[i]].first){
                    member->setOwner(p);
                    p->addProperty(member);  
                }
            }
            // set improvements somewhere here
            
            // for now, before read in file is fully implemented, we will do this with a sample vector of 10 objects
        } else {
            // same thing as above, we use a small scalaed down verison of the vector for now
            theBoard.emplace_back(NonPropertiesFactory::createNonProperties(squareNames[i], i));

        }
    }
    
    // by this point, the vector<Building *> theBoard, vector has been initialized
    // now, we take the time to add the board's pointer to each player
    for (int i = 0; i < players.size(); i++) {
        players[i]->setBoard(this);
    }
    
    ifstream improvementsFile;
    improvementsFile.open("Improvements.txt");
    // now, we make a ImprovableData table and pass its pointer to baord
    for (int i = 0; i < 22; i++) {
        // now, we read in from the file and store a line into an entry object
        ImprovementData *entry = new ImprovementData;
        string name;
        improvementsFile >> name;
        entry->name = name;
        string monopolyblock;
        improvementsFile >> monopolyblock;
        entry->monpoly = monopolyblock;
        int pcost;
        improvementsFile >> pcost;
        entry->purchaseCost = pcost;
        int icost;
        improvementsFile >> icost;
        entry->improvementCost = icost;
        
        // now, we loop and read in tuition changes
        vector<int> tuitionChanges;
        for (int i = 0; i < 6; i++) {
            int num;
            improvementsFile >> num;
            tuitionChanges.emplace_back(num);
        }

        table.emplace_back(entry);
        
    }
    // now, the table of improvement data is initialized
    improvementsFile.close();
}

Board::~Board() {
    // calling Board's destructor will now delete the buildings
    for (auto i: theBoard) {
        delete i; // calls each buildings constructor
    }
    for (auto i: table) {
        delete i;
    }
}
