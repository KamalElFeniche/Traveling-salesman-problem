#include "tour.h"
#include "town.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Tour_t{
	TourPosition *start;
	TourPosition *end;
	int size;
};


struct TourPosition_t{ 
	Town *currentTown;
	TourPosition *next;
	int position; 
	// On considère que la première ville du tour est à la position 0.
};


Tour *createEmptyTour(void){

	Tour *emptyTour;
	emptyTour = malloc(sizeof(Tour));
	
	if (emptyTour == NULL)
		exit(-1);
	
	emptyTour -> start = NULL;
	emptyTour -> end = NULL;
	emptyTour -> size = 0;

	return emptyTour;
}


Tour *createTourFromFile(char *filename){
	if (filename == NULL)
		exit(-1);

	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
		exit(-1);

	int numberOfTown = 0;
	char buffer[1000];
	// Permettra de séparer une chaine de caractère lue dans le fichier.
	const char delimiter [2] = ","; 
	char *token;
	
	if (fgets(buffer, 1000, fp) == 0)
		exit(-1);

	numberOfTown ++;

	TourPosition *startPos;
	startPos = malloc(sizeof(TourPosition));
	if (startPos == NULL)
		exit(-1);

	startPos -> position = 0;
	startPos -> next = NULL;

	Tour *newTour = createEmptyTour();

	newTour -> start = startPos;
	newTour -> size = 1;
	
	token = strtok(buffer, delimiter);
	// token contient le nom de ville.
	const char *newTownName = token;

	token = strtok(NULL, delimiter);
	//token contient la coord. X de la ville.
	double newTownX = atof(token);

	token = strtok(NULL, delimiter);
	//token contient la coord. Y de la ville.
	double newTownY = atof(token);

	Town *newTown = createTown(newTownName, newTownX, newTownY);
	
	startPos -> currentTown = newTown;

	TourPosition *browser;
	browser = startPos; 


	while (fgets(buffer, 1000, fp)){ 
		numberOfTown ++;

		TourPosition *newPosition;
		newPosition = malloc(sizeof(TourPosition));
		if (newPosition == NULL)
			exit(-1);

		browser -> next = newPosition;

		newPosition -> position = numberOfTown - 1;

		token = strtok(buffer, delimiter);
		//token contient le nom de la ville.
		const char *newTownName = token = token;

		token = strtok(NULL, delimiter);
		//token contient la coord. X de la ville.
		double newTownX = atof(token);

		token = strtok(NULL, delimiter);
		//token contient la coord. Y de la ville.
		double newTownY = atof(token);

		Town *newTown = createTown(newTownName, newTownX, newTownY);
	
		newPosition -> currentTown = newTown;

		browser = newPosition;

	}

	newTour -> start = startPos;

	newTour -> end = browser;

	newTour -> end -> next = NULL;

	newTour -> size = numberOfTown;


	return newTour;
}


void freeTour(Tour *tour, int wantFreeTown){
	if (tour == NULL)
		exit(-1);

	if (wantFreeTown <= 0){
		TourPosition *destroyer;
		destroyer = tour -> start;

		while (destroyer != NULL){
			TourPosition *nDestroyer;
			nDestroyer = destroyer -> next;

			free(destroyer);

			destroyer = nDestroyer;
		}

		free(tour);

	}else{

		TourPosition *destroyer;
		destroyer = tour -> start;

		while (destroyer != NULL){
			TourPosition *nDestroyer;
			nDestroyer = destroyer -> next;

			freeTown(destroyer -> currentTown);

			free(destroyer);

			destroyer = nDestroyer;
		}

		free(tour);
	}	
}


void addTownAtTourEnd(Tour *tour, Town *town){
	if (tour == NULL)
		exit(-1);

	if (town == NULL)
		exit(-1);

	if (tour -> start == NULL){ // Il s'agit d'un tour vide !

		TourPosition *startPos = malloc(sizeof(TourPosition));
		if (startPos == NULL)
			exit(-1);

		startPos -> currentTown = town;
		startPos -> next = NULL;
		startPos -> position = 1;
		tour -> start = startPos;
		//Comme il ne contient qu'une seule ville, la position de départ est
		// également la position finale.
		tour -> end = startPos;
		tour -> size = 1;

	}else{

	TourPosition *endPosition;
	endPosition = malloc(sizeof(TourPosition));
	
		if (endPosition == NULL)
			exit(-1);

		endPosition -> currentTown = town;
		endPosition -> next = NULL;
	
		endPosition -> position = tour -> size;	
		tour -> end -> next = endPosition;
		tour -> end = endPosition;

		tour -> size = tour -> size + 1;

    }

	return;
}


void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town){
	if (tour == NULL)
		exit(-1);

	if (pos == NULL)
		exit(-1);

	if (town == NULL)
		exit(-1);

	if (pos -> next == NULL){ // Au cas où l'utilisateur se tromperait de fonction
		addTownAtTourEnd(tour, town);
		return;
	}

	TourPosition *positionToAdd;
	positionToAdd = malloc(sizeof(TourPosition));
	assert(positionToAdd != NULL);

	positionToAdd -> currentTown = town;
	positionToAdd -> position = pos -> position + 1;

	TourPosition *browser;
	browser = pos;
	

	positionToAdd -> next = browser -> next;
	browser -> next = positionToAdd;

	browser = positionToAdd -> next;

	while (browser != NULL){
		browser -> position = browser -> position + 1;
		browser = browser -> next;
	}

	tour -> size = tour -> size + 1; 
}


TourPosition *getTourStartPosition(Tour *tour){
	if (tour == NULL)
		exit(-1);

	return tour -> start;
}


TourPosition *getNextTourPosition(Tour *tour, TourPosition *pos){
	if (tour == NULL)
		exit(-1);
	
	if (pos == NULL)
		exit(-1);

	if (pos -> next == NULL)
		return NULL;

	return pos -> next;
}


Town *getTownAtPosition(Tour *tour, TourPosition *pos){
	if (tour == NULL)
		exit(-1);
	
	if (pos == NULL)
		exit(-1);

	return pos -> currentTown;
}


int getTourSize(Tour *tour){
	if (tour == NULL)
		exit (-1);

	return tour -> size;
}


double getTourLength(Tour *tour){
	if (tour == NULL)
		exit(-1);

	double tourLength = 0.0;
	double distanceToAdd = 0.0;

	TourPosition *browser = tour -> start;

	while (browser -> next != NULL){
		distanceToAdd = distanceBetweenTowns(browser -> currentTown, browser -> next -> currentTown);

		tourLength = tourLength + distanceToAdd;

		browser = browser -> next;
	}
	// A la fin du tour, on doit retourner à la ville de départ.
	distanceToAdd = distanceBetweenTowns(tour -> start -> currentTown, tour -> end -> currentTown);
	tourLength = tourLength + distanceToAdd;

	return tourLength;
}

