#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

char human = 'X'; // Jucatorul este reprezentat de caracterul 'X'
char computer = 'O'; // Calculatorul este reprezentat de caracterul 'O'

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
void humanMove(vector<char> &board) {
    int move;
    cout << "Introdu pozitia (0-8): ";
    cin >> move;

    while (move < 0 || move > 8 || !isMoveValid(board, move)) {
        cout << "Mutare invalida. Introdu din nou pozitia (0-8): ";
        cin >> move;
    }

    board[move] = human; // Actualizează tabla cu mutarea jucătorului
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
    vector<char> board(9, ' '); // Initializeaza tabla de joc cu spații goale pentru fiecare celula
    srand(static_cast<unsigned int>(time(0))); // Initializare seed pentru generarea de numere aleatoare

    while (!isBoardFull(board)) {
        printBoard(board); // Afiseaza tabla de joc
        humanMove(board); // Permite jucatorului sa faca o mutare

        if (checkForWin(board, human)) { // Verifica daca jucătorul a castigat
            printBoard(board);
            cout << "Felicitari! Ai castigat!" << endl;
            return 0; // Termina jocul
        }

        if (isBoardFull(board)) {
            break; // Verificare pentru a evita o mutare suplimentara dacă tabla este plină
        }

        computerMove(board); // Computerul face o mutare

        if (checkForWin(board, computer)) { // Verifica daca computerul a castigat
            printBoard(board);
            cout << "Calculatorul a castigat!" << endl;
            return 0; // Termina jocul
        }
    }

    printBoard(board); // Afiseaza tabla de joc finala
    cout << "Remiza!" << endl;

    return 0; // Termina jocul în caz de remiza
}
