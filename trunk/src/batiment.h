#ifndef _BATIMENT_H_
#define _BATIMENT_H_

#include <stdlib.h>
#include <stdio.h>

#include "planete.h"

#define NB_TOUR_BATIMENT_QUARTIER_GENERAL 1
#define NB_TOUR_BATIMENT_METAL 1


void validation_creer_batiment_metal(Planete *une_planete);
void validation_creer_batiment_quartier_general(Planete *une_planete);
void creer_batiment_quartier_general(Planete *une_planete);
void creer_batiment_metal(Planete *une_planete);


#endif
