#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // biblioteka umożliwiająca odczywanie użytych klawiszy na klawiaturze
#include "game.h"
#include "board.h"


//int board[boardWidth][boardHeight];
int score = 0;

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

    srand(time(NULL));

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

void blockBlock() {
    for (int i = 0; i < 4;i++) {
        for (int j = 0;j < 4;j++) {
            if (blockShapes[currentBlock][i][j] == 1) {
                board[currentBlockX + j][currentBlockY + i] = 1;
            }
        }
    }
    clearLine();
    spawnBlock();
}

void clearLine() {
    int clearedLines = 0;
        for (int  y = boardHeight - 1;y >= 0;y--) {
            int isFull = 1;
            for (int x = 0;x < boardWidth; x++) {
                if (board[x][y] == 0) {
                    isFull = 0;
                    break;
                }
            }
            if (isFull) {
                clearedLines++;
                linesClearedTotal++;
                for (int tempy = y; tempy > 0; tempy--) {
                    for (int tempx = 0; tempx < boardWidth;tempx++) {
                        board[tempx][tempy] = board[tempx][tempy - 1];
                    }
                }
                for (int tempx = 0;tempx < boardWidth;tempx++) {
                    board[tempx][0] = 0;
                }
                y++;
            }
        }
        /*if (clearedLines == 1){
        *   score = 40 * (level +1);}
        * else if (clearedLines == 2){
        *   score = 100 * (level +1);}
        * else if (clearedLines == 3){
        *   score = 300 * (level +1);}
        * else if (clearedLines == 4){
        *   score = 1200 * (level +1);}
        */
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

