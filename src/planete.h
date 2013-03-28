#ifndef _PLANETE_H_
#define _PLANETE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
     int x;
     int y;
     char *nom_planete;
     /*lien sur proprietaire
     tab de batiments*/
     int taille_utilisee;
     int taille_planete;
     int planete_principale; /*1 si oui, 0 sinon */
     int planete_colonisee; /*1 si oui, 0 sinon */

     int metal;
     int argent;
     int carburant;
     int population;

 }Planete;

void initialise_planete(Planete *planete);
Planete *creer_planete();

void set_nom_planete(Planete *planete, char nom[30]);

void set_taille_utilisee(Planete *planete, int taille_utilisee);
int get_taille_utilisee(Planete *planete);
void set_taille_planete(Planete *planete, int taille_planete);
int get_taille_planete(Planete *planete);
void set_planete_principale(Planete *planete, int booleen);
int get_planete_principale(Planete *planete);
void set_planete_colonise(Planete *planete, int booleen);
int get_planete_colonise(Planete *planete);

void set_metal(Planete *une_planete, int nb);
int get_metal(Planete *une_planete);
void set_argent(Planete *une_planete, int nb);
int get_argent(Planete *une_planete);
void set_carburant(Planete *une_planete, int nb);
int get_carburant(Planete *une_planete);
void set_population(Planete *une_planete, int nb);
int get_population(Planete *une_planete);

void libere_planete(Planete *planete);
void detruit_planete(Planete **planete);

void affiche_planete(Planete *une_planete);

void test_module_planete();



#endif
