#ifndef _JEU_H_
#define _JEU_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "joueur.h"

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
	 Joueur *tab_joueur;
 }Jeu;

void initialise_jeu(Jeu *un_jeu);
Jeu *creer_jeu();
void ajouter_joueur(Jeu *un_jeu, Joueur *un_joueur);
void joueur_suivant(Jeu *un_jeu);
void tour_suivant(Jeu *un_jeu);
void afficher_ressource_joueur(Jeu *un_jeu);
void afficher_info(Jeu *un_jeu);

#endif
