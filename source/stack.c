#include "stack.h"
#include "da.h"
#include <stdlib.h>
typedef struct stack{
	DA *dynamicArray;
	int debugFlag;
	void(*displayMethod)(void *,FILE *);
	void(*freeMethod)(void *);	
}STACK;

STACK *newSTACK(void){
	STACK *newStack = malloc(sizeof(STACK));
	newStack->displayMethod = NULL;
	newStack->freeMethod = NULL;
	newStack->dynamicArray = newDA();
	newStack->debugFlag = 0;
	return newStack;
}
void  setSTACKdisplay(STACK *items,void (*d)(void *v,FILE *f)){
	items->displayMethod = d;
	setDAdisplay(items->dynamicArray,d);
	return;
}
void  setSTACKfree(STACK *items,void (*f)(void *v)){
	items->freeMethod = f;
	setDAfree(items->dynamicArray,f);
	return;
}
void  push(STACK *items,void *value){
	insertDAback(items->dynamicArray,value);	
	return;
}
void *pop(STACK *items){
	return removeDAback(items->dynamicArray);
}
void *peekSTACK(STACK *items){
	return getDA(items->dynamicArray,sizeDA(items->dynamicArray)-1);
}
void  displaySTACK(STACK *items,FILE *fp){
	if(items->debugFlag == 0){
		fprintf(fp,"|");
		for(int i = sizeDA(items->dynamicArray) - 1; i >= 0; i--){
			if(i < sizeDA(items->dynamicArray) - 1 && i > -1)
				fprintf(fp,",");
			if(items->displayMethod == NULL)
				fprintf(fp,"@%p",getDA(items->dynamicArray,i));
			else
				items->displayMethod(getDA(items->dynamicArray,i),fp);
		}	
		fprintf(fp,"|");
	}
	else if(items->debugFlag == 1){
		debugDA(items->dynamicArray,0);
		displayDA(items->dynamicArray,fp);
	}
	else if(items->debugFlag == 2){
		debugDA(items->dynamicArray,1);
		displayDA(items->dynamicArray,fp);
	}
}
int   debugSTACK(STACK *items,int level){
	int prev = items->debugFlag;
	items->debugFlag = level;
	return prev;
}
void  freeSTACK(STACK *items){
	freeDA(items->dynamicArray);
	free(items);
}
int   sizeSTACK(STACK *items){
	return sizeDA(items->dynamicArray);
}
