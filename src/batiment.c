#include <stdlib.h>
#include <stdio.h>

#include "batiment.h"
#include "planete.h"


/*1 pour une planete, 2 pour une planete ennemie, 3 pour une flotte, 4 pour une flotte ennemie, 5 pour la création d'unités sur une planète*/
void validation_creer_batiment_quartier_general(Planete *une_planete)
{
	if((une_planete->batiment_nb_tour_restant == 0) && (une_planete->batiment_en_cours == 0))
	{
		une_planete->batiment[0]++;
		une_planete->taille_utilisee++;
	}
}
void creer_batiment_quartier_general(Planete *une_planete)
{
	une_planete->batiment_en_cours = 0;
	une_planete->batiment_nb_tour_restant = NB_TOUR_BATIMENT_QUARTIER_GENERAL;
}

void validation_creer_batiment_metal(Planete *une_planete)
{
    if((une_planete->batiment_nb_tour_restant == 0) && (une_planete->batiment_en_cours == 1))
    {
        une_planete->batiment[1]++;
        une_planete->metal += 100;
		une_planete->taille_utilisee++;
    }
}
void creer_batiment_metal(Planete *une_planete)
{
	une_planete->batiment_en_cours = 1;
	une_planete->batiment_nb_tour_restant = NB_TOUR_BATIMENT_METAL;
}

void validation_creer_batiment_argent(Planete *une_planete)
{
	if((une_planete->batiment_nb_tour_restant == 0) && (une_planete->batiment_en_cours == 2))
	{
		une_planete->batiment[2]++;
		une_planete->argent += 100;
		une_planete->taille_utilisee++;
	}
}
void creer_batiment_argent(Planete *une_planete)
{
	une_planete->batiment_en_cours = 2;
	une_planete->batiment_nb_tour_restant = NB_TOUR_BATIMENT_ARGENT;
}

void validation_creer_batiment_carburant(Planete *une_planete)
{
	if((une_planete->batiment_nb_tour_restant == 0) && (une_planete->batiment_en_cours == 3))
	{
		une_planete->batiment[3]++;
		une_planete->carburant += 100;
		une_planete->taille_utilisee++;
	}
}
void creer_batiment_carburant(Planete *une_planete)
{
	une_planete->batiment_en_cours = 3;
	une_planete->batiment_nb_tour_restant = NB_TOUR_BATIMENT_CARBURANT;
}

void validation_creer_batiment_population(Planete *une_planete)
{
	if((une_planete->batiment_nb_tour_restant == 0) && (une_planete->batiment_en_cours == 4))
	{
		une_planete->batiment[4]++;
		une_planete->population += 100;
		une_planete->taille_utilisee++;
	}
}
void creer_batiment_population(Planete *une_planete)
{
	une_planete->batiment_en_cours = 4;
	une_planete->batiment_nb_tour_restant = NB_TOUR_BATIMENT_POPULATION;
}

void validation_creer_batiment_spatioport(Planete *une_planete)
{
	if((une_planete->batiment_nb_tour_restant == 0) && (une_planete->batiment_en_cours == 4))
	{
		une_planete->batiment[5]++;
		une_planete->taille_utilisee++;
	}
}
void creer_batiment_spatioport(Planete *une_planete)
{
	une_planete->batiment_en_cours = 5;
	une_planete->batiment_nb_tour_restant = NB_TOUR_BATIMENT_SPATIOPORT;
}