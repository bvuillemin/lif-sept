/**
 * \file      unite.h
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les unités du jeu
 * \details   Cette classe définit les unités du jeu et leurs caractéristiques
 */

#ifndef _UNITE_H_
#define _UNITE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef enum
{
	Chasseur,
	Destroyer,
	Destructeur
}TYPE_VAISSEAU;


/**
 * \struct Unite
 * \brief unité
 */
typedef struct
{
    /** type de vaisseau */
	TYPE_VAISSEAU type;
    /** indice du joueur possédant cette unité */
	int indice_joueur;
    /** indice dans le tableau de la flotte à laquelle l'unité appartient */
	int indice_dans_flotte;
    /** coordonnée en abscisse de l'unité*/
	int x_unite;
    /** coordonnée en ordonnée de l'unité*/
	int y_unite;

    /** portée de l'unité*/
	int portee;
    /** points de vie de l'unité*/
	int pt_vie;
    /** points de vie total de l'unité*/
	int pt_vie_total;

    /** point d'attaque de l'unité*/
	int pt_attaque;
    /** point d'attaque total de l'unité*/
	int pt_attaque_total;
    /** point d'action de l'unité*/
	int pt_action;
    /** point d'action total de l'unité*/
	int pt_action_total;

    /** point de déplacement dans le combat de l'unité*/
	int pt_deplacement;
    /** point de déplacement total de l'unité*/
	int pt_deplacement_total;
    /** point de mouvement dans l'espace de l'unité*/
	int pt_mouvement_unite;
	/*ressources nécessaires*/
	/*compétence spéciale*/
}Unite;

void initialiser_unite(Unite *unite_jeu, TYPE_VAISSEAU type);
Unite *creer_unite(TYPE_VAISSEAU type);

void liberer_unite(Unite *unite_jeu);
void detruire_unite(Unite **unite_jeu);

TYPE_VAISSEAU get_type_vaisseau(Unite* une_unite);
void set_portee(Unite *unite_jeu, const int x);
int get_portee(const Unite *unite_jeu);

void set_pt_vie(Unite *unite_jeu, const int x);
int get_pt_vie(const Unite *unite_jeu);

void set_pt_vie_total(Unite *unite_jeu, const int x);
int get_pt_vie_total(const Unite *unite_jeu);

void set_pt_attaque_total(Unite *unite_jeu, const int x);
int get_pt_attaque_total(const Unite *unite_jeu);

void set_pt_action_total(Unite *unite_jeu, const int x);
int get_pt_action_total(const Unite *unite_jeu);

void set_x_unite(Unite *unite_jeu, const int x);
int get_x_unite(const Unite *unite_jeu);

void set_y_unite(Unite *unite_jeu, const int y);
int get_y_unite(const Unite *unite_jeu);

void set_pt_attaque(Unite *unite_jeu, const int x);
int get_pt_attaque(const Unite *unite_jeu);

void set_pt_action(Unite *unite_jeu, const int x);
int get_pt_action(const Unite *unite_jeu);

void set_pt_deplacement(Unite *unite_jeu, const int x);
int get_pt_deplacement(const Unite *unite_jeu);

void set_pt_mouvement_unite(Unite *unite_jeu, const int x);
int get_pt_mouvement_unite(const Unite *unite_jeu);

void set_indice_joueur_unite(Unite *unite,const int i);
int get_indice_joueur_unite(const Unite *unite);

void set_indice_unite_dans_flotte(Unite *unite,const int i);
int get_indice_unite_dans_flotte(const Unite *unite);
bool unite_peut_se_deplacer(const Unite *une_unite, const int x, const int y);
int calcul_distance_unite(const int x_depart, const int y_depart, const int x_arrivee, const int y_arrivee);

void enlever_pt_mouvement_combat_unite(Unite *une_unite, const int distance);
void enlever_pt_action_unite(Unite *une_unite, const int point);
void reinitialiser_mouvement_combat_unite(Unite *une_unite);
void reinitialiser_pt_action(Unite *une_unite);

void sauvegarde_unite(const Unite *une_unite, FILE* f);
Unite* ouverture_unite(FILE *f);

void testRegression_Unite();

#endif

