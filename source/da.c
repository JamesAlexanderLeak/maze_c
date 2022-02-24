#include "da.h"
#include <assert.h>
#include <stdlib.h>
typedef struct da{
void **data;
int totalSize, numItems, debugFlag;
void(*displayMethod)(void *,FILE *);
void(*freeMethod)(void *);
}DA;

void doubleSize(DA *items){
	if(items->data == NULL){
		items->data = (void**)malloc(sizeof(void*) * items->totalSize);
		for(int i = 0; i < items->totalSize;i++)
			items->data[i] = NULL;
		return;
	}
	else{
	items->totalSize *= 2;
	items->data = (void**)realloc(items->data,sizeof(void*) * items->totalSize);
	}
}
void halfSize(DA *items){
	items->totalSize /= 2;
	items->data = (void**)realloc(items->data,sizeof(void*) * items->totalSize);	
}
DA *newDA(void){
	DA *newDA;
	newDA = (DA *)malloc(sizeof(DA));
	newDA->data = NULL;
	newDA->totalSize = 1;
	newDA->numItems = 0;
	newDA->debugFlag = 0;
	newDA->displayMethod = NULL;
	newDA->freeMethod = NULL;
	doubleSize(newDA);
	return newDA;
}
void setDAdisplay(DA *items,void (*d)(void *v,FILE *f)){
	items->displayMethod = d;
}
void setDAfree(DA *items,void (*f)(void *)){
	items->freeMethod = f;
}	
void insertDA(DA *items,int index,void *value){
	assert(index > -1 && index <= items->totalSize);
	if(index == items->totalSize || items->numItems == items->totalSize)
		doubleSize(items);
	if(index < items->numItems){
		void *temp, *prevVal;
		prevVal = items->data[index];
		items->data[index] = value;
		for(int i = index+1; i <= items->numItems; i++){
			temp = items->data[i];
			items->data[i] = prevVal;
			prevVal = temp;
		}
	}
	else{
		items->data[index] = value;
	}
	items->numItems++;
}
void *removeDA(DA *items, int index){
	assert(index > -1 && items->totalSize);
	void* removedVal = items->data[index];
	items->numItems--;
	for(int i = index; i < items->numItems; i++){
		items->data[i] = items->data[i+1];
	}
	while((double)((double)items->numItems/(double)items->totalSize) < 0.25 && items->totalSize > 1)
		halfSize(items);
	return removedVal;
}
void unionDA(DA *recipient, DA *donor){
	int bothTotals = donor->numItems + recipient->numItems;
	while(recipient->totalSize < bothTotals)
		doubleSize(recipient);
	for(int i = 0;i < donor->numItems; i++){
//		recipient->data[recipient->numItems] = donor->data[i];
		insertDAback(recipient,removeDA(donor,0));
	}
}
void *getDA(DA *items,int index){
	assert(index >= 0 && index < items->totalSize);
	return items->data[index];
}
void *setDA(DA *items,int index,void *value){
	assert(index>=0 && index <= items->numItems);
	void *prevVal = NULL;
	if(index == items->numItems){
		insertDA(items,index,value);
	}
	else if(index > items->numItems || index < 0)
		return NULL;
	else{
		prevVal = items->data[index];
		items->data[index] = value;
		return prevVal;
	}
	return NULL;
}
int sizeDA(DA *items){
	return items->numItems;
}
void displayDA(DA *items,FILE *fp){
	fprintf(fp,"[");
	if(items->debugFlag > 0){
		for(int i = 0;i<items->numItems;i++){
			if(i>0 && i!= items->numItems)
			fprintf(fp,",");
			if(items->displayMethod == NULL)
				fprintf(fp,"@%p",items->data[i]);
			else
				items->displayMethod(items->data[i],fp);	
		}
		if(items->numItems > 0){
			fprintf(fp,",");
		}
		fprintf(fp,"[");
		fprintf(fp,"%d",items->totalSize - items->numItems);
		fprintf(fp,"]");
	}
	else{
		for(int i = 0;i<items->numItems;i++){
			if(i>0 && i!=items->numItems)
				fprintf(fp,",");
			if(items->displayMethod == NULL)
				fprintf(fp,"@%p",items->data[i]);
			else
				items->displayMethod(items->data[i],fp);
		}
	}
	fprintf(fp,"]");
}	
int debugDA(DA *items,int level){
	int previousVal = items->debugFlag;
	items->debugFlag = level;
	return previousVal;
}
void freeDA(DA *items){
	assert(items!=NULL);
	for(int i = 0; i < items->numItems;i++){
		if(items->freeMethod != NULL)
			items->freeMethod(items->data[i]);
	}
	free(items->data);
	free(items);
}
