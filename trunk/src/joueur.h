#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include <stdlib.h>
#include <stdio.h>

#include "planete.h"
#include "TableauDynamique.h"
#include "vision.h"


typedef enum
{
	DEFAUT = 1,
	BLEU,
	ROUGE
}Couleur_joueur;

/**
 * \struct Joueur
 * \brief D�finit un Joueur d'un Jeu
 */
typedef struct
{
    /** Num�ro du joueur */
    int numero_joueur;
    /** D�termine si le joueur est une intelligence artificielle ou non */
	bool ia;
    /** Vision du terrain du joueur */
	Vision_terrain* vision_terrain;
    /** Couleur du joueur */
    Couleur_joueur couleur_joueur;
    /** Ressources de m�tal */
    int metal;
    /** Ressources d'argent */
    int argent;
    /** Ressources de carburant */
    int carburant;
    /** Population g�r�e par le joueur */
    int population;
    /** Nombre de plan�tes poss�d�es */
	int nb_planete;
    /** Nombre de plan�tes qu'un joueur peut poss�der */
	int nb_planete_possible;
    /** Double pointeur de tableau de plan�tes que poss�de un joueur */
	Planete** tab_planete;
    /** Nombre de flottes que poss�de un joueur */
	int nb_flotte;
    /** Bombre de flottes que peut poss�der un joueur */
	int nb_flotte_possible;
    /** Double pointeur de tableau de flottes que poss�de un joueur */
    TableauDynamique tab_flotte;
    /** Points d'action d'un joueur */
	int pt_action_joueur;
    /** Points d'action maximales d'un joueur */
	int pt_action_joueur_total;
    /** Nom du joueur */
    char nom_joueur[20];
}Joueur;


void initialise_joueur(Joueur *un_joueur,char nom[30], int indice_joueur, bool ia);
Joueur *creer_joueur(char nom[30], int indice_joueur, bool ia);
void liberer_joueur(Joueur *un_joueur);
void detruire_joueur(Joueur **un_joueur);

void set_nom_joueur(Joueur *un_joueur, char nom[20]);
void set_couleur(Joueur *un_joueur, Couleur_joueur couleur_joueur);
Couleur_joueur get_couleur(const Joueur *un_joueur);
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
void set_numero_joueur(Joueur *un_joueur, int i);
int get_numero_joueur(const Joueur *un_joueur);
Flotte* get_ieme_flotte_joueur(const Joueur *un_joueur,int i);
Vision_terrain* get_vision_terrain(const Joueur* un_joueur);
Planete* get_ieme_planete_joueur(const Joueur* un_joueur, int i);
bool get_ia_joueur(Joueur* un_joueur);


void ajouter_metal(Joueur *un_joueur, int nb);
void retirer_metal(Joueur *un_joueur, int nb);
void ajouter_argent(Joueur *un_joueur, int nb);
void retirer_argent(Joueur *un_joueur, int nb);
void ajouter_carburant(Joueur *un_joueur, int nb);
void retirer_carburant(Joueur *un_joueur, int nb);
void ajouter_population(Joueur *un_joueur, int nb);
void retirer_population(Joueur *un_joueur, int nb);
void recuperer_ressource_planete(Joueur *un_joueur, int *metal, int *argent, int *carburant, int *population);
void recuperer_ressource_joueur(Joueur *un_joueur, int *metal, int *argent, int *carburant, int *population);
void ajouter_planete_joueur(Joueur *un_joueur, Planete *une_planete);
void ajouter_flotte_joueur(Joueur *un_joueur, Flotte *une_flotte);
void retirer_flotte_joueur(Joueur *un_joueur, int indice_flotte);
void ajouter_unite_ieme_flotte_joueur(Joueur *un_joueur, Unite * unite, int i);
void colonisation_planete(Joueur *un_joueur, Planete *une_planete);
void creation_unite_planete(Joueur *un_joueur, Planete *une_planete, int choix);
void enlever_pt_action_joueur(Joueur *un_joueur, const int point);
void reinitialiser_pt_action_joueur(Joueur *joueur);


void sauvegarde_joueur(const Joueur *un_joueur, FILE*f);
Joueur* ouverture_joueur(FILE *f);

#endif