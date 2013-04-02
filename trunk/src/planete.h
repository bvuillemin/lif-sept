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
     char nom_planete[30];
     /*lien sur proprietaire
     tab de batiments*/
     int taille_utilisee;
     int taille_planete;
	 int habitabilite;
     int planete_principale; /*1 si oui, 0 sinon */
     int planete_colonisee; /*1 si oui, 0 sinon */

     int metal;
     int argent;
     int carburant;
     int population;

 }Planete;

void initialise_planete(Planete *une_planete, char nom_planete[30]);
Planete *creer_planete(char nom_planete[30]);

void set_nom_planete(Planete *une_planete, char nom[30]);

void set_taille_utilisee(Planete *une_planete, int taille_utilisee);
int get_taille_utilisee(Planete *une_planete);
void set_taille_planete(Planete *une_planete, int taille_planete);
int get_taille_planete(Planete *une_planete);
void set_habitabilite(Planete *une_planete, int nb);
int get_habitabilite(Planete *une_planete);
void set_planete_principale(Planete *une_planete, int booleen);
int get_planete_principale(Planete *une_planete);
void set_planete_colonise(Planete *une_planete, int booleen);
int get_planete_colonise(Planete *une_planete);

void set_metal(Planete *une_planete, int nb);
int get_metal(Planete *une_planete);
void set_argent(Planete *une_planete, int nb);
int get_argent(Planete *une_planete);
void set_carburant(Planete *une_planete, int nb);
int get_carburant(Planete *une_planete);
void set_population(Planete *une_planete, int nb);
int get_population(Planete *une_planete);

void modification_production_planete(Planete *une_planete, int metal, int argent, int carburant, int population);

void libere_planete(Planete *planete);
void detruit_planete(Planete **planete);

void afficher_planete(Planete *une_planete);

void test_module_planete();



#endif
