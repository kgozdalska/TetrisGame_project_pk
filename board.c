#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "game.h"

int board[boardHeight][boardWidth];

void createBoard() {
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardHeight; j++) {
            board[i][j] = 0;
        }
    }
}

void checkIfBlockFits(current) {
}