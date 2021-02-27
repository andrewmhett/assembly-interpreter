#include "label.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_LABELS 50

int number_of_labels(struct Label** label_array){
	int size=0;
	for (size=0;size<MAX_LABELS;size++){
		if (label_array[size]->line==-1){
			break;
		}
	}
	return size;
}

char* interpret(const char* assembly_program){
	int registers[26];
	struct Label* labels[MAX_LABELS];
	//initialize all of the registers
	for (int i=0;i<26;i++){
		registers[i]=0;
	}
	//initialize all of the label indices
	for (int i=0;i<50;i++){
		labels[i]=malloc(sizeof(struct Label));
		labels[i]->name="";
		labels[i]->line=-1;
	}

	//TODO: interpret instructions and operands
	//and run program

	//free the memory allocated to the labels
	for (int i=0;i<50;i++){
		free(labels[i]);
	}
	return 0;
}

int main(){
	//TODO: parse argv input and 
	//pass program as a const char*
	interpret("exit");
	return 0;
}
