#pragma once

// definiowanie wierszy i kolumn dla planszy 
//#define boardHeight 10
//#define boardWidth 20

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

/*====================================================================================*/

//deklaracja funkcji losującej klocek
int chooseBlock();

//deklaracja funkcji tworzącej wylosowany klocek na samej gorze i środku planszy
void spawnBlock();

//deklaracja funkcji operującej grą
void gameRun();

//deklaracja funkcji kończącej grę
void gameOver();


