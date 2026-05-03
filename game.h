#pragma once

// definiowanie wierszy i kolumn dla planszy 
//#define boardHeight 10
//#define boardWidth 20

// deklaracja funkcji startowej
void gameStart();

//deklaracja funkcji rozpoznającej przycisk
int checkButton();

//deklaracja funkcji losującej klocek
void chooseBlock();

//deklaracja funkcji tworzącej wylosowany klocek na samej gorze i środku planszy
void spawnBlock();

//deklaracja funkcji wyznaczającej czas oczekiwania przed opadnięciem klocka
void waitTime();

//deklaracja funkcji operującej grą
void gameRun();

//deklaracja funkcji kończącej grę
void gameOver();


