#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "board.h"

int main() { 
	srand((unsigned int)time(NULL));
	gameStart();
	gameRun();
	return 0;
}

