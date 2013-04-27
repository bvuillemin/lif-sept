#ifndef _TERRAIN_ESPACE_H_
#define _TERRAIN_ESPACE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "case_terrain_espace.h"
#include "joueur.h"

/**
 * \file      Module terrain_espace
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Terrain_espace et ses particularités
 *
 * \details
 */

typedef struct
{
    int taille_espace_x; /*en nombre de cases*/
    int taille_espace_y; /*en nombre de cases*/
    Case_terrain_espace *tab_terrain_espace; /*x en abscisse, y en ordonnée, on commence à 0 (à modifier?)*/

	int affichage_x; /*en pixels. Permet l'affichage du terrain, le point désigné par x et y étant le point en haut à gauche de la fenêtre*/
	int affichage_y; /*en pixels*/
}Terrain_espace;

void initilaliser_terrain_espace(Terrain_espace *terrain_jeu_espace, int taille_x, int taille_y);
Terrain_espace *creer_terrain_espace(int taille_x, int taille_y);

void liberer_terrain_espace(Terrain_espace *terrain_jeu_espace);
void detruire_terrain_espace(Terrain_espace **terrain_jeu_espace);

void set_taille_espace_x(Terrain_espace *terrain_jeu_espace, int x);
int get_taille_espace_x(const Terrain_espace *terrain_jeu_espace);
void set_taille_espace_y(Terrain_espace *terrain_jeu_espace, int y);
int get_taille_espace_y(const Terrain_espace *terrain_jeu_espace);
void modifie_type_case_terrain_espace(const Terrain_espace *terrain, int x, int y, char c);/*mmodifie le type du terrain*/

Case_terrain_espace* get_case_terrain_espace(const Terrain_espace *terrain, const int x, const int y); /*Récupère les champs d'une case terrain*/
Planete* get_planete_terrain_espace(const Terrain_espace *terrain_espace, int x, int y);/*récupère le pointeur d'une planète à partir du terrain*/

void modification_terrain_espace(const Terrain_espace *terrain, const char c); /* met toutes les cases du terrain avec le type char c*/
void ajouter_planete_terrain_espace(Terrain_espace *terrain, int x, int y, char nom_planete[30]); /*va créer une planète et l'ajouter sur la carte aux coordonnées*/

void affiche_terrain_espace(const Terrain_espace *terrain); /*affiche tous les types du terrain*/

int calcul_distance(int x_depart, int y_depart, int x_arrivee, int y_arrivee);

bool peut_se_deplacer(Flotte *une_flotte, int x, int y);
void calcul_deplacement_flotte(Flotte *une_flotte);
bool deplacement_flotte(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y);
bool fusion_flotte(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y);

/*void test_module_terrain_espace();*/



#endif

