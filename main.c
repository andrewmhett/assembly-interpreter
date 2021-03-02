#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "label.h"
#include "instructions.h"

char instructions[NUM_INSTRUCTIONS][4]={"mov","add","sub","mul","div","jmp","cmp","jlt","jgt","jet","jro","msg"};

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

int lookup_label_position(char* name, Label** labels){
	int position = -1;
	for (int i=0;i<50;i++){
		if (strcmp(labels[i]->name,name)==0){
			position = labels[i]->position;
			break;
		}
	}
	return position;
}

void interpret(const char* assembly_program){
	int* registers[26];
	Label* labels[50];
	//initialize all of the registers
	for (int i=0;i<26;i++){
		registers[i] = malloc(sizeof(int));
		move(0,registers[i]);
	}
	//initialize all of the label indices
	for (int i=0;i<50;i++){
		labels[i] = malloc(sizeof(Label));
		char* name = malloc(30);
		labels[i]->name=name;
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
			labels[num_labels]->name[strlen(lines[i])] = '\0';
			labels[num_labels]->position=i;
			num_labels++;
		}
	}
	int comparison_diff = 0;
	for (int i=0;i<program_length;i++){
		char* current_line = lines[i];
		int within_quotes = 0;
		if (current_line[strlen(current_line)-1] != ':' && current_line[0] != ';'){
			char segments[10][20];
			int num_segments = 0;
			int char_position = 0;
			int skip = 0;
			for (int o=0;o<strlen(current_line)+1;o++){
				skip = 0;
				if (current_line[o] == ' ' && !within_quotes){
					skip=1;
					segments[num_segments][char_position]='\0';
					num_segments++;
					char_position=0;
				}
				if (current_line[o] == '\"'){
					skip=1;
					within_quotes = !within_quotes;
				}
				if (!skip){
					segments[num_segments][char_position]=current_line[o];
					char_position++;
				}
			}
			num_segments++;
			if (!validate_instruction(segments[0])){
				break;
			}
			int first_value = 0;
			int second_value = 0;
			switch(lookup_instruction(segments[0])){
				case MOV:
					if (is_register_name(segments[1])){
						move(*lookup_reg(segments[1][0], registers),lookup_reg(segments[2][0], registers));
					}else{
						int value = atoi(segments[1]);
						move(value,lookup_reg(segments[2][0], registers));
					}
					break;
				case ADD:
					if (is_register_name(segments[1])){
						add(*lookup_reg(segments[1][0], registers),lookup_reg(segments[2][0], registers));
					}else{
						int value = atoi(segments[1]);
						add(value,lookup_reg(segments[2][0], registers));
					}
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
					if (is_register_name(segments[1])){
						first_value = *lookup_reg(segments[1][0], registers);
					}else{
						first_value = atoi(segments[1]);
					}
					if (is_register_name(segments[2])){
						second_value = *lookup_reg(segments[2][0], registers);
					}else{
						second_value = atoi(segments[2]);
					}
					comparison_diff = first_value - second_value;
					break;
				case JLT:
					if (comparison_diff<0){
						if (lookup_label_position(segments[1], labels) >= 0){
							i--;
							i=lookup_label_position(segments[1], labels);
						}
					}
					break;
				case JGT:
					if (comparison_diff>0){
						if (lookup_label_position(segments[1], labels) >= 0){
							i--;
							i=lookup_label_position(segments[1], labels);
						}
					}
					break;
				case JET:
					if (comparison_diff==0){
						if (lookup_label_position(segments[1], labels) >= 0){
							i--;
							i=lookup_label_position(segments[1], labels);
						}
					}
					break;
				case JRO:
					i--;
					i+=atoi(segments[1]);
					break;
				case MSG:
					for (int i=1;i<num_segments;i++){
						if (is_register_name(segments[i])){
							printf("%d",*lookup_reg(segments[i][0], registers));
						}else{
							printf("%s",segments[i]);
						}
					}
					printf("%c",'\n');
					break;
			}
		}
	}

	//free the memory allocated to the registers
	for (int i=0;i<26;i++){
		free(registers[i]);
	}
	//free the memory allocated to the labels
	for (int i=0;i<50;i++){
		free(labels[i]->name);
		free(labels[i]);
	}
}

int main(int c, const char* argv[]){
	char * assembly_input = 0;
	long length;
	if (c>0){
		FILE * f = fopen(argv[1], "rb");
		if (f){
			fseek(f,0,SEEK_END);
			length = ftell(f);
			fseek(f,0,SEEK_SET);
			assembly_input = malloc(length);
			if (assembly_input){
				fread(assembly_input, 1, length, f);
			}
			fclose(f);
			if (assembly_input){
				interpret(assembly_input);
			}
			free(assembly_input);
		}else{
			interpret(argv[1]);
		}
		return 0;
	}
	return -1;
}
