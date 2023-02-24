#include "town.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct Town_t{
	char *name;
	double x;
	double y;
};

Town *createTown(const char *name, double x, double y){
	if (name == NULL)
		exit(-1);

	Town *newTown; 
	newTown = malloc(sizeof(Town));
	
	if (newTown == NULL)
		exit(-1);
	
	int stringLength = strlen(name);
	if (stringLength == 0)
		exit(-1);

	char *nameToCopy = malloc((stringLength + 1) * sizeof(char));
	if (nameToCopy == NULL)
		exit(-1);

	nameToCopy = strcpy(nameToCopy, name);
	
	newTown -> name = nameToCopy;
	newTown -> x = x;
	newTown -> y = y;

	return newTown;
}


double getTownX(Town *town){
	if (town == NULL)
		exit(-1);

	return town -> x;
}


double getTownY(Town *town){
	if (town == NULL)
		exit(-1);

	return town -> y;
}


const char *getTownName(Town *town){
	if (town == NULL)
		exit(-1);

	return town -> name;
}


double distanceBetweenTowns(Town *town1, Town *town2){
	if (town1 == NULL)
		exit(-1);

	if (town2 == NULL)
		exit(-1);

	return sqrt( (town1 -> x - town2 -> x) * (town1 -> x - town2 -> x) + (town1 -> y - town2 -> y) * (town1 -> y - town2 -> y) );
}


void freeTown(Town *town){
	if (town == NULL)
		exit(-1);

	if (town -> name == NULL)
		exit(-1);

	free(town -> name);
	free(town);	
}
