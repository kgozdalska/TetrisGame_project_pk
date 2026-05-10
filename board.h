#pragma once

// definiowanie wierszy i kolumn dla planszy 
#define boardHeight 20
#define boardWidth 10
extern int board[boardHeight][boardWidth];

// deklaracja funkcji tworzącej planszę
void createBoard();

//deklaracja funkcji rysującej planszę
void drawBoard();

//deklaracja funkcji sprawdzającej czy klocek się zmieści (czy mozna wykonać ruch)
int checkIfBlockFits (int blockX, int blockY, int blockShape);

/*==============================================================================*/

//deklaracja funkcji blokującej klocek na planszy
void blockBlock();

//deklaracja funkcji czyszczącej pełne linie
void clearLine();


