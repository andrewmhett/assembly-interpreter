#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "label.h"
#include "instructions.h"

char instructions[NUM_INSTRUCTIONS][4]={"mov","add","sub","mul","div","jmp","cmp","jlt","jgt","jet","msg"};

int validate_instruction(char* instruction){
	int valid = 0;
	for (int i=0;i<NUM_INSTRUCTIONS;i++){
		if (strcmp(instructions[i],instruction)==0){
			valid = 1;
		}
	}
	return valid;
}

int is_register_name(char* argument){
	int ret_bool = 0;
	if (strlen(argument)==1){
		if ((int)argument[0]>96 && (int)argument[0]<123){
			ret_bool=1;
		}
	}
	return ret_bool;
}

int* lookup_reg(char reg_name, int** registers){
	return registers[(int)reg_name-97];
}

char* interpret(char* assembly_program){
	char* output = malloc(100);
	//allocate memory for the registers
	int* registers[26];
	Label* labels[50];
	//initialize all of the registers
	for (int i=0;i<26;i++){
		registers[i] = malloc(sizeof(int));
		move(0,registers[i]);
	}
	printf("REGISTERS INITIALIZED\n");
	//initialize all of the label indices
	for (int i=0;i<50;i++){
		labels[i]=malloc(sizeof(Label));
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
	printf("%d LINE%s PARSED\n",program_length,(program_length != 1) ? "S" : "");
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
	printf("%d LABEL%s PARSED\n",num_labels,(num_labels != 1) ? "S" : "");
	for (int i=0;i<program_length;i++){
		char* current_line = lines[i];
		if (current_line[strlen(current_line)-1] != ':' && current_line[0] != ';'){
			char* segments[10];
			int segment = 0;
			int char_position = 0;
			for (int o=0;o<strlen(current_line);o++){
				if (current_line[o] == ' '){
					segments[segment][char_position]='\0';
					segment++;
					o++;
					char_position=0;
				}
				segments[segment][char_position]=current_line[o];
				char_position++;
			}
			if (!validate_instruction(segments[0])){
				exit(-1);
			}
			switch(lookup_instruction(segments[0])){
				case MOV:
					if (is_register_name(segments[1])){
						move(*lookup_reg(segments[1][0], registers),lookup_reg(segments[2][0], registers));
					}else{
						move((int)segments[1],lookup_reg(segments[2][0], registers));
					}
					break;
				case ADD:
					break;
				case SUB:
					break;
				case MUL:
					break;
				case DIV:
					break;
				case JMP:
					break;
				case CMP:
					break;
				case JLT:
					break;
				case JGT:
					break;
				case JET:
					break;
				case MSG:
					break;
			}
		}
	}

	//free the memory allocated to the labels
	for (int i=0;i<50;i++){
		free(labels[i]);
	}
	//free the memory allocated to the registers
	for (int i=0;i<26;i++){
		free(registers[i]);
	}
	return output;
}

int main(){
	//TODO: parse argv input and 
	//pass program as a const char*
	char* output = interpret("top:\nadd a 1\nadd b 2\nadd 3 c\nmsg a, b, c");
	printf("%s",output);
	free(output);
	return 0;
}
