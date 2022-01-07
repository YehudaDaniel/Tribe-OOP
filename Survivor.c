#define _CRT_SECURE_NO_WARNINGS

#include "Survivor.h"



//The function recieves an information for a new survivor and returns its data.
Survivor* CreateSurvivor(char* _name, float _age, int _followers) {
	
	//defining buff char with limit of 50 bytes
	char buff[50];
	//copying the name from the parameter into buff
	strcpy(buff, _name);
	//defining new survivor struct
	Survivor* survivor;
	//allocating memory for survivor and name and making sure it isnt null
	survivor = (Survivor*)malloc(sizeof(Survivor));
	if (survivor == NULL) return NULL;

	survivor->name = (char*)malloc(strlen(buff) + 1);
	if (survivor->name == NULL) {
		free(survivor->name);
		free(survivor);
		return NULL;
	}

	//copying the data from the parameters to the variables accordingly
	strcpy(survivor->name, _name);
	survivor->age = _age;
	survivor->followers = _followers;

	return survivor;
}

//The function recieves a pointer to survivor and returns a new identical survivor
//simply by calling the function CreateSurvivor
Survivor* DuplicateSurvivor(Survivor* source) {
	return CreateSurvivor(source->name, source->age, source->followers);
}

//------------------------- Free Memory functions -------------------------------//

void FreeSurvivor(Survivor* s) {
	free(s->name);
	free(s);
}