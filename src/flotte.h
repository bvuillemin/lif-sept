/**
 * \file      flotte.h
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les flottes du jeu
 * \details   Cette classe définit les flottes du jeu et leurs caractéristiques
 */

#ifndef _FLOTTE_H_
#define _FLOTTE_H_

#include "unite.h"

/**
 * \struct Flotte
 * \brief Flotte du jeu
 */
 typedef struct
 {
     /** Abscisse de la flotte */
     int x_flotte;
     /** Ordonnée de la flotte */
     int y_flotte;
     /** Numéro du joueur contrôlant la flotte */
     int indice_joueur;
     /** Indice dans le tableau de flotte d'un joueur */
     int indice_tableau_joueur;
     /** Définit la taille maximale que peut avoir une flotte */
     int taille_maximum_flotte;
     /** Définit la taille d'une flotte */
     int taille_flotte;
     /** Définit les cours de mouvement que peut avoir une flotte */
     int pt_mouvement_espace_flotte;
     /** Définit la vision d'une flotte */
	 int portee_vision;
     /** Pointeur de pointeur sur tableau contenant les unités d'une flotte */
     Unite **tab_unite;
 }Flotte;

void initialiser_flotte(Flotte *flotte);
Flotte *creer_flotte();
void liberer_flotte(Flotte *flotte);
void detruire_flotte(Flotte **flotte);

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
Unite * get_unite_i_flotte(const Flotte * flotte, const int i);
void set_indice_joueur_flotte(Flotte *flotte,const int i);
int get_indice_joueur_flotte(const Flotte *flotte);
int get_portee_vision_flotte(const Flotte* une_flotte);
int get_indice_tableau_joueur(const Flotte* une_flotte);

int ajouter_unite_flotte(Flotte *flotte, Unite *unite); /*renvoie 1 en cas de succès, 0 en cas d'échecs*/
int transferer_unite_flotte(Flotte *flotte, Unite *unite);
int retirer_unite_flotte(Flotte *flotte,const int indice_unite);
void enlever_pt_mouvement_espace_flotte(Flotte *une_flotte,const int distance);
void afficher_flotte(const Flotte *flotte);
void reinitialiser_mouvement_flotte(Flotte *une_flotte);
void reinitialiser_deplacement_unite_flotte(Flotte *une_flotte);
void reinitialiser_pt_action_unite_flotte(Flotte *une_flotte);


void sauvegarde_flotte(const Flotte *une_flotte, FILE*f);
Flotte* ouverture_flotte(FILE *f);

void testRegression_flotte();

#endif

