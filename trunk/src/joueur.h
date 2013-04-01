#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include <stdlib.h>
#include <stdio.h>

#include "planete.h"
#include "flotte.h"

typedef struct
{
    char nom_joueur[20];
    enum {bleu, rouge} couleur_joueur;

    int metal;
    int argent;
    int carburant;
    int population;

	int nb_planete; /*Correspond au nombre de planètes possédées et donc au nombre de cases du tableau ci-dessous*/
	int nb_planete_possible;
    Planete* tab_planete[];

	int nb_flotte;
	int nb_flotte_possible;
	Flotte* tab_flotte[];

}Joueur;

void set_nom_joueur(Joueur *un_joueur, char nom[20]);
void set_couleur(Joueur *un_joueur, int i);
int get_couleur(const Joueur *un_joueur);
void set_metal_joueur(Joueur *un_joueur, int nb);
int get_metal_joueur(const Joueur *un_joueur);
void set_argent_joueur(Joueur *un_joueur, int nb);
int get_argent_joueur(const Joueur *un_joueur);
void set_carburant_joueur(Joueur *un_joueur, int nb);
int get_carburant_joueur(const Joueur *un_joueur);
void set_population_joueur(Joueur *un_joueur, int nb);
int get_population_joueur(const Joueur *un_joueur);
//void set_nb_planete(Joueur *un_joueur, int nb);
int get_nb_planete(Joueur *un_joueur);

void initialise_joueur(Joueur *un_joueur, char nom[30]);
Joueur *creer_joueur(char nom[30]);

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


#endif
