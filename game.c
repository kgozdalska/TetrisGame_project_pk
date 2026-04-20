#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    printf("Plansza uzupełniona, punktacja: %d\n", score);
}