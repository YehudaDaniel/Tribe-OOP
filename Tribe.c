/*
	Name: Yehuda Daniel
	ID: 211789680
	Date: 07/01/22
*/
#define _CRT_SECURE_NO_WARNINGS

#include "Tribe.h"
#include "Survivor.h"


//The function checks if a survivor exists in the tribe and adds a new one in case not.
Tribe* AddSurvivor(Tribe* tribe, Survivor* survivor) {
	//in case the tribe doesnt exist, make a default "Colman" tribe.
	if (tribe == NULL) {
		//Defining buff char with limit of 100 bytes
		char buff[100];
		//Copying the name "Colman" into buff
		strcpy(buff, "Colman");
		//Defining a new struct
		Tribe* tribeStruct;
		//Allocating memory for tribe and name and making sure it isnt null
		tribeStruct = (Tribe*)malloc(strlen(buff) + 1);
		if (tribeStruct == NULL) return NULL;

		tribeStruct->name = (char*)malloc(strlen(buff) + 1);
		if (tribeStruct->name == NULL) {
			free(tribeStruct->name);
			free(tribeStruct);
			return NULL;
		}

		//copying the data from the parameters to the variables accordingly
		strcpy(tribeStruct->name, buff);
		tribeStruct->num_of_survivors = 1;
		tribeStruct->survivors = (Survivor**)malloc(sizeof(Survivor*)); // TODO: consider changing to calloc
		if (tribeStruct->survivors == NULL) return NULL;
		tribeStruct->survivors[0] = CreateSurvivor(survivor->name, survivor->age, survivor->followers);

		//returning the tribe
		return tribeStruct;
	}else {//in case the tribe exists
		for (int i = 0; i < tribe->num_of_survivors -1; i++) {
			//checks if a survivor already exists in the tribe, and creates a new one
			//in case not.
			if (strcmp(tribe->survivors[i]->name, survivor->name) == 0) {
				tribe->survivors[i]->followers = survivor->followers;
				return tribe;
			}
		}
		//reallocating more memory in order to add a new survivor to the list of survivor
		//in the tribe.
		tribe->survivors = (Survivor**)realloc((Survivor*)tribe->survivors, sizeof(Survivor*) + 1);
		if (tribe->survivors == NULL) {
			free(tribe->survivors);
			return NULL;
		}
		//adding a new survivor to the tribes survivors list.
		tribe->survivors[tribe->num_of_survivors] = CreateSurvivor(survivor->name, survivor->age, survivor->followers);
		tribe->num_of_survivors++;
		
		return tribe;
	}
}

//The function recieves a data of an existing tribe(source) and duplicates its data
//to a new tribe
Tribe* DuplicateTribe(Tribe* source) {

	//defining buff char with limit of 100 bytes
	char buff[100], buff2[100];
	//copying the name from the parameter into buff
	strcpy(buff, source->name);
	//defining new tribe struct
	Tribe* tribe;
	//allocating memory for tribe and name and making sure it isnt null
	tribe = (Tribe*)malloc(sizeof(Tribe));
	if (tribe == NULL) {
		free(tribe);
		return NULL;
	}
	tribe->name = (char*)malloc(strlen(buff) + 1);
	if (tribe->name == NULL) {
		free(tribe->name);
		return NULL;
	}

	//copying the data from the parameters to the variables accordingly
	strcpy(tribe->name, buff);
	tribe->num_of_survivors = source->num_of_survivors;

	//allocating memory for the new array of survivors
	tribe->survivors = (Survivor**)malloc(sizeof(Survivor*) * source->num_of_survivors); //TODO: consider changing to calloc
	if (tribe->survivors == NULL) {
		free(tribe->survivors);
		return NULL;
	}
	//copying the array of survivors
	for (int i = 0; i < source->num_of_survivors; i++) {
		//Allocating memory for each survivor in the array in order to contain
		//the content of the survivor
		//In case the allocation failed, free the location and return NULL
		tribe->survivors[i] = DuplicateSurvivor(source->survivors[i]);
		//copying the name of the survivor into buff2 ^^^
	}
	return tribe;
}



//------------------------- Sorting functions -------------------------------//
//The function sorts the survivors in the tribe by age ascendingly
void SortByAge(Tribe* t) {
	int i, j;

	for (i = 0; i < t->num_of_survivors - 1; i++) {
		for(j = 0; j < t->num_of_survivors - i - 1; j++) {
			if (t->survivors[j]->age > t->survivors[j + 1]->age) {
				Survivor** temp = t->survivors[j];
				t->survivors[j] = t->survivors[j + 1];
				t->survivors[j + 1] = temp;
			}
		}
	}
}

//The function sorts the survivors by lexicographical order
void SortByName(Tribe* t) {
	int i, j;

	for (i = 0; i < t->num_of_survivors - 1; i++) {
		for (j = 0; j < t->num_of_survivors - i - 1; j++) {
			if (strcmp(t->survivors[j]->name, t->survivors[j + 1]->name) > 0) {
				Survivor** temp = t->survivors[j];
				t->survivors[j] = t->survivors[j + 1];
				t->survivors[j + 1] = temp;
			}
		}
	}
}

//----------------------------------------------------------------//

//------------------------- Updating functions -------------------------------//

//The function sums up and returns all the followers of all the survivors in the tribe
int TotalFollowers(Tribe* t) {
	int i, sum = 0;

	for (i = 0; i < t->num_of_survivors; i++) {
		sum += t->survivors[i]->followers;
	}
	return sum;
}

//The function searches by name and updates the amount of followers of a specific survivor
int UpdateFollowers(Tribe* t, char* name, int toAdd) {
	int i, flag = 0;

	for (i = 0; i < t->num_of_survivors; i++) {
		if (strcmp(t->survivors[i]->name, name) == 0) {
			t->survivors[i]->followers += toAdd;
			flag = 1;
		}
	}

	return flag;
}

//The function searches by name and updates the age of a specific survivor
int UpdateAge(Tribe* t, char* name, float newAge) {
	int i, flag = 0;

	for (i = 0; i < t->num_of_survivors; i++) {
		if (strcmp(t->survivors[i]->name, name) == 0) {
			t->survivors[i]->age = newAge;
			flag = 1;
		}
	}

	return flag;
}

//----------------------------------------------------------------//

//------------------------- Get functions -------------------------------//

//The function 
int GetSurvivorFollowers(Tribe* t, char* name) {
	int i, flag, numOfFollowers;
	flag = numOfFollowers = 0;

	for (i = 0; i < t->num_of_survivors; i++) {
		if (strcmp(t->survivors[i]->name, name) == 0) {
			numOfFollowers = t->survivors[i]->followers;
			flag = 1;
		}
	}

	return (flag ? numOfFollowers : -1);
}

//------------------------- Free Memory functions -------------------------------//

void FreeTribe(Tribe* t) {
	int i;

	for (i = 0; i < t->num_of_survivors; i++) {
		FreeSurvivor(t->survivors[i]);
	}
	free(t->survivors);
	free(t);
}