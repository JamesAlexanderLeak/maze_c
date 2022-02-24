#ifndef __MAZE_INCLUDED__
#define __MAZE_INCLUDED__

#include "cell.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct maze{
	CELL ***cells;
	int rows;
	int columns;
}MAZE;

extern MAZE *newMAZE(void);
extern MAZE *createMaze(int,int);
extern void printMaze(MAZE *);
extern void solveMaze(MAZE *);
extern void freeMaze(MAZE *);

#endif
