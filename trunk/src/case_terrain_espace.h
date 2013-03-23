#ifndef _CASE_TERRAIN_H_
#define _CASE_TERRAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "planete.h"


/**
 * \file      Module case_terrain_espace
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Case du Terrain_espace et ses particularités
 *
 * \details
 */

typedef struct
{
    int x_espace,y_espace;
    char type_case_terrain_espace;/* E pour l'espace, P pour une planète, N si non initialisé*/
    bool presence_flotte;
	Planete *planete;/*lien sur une planète si la case est de type planète, sinon NULL*/
}Case_terrain_espace;

void initialise_case_espace(Case_terrain_espace *une_case_terrain_espace);
Case_terrain_espace *creer_case_espace();

void set_x_espace(Case_terrain_espace *une_case_terrain_espace, int x_espace);
int get_x_espace(const Case_terrain_espace *une_case_terrain_espace);
void set_y_espace(Case_terrain_espace *une_case_terrain_espace, int y_espace);
int get_y_espace(const Case_terrain_espace *une_case_terrain_espace);

void detruit_case_terrain_espace(Case_terrain_espace **une_case_terrain_espace);
void libere_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace);

void definir_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace, char c);
void ajouter_planete(Case_terrain_espace *une_case_terrain_espace, Planete *une_planete);

void affiche_case_terrain_espace(const Case_terrain_espace *une_case_terrain_espace);
void test_module_case_terrain_espace();


#endif

