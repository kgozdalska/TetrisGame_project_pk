#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // biblioteka umożliwiająca odczywanie użytych klawiszy na klawiaturze
#include "game.h"
#include "board.h"


//int board[boardWidth][boardHeight];
int score = 0;

const int blockShapes [7][4][4] = {
    //Tetrimino "I"
    {
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0}
    },
    //Tetrimino "T"
    {
        {0,0,0,0},
        {1,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
    },
    //Tetrimino "O"
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    //Tetrimino "L"
    {
        {0,1,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    //Tetrimino "J"
    {
        {0,0,1,0},
        {0,0,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    //Tetrimino "S"
    {
        {0,0,0,0},
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0}
    },
    //Tetrimino "Z"
    {
        {0,0,0,0},
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
    }
}

int currentBlockX;
int currentBblockY;
int currentBlock;

void gameStart() {

    // generowanie losowych liczb żeby przy każdym ropoczęciu gry klocki losowały się inaczej
    //srand(time(NULL));

    // resetowanie punktacji
    score = 0;

    // uzupełnianie planszy zerami, 0 oznacza puste pole
    createBoard();
   /* for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardHeight; j++) {
            board[i][j] = 0;
        }
    }*/

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

int chooseBlock() {
    return currentBlock = rand() % 7;
}

void spawnBlock() {
    currentBlock = chooseBlock();
    currentBlockX = 3;
    currentBlockY = 0;

    if(checkIfBlockFits(currentBlockX, currentBblockY,currentBlock) == 0) {
        return 0;
    }
    return 1;
}

void waitTime() {
    sleep(800);
    //trzeba się zastanowić jak zrobić, zeby w tym czasie uzytkownik mogl obracac klocek
}

void gameRun() {
    int isGameOver = 0;

    while (isGameOver == 0) {
        checkButton();
        //.....

    }
}

void gameOver() {
    printf("\n====================\n");
    printf("      GAME OVER      \n");
    printf("====================\n");
    printf("     wynik: %d     \n", score);
    printf("====================\n\n");

    printf("Wciśnij klawisz ESC, aby wyjść");
}
