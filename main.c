#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main() { 
	gameStart();
	
	while (1) { // główna pętla działająca w nieskończoność 
		int sign = checkButton(); 
		
		if (sign == 27) { // 27 to kod klawisza ESC
			printf("Koniec gry!\n");
			break; // to słowo przerywa pętlę while(1)
		}

		//sprawdzanie czy działa 
		if (sign != 0) {
			printf("wybrano klawisz o kodzie %d\n", sign);
		}
	}
	return 0;
}