// 0 - клетка мертва
// 1 - клетка жива

#include <stdio.h>
#include "helpers.h"
#include <time.h>
#include <stdlib.h>

#define FIELD_H 30
#define FIELD_W 30

#define POINT_LIVE "x"
#define POINT_UNLIVE ""
#define ChanceGeneratingPointAtRandom 80

int Field[FIELD_H][FIELD_W];
#define IsInitField 0

void InitField() {
	for(int x = 0; x < FIELD_H; x++) {
		for(int y = 0; y < FIELD_W; y++) {
			Field[x][y] = 0;
		}
	}
}

void PrintField() {
	ClearTerminal();
	for(int x = 0; x < FIELD_H; x++) {
		for(int y = 0; y < FIELD_W; y++) {
			printf("%2s", (Field[x][y] ? POINT_LIVE : POINT_UNLIVE));
		}
		printf("\n");
	}
}

void SetFieldRandomPoints() {
	for(int x = 0; x < FIELD_H; x++) {
		for(int y = 0; y < FIELD_W; y++) {
			int isNeedSpawnPoint = rand() % 100 > ChanceGeneratingPointAtRandom;
			Field[x][y] = isNeedSpawnPoint % 2;
		}
	}
}

int EqualTwoStrings(char from[], char to[], int len) {
	for(int i = 0; i < len; i++) {
		if(from[i] != to[i]) return 0;
	}

	return 1;
}

int main(int argc, char * argv[]) {
	if(argc == 2 && EqualTwoStrings(argv[1], "-v", 2)) {
		PrintHelp();
		getchar();
	}

	srand(time(0));
	if(!IsInitField) InitField();

	while(1) {
		SetFieldRandomPoints();
		PrintField();
		getchar();
	}

	return 0;
}
