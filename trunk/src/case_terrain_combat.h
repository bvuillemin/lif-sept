#ifndef _CASE_TERRAIN_COMBAT_H_
#define _CASE_TERRAIN_COMBAT_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "planete.h"
#include "unite.h"
#include "joueur.h"

/**
 * \file      Module case_terrain_combat
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Case du Terrain_combat et ses particularités
 *
 * \details
 */

typedef struct
{
    int x_combat,y_combat;
    char type_case_terrain_combat;/* N si non initialisé*/
    bool presence_unite;
	Unite *unite;
	int id_joueur;
}Case_terrain_combat;

void initialise_case_combat(Case_terrain_combat *une_case_terrain_combat);
Case_terrain_combat *creer_case_combat();

void set_x_combat(Case_terrain_combat *une_case_terrain_combat, int x_combat);
int get_x_combat(const Case_terrain_combat *une_case_terrain_combat);
void set_y_combat(Case_terrain_combat *une_case_terrain_combat, int y_combat);
int get_y_combat(const Case_terrain_combat *une_case_terrain_combat);
void set_type_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat, char type);
char get_type_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat);

void set_id_joueur(Case_terrain_combat *une_case_terrain_combat, int id_joueur);
int get_id_joueur(const Case_terrain_combat *une_case_terrain_combat);

void set_presence_unite(Case_terrain_combat *une_case_terrain_combat,bool p);
bool get_presence_unite(Case_terrain_combat *une_case_terrain_combat);

void detruit_case_terrain_combat(Case_terrain_combat **une_case_terrain_combat);
void libere_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat);

void definir_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat, char c);

void set_unite(Case_terrain_combat *une_case_terrain_combat, Unite *une_unite);
Unite * get_unite(Case_terrain_combat *une_case_terrain_combat);

void ajouter_unite(Case_terrain_combat *une_case_terrain_combat, Unite *une_unite);
void retirer_unite(Case_terrain_combat *une_case_terrain_combat);

void affiche_case_terrain_combat(const Case_terrain_combat *une_case_terrain_combat);
void test_module_case_terrain_combat();


#endif


