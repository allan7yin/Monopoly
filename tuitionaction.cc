#include "tuitionaction.h"
#include "Player.h"
#include <iostream>

class Player;


void TuitionAction::actionOnSquare(Player * p){
    // rule for tuition
    std::string input;
    const int FLAT_FEE = 300;
    while(true){
        std::cout << "Do you want to pay a $" + std::to_string(FLAT_FEE) + " flat fee (1) or 10% of your total worth(2) " << std::endl;
        std::cin >> input;
        if(input == "1"){
            p->subCash(FLAT_FEE);
            return;
        }
        else if(input == "2"){
            p->subCash(0.1 * p->netWorth()); // need to change to totalNetWorth
            return;
        }
    }
}

