#include <stdio.h>
#include "helpers.h"
#include <time.h>
#include <stdlib.h>

#define FIELD_H 30
#define FIELD_W 30

#define POINT_LIVE 1
#define POINT_UNLIVE 0

#define POINT_LIVE_PRINT "x" // \u25A0
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

/*

gen[15][4]  = 1;
  gen[15][5]  = 1;
  gen[15][6]  = 1;
  gen[16][5]  = 1;
  gen[17][5]  = 1;
  gen[17][6]  = 1;
  gen[17][7]  = 1;
  gen[18][9]  = 1;
  gen[18][10] = 1;
  gen[18][8]  = 1;

*/


/*

void rules(int array[25][100], char choice) {
    int temp[25][100];
    copy(array, temp);
    for(int j = 0; j < 25; j++) {
        for(int i = 0; i < 100; i++) {
            int count = 0;
            if (j>0 && j<24 && i>0 && i<99) {
                count = array[j-1][i] +
                        array[j-1][i-1] +
                        array[j][i-1] +
                        array[j+1][i-1] +
                        array[j+1][i] +
                        array[j+1][i+1] +
                        array[j][i+1] +
                        array[j-1][i+1];
                if(count < 2 || count > 3)
                    temp[j][i] = 0;
                if(count == 2)
                    temp[j][i] = array[j][i];
                if(count == 3)
                    temp[j][i] = 1;
            } else {
                if (j>0 && j<24 && i == 0) {
                    count = array[j][99] +
                            array[j+1][99] +
                            array[j-1][99] +
                            array[j][i+1] +
                            array[j+1][i+1] +
                            array[j-1][i+1] +
                            array[j-1][i] +
                            array[j+1][i];
                    if(count < 2 || count > 3)
                        temp[j][i] = 0;
                    if(count == 2)
                        temp[j][i] = array[j][i];
                    if(count == 3)
                        temp[j][i] = 1;
                }
                if (j == 0 && i>0 && i<99) {
                    count = array[24][i+1] +
                            array[24][i] +
                            array[24][i-1] +
                            array[j][i+1] +
                            array[j+1][i+1] +
                            array[j+1][i-1] +
                            array[j][i-1] +
                            array[j+1][i];
                    if(count < 2 || count > 3)
                        temp[j][i] = 0;
                    if(count == 2)
                        temp[j][i] = array[j][i];
                    if(count == 3)
                        temp[j][i] = 1;
                }
                if (j == 24 && i>0 && i<99) {
                    count = array[0][i+1] +
                            array[0][i] +
                            array[0][i-1] +
                            array[j][i+1] +
                            array[j-1][i+1] +
                            array[j-1][i-1] +
                            array[j][i-1] +
                            array[j-1][i];
                    if(count < 2 || count > 3)
                        temp[j][i] = 0;
                    if(count == 2)
                        temp[j][i] = array[j][i];
                    if(count == 3)
                        temp[j][i] = 1;
                }
                if (j>0 && j<24 && i == 99) {
                    count = array[j][0] +
                            array[j+1][0] +
                            array[j-1][0] +
                            array[j][i-1] +
                            array[j+1][i-1] +
                            array[j-1][i-1] +
                            array[j+1][i] +
                            array[j-1][i];
                    if(count < 2 || count > 3)
                        temp[j][i] = 0;
                    if(count == 2)
                        temp[j][i] = array[j][i];
                    if(count == 3)
                        temp[j][i] = 1;
                }
                if (j == 0 && i == 0) {
                    count = array[j][i+1] +
                            array[j-1][i+1] +
                            array[j-1][i] +
                            array[j][99] +
                            array[j+1][99] +
                            array[24][i+1] +
                            array[24][i] +
                            array[24][99];
                    if(count < 2 || count > 3)
                        temp[j][i] = 0;
                    if(count == 2)
                        temp[j][i] = array[j][i];
                    if(count == 3)
                        temp[j][i] = 1;
                }
                if (j == 0 && i == 99) {
                    count = array[j][i-1] +
                            array[j-1][i-1] +
                            array[j+1][i] +
                            array[j][99] +
                            array[j-1][99] +
                            array[0][i-1] +
                            array[0][i] +
                            array[24][0];
                    if(count < 2 || count > 3)
                        temp[j][i] = 0;
                    if(count == 2)
                        temp[j][i] = array[j][i];
                    if(count == 3)
                        temp[j][i] = 1;
                }
                if (j == 24 && i == 99) {
                    count = array[j][i-1] +
                            array[j-1][i-1] +
                            array[j-1][i] +
                            array[j][0] +
                            array[j-1][0] +
                            array[99][i-1] +
                            array[99][i] +
                            array[0][0];
                    if(count < 2 || count > 3)
                        temp[j][i] = 0;
                    if(count == 2)
                        temp[j][i] = array[j][i];
                    if(count == 3)
                        temp[j][i] = 1;
                }
                if (j == 24 && i == 0) {
                    count = array[j][i+1] +
                            array[j-1][i+1] +
                            array[j-1][i] +
                            array[j][99] +
                            array[j-1][99] +
                            array[0][i+1] +
                            array[0][i] +
                            array[0][99];
                    if(count < 2 || count > 3)
                        temp[j][i] = 0;
                    if(count == 2)
                        temp[j][i] = array[j][i];
                    if(count == 3)
                        temp[j][i] = 1;
                }
            }
        }
    }
    copy(temp, array);
}

*/


/*

#include <iostream>

const int n=19, m=20, N=n*m; bool a[N], b[N];

bool get(bool *a, int i, int j) { return a[(i+n)%n*n + (j+m)%m]; }

int neibs(bool *a, int i, int j) {
    int r = 0;
    for(int p=-1; p<=1; p++) for(int q=-1; q<=1; q++) r += get(a, i+p, j+q);
    return r - get(a, i, j);
}
void show(bool *a) {
    for(int k=0; k<N; k++) std::cout<<(a[k] ? '@' : '-')<<((k+1)%n ? ' ' : '\n');}

void go(bool *a, bool *b, int c) {
    for(int i=0; i<=c; i++) {
        std::cout << "generation " << i << ":\n"; show(a); std::cout<<'\n';
        for(int k=0; k<N; k++) {
            int s = neibs(a, k/n, k%n);
            b[k] = !a[k] && s==3 ? 1 : a[k] && (s<2 || s>3) ? 0 : a[k];
        }
        bool *t=a; a=b; b=t;
    }
}
int main() { for(int i=6; i<=13; i++) a[i*n+n/2]=1; go(a, b, 50); }

*/
