#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "maze.h"
#include "cell.h"
long int random(void);
void srandom(unsigned int seed);
int main(int argc,char **argv){
	if(argc == 1){
		printf("No arguments given, EXITING PROGRAM\n");
		return -1;
	}
	FILE *fp;
	MAZE *maze = NULL;
	int n = 1;
	int solvedBool = 0;
	char *mazeToSolveFile = NULL;
	char *solvedMazeFile = NULL;
	char *drawFile = NULL;
	char *createdMazeFile = NULL;
	int rowsInput = 1;
	int columnsInput = 1;
	int argsUsed = 0;
	int seed = 1;
	while(n < argc && *argv[n] == '-'){	
		argsUsed = 0;
		if(argv[n][1] == '\0'){
			printf("invalid argument, EXITING PROGRAM\n");
			return -1;
		}	
		if(argv[n][2] != '\0'){			 
			printf("invalid argument, EXITING PROGRAM\n");
			return -1;
		}	
		switch(argv[n][1]){
			case 'v':
				printf("Written by James Leak\n");
				return 0;
				break;				
			case 'c':
				rowsInput = atoi(argv[n+1]);
				columnsInput = atoi(argv[n+2]);
				createdMazeFile = argv[n+3];
				argsUsed = 4;
				break;
			case 's':
				mazeToSolveFile = argv[n+1];
				solvedMazeFile = argv[n+2];
				argsUsed = 3;
				break;
			case 'r':
				seed = atoi(argv[n+1]);
				argsUsed = 2;
				break;
			case 'd':
				drawFile = argv[n+1];
				argsUsed = 2;
				break;
					
		}
		if(argsUsed > 0){
		n += argsUsed;
		}
		else
			n++;
	}		
	if(createdMazeFile != NULL){
		fp = fopen(createdMazeFile,"w");
		if(fp != NULL)
		fprintf(fp,"%d %d %d %d",rowsInput,columnsInput,seed,0);
	//	fwrite(&maze,sizeof(MAZE),1,fp);
		fclose(fp);
//		freeMaze(maze);
		}
	if(mazeToSolveFile != NULL){
		fp = fopen(mazeToSolveFile,"r");	
		if(fp != NULL){
	//	fread(&temp,sizeof(MAZE),1,fp);
		fscanf(fp,"%d %d %d",&rowsInput,&columnsInput,&seed);	
		fclose(fp);
		}
		fp = fopen(solvedMazeFile,"w");
		if(fp != NULL){
		fprintf(fp,"%d %d %d %d",rowsInput,columnsInput,seed,1);
	//	fwrite(&temp,sizeof(MAZE),1,fp);
		fclose(fp);
		}	
//		freeMaze(temp);
	}
	if(drawFile != NULL){	
		fp = fopen(drawFile,"r");	
		if(fp != NULL){
		fscanf(fp,"%d %d %d %d",&rowsInput,&columnsInput,&seed,&solvedBool);
	//	fread(&temp,sizeof(MAZE),1,fp);
		srandom(seed);
		maze = createMaze(rowsInput,columnsInput);
		if(solvedBool == 1){
			solveMaze(maze);
		}	
		printMaze(maze);	
		fclose(fp);
		freeMaze(maze);
		}
	}
}
