#ifndef _FLOTTE_H_
#define _FLOTTE_H_

#include <stdlib.h>
#include <stdio.h>

#include "unite.h"

/**
 * \file      Module terrain
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Planète et ses particularités
 *
 * \details
 */


 typedef struct
 {
     int x_flotte;
     int y_flotte;
     int indice_joueur;

     int taille_maximum_flotte;
     int taille_flotte;
     int pt_mouvement_espace_flotte;
     Unite *tab_unite;
 }Flotte;

void initialiser_flotte(Flotte *flotte);
Flotte *creer_flotte();

void set_taille_maximum_flotte(Flotte *flotte,const int max);
int get_taille_maximum_flotte(const Flotte *flotte);
void set_taille_flotte(Flotte *flotte,const int nb);
int get_taille_flotte(const Flotte *flotte);
void set_x_flotte(Flotte *une_flotte,const int x);
int get_x_flotte(const Flotte *une_flotte);
void set_y_flotte(Flotte *une_flotte,const int y);
int get_y_flotte(const Flotte *une_flotte);
void set_pt_mouvement_espace_flotte(Flotte *une_flotte, const int pt);
int get_pt_mouvement_espace_flotte( const Flotte *une_flotte);

void liberer_flotte(Flotte *flotte);
void detruire_flotte(Flotte **flotte);

int ajouter_unite_flotte(Flotte *flotte, Unite *unite); /*renvoie 1 en cas de succès, 0 en cas d'échecs*/
Unite * get_unite_i_flotte(const Flotte * flotte, const int i);

int retirer_unite_flotte(Flotte *flotte,const int indice_unite);

void enlever_pt_mouvement_espace_flotte(Flotte *une_flotte,const int distance);
void afficher_flotte(const Flotte *flotte);
void reinitialiser_mouvement_flotte(Flotte *une_flotte);
void reinitialiser_deplacement_unite_flotte(Flotte *une_flotte);
void reinitialiser_pt_action_unite_flotte(Flotte *une_flotte);

void test_module_flotte();

#endif

