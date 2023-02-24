#include "tour.h"
#include "town.h"
#include "tsp.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


Tour *heuristic1(Tour *tour){

	if (tour == NULL)
    	exit(-1);

  Tour *newTour = createEmptyTour();
  TourPosition *pos = getTourStartPosition(tour);
  Town *firstTown = getTownAtPosition(tour, pos);
  addTownAtTourEnd(newTour, firstTown);

  double distance;
  double distanceMin;
  
  TourPosition *positionToKeep;
  TourPosition *pos2;
  
  Town *townToAdd;
  Town *townToCompare;

  pos = getNextTourPosition(tour, pos);
  townToAdd = getTownAtPosition(tour, pos);
  // On peut directement ajouter la deuxième ville dans le tour.
  addTownAtTourEnd(newTour, townToAdd);
  pos = getNextTourPosition(tour, pos);

  while (pos != NULL){
    //On fixe la position qui minimise la distance comme étant la première
    // position du newTour.
    townToAdd = getTownAtPosition(tour, pos);
    positionToKeep = getTourStartPosition(newTour);
    pos2 = positionToKeep;
    //On fixe la distance minimum comme étant celle de la première ville du
    //newTour à la ville à ajouter dans ce tour.
    distanceMin = distanceBetweenTowns(firstTown, townToAdd);

    while (pos2 != NULL){

      townToCompare = getTownAtPosition(newTour, pos2);
      distance = distanceBetweenTowns(townToCompare, townToAdd);

      if (distance < distanceMin){
        
        distanceMin = distance;
        positionToKeep = pos2;
      
      }

      pos2 = getNextTourPosition(newTour, pos2);
    }

    addTownAfterTourPosition(newTour, positionToKeep, townToAdd);
    
    pos = getNextTourPosition(tour, pos);
  }

  return newTour;

}




Tour *heuristic2(Tour *tour){
  if(tour == NULL)
    exit(-1);

  if (tour == NULL)
    exit(-1);

  Tour *newTour = createEmptyTour();
  TourPosition *pos = getTourStartPosition(tour);
  Town *firstTown = getTownAtPosition(tour, pos);
  addTownAtTourEnd(newTour, firstTown);

  double initialTourLength = 0.0;
  double TourLength = 0.0;
  double TourLengthMin= 0.0;
  double distanceToPrevious = 0.0;
  double distanceToNext = 0.0;
  double distanceNextToPrevious = 0.0;
  
  TourPosition *positionToKeep;
  TourPosition *pos2;
  
  Town *townToAdd;
  Town *nextTown; // Ville qui suit previousTown dans le newTour.
  Town *previousTown; // Ville dans le newTour après laquelle on veut ajouter townToAdd

  pos = getNextTourPosition(tour, pos);
  townToAdd = getTownAtPosition(tour, pos);
  // On peut directement ajouter la deuxième ville dans le tour.
  addTownAtTourEnd(newTour, townToAdd);
  pos = getNextTourPosition(tour, pos);

  while (pos != NULL){
    //On fixe la position qui minimise la longueur du tour comme étant la première
    // Et ensuite, on compare avec les positions suivantes dans la 2eme boucle.
    positionToKeep = getTourStartPosition(newTour);

    townToAdd = getTownAtPosition(tour, pos);
    previousTown = getTownAtPosition(newTour, positionToKeep);
    
    if (getNextTourPosition(tour, pos) == NULL)
      nextTown = getTownAtPosition(newTour, positionToKeep);
    else
      nextTown = getTownAtPosition(newTour, getNextTourPosition(newTour, positionToKeep));

    
    initialTourLength = getTourLength(newTour);
    distanceToPrevious = distanceBetweenTowns(townToAdd, previousTown);
    distanceToNext = distanceBetweenTowns(townToAdd, nextTown);
    distanceNextToPrevious = distanceBetweenTowns(nextTown, previousTown);
    // On fixe la longueur minimum quand la ville à ajouter est ajoutée juste 
    // après la première ville du newTour.
    TourLengthMin = initialTourLength + distanceToNext + distanceToPrevious;

    pos2 = positionToKeep;

    while (pos2 != NULL){
      
      previousTown = getTownAtPosition(newTour, pos2);
  
      if (getNextTourPosition(newTour, pos2) == NULL) 
    //Cela veut dire que c'était la dernière ville du tour, or à la fin du tour
    //On doit revenir à la ville de départ.
        nextTown = getTownAtPosition(newTour, getTourStartPosition(newTour));
      else
        nextTown = getTownAtPosition(newTour, getNextTourPosition(newTour,pos2));

       distanceToPrevious = distanceBetweenTowns(townToAdd, previousTown);
       distanceToNext = distanceBetweenTowns(townToAdd, nextTown);
       distanceNextToPrevious = distanceBetweenTowns(nextTown, previousTown);

       TourLength = initialTourLength + distanceToNext + distanceToPrevious - distanceNextToPrevious; 
      
      if(TourLength < TourLengthMin){
        
        TourLengthMin = TourLength;
        positionToKeep = pos2;
      
      }

      pos2 = getNextTourPosition(newTour, pos2);

    }

    addTownAfterTourPosition(newTour, positionToKeep, townToAdd);
   
    pos = getNextTourPosition(tour, pos);

  }



  return newTour;
} 