#ifndef _JEU_H_
#define _JEU_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "terrain_espace.h"
#include "terrain_combat.h"
#include "joueur.h"
#include "constante.h"

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
	 int nb_joueur;
	 Flotte *selection_flotte;
	 Planete *selection_planete;
	 Joueur *tab_joueur;
 }Jeu;

void initialise_jeu(Jeu *un_jeu);
Jeu *creer_jeu();
void liberer_jeu(Jeu *un_jeu);
void detruire_jeu(Jeu **un_jeu);

void ajouter_joueur(Jeu *un_jeu, Joueur *un_joueur);
void joueur_suivant(Jeu *un_jeu, Terrain_espace *un_terrain_espace);
void tour_suivant(Jeu *un_jeu, Terrain_espace *un_terrain_espace);
void afficher_ressource_joueur(Jeu *un_jeu);
void afficher_info(Jeu *un_jeu);
void validation_creation_unite_planete(Case_terrain_espace *une_case_terrain_espace, Joueur *un_joueur);



/**/
void placer_joueur_combat(Terrain_combat * un_terrain_combat,Joueur* joueur);
void placer_unite_flotte_en_haut(Terrain_combat * un_terrain_combat, Flotte * flotte);
void placer_unite_flotte_en_bas(Terrain_combat * un_terrain_combat, Flotte * flotte);
#endif
