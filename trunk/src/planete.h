/**
 * \file      planete.h
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les planètes du jeu
 * \details   Cette classe définit les planètes du jeu et leurs caractéristiques
 */

#ifndef _PLANETE_H_
#define _PLANETE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*Permettra d'initialiser le tableau de pointeurs sur fonction*/
struct sPlanete;
typedef void (*Creation_batiment)(struct sPlanete*);
typedef void (*Validation_creation_batiment)(struct sPlanete*);

/**
 * \struct sPlanete
 * \brief Planète du jeu
 */
 typedef struct sPlanete
 {
     /** Abscisse */
     int x;
     /** Ordonnée */
     int y;
     /** Nom de la planète */
     char nom_planete[30];
     /** indice du joueur */
	 int indice_joueur;

     /** Tableau de bâtiments */
     int batiment[10];
     /** Indice dans le tableau du batiment en cours de construction */
     int batiment_en_cours;
     /** Entier indiquant le nombre de tours restants, si 0 on peut construire un batiment */
     int batiment_nb_tour_restant;
     /** Tableau rassemblant les validations des bâtiments */
     Validation_creation_batiment tab_fonction_validation[10];
     /** Tableau rassemblant les créations de bâtiments */
     Creation_batiment tab_fonction_creation[10];
     /** unite en cours */
     int unite_en_cours;
     /** Nombre de tours restants pour une unite */
     int unite_nb_tour_restant;
     /** Définit le nombre de bâtiments construits sur cette planète */
     int taille_utilisee;
     /** Définit la taille de la planète */
     int taille_planete;

	 /**Définit la portée du champ de vision de la planète*/
	 int portee_vision;
     /** Précise si c'est une planete principale ou non */
     bool planete_principale;
     /** Précise si la planète est colonisée (0 : no, 1 : oui) */
     bool planete_colonisee;
     /** Ressources de métal */
     int metal;
     /** Ressources d'argent */
     int argent;
     /** Ressources de carburant */
     int carburant;
     /** Population présente sur cette planète*/
     int population;

 }Planete;

void initialise_planete(Planete *une_planete, const char nom_planete[30]);
Planete *creer_planete(char nom_planete[30]);
void libere_planete(Planete *planete);
void detruire_planete(Planete **planete);

void set_nom_planete(Planete *une_planete,const char nom[30]);
char* get_nom_planete(Planete *une_planete);
void set_position_planete(Planete *une_planete,const int x,const int y);
int get_x_planete(const Planete *une_planete);
int get_y_planete(const Planete *une_planete);
void set_taille_utilisee(Planete *une_planete,const int taille_utilisee);
int get_taille_utilisee(const Planete *une_planete);
void set_taille_planete(Planete *une_planete,const int taille_planete);
int get_taille_planete(const Planete *une_planete);
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
void set_portee_planete(Planete* une_planete, int portee);
int get_portee_vision(const Planete* une_planete);
int get_ieme_batiment(const Planete* une_planete, int i);
int get_planete_unite_nb_tour_restant(const Planete* une_planete);
void set_planete_unite_nb_tour_restant(Planete* une_planete, int nb);
void set_planete_unite_en_cours(Planete* une_planete, int nb);
int get_planete_batiment_nb_tour_restant(const Planete* une_planete);
void set_planete_batiment_nb_tour_restant(Planete* une_planete, int nb);
void set_planete_batiment_en_cours(Planete* une_planete, int nb);


void modification_production_planete(Planete *une_planete,const int metal,const int argent,const int carburant,const int population);
void reduire_unite_nb_tour_restant(Planete* une_planete);
void reduire_batiment_nb_tour_restant(Planete* une_planete);
void afficher_planete(Planete *une_planete);
void afficher_batiment(Planete *une_planete);
void creation_batiment(Planete *une_planete, int choix);
void validation_batiment(Planete *une_planete);
void test_module_planete();


void suppr_retour( char *s );
void sauvegarde_planete(const Planete *une_planete, FILE*f);
Planete* ouverture_planete(FILE *f);

#endif
