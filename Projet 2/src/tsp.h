#ifndef _TSP_H_
#define _TSP_H_
#include "tour.h"
#include "town.h"

/* heuristic1 : fonction qui renvoie un nouveau tour qui contient l'ensemble
 des villes ordonnées grâce à la première heuristique.

 		INPUTS: -> tour : un pointeur valide vers un tour

 		OUTPUTS: le nouveau tour ordonné selon le premier heuristique.
*/
Tour *heuristic1(Tour *tour);


/* heuristic2 : fonction qui renvoie un nouveau tour qui contient l'ensemble
 des villes ordonnées grâce à la seconde heuristique.

 		INPUTS: -> tour : un pointeur valide vers un tour

 		OUTPUTS: le nouveau tour ordonné selon la seconde heuristique.
*/
Tour *heuristic2(Tour *tour);



#endif
