#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "board.h"
#include "game.h"

int board[boardHeight][boardWidth];

void createBoard() {
    for (int j = 0; j < boardHeight; j++) { //tworzenie planszy wypelnionej zerami
        for (int i = 0; i < boardWidth; i++) {
            board[j][i] = 0;
        }
    }
}

void drawBoard() {
    COORD cursorPosition = {0, 0}; //zmienna przechowująca koordynaty początku planszy (lewy gorny rog)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition); //funkcja z windows.h zmieniajaca pozycje kursora na wskazane miejsce

    printf("Wynik: %d   Poziom: %d\n", score, level); // wskazywanie wyniku i poziomu nad plansza
    printf("--------------------\n"); //rysowanie gory planszy

    for (int j = 0; j < 20; j++) { //rysowanie wnetrza planszy
        printf("|"); //rysowanie lewej sciany planszy

        for (int i = 0; i < 10; i++) { 

            int isDrawn = 0; //zmienna do sprawdzania czy w danym miejscu zostal narysowany aktualny klocek (1) czy nie (0)

            if (i >= currentBlockX && i < currentBlockX + 4 && j >= currentBlockY && j < currentBlockY + 4) { //sprawdzanie czy aktualnie znajdujemy sie w miejscu planszy w ktorym znajduje sie tablica z klockiem
                int blockX = i - currentBlockX; //zmiana x planszy na x tablicy klocka
                int blockY = j - currentBlockY; //zmiana y planszy na y tablicy klocka

                if (currentBlockRotate[blockY][blockX] == 1) { // sprawdzanie czy w tym miejscu tablicy z klockiem znajduje sie klocek
                    printf("[]"); //rysowanie klocka
                    isDrawn = 1; //oznaczenie, ze to miejsce jest juz narysowane
            }
        }

        if(isDrawn == 0) { //rysowanie planszy w polach, w ktorych nie ma aktualnego klocka
            if(board[j][i] == 1) { 
                printf("[]"); //rysowanie starych klockow 
            }
            else {
                printf("  "); //rysowanie pustego tla planszy
            }
        }
    }
    printf("|\n"); //rysowanie prawej sciany planszy
}
printf("--------------------\n"); //rysowanie dolu planszy
}

int checkIfBlockFits(int blockTestX, int blockTestY, int currentBlockRotate) {
    for (int j = 0; j < 4; j++) {  
        for (int i = 0; i < 4; i++) {
            if (currentBlockRotate[j][i] == 1) { //branie jedynie pol w tablicy klocka, w ktorych istnieje klocek
                int boardX = blockTestX + i;  //zmiana x klocka na x planszy 
                int boardY = blockTestY +j; // //zmiana y klocka na y planszy

                if (boardX < 0 || boardX >= 10) { //sprawdzanie ścian
                    return 0; // uderzy w bok planszy
                }

                if (boardY >= boardHeight) { //sprawdzanie podłogi
                    return 0; // uderzy w podłogę
                }
 
                if (boardY >= 0 && board[boardY][boardX] == 1) { //sprawdzanie innych klockow
                    return 0; // zderzenie z klockiem
                }
            }
        }
    }
    return 1; //brak kolizji
}

/*===========================================================================*/

void blockBlock() { //funkcja blokująca ruch klocka
    for (int i = 0; i < 4;i++) {
        for (int j = 0;j < 4;j++) {
            if (currentBlockRotate[i][j] == 1) { //warunek  szykający 1 - sprawdzający na jakiej pozycji w obruconym klocku jest 1
                board[currentBlockY + i][currentBlockX + j] = 1; //jeśli jedynka została znaleziona to zostaje ona umieszczona w odpowiednim miejscu planszy
            }
        }
    }
    clearLine(); //wywołanie funkcji clearLine

    if (spawnBlock() == 0) { //warunek sprawdzający czy można wygenerować kolejny klocek 
        isGameOver = 1; //jeśli nie to koniec gry 
    }
}

void clearLine() {
    int clearedLines = 0; //licznik wiersy usuniętych za jednym razem
        for (int  y = boardHeight - 1;y >= 0;y--) {//pętla przechodzi od dołu planszy
            int isFull = 1; //zmienna do sprawdzania czy wiersz jest pełen ustawiona na 1
            for (int x = 0;x < boardWidth; x++) { //przechodzenie przez wiersz
                if (board[y][x] == 0) { //sprawdzanie czy w wierszy występuje 0 - nie jest pełen
                    isFull = 0; //jeśli tak to ustaw isFull na 0 
                    break; //przerywanie pętli
                }
            }
            if (isFull) { //jeśli pełny wiersz
                clearedLines++; //zwiększenie zmiennej clearLines o 1
                linesClearedTotal++; //zwiększenie zmiennej linesClearedTotal o 1
                for (int tempy = y; tempy > 0; tempy--) { //pętla do kopiowania wierszy w dół - spadania
                    for (int tempx = 0; tempx < boardWidth;tempx++) {
                        board[tempy][tempx] = board[tempy - 1][tempx]; //kopiowanie wiersza o jeden wyżej w dół
                    }
                }
                for (int tempx = 0;tempx < boardWidth;tempx++) { //pętla do usuwania  
                    board[0][tempx] = 0; //wypełnianie wierszy zerami - usuwanie
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