/**
 * \file      terrain_espace.h
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit un terrain d'espace
 * \details   Cette classe définit un terrain d'espace et ses caractéristiques
 */

#ifndef _TERRAIN_ESPACE_H_
#define _TERRAIN_ESPACE_H_

#include "case_terrain_espace.h"

typedef struct
{
    int taille_espace_x; 
	/** Taille en nombre de cases*/
    int taille_espace_y; 
	/** Taille en nombre de cases*/
    Case_terrain_espace *tab_terrain_espace; 
	/** Tableau de cases:x en abscisse, y en ordonnée, on commence à 0*/

	int affichage_x; 
	/** Valeur en pixels. Permet l'affichage du terrain, le point désigné par x et y étant le point en haut à gauche de la fenêtre*/
	int affichage_y; 
	/** Valeur en pixels*/
}Terrain_espace;

void initilaliser_terrain_espace(Terrain_espace *terrain_jeu_espace, int taille_x, int taille_y);
Terrain_espace *creer_terrain_espace(int taille_x, int taille_y);
void liberer_terrain_espace(Terrain_espace *terrain_jeu_espace);
void detruire_terrain_espace(Terrain_espace **terrain_jeu_espace);

int get_taille_espace_x(const Terrain_espace *terrain_jeu_espace);
int get_taille_espace_y(const Terrain_espace *terrain_jeu_espace);
Case_terrain_espace* get_case_terrain_espace(const Terrain_espace *terrain, const int x, const int y); /*Récupère les champs d'une case terrain*/
Planete* get_planete_terrain_espace(const Terrain_espace *terrain_espace, int x, int y);/*récupère le pointeur d'une planète à partir du terrain*/
void set_affichage(Terrain_espace* un_terrain, int x, int y);
int get_affichage_x(const Terrain_espace* un_terrain);
int get_affichage_y(const Terrain_espace* un_terrain);
void set_affichage_x(Terrain_espace* un_terrain, int nb);
void set_affichage_y(Terrain_espace* un_terrain, int nb);

void modifie_type_case_terrain_espace(const Terrain_espace *terrain, int x, int y, char c);/*mmodifie le type du terrain*/
void modification_terrain_espace(const Terrain_espace *terrain, const char c); /* met toutes les cases du terrain avec le type char c*/
void ajouter_planete_terrain_espace(Terrain_espace *terrain_espace, int x, int y, char nom_planete[30], int metal, int argent, int carburant, int  population); /*va créer une planète et l'ajouter sur la carte aux coordonnées*/
int indice_tableau(Terrain_espace* un_terrain_espace, int x, int y);
void affiche_terrain_espace(const Terrain_espace *terrain); /*affiche tous les types du terrain*/
int calcul_distance(int x_depart, int y_depart, int x_arrivee, int y_arrivee);
bool peut_se_deplacer(Flotte *une_flotte, int x, int y);
void calcul_deplacement_flotte(Flotte *une_flotte);

void sauvegarde_terrain_espace(const Terrain_espace *un_terrain_espace, FILE*f);
Terrain_espace* ouverture_terrain_espace(FILE *f);

void testRegression_Terrain_espace(void);
/*void test_module_terrain_espace();*/

#endif

