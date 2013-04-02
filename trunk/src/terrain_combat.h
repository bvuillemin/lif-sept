#ifndef _TERRAIN_COMBAT_H_
#define _TERRAIN_COMBAT_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "flotte.h"
#include "case_terrain_combat.h"

/**
 * \file      Module Terrain_combat
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Terrain_combat et ses particularités
 *
 * \details
 */

typedef struct
{
    int taille_combat_x;
    int taille_combat_y;
    Case_terrain_combat *tab_terrain_combat; /*x en abscisse, y en ordonnée, on commence à 0 (à modifier?)*/
	Flotte * flotte1;
	Flotte * flotte2;
}Terrain_combat;

void initilalise_terrain_combat(Terrain_combat *terrain_jeu_combat, int taille_x, int taille_y);
Terrain_combat *creer_terrain_combat(int taille_x, int taille_y);

void libere_terrain_combat(Terrain_combat *terrain_jeu_combat);
void detruit_terrain_combat(Terrain_combat **terrain_jeu_combat);

void set_taille_combat_x(Terrain_combat *terrain_jeu_combat, int x);
int get_taille_combat_x(const Terrain_combat *terrain_jeu_combat);
void set_taille_combat_y(Terrain_combat *terrain_jeu_combat, int y);
int get_taille_combat_y(const Terrain_combat *terrain_jeu_combat);

/*modifie une case du terrain*/
void set_case_terrain_combat(const Terrain_combat *terrain_jeu_combat, int x, int y, char c);
Case_terrain_combat * get_case_terrain_combat(const Terrain_combat *terrain_jeu_combat, const int x, const int y);


void modification_terrain_combat(const Terrain_combat *terrain_jeu_combat, const char c); /* met toutes les cases du terrain avec le type char c*/

void affiche_terrain_combat(const Terrain_combat *terrain_jeu_combat); /*affiche tous les types du terrain*/

bool unite_peut_se_deplacer(Unite *une_unite, int x, int y);
int calcul_distance_unite(int x_depart, int y_depart, int x_arrivee, int y_arrivee);
bool deplacement_unite(Terrain_combat *un_terrain_combat, Unite *une_unite, int x, int y);
/*ajoute une unité sur la case de coordonnées (x,y)*/
void ajoute_unite_terrain(Terrain_combat * un_terrain_combat, Unite * unite, int x, int y);



/*void test_module_terrain_combat();*/



#endif

