#include "register.h"
#include <stdlib.h>

int interpret(const char* assembly_program){
	struct Register* reg_array[26];
	//initialize all of the registers
	for (int i=0;i<26;i++){
		reg_array[i]=malloc(sizeof(struct Register));
		reg_array[i]->key=(char)(i+97);
		reg_array[i]->value=0;
	}

	//TODO: interpret instructions and operands
	//and run program

	//free the memory allocated to the registers
	for (int i=0;i<26;i++){
		free(reg_array[i]);
	}
	return 0;
}

int main(){
	//TODO: parse argv input and 
	//pass program as a const char*
	interpret("");
	return 0;
}
