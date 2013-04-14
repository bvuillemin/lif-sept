#include <stdlib.h>
#include <stdio.h>

#include "batiment.h"
#include "planete.h"


void validation_creer_batiment_metal(Planete *une_planete)
{
    if((une_planete->batiment_nb_tour_restant == 0) && (une_planete->batiment_en_cours == 1))
    {
        une_planete->batiment[1]++;
        une_planete->metal += 100;
    }
}

void validation_creer_batiment_quartier_general(Planete *une_planete)
{
    if((une_planete->batiment_nb_tour_restant == 0) && (une_planete->batiment_en_cours == 0))
    {
        une_planete->batiment[0]++;
    }
}

void creer_batiment_quartier_general(Planete *une_planete)
{
    une_planete->batiment_en_cours = 0;
    une_planete->batiment_nb_tour_restant = NB_TOUR_BATIMENT_QUARTIER_GENERAL;
}

void creer_batiment_metal(Planete *une_planete)
{
    une_planete->batiment_en_cours = 1;
    une_planete->batiment_nb_tour_restant = NB_TOUR_BATIMENT_METAL;
}
