#pragma once

extern int currentBlockX;
extern int currentBlockY;
extern int currentBlock;
extern int linesClearedTotal;
extern int isGameOver;
extern int score;
extern int level;
extern const int blockShapes[7][4][4];

// deklaracja funkcji startowej
void gameStart();

//deklaracja funkcji rozpoznającej przycisk
int checkButton();

//deklaracja funkcji poruszającej klockiem w dół
void moveBlock();

//deklaracja funkcji poruszającej klockiem w lewo
void moveLeft();

//deklaracja funkcji poruszającej klockiem w prawo
void moveRight();

//deklaracja funkcji obracającj klocek
void rotateBlock();

/*====================================================================================*/

//deklaracja funkcji losującej klocek
int chooseBlock();

//deklaracja funkcji tworzącej wylosowany klocek na samej gorze i środku planszy
int spawnBlock();

//deklaracja funkcji operującej grą
void gameRun();

//deklaracja funkcji kończącej grę
void gameOver();


