#ifndef __CELL_INCLUDED__
#define __CELL_INCLUDED__

#include <stdlib.h>
#include <stdbool.h>

typedef struct cell CELL;

extern CELL *newCell(int,int);
extern int getRow(CELL *);
extern int getColumn(CELL *);
extern int getVal(CELL *);
extern bool hasBottom(CELL *);
extern bool hasRight(CELL *);
extern bool isVisited(CELL *);
extern void destroyBottom(CELL *);
extern void destroyRight(CELL *);
extern void setValue(CELL *,int);
extern void visit(CELL *);
extern void freeCell(CELL *); 

#endif
