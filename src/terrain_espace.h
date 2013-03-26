#ifndef _TERRAIN_ESPACE_H_
#define _TERRAIN_ESPACE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "case_terrain_espace.h"

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
    int taille_espace_x;
    int taille_espace_y;
    Case_terrain_espace *tab_terrain_espace; /*x en abscisse, y en ordonnée, on commence à 0 (à modifier?)*/
}Terrain_espace;

void initilalise_terrain_espace(Terrain_espace *terrain_jeu_espace, int taille_x, int taille_y);
Terrain_espace *creer_terrain_espace(int taille_x, int taille_y);

void libere_terrain_espace(Terrain_espace *terrain_jeu_espace);
void detruit_terrain_espace(Terrain_espace **terrain_jeu_espace);

void set_taille_espace_x(Terrain_espace *terrain_jeu_espace, int x);
int get_taille_espace_x(const Terrain_espace *terrain_jeu_espace);
void set_taille_espace_y(Terrain_espace *terrain_jeu_espace, int y);
int get_taille_espace_y(const Terrain_espace *terrain_jeu_espace);
void modifie_type_case_terrain_espace(const Terrain_espace *terrain, int x, int y, char c);/*mmodifie le type du terrain*/

Case_terrain_espace* get_case_terrain_espace(const Terrain_espace *terrain, const int x, const int y); /*Récupère les champs d'une case terrain*/
Planete* get_planete_terrain_espace(const Terrain_espace *terrain_espace, int x, int y);/*récupère le pointeur d'une planète à partir du terrain*/

void modification_terrain_espace(const Terrain_espace *terrain, const char c); /* met toutes les cases du terrain avec le type char c*/
void ajouter_planete_terrain_espace(Terrain_espace *terrain, int x, int y); /*va créer une planète et l'ajouter sur la carte aux coordonnées*/

void affiche_terrain_espace(const Terrain_espace *terrain); /*affiche tous les types du terrain*/

/*void test_module_terrain_espace();*/



#endif

