#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // biblioteka umożliwiająca odczywanie użytych klawiszy na klawiaturze
#include "game.h"


int board[boardWidth][boardHeight];
int score = 0;

void gameStart() {

    // generowanie losowych liczb żeby przy każdym ropoczęciu gry klocki losowały się inaczej
    srand(time(NULL));

    // resetowanie punktacji
    score = 0;

    // uzupełnianie planszy zerami, 0 oznacza puste pole
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardHeight; j++) {
            board[i][j] = 0;
        }
    }

    //te printy potem są do usunięcia albo po prostu sprawdzam sobie czy działa coś 
    printf("Gra Tetris uruchomiona!\n");
    printf("Plansza uzupelniona, punktacja: %d\n", score);
    printf("Jesli chcesz zakonczyc gre wcisnij [ESC]\n");
}

int checkButton() {
    if (_kbhit()) { // warunek z funkcją kbhit sprawdza czy jakiś klawisz został naciśnięty
        return _getch(); // jeśli tak to funkcja getch odczytuje kod znaku wciśniętego na klawiaturze
    }
    return 0; // jeśli nie zwraca 0
}