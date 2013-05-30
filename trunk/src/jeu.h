/**
 * \file      jeu.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit le jeu
 * \details   Cette classe définit le jeu et ses composantes (flottes, terrain...)
 */

#ifndef _JEU_H_
#define _JEU_H_

#include "terrain_espace.h"
#include "terrain_combat.h"
#include "constante.h"
#include "animation.h"

/**
 * \struct Jeu
 * \brief Définit le jeu
 */
 typedef struct
 {
     /** Définit le nombre de tours en cours */
     int tour_en_cours;
     /** Définit le joueur en train de jouer */
     int joueur_en_cours;
     /** Définit le joueur en train de jouer lors d'un combat */
     int joueur_en_cours_combat;
     /** Définit le nombre de joueurs lors d'une partie */
     int nb_joueur;
     /** Pointeur sur tableau regroupant tous les joueurs d'une partie */
     Joueur *tab_joueur;
     /** Pointeur sur flotte sélectionnée */
     Flotte *selection_flotte;
     /** Pointeur sur planète sélectionnée */
     Planete *selection_planete;
     /** Unités sélectionnées */
     bool tab_unite_selectionnee[10];
     /** Définit l'animation à afficher (Pointeur sur Animation) */
     Animation *animation_en_cours;
     /** Définit le joueur qui a gagné le combat */
     Joueur * gagnant_combat;
 }Jeu;

void initialise_jeu(Jeu *un_jeu);
Jeu *creer_jeu();
void liberer_jeu(Jeu *un_jeu);
void detruire_jeu(Jeu **un_jeu);

Joueur* get_joueur_en_cours(Jeu *un_jeu);
Flotte* get_flotte_en_cours(Jeu *un_jeu);
int get_indice_joueur_en_cours(Jeu *un_jeu);
Planete *get_planete_en_cours(Jeu *un_jeu);
int get_joueur_en_cours_combat(Jeu * jeu);
Joueur * get_ieme_joueur_jeu(Jeu * un_jeu,int i);
bool construction_unite_possible(Planete* une_planete);

void ajouter_joueur(Jeu *un_jeu, Joueur *un_joueur);
void joueur_suivant(Jeu *un_jeu, Terrain_espace *un_terrain_espace);
void tour_suivant(Jeu *un_jeu, Terrain_espace *un_terrain_espace);
void afficher_ressource_joueur(Jeu *un_jeu);
void afficher_info(Jeu *un_jeu);
void creer_vision_joueur(Jeu* un_jeu, Terrain_espace* un_terrain, int indice_joueur);
void creer_vision_jeu(Jeu *un_jeu, Terrain_espace* un_terrain_espace);
void maj_vision_joueur(Jeu* un_jeu, Terrain_espace* un_terrain, int indice_joueur);
void maj_vision_jeu(Jeu *un_jeu, Terrain_espace* un_terrain_espace);
void affichage_vision_jeu(Jeu *un_jeu, Terrain_espace* un_terrain_espace);

bool construction_batiment_possible(Planete* une_planete);
bool condition_creation_unite(Joueur* un_joueur, Planete *une_planete, int choix);
bool condition_creation_batiment(Planete *une_planete, int choix);
void validation_creation_unite_planete(Jeu *un_jeu, Terrain_espace *un_terrain_espace, int indice_joueur_en_cours, int x, int y);
void ajouter_flotte_jeu(Jeu *un_jeu,Terrain_espace *un_terrain_espace, Flotte *une_flotte, int indice_joueur, int x, int y);
void colonisation_planete_flotte(Terrain_espace *un_terrain_espace, Flotte *une_flotte, Jeu *un_jeu);

void lancer_animation(Jeu *un_jeu, Animation *une_animation, int temps, SDL_Surface *ecran, int x, int y);
void maj_animation(Jeu *un_jeu,Terrain_espace *un_terrain_espace, Animation *une_animation, int temps, SDL_Surface *ecran, SDL_Surface **tab_surface, int interface_affichee);
void lancer_animation_bloquante(Jeu *un_jeu, Terrain_espace *un_terrain_espace, Animation *une_animation, SDL_Surface *ecran, int x, int y);

void lancer_animation_bloquante_combat(Jeu *un_jeu, Terrain_combat *un_terrain_combat, Animation *une_animation, SDL_Surface *ecran, int x, int y);

bool deplacement_flotte(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y);
/*bool fusion_flotte(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y);*/
bool fusion_flotte(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *flotte_depart, Flotte* flotte_arrivee);
bool test_unite_selectionnee(Jeu *un_jeu);
bool deplacement_unite_flotte(Jeu *un_jeu, Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y);
void selectionner_case_combat(Jeu *jeu,Terrain_combat *un_terrain_combat,const int x, const int y);
void placer_unite_flotte_en_haut(Terrain_combat * un_terrain_combat, Flotte * flotte);
void placer_unite_flotte_en_bas(Terrain_combat * un_terrain_combat, Flotte * flotte);
void passer_tour_combat(Jeu * jeu, Terrain_combat * un_terrain_combat);
void enlever_pt_action_ieme_joueur(Jeu * jeu,const int i, const int nb);

void sauvegarde_jeu(const Jeu *un_jeu, FILE*f);
Jeu* ouverture_jeu(FILE *f);

#endif
