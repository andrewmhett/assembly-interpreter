#include "label.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LABELS 50

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
		char empty[50];
		labels[i]->name=empty;
		labels[i]->position=-1;
	}
	int program_length = 1;
	for (int i=0;i<strlen(assembly_program);i++){
		if (assembly_program[i]=='\n'){
			program_length++;
		}
	}
	char lines[program_length][50];
	int line = 0;
	int char_position = 0;
	for (int i=0;i<strlen(assembly_program);i++){
		if (assembly_program[i]=='\n'){
			lines[line][char_position]='\0';
			line++;
			char_position=0;
			i++;
		}
		lines[line][char_position] = assembly_program[i];
		char_position++;
	}

	int num_labels = 0;
	for (int i=0;i<program_length;i++){
		if (lines[i][strlen(lines[i])-1]==':'){
			for (int o=0;o<strlen(lines[i])-1;o++){
				labels[num_labels]->name[o]=lines[i][o];
			}
			labels[num_labels]->position=i;
			num_labels++;
		}
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
	interpret("top:\nadd a 1\nadd b 2\nadd 3 c\nmsg a, b, c");
	return 0;
}
