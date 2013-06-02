/**
 * \file      terrain_combat.h
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit un terrain de combat
 * \details   Cette classe définit un terrain de combat et ses caractéristiques
 */
#ifndef _TERRAIN_COMBAT_H_
#define _TERRAIN_COMBAT_H_

#include "case_terrain_combat.h"

/**
 * \struct Terrain_combat
 * \brief Terrain du combat
 */
typedef struct
{
    /** Taille du terrain en abscisse */
    int taille_combat_x;
    /** Taille du terrain en ordonnées */
    int taille_combat_y;
    /** 1 si une case est sélectionnée 0 sinon */
	bool une_case_selectionnee;
    /** Case sélectionnée */
	Case_terrain_combat * selection;
    /** Les cases du terrain*/
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
void deselectionner(Terrain_combat * un_terrain_combat);
/*void test_module_terrain_combat();*/



#endif

