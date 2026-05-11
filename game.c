#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h> // biblioteka umożliwiająca odczywanie użytych klawiszy na klawiaturze
#include "game.h"
#include "board.h"


int score = 0;
int level = 0;
int timeBeforeMove = 800;
const int speed[20] = {800, 716, 633, 550, 466, 383, 300, 216, 133, 100, 83, 66, 50, 33}; //tablica z wartosciami uzywanymi do wskazania czasu przed opadnieciem klocka


int currentBlockX;
int currentBlockY;
int currentBlock;
int currentBlockRotate[4][4];
int linesClearedTotal = 0;
int isGameOver = 0;

const int blockShapes[7][4][4] = { //tablica z klockami Tetrimino
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
};

void gameStart() {
    CONSOLE_CURSOR_INFO cursorInfo = {1, FALSE}; //zmienna wskazująca, ze kursor ma być niewidoczny
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);//funkcja z windows.h ustawiająca wielkość i widoczność kursora

    createBoard(); //wywołanie fukcji createBoard

    score = 0; //zerowanie licznika puktów
    linesClearedTotal = 0; //zerowanie licznika usuniętych lini

    spawnBlock(); //wywołanie funkcji spawnBlock
}

int checkButton() { //funkcja sprawdzająca jaki klawisz został wciśnięty 
    if (_kbhit()) { //warunek z funkcją kbhit sprawdza czy jakiś klawisz został naciśnięty
        return _getch(); //jeśli tak to funkcja getch odczytuje kod znaku wciśniętego na klawiaturze
    }
    return 0; //jeśli nie zwraca 0
}

void moveBlock() { //funkcja poruszająca klocek w dół
    if (checkIfBlockFits(currentBlockX, currentBlockY + 1, currentBlock)) { //warunek sprawdzający czy po przesunięcia klocka w dół zmieści się on na planszy
        currentBlockY++; //jeśli tak to przesuń klocke w dół dodając 1 do współrzędnej Y
    }
    else { //jeśli nie 
        blockBlock(); //wywołaj funkcję blokującą klocek
    }
}

void moveLeft() { //funkcja poruszająca klocek w lewo
    if (checkIfBlockFits(currentBlockX - 1, currentBlockY, currentBlock)) { //warunek sprawdzający czy po przesunięcia klocka w lewo zmieści się on na planszy
        currentBlockX--; //jeśli tak to przesuń klocek w lewo odejmując 1 od współrzędnej X
    }
}

void moveRight() { //funkcja poruszająca klocek w prawo
    if (checkIfBlockFits(currentBlockX + 1, currentBlockY, currentBlock)) { //warunek sprawdzający czy po przesunięcia klocka w prawo zmieści się on na planszy
        currentBlockX++; //jeśli tak to przesuń klocek w prawo dodając 1 do współrzędnej X
    }
}

void rotateBlock() { //funkcja obracająca klocek o 90 stopni
    int oldShape[4][4];
    int tempShape[4][4];

    //zapamiętanie aktualnego klocka
    for (int i = 0; i < 4; i++) { 
        for (int j = 0; j < 4; j++) {
            oldShape[i][j] = currentBlockRotate[i][j]; //zapisanie kształtu aktualnego klocka w tablicy oldShape
        }
    }

    //tworzenie obróconego klocka
    for (int i = 0; i < 4; i++) { 
        for (int j = 0; j < 4; j++) {
            tempShape[j][3 - i] = oldShape[i][j]; //obrócenie i zapisanie obróconego klocka w tablicy tempShape
        }
    }

    //wpisanie nowego kształtu klocka w plansze żeby sprawdzić czy się mieści 
    for (int i = 0; i < 4; i++) { 
        for (int j = 0; j < 4; j++) {
            currentBlockRotate[i][j] = tempShape[i][j]; //ustawienie nowego klocka na tablicy 
        }
    }

    if (!checkIfBlockFits(currentBlockX, currentBlockY, currentBlock)) { //sprawdzenie czy obrócony klocek nie mieści się na planszy
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                currentBlockRotate[i][j] = oldShape[i][j]; //jeśli tak to klocek powraca do pierwotnej pozycji
            }
        }
    }
}

/*=========================================================================================================*/

int chooseBlock() {
    return currentBlock = rand() % 7; //losowanie indeksu od 0 do 6 
}

int spawnBlock() {
    currentBlock = chooseBlock(); //wywolanie losowania indeksu klocka

    //dodawanie klocka na srodku u gory planszy
    currentBlockX = 3; 
    currentBlockY = 0;

    for (int i = 0; i < 4; i++) { 
        for (int j = 0; j < 4; j++) {
            currentBlockRotate[i][j] = blockShapes[currentBlock][i][j]; // kopiowanie klocka potrzebne do rotateBlock i drawBoard
        }
    }

    if(checkIfBlockFits(currentBlockX, currentBlockY,currentBlock) == 0) { //sprawdzanie czy klocek sie zmiesci na gorze planszy
        return 0; // jest kolizja 
    }
    return 1; //nie ma kolizji
}

void gameRun() {
    clock_t previousTime = clock(); //poczatek stopera (zapisanie punktu poczatkowego czasu)

    drawBoard(); //rysowanie planszy
    
    while (isGameOver == 0) { 
        int button = checkButton(); //pobranie kodu wcisnietego klawisza
        
        if(button == 224) { //sprawdzenie czy wcisniety klawisz jest strzalka
            button = checkButton(); //pobranie drugiego kodu klawisza (strzalki wysylaja sekwencje dwoch kodow)
            if (button == 75) { // kod strzalki w lewo
                moveLeft(); //funkcja przesuwajaca klocek w lewo
            }
            else if (button == 77) { //kod strzalki w prawo
                moveRight(); //funkcja przesuwajaca klocek w prawo
            } 
            else if (button == 80) { //kod strzalki w dol
                moveBlock(); //funkcja przesuwajaca klocek w dol
            }

        }
        else if (button == 32) { //kod spacji
            rotateBlock(); //funkcja obracajaca klocek
        }
        else if (button == 27) { //kod ESC
            break; //zakonczenie gry
        }
        clock_t currentTime = clock(); //pobranie aktualnego czasu

        if((currentTime - previousTime) >= timeBeforeMove) { //sprawdzenie czy od ostatniego ruchu klocka w dol minelo wystarczajaco czasu
            moveBlock(); //ruch klocka w dol
            previousTime = currentTime; //resetowanie stopera (ustawienie aktualnego czasu jako punkt poczatkowy)
        }

        clearLine(); //sprawdzenie i ewentualne usuniecie pelnych linii oraz zaktualizowanie wyniku i poziomu

        int speedLevel = level; // skopiowanie aktualnego poziomu
        if(speedLevel > 19) { //sprawdzenie czy wyszlismy poza tablice predkosci (maksymalny poziom to 19)
            speedLevel = 19;
        }

        timeBeforeMove = speed[speedLevel]; //zaktualizowanie czasu przed opadnieciem klocka zgodnie z aktualnym poziomem

        drawBoard(); //narysowanie zaktualizowanej planszy

        Sleep(10); //krotka przerwa dla odciazenia procesora
    }
    if (isGameOver == 1) {
        gameOver(); //wyswietlenie ekranu przegranej
    }
}

void gameOver() { //rysowanie ekranu przegranej
    printf("\n======================\n");
    printf("      GAME OVER      \n");
    printf("======================\n");
    printf("      wynik: %d     \n", score);
    printf("======================\n\n");

    printf("Wcisnij klawisz ESC, aby wyjsc");
}


