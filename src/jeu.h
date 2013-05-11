#ifndef _JEU_H_
#define _JEU_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "terrain_espace.h"
#include "terrain_combat.h"
#include "joueur.h"
#include "constante.h"
#include "flotte.h"
#include "animation.h"

/**
 * \file      Module terrain
 * \author
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Planète et ses particularités
 *
 * \details
 */

 typedef struct
 {
    int tour_en_cours;
	int joueur_en_cours;
	int joueur_en_cours_combat;
	int nb_joueur;
	Joueur *tab_joueur;

	Flotte *selection_flotte;
	Planete *selection_planete;
	bool tab_unite_selectionnee[10];
	Animation *animation_en_cours;
 }Jeu;

void initialise_jeu(Jeu *un_jeu);
Jeu *creer_jeu();
void liberer_jeu(Jeu *un_jeu);
void detruire_jeu(Jeu **un_jeu);

Joueur* get_joueur_en_cours(Jeu *un_jeu);
Flotte* get_flotte_en_cours(Jeu *un_jeu);
int get_indice_joueur_en_cours(Jeu *un_jeu);
Planete *get_planete_en_cours(Jeu *un_jeu);

void ajouter_joueur(Jeu *un_jeu, Joueur *un_joueur);
void joueur_suivant(Jeu *un_jeu, Terrain_espace *un_terrain_espace);
void tour_suivant(Jeu *un_jeu, Terrain_espace *un_terrain_espace);
void afficher_ressource_joueur(Jeu *un_jeu);
void afficher_info(Jeu *un_jeu);
void validation_creation_unite_planete(Jeu *un_jeu, Terrain_espace *un_terrain_espace, int indice_joueur_en_cours, int x, int y);
void ajouter_flotte_jeu(Jeu *un_jeu,Terrain_espace *un_terrain_espace, Flotte *une_flotte, int indice_joueur, int x, int y);
void colonisation_planete_flotte(Terrain_espace *un_terrain_espace, Flotte *une_flotte, Jeu *un_jeu);

void lancer_animation(Jeu *un_jeu, Animation *une_animation, int temps, SDL_Surface *ecran, int x, int y);
void maj_animation(Jeu *un_jeu,Terrain_espace *un_terrain_espace, Animation *une_animation, int temps, SDL_Surface *ecran, SDL_Surface **tab_surface, int interface_affichee);
void lancer_animation_bloquante(Jeu *un_jeu, Terrain_espace *un_terrain_espace, Animation *une_animation, SDL_Surface *ecran, int x, int y, SDL_Surface **tab_surface, int interface_affichee);

int get_joueur_en_cours_combat(Jeu * jeu);
/**/
Joueur * get_ieme_joueur_jeu(Jeu * un_jeu,int i);

bool test_unite_selectionnee(Jeu *un_jeu);
bool deplacement_unite_flotte(Jeu *un_jeu, Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y);
void selectionner_case_combat(Jeu *jeu,Terrain_combat *un_terrain_combat,const int x, const int y);
void placer_unite_flotte_en_haut(Terrain_combat * un_terrain_combat, Flotte * flotte);
void placer_unite_flotte_en_bas(Terrain_combat * un_terrain_combat, Flotte * flotte);
void passer_tour_combat(Jeu * jeu, Terrain_combat * un_terrain_combat);
void enlever_pt_action_ieme_joueur(Jeu * jeu,const int i, const int nb);
void sauvegarde_jeu(const Jeu *un_jeu, FILE*f);
Jeu* ouverture_jeu(FILE *f);
#endif
