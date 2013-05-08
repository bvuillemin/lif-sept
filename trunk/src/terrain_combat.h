#ifndef _TERRAIN_COMBAT_H_
#define _TERRAIN_COMBAT_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "flotte.h"
#include "case_terrain_combat.h"
#include "flotte.h"

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
	bool une_case_selectionnee;
	Case_terrain_combat * selection;
    Case_terrain_combat *tab_terrain_combat; /*x en abscisse, y en ordonnée, on commence à 0 (à modifier?)*/
}Terrain_combat;

void initilalise_terrain_combat(Terrain_combat *terrain_jeu_combat, const int taille_x,const int taille_y);
Terrain_combat *creer_terrain_combat(const int taille_x,const int taille_y);

void libere_terrain_combat(Terrain_combat *terrain_jeu_combat);
void detruit_terrain_combat(Terrain_combat **terrain_jeu_combat);

void set_taille_combat_x(Terrain_combat *terrain_jeu_combat,const int x);
int get_taille_combat_x(const Terrain_combat *terrain_jeu_combat);
void set_taille_combat_y(Terrain_combat *terrain_jeu_combat,const int y);
int get_taille_combat_y(const Terrain_combat *terrain_jeu_combat);

void set_selection(Terrain_combat *terrain_jeu_combat,Case_terrain_combat * un_case_terrain_combat);
Case_terrain_combat * get_selection(const Terrain_combat *terrain_jeu_combat);

void set_une_case_selectionnee(Terrain_combat *terrain_jeu_combat,const bool y);
bool get_une_case_selectionnee(const Terrain_combat *terrain_jeu_combat);

/*modifie une case du terrain*/
void set_case_terrain_combat(const Terrain_combat *terrain_jeu_combat,const int x,const int y,const char c);
Case_terrain_combat * get_case_terrain_combat(const Terrain_combat *terrain_jeu_combat, const int x, const int y);


void modification_terrain_combat(const Terrain_combat *terrain_jeu_combat, const char c); /* met toutes les cases du terrain avec le type char c*/

void affiche_terrain_combat(const Terrain_combat *terrain_jeu_combat); /*affiche tous les types du terrain*/


bool deplacement_unite(Terrain_combat *un_terrain_combat, Unite *une_unite, const int x,const int y);
/*ajoute une unité sur la case de coordonnées (x,y)*/
void ajoute_unite_terrain(Terrain_combat * un_terrain_combat, Unite * unite,const int x,const int y);

bool case_libre(const Terrain_combat * un_terrain_combat,const int x,const int y);


void un_tour_combat(Terrain_combat * un_terrain_combat, Flotte * flotte);
bool peut_attaquer_diag(Terrain_combat * un_terrain_combat, Unite * unite,const int x,const int y);
bool peut_attaquer_hor_vert(Terrain_combat * un_terrain_combat, const Unite * unite,const int x,const int y);
int attaquer(Terrain_combat * un_terrain_combat,Unite * une_unite,const int x,const int y);
void supprimer_unite_flotte(Terrain_combat * un_terrain_combat,Flotte * flotte ,Unite* unite);

/*void test_module_terrain_combat();*/



#endif

