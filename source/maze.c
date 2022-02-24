#include "maze.h"
#include <stdlib.h>
#include <stdio.h>
#include "cell.h"
#include "stack.h"
#include "da.h"
#include "cda.h"
#include "queue.h"
long int random(void);
void srandom(unsigned int seed);
//typedef struct maze{
//	CELL ***cells;
//	int rows, columns;
//}MAZE;
MAZE *newMAZE(void){
	MAZE *maze = (MAZE *)malloc(sizeof(MAZE));	
	maze->rows = 0;
	maze->columns = 0;
	maze->cells = NULL;
	return maze;
} 
MAZE *createMaze(int r, int c){
	int i = 0;
	int j = 0;
	int count  = 0;
	int rand = 0;
	MAZE *maze = newMAZE();
	CELL *currentCell = NULL;
	DA *da = newDA();
	maze->columns = c;
	maze->rows = r;
	maze->cells = malloc(sizeof(CELL **) * r);
	for(i = 0; i < r; ++i){
		maze->cells[i] = malloc(sizeof(CELL *) * c);
		for(j = 0; j < c; ++j){
			maze->cells[i][j] = newCell(i,j);
		}
	}
	STACK *stack = newSTACK();
	push(stack,maze->cells[0][0]);
	CELL *v = peekSTACK(stack);
	visit(maze->cells[0][0]);
	while(sizeSTACK(stack) != 0){
		v = peekSTACK(stack);
		//check adjacent cells
		if(getRow(v)-1 >= 0 && isVisited(maze->cells[getRow(v)-1][getColumn(v)]) == false){
			insertDA(da,count,maze->cells[getRow(v)-1][getColumn(v)]);	
			count++;
		}
		if(getColumn(v)-1 >= 0 && isVisited(maze->cells[getRow(v)][getColumn(v)-1]) == false){
			insertDA(da,count,maze->cells[getRow(v)][getColumn(v)-1]);	
			count++;
		}
		if(getColumn(v)+1 < maze->columns && isVisited(maze->cells[getRow(v)][getColumn(v)+1]) == false){
			insertDA(da,count,maze->cells[getRow(v)][getColumn(v)+1]);	
			count++;
		}
		if(getRow(v)+1 < maze->rows && isVisited(maze->cells[getRow(v)+1][getColumn(v)]) == false){
			insertDA(da,count,maze->cells[getRow(v)+1][getColumn(v)]);	
			count++;
		}	
		if(count > 0){
			rand = random() % count;
			currentCell = removeDA(da,rand);
			for(i = 0; i < count-1; i++){
				removeDA(da,i);
			}
			visit(currentCell);
			if(getRow(currentCell) == getRow(v)){
				if(getColumn(currentCell) - getColumn(v) > 0){
					destroyRight(v);	
				}	
				else
					destroyRight(currentCell);
			}
			else{
				if(getRow(currentCell) - getRow(v) > 0){
					destroyBottom(v);
				}	
				else
					destroyBottom(currentCell);
			}
			push(stack,currentCell);	
			count = 0;
		}
		else{
			pop(stack);
			count = 0;
		}
	}
	destroyRight(maze->cells[r-1][c-1]);
	freeSTACK(stack);
	freeDA(da);
//		for(i = 0; i < maze->rows; i++){
//			for(j = 0; j< maze->columns; j++){
//				printf("Row: %d Column: %d Val: %d Visited: %d \n",getRow(maze->cells[i][j]),getColumn(maze->cells[i][j]),getVal(maze->cells[i][j]),isVisited(maze->cells[i][j]));
//			}
//		}	
	return maze; 
}
void printMaze(MAZE *maze){
	int i = 0;
	int j = 0;
	int rowCount = 0;
	int counter = 0;
	printf("-");
	for(i = 0; i < maze->columns; i++){
		printf("----");
	}
	printf("\n");
	for(i = 0; i < maze->rows * 2; i++){
		for(j = 0; j < maze->columns; j++){
			if(counter > 1){
				rowCount++;
				counter = 0;
			}					
			if(counter == 0){
				if(j == 0 && rowCount == 0){
					printf(" ");
				}
				else if(j == 0)
					printf("|");
				printf(" ");
				if(getVal(maze->cells[rowCount][j]) > -1)
					printf("%d",getVal(maze->cells[rowCount][j]));
				else
					printf(" ");
				printf(" ");
				if(hasRight(maze->cells[rowCount][j]) == true)
					printf("|");
				else
					printf(" ");
			}
			if(counter == 1){
				if(j == 0)
					printf("-");
				if(hasBottom(maze->cells[rowCount][j]) == true)	
					printf("---");
				else
					printf("   ");
				printf("-");
			}
			if(j + 1 == maze->columns){
				printf("\n");
				counter++;
			}
		}		
	}
}
void solveMaze(MAZE *maze){
	QUEUE *queue = newQUEUE();
	CELL *v = NULL;
	enqueue(queue,maze->cells[0][0]);
	setValue(maze->cells[0][0],0);
	visit(maze->cells[0][0]);
	while(isVisited(maze->cells[maze->rows-1][maze->columns-1]) == true){	
		v = dequeue(queue);
		//top
		if(getRow(v)-1 >= 0 && isVisited(maze->cells[getRow(v)-1][getColumn(v)]) == true){
			if(hasBottom(maze->cells[getRow(v)-1][getColumn(v)]) == false){
				enqueue(queue,maze->cells[getRow(v)-1][getColumn(v)]);	
				visit(maze->cells[getRow(v)-1][getColumn(v)]);	
				setValue(maze->cells[getRow(v)-1][getColumn(v)],(getVal(v) + 1) % 10);
			}
		}
		//left
		if(getColumn(v)-1 >= 0 && isVisited(maze->cells[getRow(v)][getColumn(v)-1]) == true){
			if(hasRight(maze->cells[getRow(v)][getColumn(v)-1]) == false){
				enqueue(queue,maze->cells[getRow(v)][getColumn(v)-1]);	
				visit(maze->cells[getRow(v)][getColumn(v)-1]);	
				setValue(maze->cells[getRow(v)][getColumn(v)-1],(getVal(v) + 1) % 10);
			}
		}
		//right
		if(getColumn(v)+1 < maze->columns && isVisited(maze->cells[getRow(v)][getColumn(v)+1]) == true){
			if(hasRight(v) == false){
				enqueue(queue,maze->cells[getRow(v)][getColumn(v)+1]);	
				visit(maze->cells[getRow(v)][getColumn(v)+1]);	
				setValue(maze->cells[getRow(v)][getColumn(v)+1],(getVal(v) + 1) % 10);
			}
		}
		//bottom
		if(getRow(v)+1 < maze->rows && isVisited(maze->cells[getRow(v)+1][getColumn(v)]) == true){
			if(hasBottom(v) == false){
				enqueue(queue,maze->cells[getRow(v)+1][getColumn(v)]);	
				visit(maze->cells[getRow(v)+1][getColumn(v)]);	
				setValue(maze->cells[getRow(v)+1][getColumn(v)],(getVal(v) + 1) % 10);
			}		
		}
	}
	freeQUEUE(queue);
}
void freeMaze(MAZE *maze){
	int i = 0;
	int j = 0;
	for(i = 0; i < maze->rows;i++){
		for(j = 0; j < maze->columns;j++){
			freeCell(maze->cells[i][j]);
		}
		free(maze->cells[i]);
	}
	free(maze->cells);
	free(maze);
}
