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
     int taille_maximum_flotte;
     int taille_flotte;
     Unite *tab_unite;
 }Flotte;

void initialise_flotte(Flotte *flotte);
Flotte *creer_flotte();

void set_taille_maximum_flotte(Flotte *flotte,const int max);
int get_taille_maximum_flotte(Flotte *flotte);
void set_taille_flotte(Flotte *flotte,const int nb);
int get_taille_flotte(Flotte *flotte);

void libere_flotte(Flotte *flotte);
void detruit_flotte(Flotte **flotte);

int ajouter_unite_flotte(Flotte *flotte, Unite *unite); /*renvoie 1 en cas de succès, 0 en cas d'échecs*/
void retirer_unite_flotte(Flotte *flotte,const int indice_unite);

void afficher_flotte(Flotte *flotte);

void test_module_flotte();

#endif

