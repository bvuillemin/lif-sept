#ifndef _BATIMENT_H_
#define _BATIMENT_H_

#include "planete.h"

#define NB_TOUR_BATIMENT_QUARTIER_GENERAL 1
#define NB_TOUR_BATIMENT_METAL 1
#define NB_TOUR_BATIMENT_ARGENT 1
#define NB_TOUR_BATIMENT_CARBURANT 1
#define NB_TOUR_BATIMENT_POPULATION 1
#define NB_TOUR_BATIMENT_SPATIOPORT 2

void validation_creer_batiment_quartier_general(Planete *une_planete);
void creer_batiment_quartier_general(Planete *une_planete);

void validation_creer_batiment_metal(Planete *une_planete);
void creer_batiment_metal(Planete *une_planete);

void validation_creer_batiment_argent(Planete *une_planete);
void creer_batiment_argent(Planete *une_planete);

void validation_creer_batiment_carburant(Planete *une_planete);
void creer_batiment_carburant(Planete *une_planete);

void validation_creer_batiment_population(Planete *une_planete);
void creer_batiment_population(Planete *une_planete);

void validation_creer_batiment_spatioport(Planete *une_planete);
void creer_batiment_spatioport(Planete *une_planete);

#endif
