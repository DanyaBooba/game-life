#include <stdio.h>
#include "helpers.h"
#include <time.h>
#include <stdlib.h>

#define FIELD_H 30
#define FIELD_W 30

#define POINT_LIVE 1
#define POINT_UNLIVE 0

#define POINT_LIVE_PRINT "x"
#define POINT_UNLIVE_PRINT ""

#define ChanceGeneratingPointAtRandom 80

int Field[FIELD_H][FIELD_W];
#define IsInitField 0

void InitField();
void PrintField();
int ValuePoint(int x, int y);
int CountNeighbors(int x, int y);
int EqualTwoStrings(char from[], char to[], int len);
void FieldStep();
void SetFieldAll();
void SetFieldGrider();
void SetFieldRandomPoints();

int main(int argc, char * argv[]) {
	int defaultSpawn = 1;

	if(argc > 1) {
		for(int i = 1; i < argc; i++) {
			if(EqualTwoStrings(argv[i], "-help", 2)) {
				PrintHelp();
				getchar();
			}

			if(EqualTwoStrings(argv[i], "-glider", 2)) {
				defaultSpawn = -1;
			}

			if(EqualTwoStrings(argv[i], "-all", 2)) {
				defaultSpawn = -2;
			}
		}
	}

	srand(time(0));
	if(!IsInitField) InitField();

	if(defaultSpawn == 1) {
		SetFieldRandomPoints();
	}
	else if(defaultSpawn == -1) {
		SetFieldGrider();
	}
	else if(defaultSpawn == -2) {
		SetFieldAll();
	}

	while(1) {
		PrintField();
		FieldStep();

		getchar();
	}

	return 0;
}

//
// Инициализация поля
//

void InitField() {
	for(int x = 0; x < FIELD_H; x++) {
		for(int y = 0; y < FIELD_W; y++) {
			Field[x][y] = POINT_UNLIVE;
		}
	}
}

//
// Печать поля
//

void PrintField() {
	ClearTerminal();
	for(int x = 0; x < FIELD_H; x++) {
		for(int y = 0; y < FIELD_W; y++) {
			printf("%2s", (Field[x][y] ? POINT_LIVE_PRINT : POINT_UNLIVE_PRINT));
		}
		printf("\n");
	}
}

//
// Значение в точке
//

int ValuePoint(int x, int y) {
	int value = x < 0 || x >= FIELD_H || y < 0 || y >= FIELD_W || Field[x][y] != POINT_LIVE;
	return !value;
}

//
// Количество соседей
//

int CountNeighbors(int x, int y) {
	int count = 0;

	count += ValuePoint(x - 1, y - 1);
    count += ValuePoint(x - 1, y);
    count += ValuePoint(x - 1, y + 1);
    count += ValuePoint(x, y - 1);
    count += ValuePoint(x, y + 1);
    count += ValuePoint(x + 1, y - 1);
    count += ValuePoint(x + 1, y);
    count += ValuePoint(x + 1, y + 1);

	return count;
}

//
// Действие шага игры
//

void FieldStep() {
	int TempField[FIELD_H][FIELD_W];

	for(int x = 0; x < FIELD_H; x++) {
		for(int y = 0; y < FIELD_W; y++) {
			int neighbor = CountNeighbors(x, y);
			if(neighbor == 3) {
				TempField[x][y] = POINT_LIVE;
			}
			else if(neighbor == 2 && Field[x][y] == POINT_LIVE) {
				TempField[x][y] = POINT_LIVE;
			}
			else {
				TempField[x][y] = POINT_UNLIVE;
			}
		}
	}

	for(int x = 0; x < FIELD_H; x++) {
		for(int y = 0; y < FIELD_W; y++) {
			Field[x][y] = TempField[x][y];
		}
	}
}

//
// Равенство 2 строк
//

int EqualTwoStrings(char from[], char to[], int len) {
	for(int i = 0; i < len; i++) {
		if(from[i] != to[i]) return 0;
	}

	return 1;
}

//
// Заполнение всего поля
//

void SetFieldAll() {
	for(int x = 0; x < FIELD_H; x++) {
		for(int y = 0; y < FIELD_W; y++) {
			Field[x][y] = POINT_LIVE;
		}
	}
}

//
// Спавн глайдера
//

void SetFieldGrider() {
	Field[10][4] = POINT_LIVE;
    Field[11][5] = POINT_LIVE;
    Field[12][5] = POINT_LIVE;
    Field[12][4] = POINT_LIVE;
    Field[12][3] = POINT_LIVE;
}

//
// Заполнение поля случайно
//

void SetFieldRandomPoints() {
	for(int x = 0; x < FIELD_H; x++) {
		for(int y = 0; y < FIELD_W; y++) {
			int isNeedSpawnPoint = rand() % 100 > ChanceGeneratingPointAtRandom;
			Field[x][y] = isNeedSpawnPoint % 2 ? POINT_LIVE : POINT_UNLIVE;
		}
	}
}
