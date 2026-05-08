#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "board.h"
#include "game.h"

int board[boardHeight][boardWidth];

void createBoard() {
    for (int j = 0; j < boardHeight; j++) {
        for (int i = 0; i < boardWidth; i++) {
            board[j][i] = 0;
        }
    }
}

void drawBoard() {
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    printf("Wynik: %d   Poziom: %d\n", score, level);
    printf("--------------------\n");

    for (int j = 0; j < 20; j++) {
        printf("|");

        for (int i = 0; i < 10; i++) {

            int isDrawn = 0;

            if (i >= currentBlockX && i < currentBlockX + 4 && j >= currentBlockY && j < currentBlockY + 4) {
                int blockX = i - currentBlockX;
                int blockY = j - currentBlockY;

                if (currentBlockRotate[blockY][blockX] == 1) {
                    printf("[]");
                    isDrawn = 1;
            }
        }

        if(isDrawn == 0) {
            if(board[j][i] == 1) {
                printf("[]");
            }
            else {
                printf("  ");
            }
        }
    }
    printf("|\n");
}
printf("--------------------\n");
}

int checkIfBlockFits(int blockTestX, int blockTestY, int currentBlock) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (currentBlockRotate[y][x] == 1) {
                int boardX = blockTestX + x;
                int boardY = blockTestY +y;

                //sprawdzanie ścian
                if (boardX < 0 || boardX >= 10) {
                    return 0; // uderzy w bok planszy
                }

                //sprawdzanie podłogi
                if (boardY >= boardHeight) {
                    return 0; // uderzy w podłogę
                }

                //sprawdzanie innych klockow
                if (boardY >= 0 && board[boardY][boardX] == 1) {
                    return 0; // zderzenie z klockiem
                }
            }
        }
    }
    return 1;
}

void blockBlock() {
    for (int i = 0; i < 4;i++) {
        for (int j = 0;j < 4;j++) {
            if (currentBlockRotate[i][j] == 1) {
                board[currentBlockY + i][currentBlockX + j] = 1;
            }
        }
    }
    clearLine();
   if (spawnBlock() == 0) {
    isGameOver = 1;
   }
}

void clearLine() {
    int clearedLines = 0;
        for (int  y = boardHeight - 1;y >= 0;y--) {//pętla przechodzi od dołu planszy
            int isFull = 1;
            for (int x = 0;x < boardWidth; x++) {//sprawdzanie czy wiersz zawiera 0 nie jest pełen
                if (board[y][x] == 0) {
                    isFull = 0;
                    break;
                }
            }
            if (isFull) { //jeśli pełny wiersz
                clearedLines++;
                linesClearedTotal++;
                for (int tempy = y; tempy > 0; tempy--) {//kopiowanie wiersza na dół - spadanie
                    for (int tempx = 0; tempx < boardWidth;tempx++) {
                        board[tempy][tempx] = board[tempy - 1][tempx];
                    }
                }
                for (int tempx = 0;tempx < boardWidth;tempx++) { //usuwanie 
                    board[0][tempx] = 0;
                }
                y++; //sprawdzanie znów tego samego wiersza
            }
        }
        if (clearedLines > 0) { //liczenie punktów
            if (clearedLines == 1) {
                score += 40 * (level + 1);
            }
            else if (clearedLines == 2) {
                score += 100 * (level + 1);
            }
            else if (clearedLines == 3) {
                score += 300 * (level + 1);
            }
            else if (clearedLines >= 4) {
                score += 1200 * (level + 1);
            }
        }

        if (linesClearedTotal >= (level + 1) * 10) { //zwiększanie levelu
            level++;
        }
        
}