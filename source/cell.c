#include "cell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
typedef struct cell{
	int row,column;
	int value;
	bool visited;
	bool bottom, right;			
}CELL;

CELL *newCell(int rowInput, int columnInput){
	CELL *newCell = (CELL *)malloc(sizeof(CELL));
	newCell->row = rowInput;
	newCell->column = columnInput;
	newCell->value = -1;
	newCell->visited = false;
	newCell->bottom = true;
	newCell->right = true; 	
	return newCell;
}
int getRow(CELL *cell){
	return cell->row;
}
int getColumn(CELL *cell){
	return cell->column;
}
int getVal(CELL *cell){
	return cell->value;
}
bool hasBottom(CELL *cell){
	return cell->bottom;	
}
bool hasRight(CELL *cell){
	return cell->right;
}
bool isVisited(CELL *cell){
	return cell->visited;
}
void destroyBottom(CELL *cell){
	cell->bottom = false;
	return;
}
void destroyRight(CELL *cell){
	cell->right = false;	
	return;
}
void setValue(CELL *cell,int val){
	cell->value = val;
	return;
}
void visit(CELL *cell){
	if(cell->visited == false){
	cell->visited = true;
	}
	else{
	cell->visited = false;	
	}
	return;
}
void freeCell(CELL *cell){
	assert(cell!=NULL);
	free(cell);
	return;
}
