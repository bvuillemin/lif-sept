#ifndef _PLANETE_H_
#define _PLANETE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * \file      Module terrain
 * \author
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Planète et ses particularités
 *
 * \details
 */


struct sPlanete;
typedef void (*Creation_batiment)(struct sPlanete*);
typedef void (*Validation_creation_batiment)(struct sPlanete*);

 typedef struct sPlanete
 {
     int x;
     int y;
     char nom_planete[30];
	 int indice_joueur;

     int batiment[10];
     int batiment_en_cours; /*indice dans le tableau du batiment en cours de construction*/
     int batiment_nb_tour_restant; /*entier indiquant le nombre de tours restants, si 0 on peut construire un batiment*/

     Validation_creation_batiment tab_fonction_validation[10];
     Creation_batiment tab_fonction_creation[10];

     int unite_en_cours;
     int unite_nb_tour_restant;

     int taille_utilisee;
     int taille_planete;
	 int habitabilite;
     bool planete_principale; /*1 si oui, 0 sinon */
     bool planete_colonisee; /*1 si oui, 0 sinon */

     int metal;
     int argent;
     int carburant;
     int population;

 }Planete;

void initialise_planete(Planete *une_planete, const char nom_planete[30]);
Planete *creer_planete(char nom_planete[30]);

void set_nom_planete(Planete *une_planete,const char nom[30]);
char* get_nom_planete(Planete *une_planete);
void set_position_planete(Planete *une_planete,const int x,const int y);
int get_position_x_planete(const Planete *une_planete);
int get_position_y_planete(const Planete *une_planete);
void set_taille_utilisee(Planete *une_planete,const int taille_utilisee);
int get_taille_utilisee(const Planete *une_planete);
void set_taille_planete(Planete *une_planete,const int taille_planete);
int get_taille_planete(const Planete *une_planete);
void set_habitabilite(Planete *une_planete,const int nb);
int get_habitabilite(const Planete *une_planete);
void set_planete_principale(Planete *une_planete, const bool booleen);
bool get_planete_principale(const Planete *une_planete);
void set_planete_colonisee(Planete *une_planete,const bool booleen);
bool get_planete_colonisee(const Planete *une_planete);

void set_metal(Planete *une_planete,const int nb);
int get_metal(const Planete *une_planete);
void set_argent(Planete *une_planete,const int nb);
int get_argent(const Planete *une_planete);
void set_carburant(Planete *une_planete,const int nb);
int get_carburant(const Planete *une_planete);
void set_population(Planete *une_planete,const int nb);
int get_population(const Planete *une_planete);

void modification_production_planete(Planete *une_planete,const int metal,const int argent,const int carburant,const int population);

void libere_planete(Planete *planete);
void detruire_planete(Planete **planete);

void afficher_planete(Planete *une_planete);
void afficher_batiment(Planete *une_planete);

void creation_batiment(Planete *une_planete, int choix);
void validation_batiment(Planete *une_planete);

void test_module_planete();



#endif
