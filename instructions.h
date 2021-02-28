#pragma once

#include <string.h>

#define NUM_INSTRUCTIONS 11

enum Instruction {MOV,ADD,SUB,MUL,DIV,JMP,CMP,JLT,JGT,JET,MSG};

int lookup_instruction(char* instruction_name){
	int instruction = 0;
	switch (instruction_name[0]){
		case 'm':
			switch (instruction_name[1]){
				case 'o':
					instruction = MOV;
					break;
				case 's':
					instruction = MSG;
					break;
				case 'u':
					instruction = MUL;
					break;
			}
			break;
		case 'a':
			instruction = ADD;
			break;
		case 's':
			instruction = SUB;
			break;
		case 'd':
			instruction = DIV;
			break;
		case 'j':
			switch (instruction_name[1]){
				case 'm':
					instruction = JMP;
					break;
				case 'l':
					instruction = JLT;
					break;
				case 'g':
					instruction = JGT;
					break;
				case 'e':
					instruction = JET;
					break;
			}
			break;
		case 'c':
			instruction = CMP;
			break;
	}
	return instruction;
}

void move(int value, int* reg){
	*reg = value;
}

void add(int value, int* reg){
	*reg+=value;
}

void subtract(int value, int* reg){
	*reg-=value;
}

void divide(int value, int* reg){
	*reg/=value;
}

void multiply(int value, int* reg){
	*reg*=value;
}
