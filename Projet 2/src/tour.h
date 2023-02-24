#ifndef TOUR_H_
#define TOUR_H_
#include "town.h"

typedef struct Tour_t Tour;


typedef struct TourPosition_t TourPosition;

/* createTourFromFile: fonction qui crée un tour à partir d'un fichier contenant
       des villes enocdée selon l'odre suivant: nom, coord.X, coord. Y.

       INPUTS: -> filename : un pointeur valide vers une chaine de caractère qui contient
        le nom du fichier.

       OUTPUTS: Un pointeur vers un Tour organisé selon l'ordre du fichier.
*/
Tour *createTourFromFile(char *filename);


/* createEmptyTour: foncion qui crée un tour vide.
		
		INPUTS: /

		OUTPUTS: Un pointeur vers un tour vide.
*/
Tour *createEmptyTour(void);


/* freeTour: fonction qui libère la mémoire occupée par le tour tour.
		
		INPUTS: -> tour : un pointeur valide vers le tour dont on veut libérer la
				mémoire.
				-> wantFreeTown: Un entier indiquant si on veut aussi libérer les
				villes contenues dans le tour. Si wantFreeTown est supérieur à 0
				les villes seront libéreées. Sinon, elles ne le seront pas.

		OUTPUTS: /
*/
void freeTour(Tour *tour, int wantFreeTown);


/* addTownAtTourEnd : fonction qui ajoute la ville pointée par town à la fin du
	tour tour.

		INPUTS: -> tour : un pointeur valide vers le tour dont on veut ajouter à la fin
				la ville pointée par town.
				-> town : un pointeur valide vers la ville que l'on veut rajouter à la fin
				du tour tour.

		OUTPUTS: town a été ajouté à la fin du tour tour.
*/
void addTownAtTourEnd(Tour *tour, Town *town);


/* addTownAfterTourPosition : fonction qui ajoute la ville town après le
	tourPosition pos, dans le tour tour.

		INPUTS: -> tour : un pointeur valide vers le tour dont on veut rajouter 
				la ville.
				-> pos : un pointeur valide vers le tourPosition après lequel
				on veut rajouter la ville.
				-> town : un pointeur valide vers la ville que l'on veut rajouter
				dans le tour tour juste après le tourPosition pos.

		OUPUTS: la ville pointée par town a été ajoutée dans le tour tour juste après
		le tourPosition pos.
*/
void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town);


/* getTourStartPosition : fonction qui renvoie la première position du tour.

		INPUTS: -> tour : un pointeur valide vers le tour dont on veut avoir la
		première position.

		OUPUTS: un pointeur vers la première position du tour tour.

*/
TourPosition *getTourStartPosition(Tour *tour);


/* getNextTourPosition : fonction qui renvoie la position qui suit la position pos.

		INPUTS: -> tour : pointeur valide vers le tour contenant la position pos.
				-> pos : pointeur valide vers la position dont on veut connaitre 
				la position suivante.

		OUPUTS: un pointeur vers la position qui suit la position pos ou un
				pointeur NULL si pos est la dernière position du tour.
*/
TourPosition *getNextTourPosition(Tour *tour, TourPosition *pos);


/* getTownAtPosition : fonction qui renvoie la ville à la position pos.
		
		INPUTS: -> tour : un pointeur valide vers le tour contenant la position
				pos.
				-> pos : un pointeur valide vers la position qui contient la ville.

		OUTPUTS: un pointeur vers la ville contenue à la position pos dans
		le tour tour.
*/
Town *getTownAtPosition(Tour *tour, TourPosition *pos);


/* getTourSize : fonction qui renvoie le nombre de villes contenues dans le tour.

		INPUTS: -> tour : un pointeur valide vers le tour dont on veut connaitre
				le nombre de villes.

		OUTPUTS: le nombre de villes contenues dans le tour tour. 
*/
int getTourSize(Tour *tour);


/* getTourLength : fonction qui renvoie la longueur du tour.

		INPUTS: -> tour : un pointeur valide vers le tour dont on veut connaitre
		la longueur.

		OUTPUTS: la longueur du tour tour.
*/
double getTourLength(Tour *tour);


#endif