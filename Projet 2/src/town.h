#ifndef TOWN_H_
#define TOWN_H_

typedef struct Town_t Town;

/* createTown : crée une ville caractèrisée par les arguments donnée en entrée.

    INPUTS : -> char name , un chaine de caractère valide qui contient le nom
             de la ville.
            -> x et y les coordonées des la ville.

    OUTPUTS : -> un pointeur valide vers une ville .
  */
Town *createTown(const char *name, double x, double y);


/* getTownName : renvoie le nom de la ville pointée par town.
    INPUTS : -> town un pointeur valide vers une ville.

    OUTPUTS : -> le nom de la ville town.
*/
const char *getTownName(Town *town);

/* getTownY :renvoie la coordonée y de la ville pointée par town.
      INPUT: -> town un pointeur valide vers une ville.

      OUTPUTS : -> la coordonée y de la ville.
*/
double getTownY(Town *town);

/* getTownX : renvoie la coordonée x de la ville pointée par town.
      INPUT: -> town un pointeur valide vers une ville.

      OUTPUTS : -> la coordonée x de la ville.
*/
double getTownX(Town *town);

/* distanceBetweenTowns : renvoie la distance euclidienne séparant les villes
  town1 et town2.

      INPUTS: -> town1 et town2 deux pointeurs valides vers deux villes.

      OUTPUTS : -> la distance euclidienne entre les deux villes calculée sur
                base de leurs coordonées x et y respective.
*/
double distanceBetweenTowns(Town *town1, Town *town2);

/* freeTown : libère la mémoire occupée par par la ville town.

    INPUTS : -> town un pointeur valide vers une ville.

    OUTPUTS : /
*/
void freeTown(Town *town);



#endif
