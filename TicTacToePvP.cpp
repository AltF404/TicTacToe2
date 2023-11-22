#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

char player1 = 'X'; // Primul jucator este reprezentat de caracterul 'X'
char player2 = 'O'; // Al doilea jucator este reprezentat de caracterul 'O'

// Functia pentru a afisa tabla de joc
void printBoard(const vector<char> &board) {
    cout << "-------------" << endl;
    for (int i = 0; i < 9; i += 3) {
        cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |" << endl;
        cout << "-------------" << endl;
    }
}

// Functia pentru a verifica daca o mutare este valida
bool isMoveValid(const vector<char> &board, int move) {
    return (board[move] == ' ');
}

// Functia pentru a verifica daca un jucator a castigat
bool checkForWin(const vector<char> &board, char player) {
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
    return all_of(board.begin(), board.end(), [](char cell) { return cell != ' '; });
}

// Functia pentru a permite jucatorului sa faca o mutare
void playerMove(vector<char> &board, char currentPlayer) {
    int move;
    cout << "Jucatorul " << currentPlayer << ", introdu pozitia (0-8): ";
    cin >> move;

    // Verifica daca mutarea este valida si solicita o alta mutare In caz contrar
    while (move < 0 || move > 8 || !isMoveValid(board, move)) {
        cout << "Mutare invalida. Introdu din nou pozitia (0-8): ";
        cin >> move;
    }

    board[move] = currentPlayer; // Actualizeaza tabla cu mutarea jucatorului
}

// Functia principala care gestioneaza logica jocului
int main() {
    vector<char> board(9, ' '); // Initializeaza tabla de joc cu spatii goale pentru fiecare celula
    char currentPlayer = player1; // Incepe jocul cu primul jucator

    // Loop-ul jocului, se executa pana cand tabla este plina sau un jucator castiga
    while (!isBoardFull(board)) {
        printBoard(board); // Afiseaza tabla de joc

        playerMove(board, currentPlayer); // Un jucator face o mutare

        // Verifica daca jucatorul curent a castigat dupa mutarea sa
        if (checkForWin(board, currentPlayer)) {
            printBoard(board);
            cout << "Felicitari! Jucatorul " << currentPlayer << " a castigat!" << endl;
            return 0; // Termina jocul
        }

        // Schimba jucatorul curent pentru urmatoarea mutare
        if (currentPlayer == player1) {
            currentPlayer = player2;
        } else {
            currentPlayer = player1;
        }
    }

    printBoard(board); // Afiseaza tabla de joc finala In caz de remiza
    cout << "Remiza!" << endl;

    return 0; // Termina jocul In caz de remiza
}
