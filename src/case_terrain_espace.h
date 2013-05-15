#ifndef _CASE_TERRAIN_ESPACE_H_
#define _CASE_TERRAIN_ESPACE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "planete.h"
#include "flotte.h"


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
	/*bool est_visible;*/
	Planete *planete;/*lien sur une planète si la case est de type planète, sinon NULL*/
	Flotte *flotte;
}Case_terrain_espace;


void initialiser_case_espace(Case_terrain_espace *une_case_terrain_espace);
Case_terrain_espace *creer_case_espace();
void detruire_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace);
void liberer_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace);

void set_x_espace(Case_terrain_espace *une_case_terrain_espace, int x_espace);
int get_x_espace(const Case_terrain_espace *une_case_terrain_espace);
void set_y_espace(Case_terrain_espace *une_case_terrain_espace, int y_espace);
int get_y_espace(const Case_terrain_espace *une_case_terrain_espace);
void set_type_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace, char type);
char get_type_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace);
Planete * get_planete(Case_terrain_espace *une_case_terrain_espace);
Flotte * get_flotte(Case_terrain_espace *une_case_terrain_espace);
bool get_presence_flotte(Case_terrain_espace* une_case);

void definir_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace, char c);
void ajouter_planete(Case_terrain_espace *une_case_terrain_espace, Planete *une_planete);
void ajouter_flotte(Case_terrain_espace *une_case_terrain_espace, Flotte *une_flotte);
void retirer_flotte(Case_terrain_espace *une_case_terrain_espace);
void affiche_case_terrain_espace(const Case_terrain_espace *une_case_terrain_espace);
void test_module_case_terrain_espace();

void sauvegarde_case_terrain_espace(const Case_terrain_espace *une_case_terrain_espace, FILE*f);
Case_terrain_espace* ouverture_case_terrain_espace(FILE*f);





#endif

