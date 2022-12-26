//
//  Game.cpp
//  Assignment5
//
//  Created by Allan Yin on 2022-07-23.
//

#include "Game.h"
#include <iostream>
#include "Board.h"
#include <fstream>
#include <vector>
#include "Player.h"
#include "TextDisplay.h"
#include "ImprovementData.h"
#include "rollupthetims.h"
#include "die.h"
#include <string>
#include <utility>
#include <sstream>
#include <map>

Game::Game(bool testing): testing{testing} {}

void Game::play() {
    Die *die = new Die{6};

    ifstream file ("squares.txt"); // we read from a file, each line is the name of a square on the board, should be
                                   // should be 40 total lines, 40 properties

    // now, we read into file
    vector<string> squareNames;

    for (int i = 0; i < 40; i++) {
        string temp;
        getline(file,temp);
        squareNames.emplace_back(temp);
    }


    // now, this vector is loaded with the names we will assign the 40 buildigns in the game
    vector<Ownable *> bankProperties;

    // first create Bank player object

    Player *Bank = new Player{"Bank", 'b', 0, 0, bankProperties, nullptr, nullptr, nullptr};

    int numPlayers;

    // Begi User Interaction

    cout << "Y88b         /      e      ~~~888~~~   ,88~-_    888~-_     ,88~-_   888     Y88b    /" << endl;
    cout << " Y88b       /      d8b        888     d888   \\   888   \\   d888   \\  888      Y88b  /" << endl;
    cout << "  Y88b  e  /      /Y88b       888    88888    |  888    | 88888    | 888       Y88b/" << endl;
    cout << "   Y88bd8b/      /  Y88b      888    88888    |  888   /  88888    | 888        Y8Y" << endl;
    cout << "    Y88Y8Y      /____Y88b     888     Y888   /   888_-~    Y888   /  888         Y" << endl;
    cout << "     Y  Y      /      Y88b    888      `88_-~    888        `88_-~   888____    /" << endl;
    
    
    cout << endl;
    cout << "=> Welcome to Watopoly!" << endl;
    cout << "=> Enter the number of players (enter an integer between 2-8, inclusive): ";
    cin >> numPlayers;
    
    while (true) {
        if (numPlayers > 8 || numPlayers < 2) {
            cout << endl << "Inalid number of players, please enter a new amount: ";
            cin >> numPlayers;
        } else {
            break;
        }
    }
    
    cout << endl << "Game initialization now beginning. " << endl;
    
    vector<string> avatars{"Goose", "GRTBus", "TimHortonsDoughnut", "Professor", "Student", "Money", "Laptop", "Pinkie"};
    vector<char> avatarSymbols{'G', 'B', 'D', 'P','S', '$', 'L', 'T'};
    vector<Player *> players;
    
    for (int i = 0; i < numPlayers; i++) { // intialize each Player
        
        int location = 0;
        cout << endl;
        cout << "=> +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Player " << i+1 << ", select your character from the following game pieces: " << endl;
        cout << endl;
        
        for (int i = 0; i < avatars.size(); i++){
            cout << "=> " << avatars[i] << " (" << avatarSymbols[i] << ")" << endl;
        }
        
        cout << endl;
        
        char chooseSymbol;
        int count = 0;
        while (true) {
            cout << "Enter the symbol of which character you select: ";
            cin >> chooseSymbol;
            for (int i = 0; i < avatars.size(); i++) {
                if (chooseSymbol == avatarSymbols[i]) {
                    location = i;
                    count++;
                }
            }
            
            if (count == 0) {
                cout << "=> Invalid character, please try again" << endl;
            } else {
                break;
            }
        }
        cout << "=> Player " << i+1 << " confirmed, character: " << avatars[location] << " (" << avatarSymbols[location] << ")" << endl;
        
        vector<Ownable *> myProperties(0);
        Player *person = new Player{avatars[location], avatarSymbols[location], 0, 1500, myProperties, nullptr, Bank, die};
        players.emplace_back(person);
        
        // pop the chosen name and symbol out of the vector
        
        // need location of th
        avatars.erase(avatars.begin() + location);
        avatarSymbols.erase(avatarSymbols.begin() + location);
    }

    // now, we have:
    //  : vector of strings -> names of buildigns
    //  : vector of player pointers -> max 8

    ifstream types ("square_types.txt");
    vector<string> buildingTypes;
    // now, we need to read in, again from a new file, a list of "building types" -> where each line is either the word "ownable" or "nonownable"

    for (int i = 0; i < 40; i++) {
        string temp;
        types >> temp;
        buildingTypes.emplace_back(temp);
    }

    Board * game = new Board{players, die, squareNames, buildingTypes, Bank}; // here, we make the board vector
    TextDisplay *display = new TextDisplay{game};
    game->attach(display);
    runGame(game, players);
    
    // free memory for dice
    delete die;
    delete game;
    delete display;
    delete Bank;
    
    // free memory for the players occupy
    for (auto i: players) {
        delete i;
    }
    
}

void Game::load(ifstream & in){
    string line;
    // get the number of players
    getline(in, line);
    int numPlayers = stoi(line);
    
    Die *die = new Die{6};

    ifstream file ("squares.txt"); // we read from a file, each line is the name of a square on the board, should be
                                   // should be 40 total lines, 40 properties

    // now, we read into file
    vector<string> squareNames;

    for (int i = 0; i < 40; i++) {
        string temp;
        getline(file,temp);
        squareNames.emplace_back(temp);
    }


    // now, this vector is loaded with the names we will assign the 40 buildings in the game
    vector<Ownable *> bankProperties;
    
    // get the players and construct them
    // first create Bank player object

    vector<Player *> players;
    Player *Bank = new Player{"Bank", 'b', 0, 0, bankProperties, nullptr, nullptr, nullptr};
    for(int i = 0; i < numPlayers; i++){
        getline(in, line);
        string temp = "";
        vector<string> playerInput;
        
        // gets the player's data
        stringstream ss;
        ss << line;
        string word;
        
        for (int i = 0; i < 5; i++) {
            ss >> word;
            playerInput.emplace_back(word);
        }
        
        vector<Ownable *> myProperties(0); // need to update this later
        Player *person = new Player{
            playerInput[0],
            playerInput[1][0],
            stoi(playerInput[4]),
            stoi(playerInput[3]),
            myProperties,
            nullptr,
            Bank,
            nullptr
        };
        
        // add the player to the roll up the tims cup
        
        for(int i = 0; i < stoi(playerInput[2]); i++){
            RollUpTheTims::giveCup(person);
        }
        
        players.emplace_back(person);
    }
    
    // generate our board
    
    ifstream types ("square_types.txt");
    vector<string> buildingTypes;
    // now, we need to read in, again from a new file, a list of "building types" -> where each line is either the word "ownable" or "nonownable"

    for (int i = 0; i < 40; i++) {
        string temp;
        types >> temp;
        buildingTypes.emplace_back(temp);
    }
    
    // stores the name of the building, the owner and the number of improvements
    
    // probably will move this since it shouldn't be creating a map here
    map<string, pair<string, int>> buildingInfo;
    while(getline(in, line)){
        string temp = "";
        vector<string> buildingInput;
        
        // gets the building's data
        stringstream ss;
        ss << line;
        string word;
        
        for (int i = 0; i < 3; i++) {
            ss >> word;
            buildingInput.emplace_back(word);
        }
        
        buildingInput.emplace_back(temp);

        //cout << buildingInput[0] << buildingInput[1] << buildingInput[2] << endl;
        buildingInfo[buildingInput[0]] = pair<string, int>(buildingInput[1], stoi(buildingInput[2]));
    }
    
    
    // let the board handle the creation of the buildings and setting owners
    
    // update the buildings with the owner and the improvements 
    Board *game = new Board{buildingInfo, die, players, squareNames, buildingTypes, Bank};
    TextDisplay *display = new TextDisplay{game};
    game->attach(display);
    runGame(game, players);
    
    delete die;
    delete game;
    delete Bank;
    delete display;
    for (auto i: players) {
        delete i;
    }
}

void Game::runGame(Board * game, vector<Player *> players){
    cout <<"PREPARATIONS COMPLETE, THE GAME WILL NOW START!" << endl;

    int counter = 0;
    game->setCurPlayer(players[0]);
    
    cout << endl;
    cout << "=> +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "=> It is now " << players[counter]->getName() << "'s turn." << endl;
    cout << "=> ---------------------------------------------------------------------------------------------------------------------------" << endl;
    int numDoubles = 0;
    bool roll = true; // each player can only roll once per turn, so keep track of when a player can no longer roll
    bool mustLeaveLine = false;
    while (true) {

        if(players[counter]->getTurnsInLine() == 3){
            cout << "You must pay or use a tims cup to get out this turn" << endl; 
            cout << "=> Available Commands:" << endl;
            cout << "Pay $50 to get out and continue your turn (pay)" << endl;
            cout << "Use a roll up the tims cup to get out (tims)" << endl;
            mustLeaveLine = true;
        }
        else{
            // checks if the turns in line is greater than 0 so you  cant leave in the same turn
            if(players[counter]->getInLine()){
                cout << "You have been in DC Tims line for " << players[counter]->getTurnsInLine() << " turns" << endl;
                if(players[counter]->getTurnsInLine() > 0){
                    cout << "=> Available Commands:" << endl;
                    cout << "Pay $50 to get out and continue your turn (pay)" << endl;
                    cout << "Use a roll up the tims cup to get out (tims)" << endl;
                    cout << "Roll doubles and get out (roll)" << endl;
                }
            }
            else{
                cout << "=> Available Commands:" << endl;
                cout << "      => roll" << endl;
            }
            cout << "      => next" << endl;
            cout << "      => mortgage             PROPERTY" << endl;
            cout << "      => unmortgage           PROPERTY" << endl;
            cout << "      => improve              PROPERTY (buy / sell)" << endl;
            cout << "      => trade                PLAYER GIVE RECEIVE" << endl;
            cout << "      => assets" << endl;
            cout << "      => all" << endl;
            cout << "      => print" << endl;
            cout << "      => save" << endl;
            cout << "      => quit" << endl;
            //cout << " TEMPORARY: FOR TETSING MEMORY LEAKS, quit" << endl;
        }
        cout << endl;
        cout << "Player " << players[counter]->getName() << ", what would you like to do: ";
        
        string cmd;
        cin >> cmd;
        
        cout << endl;
        
        if (cmd == "roll" && !mustLeaveLine) {
            if (roll) {
                //testing rolls
                if(testing){
                    int first = 0;
                    int second = 0;
                    cin >> cmd;
                    first = stoi(cmd);
                    cin >> cmd;
                    second = stoi(cmd);
                    
                    if(first <= 0 || second <= 0){
                        cout << "Rolls must both be positive values" << endl;
                        continue;
                    }
                    
                    // in jail right now, this roll gets you out
                    if(players[counter]->getInLine()){
                        roll = (first == second);
                        // if doubles, get out of the line
                        if(roll){
                            cout << "You are no longer in line, continue as usual" << endl;
                            players[counter]->setInLine(false);
                        }
                        else{
                            cout << "You are still in line this turn and can't roll again" << endl;  
                        }
                        
                    }
                    
                    // you are not in jail right now
                    else{
                        pair<bool, int> result = game->roll(first, second, numDoubles);
                        roll = result.first;
                        numDoubles = result.second;
                    }

                }
                // just roll
                else{
                    if(players[counter]->getInLine()){
                        int first = players[counter]->roll();
                        int second = players[counter]->roll();
                        
                        // you can move forwards since you left jail
                        if(first == second){
                            pair<bool, int> result = game->roll(first, second, numDoubles);
                            roll = result.first;
                            numDoubles = 0;
                        }
                        else{
                            roll = false;
                        }
                    }
                    else{
                        pair<bool, int> result = game->roll(numDoubles);
                        roll = result.first;
                        numDoubles = result.second;
                    }
                }
                // game->roll will determine if they should be allowed to roll again
                // after the player rolls, they move and arrive at a square, the square's action is automatcially called
            } else {
                cout << "ALREADY ROLLED, CHOOSE ANOTHER ACTION" << endl;
                numDoubles = 0;
            }
            game->notifyobservers();
        } else if (cmd == "next" && !roll) {
            if(players[counter]->getInLine()){
                
                players[counter]->setTurnsInLine(players[counter]->getTurnsInLine() + 1);
            
            }
            
            counter = (counter + 1) % players.size();            
            game->setCurPlayer(players[counter]);
            roll = true;
            cout << endl;
            cout << "=> +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "=> It is now " << players[counter]->getName() << "'s turn." << endl;
            cout << "=> ---------------------------------------------------------------------------------------------------------------------------" << endl;
        } else if (cmd == "trade") {
            game->trade();
        } else if (cmd == "improve") {
            string buildName;
            cin >> buildName;
            
            string buyorsell;
            cin >> buyorsell;
            // check if curPlayer even owns the building
            if (buyorsell == "buy") {
                game->improve(buildName);
            } else if (buyorsell == "sell") {
                game->sell_improvement(buildName);
            }
        } else if (cmd == "mortgage") {
            game->mortgage();
        } else if (cmd == "unmortgage") {
            game->unmortgage();
        } else if (cmd == "assets") {
            game->display_assets();
        } else if (cmd == "all") {
            game->display_all();
        } else if (cmd == "save") {
            ofstream saveFile;
            saveFile.open("saveFile.txt");
            game->save(saveFile);
            saveFile.close();
        }
        else if(cmd == "pay" && players[counter]->getInLine()){
            // pay 50 and get out
            if(players[counter]->getCash() >= 50){
                players[counter]->subCash(50);
                cout << "You are no longer in line, continue as usual" << endl;
                players[counter]->setInLine(false);
                roll = true;
                players[counter]->setTurnsInLine(0);
                mustLeaveLine = false;
            }
            else{
                cout << "You don't have enough money" << endl;
            }
        }
        else if(cmd == "tims" && players[counter]->getInLine()){
            // use the tims cup and get out
            if(RollUpTheTims::numOfCups(players[counter]) > 0){
                RollUpTheTims::removeCup(players[counter]);
                players[counter]->setInLine(false);
                roll = true;
                players[counter]->setTurnsInLine(0);
                mustLeaveLine = false;
                cout << "You are no longer in line, continue as usual" << endl;
            }
            else{
                cout << "You don't have a roll up the tims cup" << endl;
            }
        } 
        else if (cmd == "quit") {
            return;
        } else {
            cout << "INVALID COMMAND, PLEASE TRY AGAIN." << endl;
        }
    }
    
}

