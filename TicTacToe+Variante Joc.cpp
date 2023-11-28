/*
Bun, long story short fata de variantele anterioare, am adaugat o functie noua "chooseGameMode()" pentru a-i permite jucatorului sa aleaga modul de joc.

In "main()" am adaugat i sectiune pentru a alege modul de joc. Cand dai Run primesti un mesaj care care solicita alegerea unui mod de joc (1 sau 2),
motiv pentru care am adaugat variabila "choice" la linia 88/89

Pe langa functia "chooseGameMode()" si adaugatul variabilei "choice" in functia "main()", nu am facut alte modificari in logica codurilor original
*/



#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

char human = 'X'; // Jucatorul este reprezentat de caracterul 'X'
char computer = 'O'; // Calculatorul este reprezentat de caracterul 'O'
char player1 = 'X'; // Primul jucator este reprezentat de caracterul 'X'
char player2 = 'O'; // Al doilea jucator este reprezentat de caracterul 'O'

// Functia pentru afișarea tablei de joc
void printBoard(const vector<char> &board) {
    cout << "-------------" << endl;
    for (int i = 0; i < 9; i += 3) {
        cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |" << endl;
        cout << "-------------" << endl;
    }
}

// Functia pentru a verifica daca o mutare este valida
bool isMoveValid(const vector<char> &board, int move) {
    return (board[move] == ' '); // Verifica daca pozitia selectata este libera
}

// Functia pentru a verifica daca un jucator a castigat
bool checkForWin(const vector<char> &board, char player) {
    // Verifica toate combinarile posibile pentru o victorie
    return ((board[0] == player && board[1] == player && board[2] == player) ||
            (board[3] == player && board[4] == player && board[5] == player) ||
            (board[6] == player && board[7] == player && board[8] == player) ||
            (board[0] == player && board[3] == player && board[6] == player) ||
            (board[1] == player && board[4] == player && board[7] == player) ||
            (board[2] == player && board[5] == player && board[8] == player) ||
            (board[0] == player && board[4] == player && board[8] == player) ||
            (board[2] == player && board[4] == player && board[6] == player));
}

// Functia pentru a verifica daca tabla de joc este plina (egalitate)
bool isBoardFull(const vector<char> &board) {
     // Verifica daca fiecare celula a fost ocupata
    return all_of(board.begin(), board.end(), [](char cell) { return cell != ' '; });
}

// Funcția pentru a permite jucătorului faca o mutare
void humanMove(vector<char> &board, char currentPlayer) {
    int move;
    cout << "Jucatorul " << currentPlayer << ", introdu pozitia (0-8): ";
    cin >> move;

    while (move < 0 || move > 8 || !isMoveValid(board, move)) {
        cout << "Mutare invalida. Introdu din nou pozitia (0-8): ";
        cin >> move;
    }

    board[move] = currentPlayer; // Actualizeaza tabla cu mutarea jucatorului
}

// Functia pentru a genera o mutare aleatoare pentru calculator
void computerMove(vector<char> &board) {
    int move;
    do {
        move = rand() % 9; // Genereaza o mutare aleatoare pentru calculator
    } while (!isMoveValid(board, move));

    board[move] = computer; // Actualizeaza tabla cu mutarea calculatorului
    cout << "Calculatorul a ales pozitia " << move << endl;
}

// Functia principala care conține bucla de joc
int main() {
    cout << "Alege modul de joc:" << endl;
    cout << "1. Joaca impotriva altui jucator" << endl;
    cout << "2. Joaca impotriva calculatorului" << endl;
    int choice;
    cin >> choice;

    vector<char> board(9, ' '); // Initializeaza tabla de joc cu spații goale pentru fiecare celula
    srand(static_cast<unsigned int>(time(0)));// Initializare seed pentru generarea de numere aleatoare

    if (choice == 1) { // Joaca impotriva altui jucator
        char currentPlayer = player1;

        while (!isBoardFull(board)) {
            printBoard(board);// Afiseaza tabla de joc

            humanMove(board, currentPlayer);// Permite jucatorului sa faca o mutare

            if (checkForWin(board, currentPlayer)) { // Verifica daca jucătorul a castigat
                printBoard(board);
                cout << "Felicitari! Jucatorul " << currentPlayer << " a castigat!" << endl;
                return 0; // Termina jocul
            }

            if (currentPlayer == player1) {
                currentPlayer = player2;
            } else {
                currentPlayer = player1;
            }
        }

        printBoard(board);
        cout << "Remiza!" << endl;
    } else if (choice == 2) { // Joaca impotriva calculatorului
        char currentPlayer = human;

        while (!isBoardFull(board)) {
            printBoard(board);

            if (currentPlayer == human) {
                humanMove(board, currentPlayer);
            } else {
                computerMove(board);
            }

            if (checkForWin(board, currentPlayer)) {
                printBoard(board);
                if (currentPlayer == human) {
                    cout << "Felicitari! Ai castigat!" << endl;
                } else {
                    cout << "Calculatorul a castigat!" << endl;
                }
                return 0;
            }

            if (currentPlayer == human) {
                currentPlayer = computer;
            } else {
                currentPlayer = human;
            }
        }

        printBoard(board);
        cout << "Remiza!" << endl;
    }

    return 0;
}