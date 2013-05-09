#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include <stdlib.h>
#include <stdio.h>

#include "planete.h"
#include "flotte.h"
/*#include "terrain_espace.h"*/

/*#include "terrain_espace.h"*/

typedef struct
{
    int numero_joueur;

    enum {bleu = 0, rouge} couleur_joueur;

    int metal;
    int argent;
    int carburant;
    int population;

	int nb_planete; /*Correspond au nombre de planètes possédées et donc au nombre de cases du tableau ci-dessous*/
	int nb_planete_possible;
	Planete** tab_planete;

	int nb_flotte;
	int nb_flotte_possible;
    Flotte* tab_flotte;
	
	int pt_action_joueur;
	int pt_action_joueur_total;
    char nom_joueur[20];

}Joueur;

void set_nom_joueur(Joueur *un_joueur, char nom[20]);
void set_couleur(Joueur *un_joueur, int i);
int get_couleur(const Joueur *un_joueur);
void set_pt_action_joueur(Joueur *un_joueur, int i);
int get_pt_action_joueur(const Joueur *un_joueur);
void set_metal_joueur(Joueur *un_joueur, int nb);
int get_metal_joueur(const Joueur *un_joueur);
void set_argent_joueur(Joueur *un_joueur, int nb);
int get_argent_joueur(const Joueur *un_joueur);
void set_carburant_joueur(Joueur *un_joueur, int nb);
int get_carburant_joueur(const Joueur *un_joueur);
void set_population_joueur(Joueur *un_joueur, int nb);
int get_population_joueur(const Joueur *un_joueur);
/*void set_nb_planete(Joueur *un_joueur, int nb);*/
int get_nb_planete(Joueur *un_joueur);

int get_nb_flotte_joueur(Joueur *un_joueur);
void set_numero_joueur(Joueur *un_joueur, int i);/**/
int get_numero_joueur(const Joueur *un_joueur);/**/

void initialise_joueur(Joueur *un_joueur,char nom[30]);
Joueur *creer_joueur(char nom[30]);
void liberer_joueur(Joueur *un_joueur);
void detruire_joueur(Joueur **un_joueur);

void ajouter_metal(Joueur *un_joueur, int nb);
void retirer_metal(Joueur *un_joueur, int nb);
void ajouter_argent(Joueur *un_joueur, int nb);
void retirer_argent(Joueur *un_joueur, int nb);
void ajouter_carburant(Joueur *un_joueur, int nb);
void retirer_carburant(Joueur *un_joueur, int nb);
void ajouter_population(Joueur *un_joueur, int nb);
void retirer_population(Joueur *un_joueur, int nb);

void recuperer_ressource_planete(Joueur *un_joueur, int *metal, int *argent, int *carburant, int *population);

void ajouter_planete_joueur(Joueur *un_joueur, Planete *une_planete);
void ajouter_flotte_joueur(Joueur *un_joueur, Flotte *une_flotte);
void retirer_flotte_joueur(Joueur *un_joueur, int indice_flotte);

Flotte * get_ieme_flotte_joueur(const Joueur *un_joueur,int i);/**/
void ajouter_unite_ieme_flotte_joueur(Joueur *un_joueur, Unite * unite, int i);/**/

void colonisation_planete(Joueur *un_joueur, Planete *une_planete);
void creation_unite_planete(Joueur *un_joueur, Planete *une_planete, int choix);
void enlever_pt_action_joueur(Joueur *un_joueur, const int point);
void reinitialiser_pt_action_joueur(Joueur *joueur);

void sauvegarde_joueur(const Joueur *un_joueur, FILE*f);
Joueur* ouverture_joueur(FILE *f);

#endif
