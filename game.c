#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // biblioteka umożliwiająca odczywanie użytych klawiszy na klawiaturze
#include "game.h"
#include "board.h"


int score = 0;
int level = 0;

const int blockShapes[7][4][4] = {
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
int currentBlockY;
int currentBlock;
int linesClearedTotal = 0;

void gameStart() {

    createBoard();

    score = 0;
    linesClearedTotal = 0;

    spawnBlock();
    }

int checkButton() {
    if (_kbhit()) { // warunek z funkcją kbhit sprawdza czy jakiś klawisz został naciśnięty
        return _getch(); // jeśli tak to funkcja getch odczytuje kod znaku wciśniętego na klawiaturze
    }
    return 0; // jeśli nie zwraca 0
}

void moveBlock() {
    if (checkIfBlockFits(currentBlockX, currentBlockY, currentBlock)) {
        currentBlockY++;
    }
    else {
        blockBlock();
    }
}

void moveLeft() {
    if (checkIfBlockFits(currentBlockX - 1, currentBlockY, currentBlock)) {
        currentBlockX--;
    }
}

void moveRight() {
    if (checkIfBlockFits(currentBlockX + 1, currentBlockY, currentBlock)) {
        currentBlockX++;
    }
}

/*=========================================================================================================*/

int chooseBlock() {
    return currentBlock = rand() % 7;
}

void spawnBlock() {
    currentBlock = chooseBlock();
    currentBlockX = 3;
    currentBlockY = 0;

    if(checkIfBlockFits(currentBlockX, currentBlockY,currentBlock) == 0) {
        return 0;
    }
    return 1;
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

