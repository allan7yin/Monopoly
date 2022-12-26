//
//  TextDisplay.cpp
//  Assignment5
//
//  Created by Allan Yin on 2022-07-24.
//

#include "TextDisplay.h"
#include <iostream>
#include <fstream>
#include "Board.h"

using namespace std;

TextDisplay::TextDisplay(Subject *board): Observer(board) {}

void printNewLine() { // basically, 6 lines is a new "row" of sqaures
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
}

void TextDisplay::notify(Board *whoNotified) { // each square is 10 accross and 6 down

    // (1)
    // ################################################################################################################################################################################
    
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|Goose    |         |NEEDLES  |         |         |V1       |         |         |CIF      |         |GO TO    |" << endl;
    cout << "|Nesting  |_________|HALL     |_________|_________|         |_________|_________|         |_________|TIMS     |" << endl;
    cout << "|         |EV1      |         |EV2      |EV3      |         |PHYS     |B1       |         |B2       |         |" << endl;
    // this row now prints the the players, represented by their symbols
    
    int counter;
    for (int j = 20; j <= 30; j++) { // first row in the board
        counter = 0;
        cout << "|";
        for (int i = 0; i < whoNotified->players.size(); i++) {
            if ((whoNotified->players[i]->getBoardPosition() >=20) && (whoNotified->players[i]->getBoardPosition() <=30)) {
                // means player is on this square => now print their symbol
                cout << whoNotified->players[i]->getSymbol();
                counter++;
            }
        }
            
        // now, print out remaining spaces:
        for (int i = 0; i < 9-counter; i++) {
            cout << " ";
        }
    }
    
    cout << "|" << endl;
        
    

    for (int j = 20; j <= 30; j++) {
        counter = 0;
        cout << "|";
   
        // now we print out the number of improvements per square
        for (int i = 0; i < whoNotified->theBoard[j]->getNumImprovements(); i++){
            cout << "X";
            counter++;
        }
        
        // again, fill in remaining space
        for (int i = 0; i < 9-counter; i++) {
            cout << " ";
        }
    }
    
    cout << "|" << endl;

    // (2)
    // ################################################################################################################################################################################
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    counter = 0;
    // Now, there are 9 rows, where there are only two squares separated by a lot of space
    // index 19, 31
    
    // first, 19
    cout << "|         |                                                                                         |         |" << endl;
    cout << "|_________|                                                                                         |_________|" << endl;
    cout << "|OPT      |                                                                                         |EIT      |" << endl;
    
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 19) {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|";
    cout << "                                                                                         ";

    
    counter = 0;
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 31) {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    cout << "|" << endl;
   
    // now, printing the number of improvements
    cout << "|";
    
    counter = whoNotified->theBoard[19]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << "                                                                                         " << "|";

    counter = whoNotified->theBoard[31]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << endl;
    
    cout << "-----------                                                                                         -----------" << endl;
    
    // (3)
    // ################################################################################################################################################################################
    counter = 0;
    // Now, there are 9 rows, where there are only two squares separated by a lot of space
    // index 19, 31
    
    // first, 19
    cout << "|         |                                                                                         |         |" << endl;
    cout << "|_________|                                                                                         |_________|" << endl;
    cout << "|BMH      |                                                                                         |ESC      |" << endl;
    
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 18) {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|";
    cout << "                                                                                         ";

    
    counter = 0;
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 32) {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    cout << "|" << endl;
   
    // now, printing the number of improvements
    cout << "|";
    
    counter = whoNotified->theBoard[18]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << "                                                                                         " << "|";

    counter = whoNotified->theBoard[32]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << endl;
    
    cout << "-----------                                                                                         -----------" << endl;
    // (4)
    // ################################################################################################################################################################################
    counter = 0;
    // Now, there are 9 rows, where there are only two squares separated by a lot of space
    // index 19, 31
    
    // first, 19
    cout << "|SLC      |                                                                                         |SLC      |" << endl;
    cout << "|         |                                                                                         |         |" << endl;
    cout << "|         |                                                                                         |         |" << endl;
    
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 17) {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|";
    cout << "                                                                                         ";

    
    counter = 0;
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 33) {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    cout << "|" << endl;
    
    cout << "|         |                                                                                         |         |" << endl;
    
    cout << "-----------                                                                                         -----------" << endl;

    // (5)
    // ################################################################################################################################################################################
    counter = 0;
    // Now, there are 9 rows, where there are only two squares separated by a lot of space
    // index 19, 31
    
    // first, 19
    cout << "|         |                                                                                         |         |" << endl;
    cout << "|_________|                                                                                         |_________|" << endl;
    cout << "|LHI      |                                                                                         |C2       |" << endl;
    
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 16)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|";
    cout << "                                                                                         ";

    
    counter = 0;
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 34)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    cout << "|" << endl;
    
    // now, printing the number of improvements
    cout << "|";
    
    counter = whoNotified->theBoard[16]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << "                                                                                         " << "|";

    counter = whoNotified->theBoard[34]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << endl;
    
    cout << "-----------                                                                                         -----------" << endl;
    
    // (6)
    // ################################################################################################################################################################################
    counter = 0;
    // Now, there are 9 rows, where there are only two squares separated by a lot of space
    // index 19, 31
    
    // first, 19
    cout << "|UWP      |                                                                                         |REV      |" << endl;
    cout << "|         |                                                                                         |         |" << endl;
    cout << "|         |                                                                                         |         |" << endl;
    
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 15)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|";
    cout << "                                                                                         ";

    
    counter = 0;
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 35)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    cout << "|" << endl;
    cout << "|         |                                                                                         |         |" << endl;
    
    cout << "-----------                                                                                         -----------" << endl;


    // (7)
    // ################################################################################################################################################################################
    counter = 0;
    // Now, there are 9 rows, where there are only two squares separated by a lot of space
    // index 19, 31
    
    // first, 19
    cout << "|         |                                                                                         |NEEDLES  |" << endl;
    cout << "|_________|                                                                                         |HALL     |" << endl;
    cout << "|CPH      |                                                                                         |         |" << endl;
    
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 14)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|";
    cout << "                                                                                         ";

    
    counter = 0;
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 36)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    cout << "|" << endl;
    
    // now, printing the number of improvements
    cout << "|";
    
    counter = whoNotified->theBoard[14]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << "                                                                                         " << "|         |" << endl;
    
    cout << "-----------                                                                                         -----------" << endl;
    
    // (8)
    // ################################################################################################################################################################################
    counter = 0;
    // Now, there are 9 rows, where there are only two squares separated by a lot of space
    // index 19, 31
    
    // first, 19
    cout << "|         |                                                                                         |         |" << endl;
    cout << "|_________|                                                                                         |_________|" << endl;
    cout << "|DWE      |                                                                                         |MC       |" << endl;
    
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 13)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|";
    cout << "                                                                                         ";

    
    counter = 0;
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 37)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    cout << "|" << endl;
    
    // now, printing the number of improvements
    cout << "|";
    
    counter = whoNotified->theBoard[13]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << "                                                                                         " << "|";

    counter = whoNotified->theBoard[37]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << endl;
    
    
    cout << "-----------                                                                                         -----------" << endl;
    
    // (9)
    // ################################################################################################################################################################################
    counter = 0;
    // Now, there are 9 rows, where there are only two squares separated by a lot of space
    // index 19, 31
    
    // first, 19
    cout << "|PAC      |                                                                                         |COOP FEE |" << endl;
    cout << "|         |                                                                                         |         |" << endl;
    cout << "|         |                                                                                         |         |" << endl;
    
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 12)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|";
    cout << "                                                                                         ";

    
    counter = 0;
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 38)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    cout << "|" << endl;
    cout << "|         |                                                                                         |         |" << endl;
    
    cout << "-----------                                                                                         -----------" << endl;
    
    // (10)
    // ################################################################################################################################################################################
    counter = 0;
    // Now, there are 9 rows, where there are only two squares separated by a lot of space
    // index 19, 31
    
    // first, 19
    cout << "|         |                                                                                         |         |" << endl;
    cout << "|_________|                                                                                         |_________|" << endl;
    cout << "|RCH      |                                                                                         |DC       |" << endl;
    
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 11)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) { //
        cout << " ";
    }
    
    cout << "|";
    cout << "                                                                                         ";

    counter = 0;
    cout << "|";
    for (int i = 0; i < whoNotified->players.size(); i++) {
        if (whoNotified->players[i]->getBoardPosition() == 39)  {
            cout << whoNotified->players[i]->getSymbol();
            counter++;
        }
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    cout << "|" << endl;
    
    // now, printing the number of improvements
    cout << "|";
    
    counter = whoNotified->theBoard[11]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << "                                                                                         " << "|";

    counter = whoNotified->theBoard[39]->getNumImprovements();
    for (int i = 0; i < counter; i++) {
        cout << "X";
    }
    
    for (int i = 0; i < 9-counter; i++) {
        cout << " ";
    }
    
    cout << "|" << endl;
    
    // (11)
    
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|DC Tims  |         |         |NEEDLES  |         |MKV      |TUITION  |         |SLC      |         |COLLECT  |" << endl;
    cout << "|Line     |_________|_________|HALL     |_________|         |         |_________|         |_________|OSAP     |" << endl;
    cout << "|         |HH       |PAS      |         |ECH      |         |         |ML       |         |AL       |         |" << endl;
    // this row now prints the the players, represented by their symbols
    
    
    for (int j = 10; j >= 0; j--) { // first row in the board
        int counter = 0;
        cout << "|";
        for (int i = 0; i < whoNotified->players.size(); i++) {
            if (whoNotified->players[i]->getBoardPosition() == j) {
                // means player is on this square => now print their symbol
                cout << whoNotified->players[i]->getSymbol();
                counter++;
            }
        }
            
        // now, print out remaining spaces:
        for (int i = 0; i < 9-counter; i++) {
            cout << " ";
        }
    }
    
    cout << "|" << endl;
        
    for (int j = 10; j >= 0; j--) {
        int counter = 0;// first row in the board
        cout << "|";

        for (int i = 0; i < whoNotified->theBoard[j]->getNumImprovements(); i++){
            cout << "X";
            counter++;
        }
            
        // again, fill in remaining space
        for (int i = 0; i < 9-counter; i++) {
            cout << " ";
        }
    }
    
    cout << "|" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;

}


    
   

