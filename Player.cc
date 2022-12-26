#include "Player.h"
#include "Board.h"
#include "ownable.h"
#include "Cash.h"
#include "die.h"
#include "rollupthetims.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

Player::Player(string name, char symbol, int position, int totalMoney, vector<Ownable *> myProperties, Board *board, Player *Bank, Die *die): name{name}, symbol{symbol}, position{position}, totalMoney{totalMoney}, board{board}, Bank{Bank}, myProperties(0), die{die} {
    
    // now, passed in totalMoney, which is the starter amount
}

void Player::setBoard(Board *b) {
    board = b;
}

int Player::roll() {
    return die->roll();
}

string Player::getName() {
    return name;
}

char Player::getSymbol() {
    return symbol;
}
void Player::setInLine(bool inLine){
    this->inLine = inLine;
}

bool Player::getInLine(){
    return inLine;
}
void Player::setTurnsInLine(int n){
    turnsInLine = n; 
}

int Player::getTurnsInLine(){
    return turnsInLine;
}

Building *Player::getPosition() {
    return board->theBoard[position];
}

int Player::getBoardPosition() {
    return position;
}

void Player::move(string increment) {
    // so, this move player function must handle two situations: string of an integer, string of a location
    int num;
    stringstream ss;
    ss << increment;
    ss >> num;
    
    if (ss.fail()) { // means increment is a string location
        // so, we move the player's location there
        // we first need the integer position of the passed in name
        
        // however, if we are at SLC at moving to tims, collect osap money, the only such move where OSAP is not collected
        // is handled in the SLC action class
        if (board->theBoard[position]->getName() == "SLC" && increment == "GO TO TIMS") {
            totalMoney+=200;
        }
        
        for (int i = 0; i < board->theBoard.size(); i++) {
            if (board->theBoard[i] != nullptr) {
                if (board->theBoard[i]->getName() == increment) {
                    // set position to i
                    position = i;
                }
            }
        }
    } else {
        // this means the increment amount is an integer, now we see if its a negative amount or positive amount
        if (num < 0) {
            // negative, movingbackwards
            num*=(-1);
            for (int i = 0; i < num; i++) {
                move(false); // false means moving player backwards
            }
        } else {
            for (int i = 0; i < num; i++) {
                move(true);
            }
        }
        
        getPosition()->actionOnSquare(this);
    }
}

void Player::move(bool forward) {
    if (forward) {
        int increment = 1;
        if ((position + increment) > 39) {
            position+=increment;
            position-=40;
        } else {
            position+=increment;
        }
    } else {
        int decrement = 1;
        if ((position - decrement) < 0) {
            position+=40;
        }
        position-=decrement;
    }
}


// cash + unmortaged morttage prices
int Player::netWorth() {
    
    int netWorth = 0;
    
    for (auto i: myProperties) {
        if (i != nullptr) {
            if (!(i->checkMortgage)()) {
                netWorth+=((i->getRentPrice())/2);
            }
        }
    }
    
    netWorth+=totalMoney;
    return  netWorth;
}

Ownable *Player::is_owned(string name) {
    // checks if passed in name is valid
    for (auto i: myProperties) {
        if (i != nullptr) {
            if (i->getOwner()->name == name) {
                return i;
            }
        }
    }
    return nullptr;
}

bool Player::isOwned(string name) {
    for (auto i: myProperties) {
        if (i != nullptr && i->getName() == name) {
            return true;
        }
    }
    return false;
}

Player *Player::valid_player(string name) {
    // check if name is a valid player's name
    for (auto i: board->players) {
        if (name == i->name) return i;
    }
    return nullptr;
}

void Player::saveData(ofstream &out) {
    out << name << " " << symbol << " " << RollUpTheTims::numOfCups(this) << " " << totalMoney << " " << position << endl;
}

void Player::bankrupt(Player *p) {
    // move all money over to p
    p->addCash(totalMoney);
    subCash(totalMoney);
    
    // sets all of the properties to p
    for (auto i: myProperties) {
        if (i != nullptr) {
            i->setOwner(p);
            p->myProperties.emplace_back(i);
        }
    } // all of this's properties now belong to p
    
    for (int i = 0; i < board->players.size(); i++) {
        if (board->players[i]->name == p->name) {
            board->players.erase(board->players.begin() + i);
        }
    }
}

bool Player::getMoreCash() {
    while (true) {
        cout << "Which of the following actions would you like to commence: " << endl;
        cout << "Please enter:" << endl;
        cout << "M to Mortage a property" << endl;
        cout << "R to Request a trade" << endl;
        cout << "S to Sell Improvements" << endl;
        cout << "D to Dropout" << endl;
        cout << "Q to Quit" << endl;
        cout << "Your response: ";
        
        string response;
        cin >> response;
        
        if (response == "M") {
            cout << "Properties you own:" << endl;
            // print out names of all properties player owns
            for (int i = 1; i <= myProperties.size(); i++) {
                if (myProperties[i] != nullptr) {
                    cout << "Option " << i << ": " << myProperties[i]->getName() << endl;
                }
            }
            
            
            while (true) {
                cout << "Please enter name of property you wish to mortgage" << endl;
                string input_name;
                cin >> input_name;
                
                // breakpoint: determine if entered name is a valid property name
                if (is_owned(input_name)) {
                    // get the pointer to the property we want to mortgage
                    for (auto i: myProperties) {
                        if (i != nullptr) {
                            if (i->getName() == name) {
                                mortgage(i);
                                break;
                            }
                        }
                    }
                }
                cout << "INVALID NAME, PLEASE TRY AGAIN: " << endl;
                // loop will continue if they inputed name is invalid
            }
            return false;
        } else if (response == "R") {
            request_trade();
            return false;
        } else if (response == "D") {
            return true;
        } else if (response == "Q") {
            return false;;
        } else {
            cout << "Invalid entry, please try again" << endl;
        }
    }
}

void Player::request_trade() {
    
    Player *other;
    // now, read in user input as to which player to trade with
    
    string trade_partner;
    cin >> trade_partner;
    
    // now, we initialize the Player's pointer other
    for (auto i: board->players) {
        if (i != nullptr) {
            if (i->getName() == trade_partner) {
                other = i;
            }
        }
    }
    
    // now, we have the player we want to trade with
    
    bool trade_in_cash = false;
    bool trade_out_cash = false;
    bool trade_out_ownable = false;
    int cash;
    
    
    string trade_in;
    string trade_out;
    int want_cash;
    
    cin >> trade_out;
    
    stringstream s;
    s << trade_out;
    s >> cash;
    
    if (s.fail()) {
        trade_out_ownable = true;
    } else if (!s.fail() && cash <= totalMoney) { // so trade_out is an integer amount of cash, and affordable
        trade_out_cash = true;
    } else {
        cout << "INVALID ENTRY, PLEASE TRY AGAIN" << endl;
    }
    
    cin >> trade_in; // building name or cash
    
    stringstream ss;
    ss << trade_in;
    ss >> want_cash;
    if (ss.fail()) {
        trade_in_cash = false;
    } else {
        trade_in_cash = true;
    }
    ss.clear();
    
    // now, we should have proper trade_in and trade_out details
    // we now propose the trade to the trade partner
    
    cout << "To player " << trade_partner << ", " << name << "is proposing to trade with the following details:" << endl;
    
    cout << "You receive: " << trade_out << endl;
    cout << name << " receives: " << trade_in << endl;
    
    cout << endl;
    cout << "Player " << trade_partner << ", do you consent to the terms of this trade?" << endl;
    
    cout << "(Y/N)" << endl;
    string agree;
    
    cin >> agree;
    if (agree == "Y") {
        // check if trading money for money
        if (trade_out_cash && trade_in_cash) {
            cout << "CANNOT TRADE MONEY FOR MONEY, TRADE TERMINATED" << endl;
            return;
        } else if (trade_in_cash) {
            // check if trade partner can afford it
            for (auto i: board->players) {
                if ((i->name == trade_partner) && (i->getCash() < other->totalMoney)) {
                    cout << "Player " << trade_partner << " cannot afford payment, TRADE TERMINATED" << endl;
                    return;
                }
            }
        }
        
        // reaching here, we can just trade
        trade(trade_in, trade_out, other);
    } else if (agree == "N"){
        cout << "TRADE HAS BEEN REJECTED." << endl;
        return;
    }
}


void Player::trade(string ob1, string ob2, Player *p) {
    // when request_trade calls trade, we already know
    
    // ob1 is what trade partner owns, ob2 is what I own
    
    // first, need to know if ob1 and ob2, which, if any, are integers amount of cash
    int num1;
    int num2;
    bool in_int = true;
    bool out_int = true;
    
    stringstream ss;
    ss << ob1;
    ss >> num1;
    if (ss.fail()) {
        in_int = false;
    }
    ss.clear();
    
    stringstream s;
    s << ob2;
    s >> num2;
    if (s.fail()) {
        out_int = false;
    }
    
    // now, we should know types of our trade objects, commence trade now
    
    // I am trading ownable for cash
    Ownable *case1_1;
    Cash *case1_2;
    
    // I am trading cash for an ownable object
    Cash *case2_1;
    Ownable *case2_2;
    
    // I am trading an ownable for an ownable
    Ownable *case3_1;
    Ownable *case3_2;
    
    if (in_int) {
        // cash(owner, isOwnbed, value)
        case1_2 = new Cash{p, true, num1}; // What I currently own, before trading away
        for (int i = 0; i < myProperties.size(); i++) {
            if (myProperties[i] != nullptr) {
                if (myProperties[i]->getName() == ob2) {
                    case1_1 = myProperties[i];
                    myProperties.erase(myProperties.begin()+i);
                    p->myProperties.emplace_back(case1_1);
                }
            }
        }
        // now, we trade
        case1_1->trade(case1_2);
        totalMoney+=(case1_2->getValue());
        p->totalMoney-=(case1_2->getValue());
        
        
        delete case1_2;
    } else if (out_int) {
        // tradin out integer, receiving building from p
        case2_1 = new Cash{this, true, num2};
        for (int i = 0; i < p->myProperties.size(); i++) {
            if (p->myProperties[i] != nullptr) {
                if (p->myProperties[i]->getName() == ob1) {
                    case2_2 = p->myProperties[i];
                    p->myProperties.erase(p->myProperties.begin()+i);
                    myProperties.emplace_back(case2_2);
                }
            }
        }
        
        case2_2->trade(case2_1);
        totalMoney-=(case2_1->getValue());
        p->totalMoney+=(case2_1->getValue());
        delete case2_1;
    } else {
        
        for (int i = 0; i < myProperties.size(); i++) {
            if (myProperties[i] != nullptr) {
                if (myProperties[i]->getName() == ob2) {
                    case3_1 = myProperties[i];
                    myProperties.erase(myProperties.begin()+i);
                    p->myProperties.emplace_back(case3_1);
                }
            }
        }
        
        for (int i = 0; i < p->myProperties.size(); i++) {
            if (p->myProperties[i] != nullptr) {
                if (p->myProperties[i]->getName() == ob1) {
                    case3_2 = p->myProperties[i];
                    p->myProperties.erase(p->myProperties.begin()+i);
                    myProperties.emplace_back(case3_2);
                }
            }
        }
        // reaching here, two buildings
        
        case3_1->trade(case3_2);
    }
}

void Player::addProperty(Ownable *o) {
    myProperties.emplace_back(o);
}


void Player::auction(Ownable *myOwn) {
    int aucPrice = myOwn->getValue(); // keeps track of the current bid
    Player *highbid = nullptr; // points to the current highest bidder
    cout << "The auction for " << myOwn->getName() << " will begin at $" << aucPrice << "." << endl;
    int playercount = board->players.size();
    vector<bool> stillBidding; // vector to keep track if player is still bidding
    for (int i = 0; i < playercount; i++) {
        stillBidding.push_back(true);
    }
    int index = 0;
    Player *curbid = board->players[index]; // points to the current bidder
    while (curbid != highbid) { // if current bidder is same as highest bidder then they win and loop breaks
        bool stopBidding = true;
        for (int i = 0; i < playercount; i++) { // checks if there are still bidders left
            if (stillBidding[i]) {stopBidding = false;}
        }
        if (stopBidding) {break;} // if there are no more bidders then break the loop
        if (!stillBidding[index]) {continue;} // if the player is not bidding then move on to next
        curbid = board->players[index]; // points to the current bidder
        cout << "Does " << curbid->getName() << "'s want to make a bid of at least $" << aucPrice << " (Y/N)" << endl;
        char response;
        cin >> response;
        if (response == 'Y' || response == 'y') {
            if (curbid->getCash() < aucPrice) { // check if the player even has enough cash to make a valid bid
                cout << "The player does not have enough cash to make a bid, withdrawing from auction." << endl;
                stillBidding[index] = false;
            } else {
                int bidamount;
                cout << "Enter the amount of cash to bid: " << endl;
                cin >> bidamount; // [CONSIDER WHEN BIDAMOUNT IS NOT AN INTEGER]
                while (bidamount < aucPrice) { // check if the bid made is greater than the highest bid
                    cout << "That is not a valid bid amount, enter a new amount: " << endl;
                    cin >> bidamount;
                }
                if (bidamount <= curbid->getCash()) { // check if the player has enough cash to make the bid
                    cout << "The player has bid $" << bidamount << "." << endl;
                    highbid = curbid; // set highest bidder to current bidder
                    aucPrice = bidamount; // set auction price to current bid
                } else { // if the player does not have enough cash to make the bid then they withdraw from the auction
                    cout << "The player does not have enough cash to make this bid, withdrawing from auction." << endl;
                    stillBidding[index] = false;
                }
            }
            index += 1; // moves on to the next player
            if (index == playercount) {index = 0;} // it is the first player's turn after one cycle
        } else if (response == 'N' || response == 'n') {
            cout << "The player is withdrawing from the auction." << endl;
            stillBidding[index] = false;
            index += 1;
            if (index == playercount) {index = 0;}
        } else {
            cout << "Please enter a valid answer." << endl;
        }
    }
    if (highbid) { // if there someone made a bid then they pay for the property, otherwise nothing happens
        cout << highbid->getName() << " has won the bid for " << myOwn->getName() << " for $" << aucPrice << "." << endl;
        highbid->subCash(aucPrice); // subtracts auction price from winner's cash
        highbid->addProperty(myOwn); // adds property to list of properties that winner owns
        myOwn->setOwner(highbid); // sets the owner of the property to the winner
    }
}

void Player::mortgage(Ownable *ownable_name) {
    bool cond = false;
    if (!ownable_name->checkMortgage()) {
        // check if not owned by cur player
        for (auto i: myProperties) {
            if (i == ownable_name) {
                // exists
                cond = true;
            }
        }
        if (!cond) {
            cout << "Invalid move, cannot mortgage property you do not own." << endl;
            return;
        }

        ownable_name->toggleMortgage();
        addCash(ownable_name->getValue()/2);
    }
}

void Player::unmortgage(Ownable *other) {
    if (other->checkMortgage()) {
        if (totalMoney >= (other->getValue() * 0.6)) {
            subCash(other->getValue() * 0.6);
            other->toggleMortgage();
        }
    }
}


void Player::mortgage(string other) {
    // first, we need to decide if other is owend by the player
    for (auto i: myProperties) {
        if (i != nullptr) {
            if (!(i->checkMortgage())) {
                if (i->getName() == other) { // confirms name passed is a name of a building player owns
                    mortgage(i);
                } else {
                    cout << "Invalid action entered. Please try again." << endl;
                }
            } else {
                cout << "=> Invalid action entered. Please try again." << endl;
            }
        }
    }
}

void Player::unmortgage(string other) {
    // first, we need to decide if other is owend by the player
    for (auto i: myProperties) {
        if (i != nullptr) {
            if (i->checkMortgage()) {
                if (i->getOwner()->name == name) { // confirms name passed is a name of a building player owns
                    unmortgage(i);
                }
            } else {
                cout << "=> Invalid action entered. Please try again." << endl;
            }
        }
    }
}


void Player::displayAssets() {
    // here, we print out all of the Player's assets
    // first, we print out the flat amount of money the player has
    cout << endl;
    cout << "Total Money Owned: " << totalMoney << endl;
    
    // now, we print out each name of propety thats owned + number of improvements
    for (auto i: myProperties) {
        if (i != nullptr && (!(i->checkMortgage()))) {
            cout << "Building: " << i->getName() << ", Number of improvements: " << i->getNumImprovements() << endl;
        }
    }
    cout << "=> ---------------------------------------------------------------------------------------------------------------------------" << endl;
}


































