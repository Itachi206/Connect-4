#include <iostream>
#include <conio.h> 
#include <windows.h>
using namespace std;

#define brow 6
#define bcol 7

char board[brow][bcol] = { '0','0','0','0','0','0','0',
                           '0','0','0','0','0','0','0',
                           '0','0','0','0','0','0','0',
                           '0','0','0','0','0','0','0',
                           '0','0','0','0','0','0','0',
                           '0','0','0','0','0','0','0' };

void GameStart() {
    system("Color 02");
    cout << "-----------------------------------------------" << endl;
    cout << "|                                             |" << endl;
    cout << "|          WELCOME TO CONNECT - 4             |" << endl;
    cout << "|                                             |" << endl;
    cout << "-----------------------------------------------" << endl;
}
void BasicRule() {
    cout << endl << "RULES:" << endl;

    cout << endl << "1. Two-player (red (R) & blue(B)) game." << endl;
    cout << "2. Board size is 6 rows & 7 columns." << endl;
    cout << "3. A player wins if he/she is able to connect 4 dots horizontally, vertically or diagonally." << endl;
    cout << "4.Game Draw when the matrix is fully filled." << endl;

    cout << endl << "How to Play:" << endl;
    cout << "1. Game always start with player - 1 i.e. Red(R) \n2. In each step choose the column number in which you want to drop the ball." << endl;
    cout << "3. Rows will be filled from bottom to top in any column." << endl;

    cout << endl << "Enter Y/y to continue or N/n to close the game" << endl;
}

bool isBoardFull() {
    for (int i = 0; i < brow; i++) {
        for (int j = 0; j < bcol; j++) {
            if (board[i][j] == '0')
                return false;
        }
    }
    return true;
}

void PrintBoard() {
    cout << endl << "------------ Board ------------" << endl;
    for (int i = 0; i < brow; i++) {
        cout << " | ";
        for (int j = 0; j < bcol; j++) {
            if (board[i][j] == '0') {
                system("Color 07");
                cout << "  | ";
            }
            else if (board[i][j] != '0') {
                if (board[i][j] == 'R') {
                    textcolor(RED);
                    cout << board[i][j];
                }
                else if (board[i][j] == 'B'){
                    //system("Color 01");
                    cout << board[i][j];
                }
                system("Color 7");
                cout << " | ";
            }
        }
        cout << " " << endl;
    }
    cout << "-------------------------------" << endl;

}

int CheckRow(int col) {
    int i;
    for (i = brow - 1; i >= 0; i--) {
        if (board[i][col] == '0' &&
            board[i][col] != 'R' &&
            board[i][col] != 'B') {
            return i;
        }
    }
    return i;
}

bool winCheck(char p) {
    for (int i = 0; i < brow; i++) {
        for (int j = 0; j < bcol; j++) {
            if (board[i][j] == p &&
                board[i + 1][j + 1] == p &&
                board[i + 2][j + 2] == p &&
                board[i + 3][j + 3] == p) {               //Diagonal left down 
                return true;
            }
            if (board[i][j] == p &&
                board[i][j + 1] == p &&
                board[i][j + 2] == p &&
                board[i][j + 3] == p) {                 //Horizontal Check
                return true;
            }
            if (board[i][j] == p &&
                board[i - 1][j + 1] == p &&
                board[i - 2][j + 2] == p &&
                board[i - 3][j + 3] == p) {               //Diagonal Right Up 
                return true;
            }
            if (board[i][j] == p &&
                board[i - 1][j] == p &&
                board[i - 2][j] == p &&
                board[i - 3][j] == p) {                 //Vertical Check
                return true;
            }
        }
    }
    return false;
}

bool isColumnFull(int col) {
    for (int i = brow - 1; i >= 0; i--) {
        if (board[i][col - 1] == '0') {
            return false;
        }
    }
    return true;
}

void placeColor(char c, int col) {
    col--;
    int row = CheckRow(col);
    if (c == 'R') {
        board[row][col] = 'R';
    }
    else if (c == 'B') {
        board[row][col] = 'B';
    }
}

int main() {

    GameStart();
    BasicRule();
    char choice;
    cin >> choice;

    while (choice == 'y' || choice == 'Y') {
        bool boardFull = isBoardFull();
        // bool gameEnded = false;
        int playerChoice;
        BasicRule();
        PrintBoard();

        do {
            //Player 1 turn
            do {
                cout << endl << "Player 1 Turn (Red) " << endl;
                cout << "Choose from 1-7 " << endl;
                cout << "Select Coloumn : ";
                cin >> playerChoice;
                if (isColumnFull(playerChoice)) {
                    cout << "\nColumn is Full Choose Another Coloumn " << endl;
                    playerChoice = 10;
                }
            } while (playerChoice > bcol || playerChoice <= 0);

            placeColor('R', playerChoice);
            if (winCheck('R')) {
                cout << endl << endl;
                cout << "-------------------------------" << endl;
                cout << "|                             |" << endl;
                cout << "|      Player 1 Win (Red)     |" << endl;
                cout << "|                             |" << endl;
                cout << "-------------------------------" << endl;

                PrintBoard();
                break;
            }

            PrintBoard();

            do {
                cout << endl << "Player 2 Turn (Blue) " << endl;
                cout << "Choose from 1-7 " << endl;
                cout << "Select Coloumn : ";
                cin >> playerChoice;
                if (isColumnFull(playerChoice)) {
                    cout << "\nColumn is Full Choose Another Coloumn " << endl;
                    playerChoice = 10;
                }
            } while (playerChoice > bcol || playerChoice <= 0);

            placeColor('B', playerChoice);
            if (winCheck('B')) {
                cout << endl << endl;
                cout << "-------------------------------" << endl;
                cout << "|                             |" << endl;
                cout << "|      Player 2 Win (Blue)    |" << endl;
                cout << "|                             |" << endl;
                cout << "-------------------------------" << endl;

                PrintBoard();
                break;
            }
            PrintBoard();
            //to check board is Full or Not
            boardFull = isBoardFull();

        } while (boardFull == false);

        if (boardFull == true) {
            cout << "\nBoard is Full" << endl << "-------------Game Draw------------";
        }
        cout << endl << endl << "Enter Y/y to continue or N/n to close the game" << endl;
        cin >> choice;
    }//first while loop(continue or not)

}