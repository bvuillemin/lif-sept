/**
 * \file      affichage.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit l'affichage du jeu
 * \details   Cette classe permet l'affichage du jeu, des menus, prend en compte les actions du joueur
 */
#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#ifdef __APPLE__
#include "SDL_image.h"
#include "SDL_ttf.h"
#else
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#endif
#include "jeu.h"
#include "son.h"

typedef enum
{
	RIEN,
	PLANETE,
	PLANETE_ENNEMIE,
	FLOTTE,
	FLOTTE_ENNEMIE,
	PANNEAU_UNITE
}INTERFACE_AFFICHEE;

bool test_souris_rectangle (SDL_Rect taille_surface, int x, int y);
void initialise_sdl_rect(SDL_Rect *un_rectangle, int x, int y, int w, int h);
bool booleen_case_pointeur_souris(Terrain_espace *un_terrain_espace, int x, int y);
Case_terrain_espace* case_pointeur_souris(Terrain_espace *un_terrain_espace, int x, int y) ;
bool booleen_coordonnees_case(Terrain_espace *un_terrain_espace, int x_case, int y_case, int *x, int *y);
bool booleen_minimap_pointeur_souris(int x, int y);
void test_minimap_souris(Terrain_espace *un_terrain_espace, int x, int y);
void reinitialiser_tableau_selection_unite(Jeu *un_jeu);
void afficher_infobulle(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee, int x, int y);

SDL_Surface* affichage_ressource(Jeu *un_jeu, SDL_Surface *surface_ressource);
SDL_Surface* affichage_creation_unite(Planete* une_planete, SDL_Surface *panneau_unite);
SDL_Surface* affichage_planete(Planete* une_planete, SDL_Surface *info_planete);
SDL_Surface* affichage_planete_ennemie(Case_terrain_espace *une_case_terrain_espace, SDL_Surface *info_planete);
SDL_Surface* affichage_flotte(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *info_flotte);
SDL_Surface* affichage_flotte_ennemie(Jeu *un_jeu, SDL_Surface *info_flotte);
SDL_Surface* creer_affichage_terrain(Terrain_espace *un_terrain_espace);
SDL_Surface* creer_affichage_flotte(Terrain_espace *un_terrain_espace);
SDL_Surface* affichage_minimap(Terrain_espace *un_terrain_espace);
SDL_Surface* creer_affichage_vision(Jeu *un_jeu, Joueur* un_joueur);

void affichage_ecran(Jeu *un_jeu, Terrain_espace *un_terrain_espace, FMOD_SYSTEM *system, FMOD_SOUND *musique);
SDL_Surface* creer_affichage_terrain(Terrain_espace *un_terrain_espace);
SDL_Surface* affichage_terrain(Terrain_espace *un_terrain_espace, SDL_Surface *carte);
SDL_Surface* affichage_ressource(Jeu *un_jeu, SDL_Surface *surface_ressource);
void maj_affichage_flotte(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee);
void maj_affichage(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, INTERFACE_AFFICHEE interface_affichee, Case_terrain_espace *une_case_terrain_espace, SDL_Surface **tab_surface);
void maj_affichage_carte_terrain(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee);
void maj_affichage_vision(Jeu *un_jeu, Joueur* un_joueur, SDL_Surface *ecran, SDL_Surface **tab_surface);
void initialiser_affichage(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface);
void maj_carte_terrain(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee);
void maj_affichage_ressource(Jeu *un_jeu, SDL_Surface *ecran, SDL_Surface **tab_surface);

void saisie_texte_sdl(char* nom, SDL_Surface* ecran, SDL_Rect position_saisie_texte);

void pause();
void input_handle(void);
void menu_pause(Terrain_espace *un_terrain_espace, Jeu *un_jeu, int * exit);
void ecran_titre(void);
void affichage_ecran_acceuil(Terrain_combat *un_terrain_combat);

/*pour le combat :*/
void animation_avant_deplacement_unite(Terrain_combat * un_terrain_combat,Jeu * jeu, SDL_Surface * ecran,SDL_Surface * ecran2,SDL_Rect pos,int x, int y);
SDL_Surface * affichage_ecran_terrain_combat(const Terrain_combat *un_terrain_combat, FMOD_SYSTEM* system, FMOD_SOUND* musique);
int affichage_ecran_combat(Jeu* jeu ,Terrain_combat *un_terrain_combat, Flotte* flotte1,Flotte * flotte2,SDL_Surface * ecran, FMOD_SYSTEM* system, FMOD_SOUND* musique);
SDL_Rect coordonnee_clic(SDL_Rect position);
SDL_Rect coordonnee_case_du_clic(SDL_Rect position);
void affiche_deplacement_unite(Jeu * jeu,Terrain_combat *un_terrain_combat,SDL_Rect position,SDL_Surface * carte,SDL_Surface * bordure,SDL_Surface * ecran,SDL_Rect position_affichage_carte,SDL_Rect pos_bordure, char* infos2,FMOD_SYSTEM *system,FMOD_SOUND *son_saut_debut,FMOD_SOUND *son_saut_fin);
void selection(Jeu * jeu,Terrain_combat *un_terrain_combat,SDL_Rect position);
void affiche_info_unite(Jeu * jeu,Terrain_combat *un_terrain_combat,char * infos,SDL_Rect position);
bool attaque_ecran(Jeu * jeu,Terrain_combat * un_terrain_combat, SDL_Rect pos,Flotte* flotte1,Flotte * flotte2);
int lancer_combat_ecran(Jeu * jeu, Terrain_espace* un_terrain_espace, Flotte* flotte1,Flotte * flotte2,SDL_Surface * ecran, FMOD_SYSTEM *system, FMOD_SOUND *musique);
void clic_sur_bouton_attaque(SDL_Event evenement,SDL_Rect pos_clic,SDL_Rect pos_texte2,SDL_Rect position_affichage_carte,SDL_Rect pos_interface_carte,Jeu *jeu, Terrain_combat *un_terrain_combat,Flotte * flotte1,Flotte * flotte2, char * infos2,TTF_Font *police,SDL_Color couleur_police,SDL_Surface *carte,SDL_Surface *ecran,SDL_Surface * texte2, bool attend_attaque,bool attaque_reussi,bool continuer);
bool verifie_etat_combat(Jeu *jeu,Terrain_combat *un_terrain_combat,Flotte *flotte1,Flotte *flotte2,char *infos2,int gagnant);
void animation_explosion(Terrain_combat * un_terrain_combat,Jeu * jeu, SDL_Surface * ecran,int x, int y);
void animation_attaque(Terrain_combat * un_terrain_combat,Jeu * jeu, SDL_Surface * ecran,Case_terrain_combat *une_case,SDL_Rect pos_arrivee);

#endif
