/**
 * \file      affichage.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit l'affichage du jeu
 * \details   Cette classe permet l'affichage du jeu, des menus, prend en compte les actions du joueur
 */

#include <math.h>
#ifdef __APPLE__
#include "SDL_rotozoom.h"
#include "SDL_framerate.h"

#else
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_framerate.h>
//#include "../lib/inc/fmod.h"
#endif
#include "batiment.h"
#include "affichage.h"
#include "son.h"
#include "sauvegarde.h"


/************************************************************************/
/* Fonctions diverses                                                   */
/************************************************************************/

/**
 * \brief      Test d'un clic souris dans un rectangle
 * \details    Les coordonnées en x et y du clic souris permettent de savoir si le clic a lieu dans le rectangle passé en paramètre
 * \param      taille_surface  Rectangle SDL servant au test
 * \param      x	           Position en pixels du clic souris
 * \param      y	           Position en pixels du clic souris
 * \return     Booléen	       Renvoie vrai si le clic souris a lieu dans le rectangle
 */
bool test_souris_rectangle (const SDL_Rect taille_surface, int x, int y) /*Va tester si x et y sont dans le rectangle, utile pour les menus*/
{
	if((x >= taille_surface.x) && (x<= taille_surface.x + taille_surface.w) && (y >= taille_surface.y) && (y<= taille_surface.y + taille_surface.h))
	{
		return true;
	}
	else return false;
}

/**
 * \brief      Va définir les valeurs d'un rectangle SDL
 * \details    Utile tout le long de l'affichage, permet surtout de simplifier le code
 * \param      taille_surface  Rectangle SDL que l'on veut modifier
 * \param      x	           Position en pixels du coin supérieur gauche
 * \param      y	           Position en pixels du coin supérieur gauche
 * \param      w	           Largeur en pixels du rectangle
 * \param      h	           Hauteur en pixels du rectangle
 */
void initialise_sdl_rect(SDL_Rect *un_rectangle, int x, int y, int w, int h) /*Va modifier les atrributs d'un SDL_rect*/
{
	un_rectangle->x = x;
	un_rectangle->y = y;
	un_rectangle->w = w;
	un_rectangle->h = h;
}


/**
 * \brief      Renvoie une case grâce aux coordonnéees en pixels
 * \details    Fonction qui va récuperer les coordonnées sur l'écran d'une case et les mettre dans x et y, ou renvoyer false si elle n'est pas affichée
 * \param      un_terrain_espace  Le terrain pour récupérer les coordonnées de l'affichage
 * \param      x_case	          Position en pixels du clic souris
 * \param      y_case	          Position en pixels du clic souris
 * \param      x	              Pointeur sur entier
 * \param      y	              Pointeur sur entier
 * \return     Booléen	          Renvoie vrai si le clic souris a lieu sur une case
 */
bool booleen_coordonnees_case(const Terrain_espace *un_terrain_espace, int x_case, int y_case, int *x, int *y)
{
	SDL_Rect affichage_map = {get_affichage_x(un_terrain_espace) - 1, get_affichage_y(un_terrain_espace) - 1, get_affichage_x(un_terrain_espace) + TAILLE_TERRAIN_ESPACE_X, get_affichage_y(un_terrain_espace) + TAILLE_TERRAIN_ESPACE_Y};
	if(test_souris_rectangle(affichage_map, x_case * 100, y_case *100))
	{
		*x = (x_case * 100) - affichage_map.x;
		*y = (y_case * 100) + TAILLE_BARRE_RESSOURCE - affichage_map.y;
		return true;
	}
	else return false;
}


/**
 * \brief      Test d'un clic souris sur la minimap
 * \param      x	           Position en pixels du clic souris
 * \param      y	           Position en pixels du clic souris
 * \return     Booléen	       Renvoie vrai si le clic souris a lieu sur la minimap
 */
bool booleen_minimap_pointeur_souris(int x, int y)
{
	SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, TAILLE_MINIMAP_X, TAILLE_MINIMAP_Y};
	return test_souris_rectangle (position_minimap, x, y);
}


/**
 * \brief      Va changer l'affichage en fonction du clic souris qui est fait
 * \details    Le clic sur la minimap permet un déplacement sur le terrain
 * \param      un_terrain_espace  Le terrain grâce auquel se fait l'affichage
 * \param      x	              Position en pixels du clic souris
 * \param      y	              Position en pixels du clic souris
 */
void test_minimap_souris(Terrain_espace *un_terrain_espace, int x, int y)
{
	SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};
    int x_calcule, y_calcule;

    x = x - position_minimap.x;
    y = y - position_minimap.y;

    x_calcule = x * ((float)TAILLE_FENETRE_X/TAILLE_MINIMAP_X);
    y_calcule = y * ((float)TAILLE_FENETRE_Y/TAILLE_MINIMAP_Y);

    if((x_calcule > 0) && (x_calcule <= (get_taille_espace_x(un_terrain_espace) *100) - TAILLE_TERRAIN_ESPACE_X) && (y_calcule > 0) && (y_calcule < (get_taille_espace_y(un_terrain_espace) * 100)- TAILLE_TERRAIN_ESPACE_Y))
    {
		set_affichage_x(un_terrain_espace, x_calcule);
		set_affichage_y(un_terrain_espace, y_calcule);
    }
}


/**
 * \brief      Fonction qui va renvoyer la case pointée par la souris
 * \details    Les coordonnées en x et y du clic souris permettent de savoir quelle case a été sélectionnée
 * \param      un_terrain_espace           Rectangle SDL servant au test
 * \param      x	                       Position en pixels du clic souris
 * \param      y	                       Position en pixels du clic souris
 * \return     Case_terrain_espace	       Renvoie la case pointée par les coordonnées 
 */
Case_terrain_espace* case_pointeur_souris(const Terrain_espace *un_terrain_espace, int x, int y)
{
	x = (get_affichage_x(un_terrain_espace) + x) / 100;
	y = (get_affichage_y(un_terrain_espace) + y - 33) / 100;
	if ((x >= 0) && (x < get_taille_espace_x(un_terrain_espace)) && (y >= 0) && (y < get_taille_espace_y(un_terrain_espace)))
	{
		return get_case_terrain_espace(un_terrain_espace, x, y);
	}
	else return NULL;
}

/**
 * \brief      Remet à 0 le tableau d'unités sélectionnées
 * \details    Ce tableau prend les unités en cours de sélection
 * \param      un_jeu  Pointeur sur le jeu
 */
void reinitialiser_tableau_selection_unite(Jeu *un_jeu)
{
    int i;
    for(i=0;i<10;i++)
    {
        set_ieme_unite_selectionne(un_jeu, i, false);
    }
}


/************************************************************************/
/* Fonctions d'affichage des infobulles                                 */
/************************************************************************/

/**
 * \brief      Détaille les infobulles des bâtiments
 * \param      fond        Surface du fond des infobulles et sur laquelle sera blitté les informations
 * \param      i	       Bâtiment dont on veut afficher l'infobulle
 */
void afficher_infobulle_batiment(SDL_Surface* fond, int i)
{
	SDL_Surface* une_ligne;
	SDL_Rect position;
	TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
	char ligne[200] = "";
	int j = 3;

	if(i == 0)
	{
		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Quartier general");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		SDL_FreeSurface(une_ligne);
		TTF_CloseFont(police);

		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Indispensable a la mise en place");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "d'installations sur la planete, ce");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "batiment  est  a  construire  en");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "priorite");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 16;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_QUARTIER_GENERAL);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);
        TTF_CloseFont(police);
	}
	if(i == 1)
	{
		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Mine de metal");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);
		SDL_FreeSurface(une_ligne);

		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Le  metal  est  devenu,  avec ");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "l'apparrition   des   vaisseaux");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "spatiaux, un bien indispensable");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 16;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Metal: +100");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_METAL);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);
		TTF_CloseFont(police);
	}
	if(i == 2)
	{
		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Mine d'or");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);
		SDL_FreeSurface(une_ligne);

		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "L'or   est   la   ressource  la  plus ");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "precieuse, converti en monnaie");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "il   nous   fournira   les   fonds");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "necessaires  a  la  guerre");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 15;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Argent: +100");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_METAL);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);
		TTF_CloseFont(police);
	}
	if(i == 3)
	{
		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Raffinerie");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);
		SDL_FreeSurface(une_ligne);

		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Le carburant est extrait du sous");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "sol et nous permet  d'emmener");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "nos vaisseaux jusqu'au fin fond");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "de la galaxie");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 15;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Carburant: +100");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_CARBURANT);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);
		TTF_CloseFont(police);
	}
	if(i == 4)
	{
		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Habitations");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);
		SDL_FreeSurface(une_ligne);

		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "La construction sur nos colonies");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "d'habitations   nous   fournira");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "la  main  d'oeuvre,  vitale  a");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "l'effort   de   guerre");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 15;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Population: +100");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_POPULATION);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);
		TTF_CloseFont(police);
	}
	if(i == 5)
	{
		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Spatioport");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);
		SDL_FreeSurface(une_ligne);

		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Le  spatioport  nous  autorisera");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "a  un  developpement  toujours");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "plus  grand,  pour  partir  a  la ");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "conquete de l'espace");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 15;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Active construction des unites");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_SPATIOPORT);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);
		TTF_CloseFont(police);
	}
}


/**
 * \brief      Détaille les infobulles des unités.
 * \param      fond        Surface du fond des infobulles et sur laquelle sera blitté les informations
 * \param      un_jeu      Pointeur sur jeu pour récupérer des informations
 * \param      i	       Indice de l'unité dont on veut récupérer les informations
 */
void afficher_infobulle_unite(const Jeu* un_jeu, SDL_Surface* fond, int i)
{
	SDL_Surface* une_ligne;
	Unite *une_unite;
	SDL_Rect position;
	TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
	char ligne[200] = "";
	int j = 3;

	une_unite = get_unite_i_flotte(get_flotte_en_cours(un_jeu), i);

	police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
	sprintf(ligne, "Type unite");
	une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
	initialise_sdl_rect(&position, 4, j, 0, 0);
	SDL_BlitSurface(une_ligne, NULL, fond, &position);
	j += 18;
	TTF_CloseFont(police);
	SDL_FreeSurface(une_ligne);

	police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
	sprintf(ligne, "Point de vie: %d", get_pt_vie(une_unite));
	une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
	initialise_sdl_rect(&position, 4, j, 0, 0);
	j += 13;
	SDL_BlitSurface(une_ligne, NULL, fond, &position);
	SDL_FreeSurface(une_ligne);

	sprintf(ligne, "Attaque: %d", get_pt_attaque(une_unite));
	une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
	initialise_sdl_rect(&position, 4, j, 0, 0);
	j += 13;
	SDL_BlitSurface(une_ligne, NULL, fond, &position);
	SDL_FreeSurface(une_ligne);

	sprintf(ligne, "Action: %d", get_pt_action(une_unite));
	une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
	initialise_sdl_rect(&position, 4, j, 0, 0);
	j += 13;
	SDL_BlitSurface(une_ligne, NULL, fond, &position);
	SDL_FreeSurface(une_ligne);

	sprintf(ligne, "Point de mouvement: %d", get_pt_mouvement_unite(une_unite));
	une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
	initialise_sdl_rect(&position, 4, j, 0, 0);
	j += 13;
	SDL_BlitSurface(une_ligne, NULL, fond, &position);
	SDL_FreeSurface(une_ligne);
	TTF_CloseFont(police);

}


/**
 * \brief      Détaille les infobulles pour créer les unités
 * \param      fond        Surface du fond des infobulles et sur laquelle sera blitté les informations
 * \param      i	       Unité dont on veut afficher l'infobulle
 */
void afficher_infobulle_creation_unite(SDL_Surface* fond,int i)
{
	SDL_Surface* une_ligne;
	SDL_Rect position;
	TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
	char ligne[200] = "";
	int j = 3;

	if(i==0)
	{
		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Type unite");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);
		SDL_FreeSurface(une_ligne);

		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de vie: %d", PT_VIE_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Attaque: %d", PT_ATTAQUE_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Action: %d", PT_ACTION_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Point de mouvement: %d", PT_MOUVEMENT_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Point de mouvement-combat: %d", PT_DEPLACEMENT_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "-----------");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Metal: %d", NB_METAL_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Argent: %d", NB_ARGENT_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Carburant: %d", NB_CARBURANT_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Population: %d", NB_POPULATION_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);
		TTF_CloseFont(police);
	}
	if(i==1)
	{
		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Type unite");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);
		SDL_FreeSurface(une_ligne);

		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de vie: %d", PT_VIE_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Attaque: %d", PT_ATTAQUE_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Action: %d", PT_ACTION_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Point de mouvement: %d", PT_MOUVEMENT_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Point de mouvement-combat: %d", PT_DEPLACEMENT_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "-----------");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Metal: %d", NB_METAL_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Argent: %d", NB_ARGENT_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Carburant: %d", NB_CARBURANT_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Population: %d", NB_POPULATION_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);
		TTF_CloseFont(police);
	}
	if(i==2)
	{
		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Type unite");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);
		SDL_FreeSurface(une_ligne);

		police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de vie: %d", PT_VIE_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Attaque: %d", PT_ATTAQUE_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Action: %d", PT_ACTION_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Point de mouvement: %d", PT_MOUVEMENT_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Point de mouvement-combat: %d", PT_DEPLACEMENT_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "-----------");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Metal: %d", NB_METAL_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Argent: %d", NB_ARGENT_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Carburant: %d", NB_CARBURANT_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Population: %d", NB_POPULATION_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		SDL_FreeSurface(une_ligne);
		TTF_CloseFont(police);
	}
}


/**
 * \brief      Choisit l'infobulle qui sera affichée
 * \param      un_jeu             Pointeur sur le jeu pour récupérer des informations
 * \param      un_terrain_espace  Pointeur sur un Terrain_espace 
 * \param      ecran			  Pointeur sur l'écran pour blitter les informations
 * \param      tab_surface	      Tableau de pointeurs sur surface pour blitter les informations
 * \param      interface_affichee Indique l'interface en cours d'affichage		
 * \param      x			      Coordonnées en pixel de l'endroit où afficher l'infobulle
 * \param      y			      Coordonnées en pixel de l'endroit où afficher l'infobulle
 */
void afficher_infobulle(const Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee, int x, int y)
{
	SDL_Surface* fond = NULL;
	SDL_Rect position_fond = {2, 2, 0, 0};
    SDL_Rect position_infobulle = {0, 0, 0, 0};
	SDL_Rect test = {0, 0, 0, 0};
	int taille_infobulle_x = 200, taille_infobulle_y = 100;
	int i;

	/*les infobulles vont dépendre de l'interface affichée et de la position de la souris*/
	if((interface_affichee == PLANETE) || (interface_affichee == FLOTTE) || (interface_affichee == PANNEAU_UNITE))
	{
		/*pour initialiser la taille de l'infobulle*/
		if(interface_affichee == PLANETE)
		{

		}
		if(interface_affichee == FLOTTE)
		{

		}
		if(interface_affichee == PANNEAU_UNITE)
		{
			taille_infobulle_x = 220;
			taille_infobulle_y = 180;
		}

		/*initialisation de la position de l'infobulle*/
		if (((x + taille_infobulle_x) >= TAILLE_FENETRE_X) && ((y + taille_infobulle_y) >= TAILLE_FENETRE_Y))
		{
			initialise_sdl_rect(&position_infobulle, x - taille_infobulle_x, y- taille_infobulle_y, taille_infobulle_x, taille_infobulle_y);
		}
		if (((x + taille_infobulle_x) >= TAILLE_FENETRE_X) && ((y + taille_infobulle_y) < TAILLE_FENETRE_Y))
		{
			initialise_sdl_rect(&position_infobulle, x - taille_infobulle_x, y, taille_infobulle_x, taille_infobulle_y);
		}
		if (((x + taille_infobulle_x) < TAILLE_FENETRE_X) && ((y + taille_infobulle_y) >= TAILLE_FENETRE_Y))
		{
			initialise_sdl_rect(&position_infobulle, x, y - taille_infobulle_y, taille_infobulle_x, taille_infobulle_y);
		}
		if(((x + taille_infobulle_x) < TAILLE_FENETRE_X) && ((y + taille_infobulle_y) < TAILLE_FENETRE_Y))
		{
			initialise_sdl_rect(&position_infobulle, x, y, taille_infobulle_x, taille_infobulle_y);
		}

		/*test de la position du pointeur dsouris et affichage des informations adéquates*/
		tab_surface[12] = SDL_CreateRGBSurface(SDL_HWSURFACE, taille_infobulle_x, taille_infobulle_y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
		SDL_FillRect(tab_surface[12], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
		fond = SDL_CreateRGBSurface(SDL_HWSURFACE, taille_infobulle_x - 4, taille_infobulle_y - 4, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
		SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 128, 128, 128));
		SDL_BlitSurface(fond, NULL, tab_surface[12], &position_fond);
		SDL_FreeSurface(fond);

		if(interface_affichee == PLANETE || interface_affichee == PANNEAU_UNITE)
		{
			for(i=0;i<6;i++)
			{
				initialise_sdl_rect(&test, 10+ 120*i, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
				if(test_souris_rectangle(test, x, y))
				{
					afficher_infobulle_batiment(tab_surface[12], i);
					SDL_BlitSurface(tab_surface[12], NULL, ecran, &position_infobulle);
					SDL_Flip(ecran);
				}
			}
		}
		if(interface_affichee == FLOTTE)
		{
			for(i=0;i<5;i++)
			{
				initialise_sdl_rect(&test, 10+ 120*i, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
				if(test_souris_rectangle(test, x, y))
				{
					afficher_infobulle_unite(un_jeu, tab_surface[12], i);
					SDL_BlitSurface(tab_surface[12], NULL, ecran, &position_infobulle);
					SDL_Flip(ecran);
				}
			}
		}
		if(interface_affichee == PANNEAU_UNITE)
		{
			for(i=0;i<3;i++)
			{
				initialise_sdl_rect(&test, TAILLE_TERRAIN_ESPACE_X - 190, 40 + 120*i, 100, 100);
				if(test_souris_rectangle(test, x, y))
				{
					afficher_infobulle_creation_unite(tab_surface[12], i);
					SDL_BlitSurface(tab_surface[12], NULL, ecran, &position_infobulle);
					SDL_Flip(ecran);
				}
			}
		}
        SDL_FreeSurface(tab_surface[12]);
	}
}


/************************************************************************/
/* Fonctions d'affichage des éléments de la carte                       */
/************************************************************************/

/**
 * \brief      Surface sur laquelle les ressource sont affichées
 * \param      un_jeu             Pointeur sur le jeu pour récupérer des informations
 */
SDL_Surface* affichage_ressource(const Jeu *un_jeu)
{
	SDL_Surface *surface_ressource = NULL;
    SDL_Surface *nom_ressource = NULL;
    SDL_Surface *nombre_tour = NULL;
    SDL_Rect position;
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    char ressource[200] = "";
    char tour[50] = "";

    police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 18);
    surface_ressource = IMG_Load("../data/graphiques/images/interface_ressource.png");

	/*affichage des ressources*/
    sprintf(ressource, "%d", get_metal_joueur(get_joueur_en_cours(un_jeu)));
    nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
    initialise_sdl_rect(&position, 75, 4, 0, 0);
    SDL_BlitSurface(nom_ressource, NULL, surface_ressource, &position);
    SDL_FreeSurface(nom_ressource);

	sprintf(ressource, "%d", get_argent_joueur(get_joueur_en_cours(un_jeu)));
	nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
	initialise_sdl_rect(&position, 75 + 150, 4, 0, 0);
	SDL_BlitSurface(nom_ressource, NULL, surface_ressource, &position);
	SDL_FreeSurface(nom_ressource);

	sprintf(ressource, "%d", get_carburant_joueur(get_joueur_en_cours(un_jeu)));
	nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
	initialise_sdl_rect(&position, 75 + 300, 4, 0, 0);
	SDL_BlitSurface(nom_ressource, NULL, surface_ressource, &position);
	SDL_FreeSurface(nom_ressource);

	sprintf(ressource, "%d", get_population_joueur(get_joueur_en_cours(un_jeu)));
	nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
	initialise_sdl_rect(&position, 75 + 450, 4, 0, 0);
	SDL_BlitSurface(nom_ressource, NULL, surface_ressource, &position);
	SDL_FreeSurface(nom_ressource);

    sprintf(tour, "Tour en cours: %d   Joueur en cours: %d", get_tour_en_cours(un_jeu), get_indice_joueur_en_cours(un_jeu));
    nombre_tour = TTF_RenderText_Blended(police, tour, couleur_blanche);
    position.x = TAILLE_FENETRE_X - 400;
    SDL_BlitSurface(nombre_tour, NULL, surface_ressource, &position);
    SDL_FreeSurface(nombre_tour);
    TTF_CloseFont(police);

    return surface_ressource;
}


/**
 * \brief      Surface sur laquelle la création des unités 
 * \param      une_planete           Pointeur sur la planète dont on veut créer les unités
 */
SDL_Surface* affichage_creation_unite(const Planete* une_planete)
{
	SDL_Surface *panneau_unite = NULL;
    SDL_Surface *unite1;
	SDL_Surface *unite2;
	SDL_Surface *unite3;
    SDL_Surface *surface_texte_unite;
    SDL_Rect position_unite;
    SDL_Rect position_texte_unite;
    char texte_unite[100];
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    int i;
    panneau_unite = IMG_Load("../data/graphiques/images/interface_barrelaterale.png");
	unite1 = IMG_Load("../data/graphiques/images/unite1.png");
	unite2 = IMG_Load("../data/graphiques/images/unite2.png");
	unite3 = IMG_Load("../data/graphiques/images/unite3.png");
    police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 14);

    for(i=0;i<3;i++)
    {
		initialise_sdl_rect(&position_unite, 10, 20 + 120*i, 0, 0);
		initialise_sdl_rect(&position_texte_unite, 15, 20 + 120 *i, 0, 0);
		if(i==0)
		{
			sprintf(texte_unite, "Chasseur");
			SDL_BlitSurface(unite1, NULL, panneau_unite, &position_unite);
		}
		if(i==1)
		{
			sprintf(texte_unite, "Destroyer");
			SDL_BlitSurface(unite2, NULL, panneau_unite, &position_unite);
		}
		if(i==2)
		{
			sprintf(texte_unite, "Destructeur");
			SDL_BlitSurface(unite3, NULL, panneau_unite, &position_unite);
		}

        surface_texte_unite = TTF_RenderText_Blended(police, texte_unite, couleur_blanche);
        SDL_BlitSurface(surface_texte_unite, NULL, panneau_unite, &position_texte_unite);
        SDL_FreeSurface(surface_texte_unite);
        if(une_planete->unite_nb_tour_restant > 0)
        {
            sprintf(texte_unite, "Tour %d", une_planete->unite_nb_tour_restant);
            surface_texte_unite = TTF_RenderText_Blended(police, texte_unite, couleur_blanche);
            initialise_sdl_rect(&position_texte_unite, 10, 40 + 120 *i, 0, 0);
            SDL_BlitSurface(surface_texte_unite, NULL, panneau_unite, &position_texte_unite);
            SDL_FreeSurface(surface_texte_unite);
        }
    }

    TTF_CloseFont(police);
    SDL_FreeSurface(unite1);
	SDL_FreeSurface(unite2);
	SDL_FreeSurface(unite3);

    return panneau_unite;
}

/**
 * \brief      Surface sur laquelle on affiche les infos de planète
 * \param      une_planete           Pointeur sur la planète dont on affiche les infos
 */
SDL_Surface* affichage_planete(Planete* une_planete)
{
	SDL_Surface *info_planete = NULL;
    SDL_Surface *planete = NULL;
    SDL_Surface *fond_planete = NULL;
    SDL_Surface *batiment = NULL;
	SDL_Surface *construction = NULL;
	SDL_Surface *interdiction = NULL;
    SDL_Surface *bouton_unite = NULL;
    SDL_Rect position_texte;
    SDL_Rect position_batiment;
    SDL_Rect position_bouton_unite;
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    char texte_planete[200] = "";
    char texte_batiment[100] = "";
    int i;

    /*affichage de l'interface*/
	info_planete = IMG_Load("../data/graphiques/images/interface_bas.png");
    construction = IMG_Load("../data/graphiques/images/construction.png");
    interdiction = IMG_Load("../data/graphiques/images/interdit.png");

    police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 14);
    fond_planete = IMG_Load("../data/graphiques/images/interface_bas.png");

    sprintf(texte_planete, "Nom de la planete: %s Occupation de la planete: %d/%d Production: Metal:%d Argent:%d Carburant:%d Population:%d",
get_nom_planete(une_planete), get_taille_utilisee(une_planete), get_taille_planete(une_planete),
get_metal(une_planete), get_argent(une_planete), get_carburant(une_planete), get_population(une_planete));

    planete = TTF_RenderText_Blended(police, texte_planete, couleur_blanche);
    initialise_sdl_rect(&position_texte, 10, 10, 0, 0);
    SDL_BlitSurface(planete, NULL, fond_planete, &position_texte);
    SDL_FreeSurface(planete);

    bouton_unite = IMG_Load("../data/graphiques/images/Creer_unite.png");
    initialise_sdl_rect(&position_bouton_unite, TAILLE_FENETRE_X -150, 35, 100, 100);
    SDL_BlitSurface(bouton_unite, NULL, fond_planete, &position_bouton_unite);
    SDL_FreeSurface(bouton_unite);

    for(i=0;i<6;i++)
    {
        switch(i)
		{
		case 0:
			batiment = IMG_Load("../data/graphiques/images/batiment_mairie.png");
			break;
		case 1:
			batiment = IMG_Load("../data/graphiques/images/batiment_mine.png");
			break;
		case 2:
			batiment = IMG_Load("../data/graphiques/images/batiment_mine_or.png");
			break;
		case 3:
			batiment = IMG_Load("../data/graphiques/images/batiment_raffinerie.png");
			break;
		case 4:
			batiment = IMG_Load("../data/graphiques/images/batiment_population.png");
			break;
		case 5:
			batiment = IMG_Load("../data/graphiques/images/batiment_port.png");
			break;
		default :
			break;
		}

        sprintf(texte_batiment, "%d", get_ieme_batiment(une_planete, i));
        planete = TTF_RenderText_Blended(police, texte_batiment, couleur_blanche);
        initialise_sdl_rect(&position_texte, 15 + 120 * i, 40, 0, 0);
        initialise_sdl_rect(&position_batiment, 10 + 120*i, 35, 0, 0);
        SDL_BlitSurface(batiment, NULL, fond_planete, &position_batiment);

		if((i == get_planete_batiment_en_cours(une_planete)) && (get_planete_batiment_nb_tour_restant(une_planete) != 0))
		{
			SDL_BlitSurface(construction, NULL, fond_planete, &position_batiment);
		}
		if((i != get_planete_batiment_en_cours(une_planete)) && (get_planete_batiment_nb_tour_restant(une_planete) > 0))
		{
			SDL_BlitSurface(interdiction, NULL, fond_planete, &position_batiment);
		}
        SDL_BlitSurface(planete, NULL, fond_planete, &position_texte);
        SDL_FreeSurface(planete);

        if((i == get_planete_batiment_en_cours(une_planete)) && (get_planete_batiment_nb_tour_restant(une_planete) != 0))
        {
            sprintf(texte_batiment, "Tours: %d", une_planete->batiment_nb_tour_restant);
            initialise_sdl_rect(&position_texte, 15 + 120 * i, 60, 0, 0);
            planete = TTF_RenderText_Blended(police, texte_batiment, couleur_blanche);
            SDL_BlitSurface(planete, NULL, fond_planete, &position_texte);
            SDL_FreeSurface(planete);
        }

        SDL_FreeSurface(batiment);

    }


    SDL_FreeSurface(construction);
    SDL_FreeSurface(interdiction);
    SDL_FreeSurface(info_planete);
    TTF_CloseFont(police);

    return fond_planete;
}

/**
 * \brief      Surface sur laquelle on affiche les infos de planète ennemie
 * \param      une_planete           Pointeur sur la planète ennemie dont on affiche les infos
 */
SDL_Surface* affichage_planete_ennemie(const Case_terrain_espace *une_case_terrain_espace)
{
	SDL_Surface *info_planete = NULL;
	SDL_Surface *planete = NULL;
	SDL_Rect position_texte;
	TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
	char texte_planete[200] = "";
	Planete *une_planete = get_planete(une_case_terrain_espace);

	/*affichage de l'interface*/
	info_planete = IMG_Load("../data/graphiques/images/interface_bas.png");

	police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 14);

	sprintf(texte_planete, "Nom de la planete: %s", get_nom_planete(une_planete));
	planete = TTF_RenderText_Blended(police, texte_planete, couleur_blanche);
	initialise_sdl_rect(&position_texte, 10, 10, 0, 0);
	SDL_BlitSurface(planete, NULL, info_planete, &position_texte);

	TTF_CloseFont(police);
	SDL_FreeSurface(planete);

	return info_planete;
}

/**
 * \brief      Surface sur laquelle on affiche les infos de flotte
 * \param      un_jeu                    Pointeur sur le jeu
 * \param      un_terrain_espace         Pointeur sur le Terrain_espace pour vérifier certains boutons à afficher
 */
SDL_Surface* affichage_flotte(const Jeu *un_jeu, const Terrain_espace *un_terrain_espace)
{
	SDL_Surface *info_flotte = NULL;
    SDL_Surface *flotte = NULL;
	SDL_Surface *une_unite1 = NULL;
	SDL_Surface *une_unite2 = NULL;
	SDL_Surface *une_unite3 = NULL;
	SDL_Surface *selection = NULL;
	SDL_Surface *bouton_coloniser = NULL;
	SDL_Surface *bouton_attaquer = NULL;
	SDL_Rect position_texte = {10, 10, 0, 0};
    SDL_Rect position_une_unite;
	SDL_Rect position_bouton_coloniser = {TAILLE_FENETRE_X - 150, 35, 0, 0};
    int i;
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    char texte_flotte[200] = "";
    Flotte *une_flotte = get_flotte_en_cours(un_jeu);
	TYPE_VAISSEAU type;

	/*affichage de l'interface*/
	info_flotte = IMG_Load("../data/graphiques/images/interface_bas.png");

	/*affichage des informations d'une flotte*/
    police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 14);

    sprintf(texte_flotte, "Coordonnes de la flotte: %d %d, pt mouvement %d, taille : %d", get_x_flotte(une_flotte), get_y_flotte(une_flotte), get_pt_mouvement_espace_flotte(une_flotte), get_taille_flotte(une_flotte));
    flotte = TTF_RenderText_Blended(police, texte_flotte, couleur_blanche);
    SDL_BlitSurface(flotte, NULL, info_flotte, &position_texte);
    SDL_FreeSurface(flotte);

	/*affichage des unités*/
    une_unite1 = IMG_Load("../data/graphiques/images/unite1.png");
	une_unite2 = IMG_Load("../data/graphiques/images/unite2.png");
	une_unite3 = IMG_Load("../data/graphiques/images/unite3.png");
	selection = IMG_Load("../data/graphiques/images/selection.png");

    for(i=0; i<get_taille_flotte(une_flotte);i++)
    {
		initialise_sdl_rect(&position_une_unite, 10 + 120*i, 35, 0, 0);
		type = get_type_vaisseau(get_unite_i_flotte(une_flotte, i));
        if(get_ieme_unite_selectionnee(un_jeu, i) == true)
        {
			if(type == Chasseur)
			{
				SDL_BlitSurface(une_unite1, NULL, info_flotte, &position_une_unite);
				SDL_BlitSurface(selection, NULL, info_flotte, &position_une_unite);
			}
			if(type == Destroyer)
			{
				SDL_BlitSurface(une_unite2, NULL, info_flotte, &position_une_unite);
				SDL_BlitSurface(selection, NULL, info_flotte, &position_une_unite);
			}
			if(type == Destructeur)
			{
				SDL_BlitSurface(une_unite3, NULL, info_flotte, &position_une_unite);
				SDL_BlitSurface(selection, NULL, info_flotte, &position_une_unite);
			}
        }
        else
        {
			if(type == Chasseur)
			{
				SDL_BlitSurface(une_unite1, NULL, info_flotte, &position_une_unite);
			}
			if(type == Destroyer)
			{
				SDL_BlitSurface(une_unite2, NULL, info_flotte, &position_une_unite);
			}
			if(type == Destructeur)
			{
				SDL_BlitSurface(une_unite3, NULL, info_flotte, &position_une_unite);
			}
        }

        sprintf(texte_flotte, "%d/%d", get_pt_vie(get_unite_i_flotte(une_flotte, i)), get_pt_vie_total(get_unite_i_flotte(une_flotte, i)));
        flotte = TTF_RenderText_Blended(police, texte_flotte, couleur_blanche);
        initialise_sdl_rect(&position_texte, 15 + 120*i, 40, 0, 0);
        SDL_BlitSurface(flotte, NULL, info_flotte, &position_texte);
        SDL_FreeSurface(flotte);
    }

	/*affichage du bouton pour coloniser une planète*/
	if((get_type_case_terrain_espace(get_case_terrain_espace(un_terrain_espace, get_x_flotte(une_flotte), get_y_flotte(une_flotte))) == 'P') && (!get_planete_colonisee(get_planete_terrain_espace(un_terrain_espace, get_x_flotte(une_flotte), get_y_flotte(une_flotte)))))
	{
		bouton_coloniser = IMG_Load("../data/graphiques/images/Attaquer.png");
		SDL_BlitSurface(bouton_coloniser, NULL, info_flotte, &position_bouton_coloniser);
	}

	/*affichage du bouton pour apturer une planète ennemie*/
	if((get_type_case_terrain_espace(get_case_terrain_espace(un_terrain_espace, get_x_flotte(une_flotte), get_y_flotte(une_flotte))) == 'P') && (get_indice_joueur_planete(get_planete_terrain_espace(un_terrain_espace, get_x_flotte(une_flotte), get_y_flotte(une_flotte))) != get_indice_joueur_flotte(une_flotte)))
	{
		bouton_attaquer = IMG_Load("../data/graphiques/images/Attaquer.png");
		SDL_BlitSurface(bouton_attaquer, NULL, info_flotte, &position_bouton_coloniser);
	}

    TTF_CloseFont(police);
    SDL_FreeSurface(une_unite1);
	SDL_FreeSurface(une_unite2);
	SDL_FreeSurface(une_unite3);
    SDL_FreeSurface(selection);
	SDL_FreeSurface(bouton_coloniser);
	SDL_FreeSurface(bouton_attaquer);

    return info_flotte;
}

/**
 * \brief      Surface sur laquelle on affiche les infos de flotte ennemie
 * \param      un_jeu                    Pointeur sur le jeu
 */
SDL_Surface* affichage_flotte_ennemie(const Jeu *un_jeu)
{
	SDL_Surface *info_flotte =NULL;
	SDL_Surface *flotte = NULL;
	SDL_Surface *fond_flotte = NULL;
	SDL_Surface *une_unite = NULL;
	SDL_Rect position;
	SDL_Rect position_une_unite;
	int i;
	TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
	char texte_flotte[200] = "";
	Flotte *une_flotte = get_flotte_en_cours(un_jeu);

    /*affichage de l'interface*/
	info_flotte = IMG_Load("../data/graphiques/images/interface_bas.png");

	police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 14);
	fond_flotte = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(fond_flotte, NULL, SDL_MapRGB(fond_flotte->format, 60, 60, 60));
	SDL_SetColorKey(fond_flotte, SDL_SRCCOLORKEY, SDL_MapRGB(fond_flotte->format, 60, 60, 60));

	sprintf(texte_flotte, "Coordonnes de la flotte: %d %d, taille : %d", get_x_flotte(une_flotte), get_y_flotte(une_flotte), get_taille_flotte(une_flotte));
	flotte = TTF_RenderText_Blended(police, texte_flotte, couleur_blanche);
	initialise_sdl_rect(&position, 10, 10, 0, 0);
	SDL_BlitSurface(flotte, NULL, fond_flotte, &position);
	SDL_FreeSurface(flotte);

	une_unite = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	for(i=0; i<une_flotte->taille_flotte;i++)
	{
		une_unite = IMG_Load("../data/graphiques/images/?.png");;
		initialise_sdl_rect(&position_une_unite, 10 + 120*i, 35, 0, 0);
		SDL_BlitSurface(une_unite, NULL, fond_flotte, &position_une_unite);
	}

	TTF_CloseFont(police);
	SDL_FreeSurface(une_unite);

	return fond_flotte;
}

/**
 * \brief      Surface où l'on crée l'affichage du terrain
 * \details    On parcourt le terrain pour afficher les informations nécessaires puis on stocke la surface en mémoire pour éviter de la recréer
 * \param      un_terrain_espace         Pointeur sur le Terrain_espace
 */
SDL_Surface* creer_affichage_terrain(const Terrain_espace *un_terrain_espace)
{
	SDL_Surface *carte = NULL;
	SDL_Surface *planete1 = NULL;
	SDL_Surface *planete2 = NULL;
	SDL_Surface *planete3 = NULL;
	SDL_Surface *image_une_case = NULL;
    SDL_Surface *fond = NULL;

    SDL_Rect position_planete;
	SDL_Rect position;
	int i, j;
	Case_terrain_espace *une_case;

	position_planete.x = 0;
	position_planete.y = 0;
	position.x = 0;
	position.y = 0;

	carte = SDL_CreateRGBSurface(SDL_HWSURFACE, get_taille_espace_x(un_terrain_espace) * 100, get_taille_espace_y(un_terrain_espace) * 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	planete1 = IMG_Load("../data/graphiques/images/1.png");
	planete2 = IMG_Load("../data/graphiques/images/2.png");
	planete3 = IMG_Load("../data/graphiques/images/3.png");
	image_une_case = IMG_Load("../data/graphiques/images/quadrillage.png");
    fond = IMG_Load("../data/graphiques/images/fond.png");
    SDL_BlitSurface(fond, NULL, carte, &position);
	for(i=0;i< get_taille_espace_x(un_terrain_espace);i++)
	{
		for(j=0;j< get_taille_espace_y(un_terrain_espace);j++)
		{
			une_case = get_case_terrain_espace(un_terrain_espace, i, j);
			if(get_type_case_terrain_espace(une_case) == 'P')
			{
				initialise_sdl_rect(&position_planete, i * 100, j * 100, 0, 0);
				if(get_planete_colonisee(get_planete(une_case))== true)
				{
					if(get_indice_joueur_planete(get_planete(une_case))== 0)
					{
						SDL_BlitSurface(planete1, NULL, carte, &position_planete);
					}
					if(get_indice_joueur_planete(get_planete(une_case)) == 1)
					{
						SDL_BlitSurface(planete2, NULL, carte, &position_planete);
					}
				}
				else
				{
					SDL_BlitSurface(planete3, NULL, carte, &position_planete);
				}
			}
			SDL_BlitSurface(image_une_case, NULL, carte, &position);
		}
	}

    SDL_FreeSurface(planete1);
	SDL_FreeSurface(planete2);
	SDL_FreeSurface(planete3);
    SDL_FreeSurface(image_une_case);
    SDL_FreeSurface(fond);

	return carte;
}

/**
 * \brief      Surface où l'on crée l'affichage des flottes
 * \details    On parcourt le terrain pour afficher les informations nécessaires puis on stocke la surface en mémoire pour éviter de la recréer
 * \param      un_terrain_espace         Pointeur sur le Terrain_espace
 */
SDL_Surface* creer_affichage_flotte(const Terrain_espace *un_terrain_espace)
{
    SDL_Surface *carte = NULL;

	SDL_Surface *flotte1_bleu = NULL;
	SDL_Surface *flotte2_bleu = NULL;
	SDL_Surface *flotte3_bleu = NULL;
	SDL_Surface *flotte1_rouge = NULL;
	SDL_Surface *flotte2_rouge = NULL;
	SDL_Surface *flotte3_rouge = NULL;

	SDL_Rect position_flotte;
	SDL_Rect position;
	SDL_Surface *image_une_case = NULL;
	int i, j;
	Case_terrain_espace *une_case;
	TYPE_VAISSEAU type;

	position_flotte.x = 0;
	position_flotte.y = 0;
	position.x = 0;
	position.y = 0;

	carte = SDL_CreateRGBSurface(SDL_HWSURFACE, get_taille_espace_x(un_terrain_espace)* 100, get_taille_espace_y(un_terrain_espace) * 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	flotte1_bleu = IMG_Load("../data/graphiques/images/unite1_bleu.png");
	flotte2_bleu = IMG_Load("../data/graphiques/images/unite2_bleu.png");
	flotte3_bleu = IMG_Load("../data/graphiques/images/unite3_bleu.png");

	flotte1_rouge = IMG_Load("../data/graphiques/images/unite1_rouge.png");
	flotte2_rouge = IMG_Load("../data/graphiques/images/unite2_rouge.png");
	flotte3_rouge = IMG_Load("../data/graphiques/images/unite3_rouge.png");

	image_une_case = IMG_Load("../data/graphiques/images/quadrillage.png");
	for(i=0;i< get_taille_espace_x(un_terrain_espace);i++)
	{
		for(j=0;j< get_taille_espace_y(un_terrain_espace);j++)
		{
			position.x = i * 100;
			position.y = j *100;
			une_case = get_case_terrain_espace(un_terrain_espace, i, j);
			if(get_presence_flotte(une_case)== true)
			{
				initialise_sdl_rect(&position_flotte, i*100, j*100, 0, 0);
				type = get_type_vaisseau(get_unite_i_flotte(get_flotte(une_case), 0));
				if ((type == Chasseur) && une_case->flotte->indice_joueur == 0)
				{
					SDL_BlitSurface(flotte1_bleu, NULL, carte, &position_flotte);
				}
				if ((type == Chasseur) && une_case->flotte->indice_joueur == 1)
				{
					SDL_BlitSurface(flotte1_rouge, NULL, carte, &position_flotte);
				}
				if ((type == Destroyer) && une_case->flotte->indice_joueur == 0)
				{
					SDL_BlitSurface(flotte2_bleu, NULL, carte, &position_flotte);
				}
				if ((type == Destroyer) && une_case->flotte->indice_joueur == 1)
				{
					SDL_BlitSurface(flotte2_rouge, NULL, carte, &position_flotte);
				}
				if ((type == Destructeur) && une_case->flotte->indice_joueur == 0)
				{
					SDL_BlitSurface(flotte3_bleu, NULL, carte, &position_flotte);
				}
				if ((type == Destructeur) && une_case->flotte->indice_joueur == 1)
				{
					SDL_BlitSurface(flotte3_rouge, NULL, carte, &position_flotte);
				}
			}
			SDL_BlitSurface(image_une_case, NULL, carte, &position);
		}
	}

    SDL_FreeSurface(flotte1_bleu);
	SDL_FreeSurface(flotte2_bleu);
	SDL_FreeSurface(flotte3_bleu);
	SDL_FreeSurface(flotte1_rouge);
	SDL_FreeSurface(flotte2_rouge);
	SDL_FreeSurface(flotte3_rouge);
    SDL_FreeSurface(image_une_case);
	return carte;
}

/**
 * \brief      Surface où l'on crée la minimap
 * \details    On affiche la vision de la carte globale en cours en créant un rectangle à la position adéquate
 * \param      un_terrain_espace         Pointeur sur le Terrain_espace
 */
SDL_Surface* affichage_minimap(const Terrain_espace *un_terrain_espace)
{
	SDL_Surface *minimap = NULL;
	SDL_Surface *fond_minimap = NULL;
	SDL_Surface *rect_affichage = NULL;
	SDL_Surface *un_pixel;
	SDL_Rect position_rect_affichage;
	SDL_Rect position_un_pixel;
	int i;
	float x, y, x_affichage, y_affichage;

	minimap = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_MINIMAP_X, TAILLE_MINIMAP_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	fond_minimap = IMG_Load("../data/graphiques/images/fond_minimap.png");
	SDL_BlitSurface(fond_minimap, NULL, minimap, NULL);

	x = TAILLE_MINIMAP_X * ((float)((float)TAILLE_TERRAIN_ESPACE_X/100)/ un_terrain_espace->taille_espace_x);
	y = TAILLE_MINIMAP_Y * ((float)((float)TAILLE_TERRAIN_ESPACE_Y/100) / un_terrain_espace->taille_espace_y);
	rect_affichage = SDL_CreateRGBSurface(SDL_HWSURFACE, x, y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);

	un_pixel = SDL_CreateRGBSurface(SDL_HWSURFACE, 2, 2, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(un_pixel, NULL, SDL_MapRGB(un_pixel->format, 200, 0, 0));

	SDL_FillRect(rect_affichage, NULL, SDL_MapRGB(minimap->format, 0, 0, 0));
	SDL_SetColorKey(rect_affichage, SDL_SRCCOLORKEY, SDL_MapRGB(minimap->format, 0, 0, 0));

	for(i=0;i<rect_affichage->w - 2;i++)
	{
		initialise_sdl_rect(&position_un_pixel, i, 0, 0, 0);
		SDL_BlitSurface(un_pixel, NULL, rect_affichage, &position_un_pixel);

		initialise_sdl_rect(&position_un_pixel, i, rect_affichage->h - 2, 0, 0);
		SDL_BlitSurface(un_pixel, NULL, rect_affichage, &position_un_pixel);
	}
	for(i=0;i<rect_affichage->h - 2;i++)
	{
		initialise_sdl_rect(&position_un_pixel, 0, i, 0, 0);
		SDL_BlitSurface(un_pixel, NULL, rect_affichage, &position_un_pixel);

		initialise_sdl_rect(&position_un_pixel, rect_affichage->w - 2, i, 0, 0);
		SDL_BlitSurface(un_pixel, NULL, rect_affichage, &position_un_pixel);
	}
	x_affichage = ((float)get_affichage_x(un_terrain_espace)/(get_taille_espace_x(un_terrain_espace) * 100)) * TAILLE_MINIMAP_X;
	y_affichage = ((float)get_affichage_y(un_terrain_espace)/(get_taille_espace_y(un_terrain_espace) * 100)) * TAILLE_MINIMAP_Y;
	initialise_sdl_rect(&position_rect_affichage, x_affichage, y_affichage, 0, 0);
	SDL_BlitSurface(rect_affichage, NULL, minimap, &position_rect_affichage);

	SDL_FreeSurface(fond_minimap);
	SDL_FreeSurface(rect_affichage);
	SDL_FreeSurface(un_pixel);
	return minimap;
}

/**
 * \brief      Surface où l'on crée l'affichage de la vision du joueur
 * \details    On parcourt la vision du joueur pour afficher les informations nécessaires puis on stocke la surface en mémoire pour éviter de la recréer
 * \param      un_jeu         Pointeur sur le jeu
 * \param      un_joueur      Pointeur sur le joueur dont on veut afficher la vision
 */
SDL_Surface* creer_affichage_vision(const Jeu *un_jeu, const Joueur* un_joueur)
{
	SDL_Surface *affichee = NULL;
	SDL_Surface *jamais_visitee = NULL;
	SDL_Surface *visitee = NULL;
	SDL_Surface *fond = NULL;
	SDL_Rect position_affichage;
	int i, j;
	Terrain_espace* un_terrain_espace;
	Vision_terrain* une_vision;
	Vision_case *une_case;

	une_vision = get_vision_terrain(un_joueur);
	un_terrain_espace = get_vision_terrain(un_joueur)->terrain_espace;

	fond = SDL_CreateRGBSurface(SDL_HWSURFACE, get_taille_espace_x(un_terrain_espace) * 100, get_taille_espace_y(un_terrain_espace) * 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(fond, NULL, SDL_MapRGB(fond->format, 0, 0, 255));

	jamais_visitee = IMG_Load("../data/graphiques/images/brouillard.png");

	affichee = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(affichee, NULL, SDL_MapRGB(fond->format, 255, 255, 255));

	visitee = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(visitee, NULL, SDL_MapRGB(fond->format, 0, 255, 0));
	SDL_SetAlpha(visitee, SDL_SRCALPHA, 128);

	for(i=0;i< get_taille_espace_y(un_terrain_espace);i++)
	{
		for(j=0;j< get_taille_espace_x(un_terrain_espace);j++)
		{
			une_case = get_vision_case(une_vision, j, i);
			initialise_sdl_rect(&position_affichage, j * 100, i * 100, 100, 100);
			if(une_case->champ_vision == AFFICHEE)
			{
				SDL_BlitSurface(affichee, NULL, fond, &position_affichage);
			}
			if(une_case->champ_vision == VISITEE)
			{
				SDL_BlitSurface(visitee, NULL, fond, &position_affichage);
			}
			if(une_case->champ_vision == JAMAIS_VISITEE)
			{
				SDL_BlitSurface(jamais_visitee, NULL, fond, &position_affichage);
			}
		}
	}

	SDL_SetColorKey(fond, SDL_SRCCOLORKEY, SDL_MapRGB(fond->format, 255, 255, 255));

	SDL_FreeSurface(visitee);
	SDL_FreeSurface(jamais_visitee);
	SDL_FreeSurface(affichee);

	return fond;
}

/**
 * \brief      On reprend la surface et on la met à jour
 * \param      un_jeu         Pointeur sur le jeu
 * \param      un_joueur      Pointeur sur le joueur dont on veut afficher la vision
 * \param      ecran          Pointeur sur la surface d'ecran
 * \param      tab_surface    Pointeur sur le tableau de pointeurs sur surface
 */
void maj_affichage_vision(Jeu *un_jeu, const Joueur* un_joueur, SDL_Surface *ecran, SDL_Surface **tab_surface)
{
	SDL_Surface *affichee = NULL;
	SDL_Surface *jamais_visitee = NULL;
	SDL_Surface *visitee = NULL;
	SDL_Rect position_affichage;
	int i, j;
	Terrain_espace* un_terrain_espace;
	Vision_terrain* une_vision;
	Vision_case *une_case;

	une_vision = get_vision_terrain(un_joueur);
	un_terrain_espace = get_vision_terrain(un_joueur)->terrain_espace;
	maj_vision_joueur(un_jeu, un_terrain_espace, get_indice_joueur_en_cours(un_jeu));
    SDL_FreeSurface(tab_surface[11]);
	tab_surface[11] = SDL_CreateRGBSurface(SDL_HWSURFACE, get_taille_espace_x(un_terrain_espace) * 100, get_taille_espace_y(un_terrain_espace) * 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(tab_surface[11], NULL, SDL_MapRGB(tab_surface[11]->format, 0, 0, 255));
	SDL_SetColorKey(tab_surface[11], SDL_SRCCOLORKEY, SDL_MapRGB(tab_surface[11]->format, 0, 0, 255));

	jamais_visitee = IMG_Load("../data/graphiques/images/brouillard.png");

	affichee = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(affichee, NULL, SDL_MapRGB(tab_surface[11]->format, 255, 255, 255));
	SDL_SetColorKey(affichee, SDL_SRCCOLORKEY, SDL_MapRGB(tab_surface[11]->format, 255, 255, 255));

	visitee = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(visitee, NULL, SDL_MapRGB(tab_surface[11]->format, 0, 0, 0));
	SDL_SetAlpha(visitee, SDL_SRCALPHA, 100);

	for(i=0;i< get_taille_espace_y(un_terrain_espace);i++)
	{
		for(j=0;j< get_taille_espace_x(un_terrain_espace);j++)
		{
			une_case = get_vision_case(une_vision, j, i);
			initialise_sdl_rect(&position_affichage, j * 100, i * 100, 100, 100);
			if(une_case->champ_vision == AFFICHEE)
			{
				SDL_BlitSurface(affichee, NULL, tab_surface[11], &position_affichage);
			}
			if(une_case->champ_vision == VISITEE)
			{
				SDL_BlitSurface(tab_surface[0], &position_affichage, tab_surface[11], &position_affichage);
				SDL_BlitSurface(visitee, NULL, tab_surface[11], &position_affichage);
			}
			if(une_case->champ_vision == JAMAIS_VISITEE)
			{
				SDL_BlitSurface(jamais_visitee, NULL, tab_surface[11], &position_affichage);
			}
		}
	}

	SDL_FreeSurface(visitee);
	SDL_FreeSurface(jamais_visitee);
	SDL_FreeSurface(affichee);
}

/**
 * \brief      On initialise l'affichage
 * \details    L'affichage est créé, les surfaces utiles sont stockées en mémoire: tab_surface[0] = carte,
 tab_surface[1] = carte_flotte, tab_surface[2] = ressource, tab_surface[3] = bordure, tab_surface[4] = deplacement_carte, 
 tab_surface[5] = interface, tab_surface[6] = mini_carte, tab_surface[7] = info, tab_surface[8] = panneau_unite, 
 tab_surface[9] = minimap, tab_surface[10] = bouton_passer_tour, tab_surface[11] = visibilite, tab_surface[12] = infobulle;
 * \param      un_jeu                Pointeur sur le jeu
 * \param      un_terrain_espace     Pointeur sur le terrain espace
 * \param      ecran                 Pointeur sur la surface d'ecran
 * \param      tab_surface           Pointeur sur le tableau de pointeurs sur surface
 */
void initialiser_affichage(const Jeu *un_jeu, const Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface)
{
    int i;
	SDL_Rect position = {0, 0, 0, 0};
	SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
	SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect affichage_carte = {0, 0, 0, 0};
	SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 300, 20, 300, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};
	SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -207, TAILLE_TERRAIN_ESPACE_Y - 8, 0, 0};

    for(i=0;i<13;i++)
    {
        tab_surface[i] = NULL;
    }

	tab_surface[0] = creer_affichage_terrain(un_terrain_espace);

	/*Creation du terrain en entier, celui-ci est stocké en mémoire*/
	tab_surface[1] = creer_affichage_flotte(un_terrain_espace);
	initialise_sdl_rect(&affichage_carte, get_affichage_x(un_terrain_espace), get_affichage_y(un_terrain_espace), TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y);
	SDL_SetColorKey(tab_surface[1], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_BlitSurface(tab_surface[0], &affichage_carte, ecran, &position_affichage_carte);
	SDL_BlitSurface(tab_surface[1], &affichage_carte, ecran, &position_affichage_carte);

	/*creation de l'affichage de la visibilité*/
	tab_surface[11] = creer_affichage_vision(un_jeu, get_ieme_joueur_jeu(un_jeu, 0));
	SDL_BlitSurface(tab_surface[11], &affichage_carte, ecran, &position_affichage_carte);

	/*affichage de la barre de ressources*/
    tab_surface[2] = affichage_ressource(un_jeu);
	SDL_BlitSurface(tab_surface[2], NULL, ecran, &position);
	SDL_FreeSurface(tab_surface[2]);

	/*affichage de l'interface*/
	tab_surface[5] = IMG_Load("../data/graphiques/images/interface_bas.png");
	SDL_BlitSurface(tab_surface[5], NULL, ecran, &position_interface);

	initialise_sdl_rect(&position_panneau_unite, TAILLE_FENETRE_X - 214, 35, 200, TAILLE_TERRAIN_ESPACE_Y-300);

	/*affichage de la minimap*/
	tab_surface[9] = affichage_minimap(un_terrain_espace);
	SDL_BlitSurface(tab_surface[9], NULL, ecran, &position_minimap);

	/*affichage du bouton de tour suivant*/
	tab_surface[10] = IMG_Load("../data/graphiques/images/passer_tour.png");
    SDL_BlitSurface(tab_surface[10], NULL, ecran, &position_bouton_tour);

    /*affichage du cadre*/
    tab_surface[3] = IMG_Load("../data/graphiques/images/bordure_bleue.png");
    SDL_BlitSurface(tab_surface[3], NULL, ecran, &position_affichage_carte);
	SDL_Flip(ecran);
}

/**
 * \brief      On reprend la surface et on la met à jour
 * \param      un_jeu                Pointeur sur le jeu
 * \param      un_terrain_espace     Pointeur sur le terrain espace
 * \param      ecran                 Pointeur sur la surface d'ecran
 * \param      tab_surface           Pointeur sur le tableau de pointeurs sur surface
 * \param      interface_affichee    Interface en cours d'affichage
 */
void maj_carte_terrain(Jeu *un_jeu, const Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee)
{
	SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
	SDL_Rect position_mini_carte = {TAILLE_FENETRE_X - 240, TAILLE_FENETRE_Y - 158};
	SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect affichage_carte = {0, 0, 0, 0};
	SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -207, TAILLE_TERRAIN_ESPACE_Y - 8, 0, 0};

	/*Creation du terrain en entier, celui-ci est stocké en mémoire*/
	SDL_FreeSurface(tab_surface[0]);
	tab_surface[0] = creer_affichage_terrain(un_terrain_espace);
	initialise_sdl_rect(&affichage_carte, un_terrain_espace->affichage_x, un_terrain_espace->affichage_y, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y);
	SDL_BlitSurface(tab_surface[0], &affichage_carte, ecran, &position_affichage_carte);
	SDL_BlitSurface(tab_surface[1], &affichage_carte, ecran, &position_affichage_carte);
	SDL_BlitSurface(tab_surface[11], &affichage_carte, ecran, &position_affichage_carte);

	/*affichage de l'interface*/
	SDL_BlitSurface(tab_surface[5], NULL, ecran, &position_interface);
	SDL_BlitSurface(tab_surface[6], NULL, ecran, &position_mini_carte);

	/*affichage de la barre de ressources*/
    maj_affichage_ressource(un_jeu, ecran, tab_surface);

	/*affichage de la bordure*/
	SDL_BlitSurface(tab_surface[3], NULL, ecran, &position_affichage_carte);

	/*affichage bouton passer tour*/
	SDL_BlitSurface(tab_surface[10], NULL, ecran, &position_bouton_tour);

	if(interface_affichee == FLOTTE)
	{
		maj_affichage_flotte(un_jeu, un_terrain_espace,ecran,tab_surface, interface_affichee);
	}

	SDL_Flip(ecran);


}

/**
 * \brief      On reprend la surface et on la met à jour
 * \param      un_jeu                Pointeur sur le jeu
 * \param      un_terrain_espace     Pointeur sur le terrain espace
 * \param      ecran                 Pointeur sur la surface d'ecran
 * \param      tab_surface           Pointeur sur le tableau de pointeurs sur surface
 * \param      interface_affichee    Interface en cours d'affichage
 */
void maj_affichage_carte_terrain(const Jeu *un_jeu, const Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee)
{
    SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};
    SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 30 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 214, 35, 200, TAILLE_TERRAIN_ESPACE_Y-300};
    SDL_Rect affichage_carte = {un_terrain_espace->affichage_x, un_terrain_espace->affichage_y, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -207, TAILLE_TERRAIN_ESPACE_Y - 8, 0, 0};

    /*Réaffichage des différentes parties de la carte*/
    SDL_BlitSurface(tab_surface[0], &affichage_carte, ecran, &position_affichage_carte);
    SDL_BlitSurface(tab_surface[1], &affichage_carte, ecran, &position_affichage_carte);
	SDL_BlitSurface(tab_surface[11], &affichage_carte, ecran, &position_affichage_carte);

    /*affichage de la bordure*/
    SDL_BlitSurface(tab_surface[3], NULL, ecran, &position_affichage_carte);

    /*affichage bouton passer tour*/
    SDL_BlitSurface(tab_surface[10], NULL, ecran, &position_bouton_tour);

    if(interface_affichee == RIEN)
    {
        /*affichage de la minimap*/
		SDL_FreeSurface(tab_surface[9]);
        tab_surface[9] = affichage_minimap(un_terrain_espace);
        SDL_BlitSurface(tab_surface[9], NULL, ecran, &position_minimap);
    }
	if(interface_affichee == PANNEAU_UNITE)
	{
		tab_surface[7] = affichage_planete(get_planete_en_cours(un_jeu));
		SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
        SDL_FreeSurface(tab_surface[7]);
		tab_surface[8] = affichage_creation_unite(get_planete_en_cours(un_jeu));
		SDL_BlitSurface(tab_surface[8], NULL, ecran, &position_panneau_unite);
        SDL_FreeSurface(tab_surface[8]);
	}

    SDL_Flip(ecran);
}


/**
 * \brief      On reprend la surface et on la met à jour
 * \param      un_jeu                Pointeur sur le jeu
 * \param      un_terrain_espace     Pointeur sur le terrain espace
 * \param      ecran                 Pointeur sur la surface d'ecran
 * \param      tab_surface           Pointeur sur le tableau de pointeurs sur surface
 * \param      interface_affichee    Interface en cours d'affichage
 */
void maj_affichage_flotte(Jeu *un_jeu, const Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee)
{
    SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
    SDL_Rect position_mini_carte = {TAILLE_FENETRE_X - 240, TAILLE_FENETRE_Y - 158};
    SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 30 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect affichage_carte = {0, 0, 0, 0};
    SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -207, TAILLE_TERRAIN_ESPACE_Y - 8, 0, 0};

    /*Creation du terrain en entier, celui-ci est stocké en mémoire*/
	SDL_FreeSurface(tab_surface[1]);
    tab_surface[1] = creer_affichage_flotte(un_terrain_espace);
    initialise_sdl_rect(&affichage_carte, un_terrain_espace->affichage_x, un_terrain_espace->affichage_y, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y);
    SDL_BlitSurface(tab_surface[0], &affichage_carte, ecran, &position_affichage_carte);
    SDL_SetColorKey(tab_surface[1], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(tab_surface[1], &affichage_carte, ecran, &position_affichage_carte);

	/*creation de l'affichage de la visibilité*/
	/*SDL_FreeSurface(tab_surface[11]);*/
	maj_affichage_vision(un_jeu, get_joueur_en_cours(un_jeu), ecran, tab_surface);
	SDL_BlitSurface(tab_surface[11], &affichage_carte, ecran, &position_affichage_carte);

    /*affichage de l'interface*/
    SDL_BlitSurface(tab_surface[5], NULL, ecran, &position_interface);
    SDL_BlitSurface(tab_surface[6], NULL, ecran, &position_mini_carte);

    /*affichage de la barre de ressources*/
    maj_affichage_ressource(un_jeu, ecran, tab_surface);

    /*affichage de la bordure*/
    SDL_BlitSurface(tab_surface[3], NULL, ecran, &position_affichage_carte);

    /*affichage bouton passer tour*/
    SDL_BlitSurface(tab_surface[10], NULL, ecran, &position_bouton_tour);

    if(interface_affichee == FLOTTE)
    {
        tab_surface[7] = affichage_flotte(un_jeu, un_terrain_espace);
        SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
        SDL_FreeSurface(tab_surface[7]);
    }

    SDL_Flip(ecran);
}


/**
 * \brief      On reprend la surface et on la met à jour
 * \param      un_jeu                Pointeur sur le jeu
 * \param      ecran                 Pointeur sur la surface d'ecran
 * \param      tab_surface           Pointeur sur le tableau de pointeurs sur surface
 */
void maj_affichage_ressource(const Jeu *un_jeu, SDL_Surface *ecran, SDL_Surface **tab_surface)
{
	SDL_Rect position = {0, 0, 0, 0};
	tab_surface[2] = affichage_ressource(un_jeu);
	SDL_BlitSurface(tab_surface[2], NULL, ecran, &position);
	SDL_FreeSurface(tab_surface[2]);
}

/**
 * \brief      On remet à jour tout l'affichage
 * \param      un_jeu                Pointeur sur le jeu
 * \param      un_terrain_espace     Pointeur sur le terrain espace
 * \param      interface_affichee    Interface en cours d'affichage
 * \param      ecran                 Pointeur sur la surface d'ecran
 * \param      une_case_terrain_espace    Pointeur sur une case du terrain (utile pour un des appels de fonction)
 * \param      tab_surface           Pointeur sur le tableau de pointeurs sur surface
 */
void maj_affichage(const Jeu *un_jeu, const Terrain_espace *un_terrain_espace, SDL_Surface *ecran, INTERFACE_AFFICHEE interface_affichee, Case_terrain_espace *une_case_terrain_espace, SDL_Surface **tab_surface)
 {
    SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
    SDL_Rect position_mini_carte = {TAILLE_FENETRE_X - 240, TAILLE_FENETRE_Y - 158};
    SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 30 , 0, 0};
    SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 214, 35, 200, TAILLE_TERRAIN_ESPACE_Y-300};
    SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};

   /*affichage de l'interface*/
    SDL_BlitSurface(tab_surface[5], NULL, ecran, &position_interface);
    SDL_BlitSurface(tab_surface[6], NULL, ecran, &position_mini_carte);

        if(interface_affichee == RIEN)
        {
            /*affichage de la minimap*/
			SDL_FreeSurface(tab_surface[9]);
            tab_surface[9] = affichage_minimap(un_terrain_espace);
            SDL_BlitSurface(tab_surface[9], NULL, ecran, &position_minimap);
        }
        if(interface_affichee == PLANETE)
        {
			tab_surface[7] = affichage_planete(get_planete_en_cours(un_jeu));
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
            SDL_FreeSurface(tab_surface[7]);
        }
        if(interface_affichee == PLANETE_ENNEMIE)
        {
			tab_surface[7] = affichage_planete_ennemie(une_case_terrain_espace);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
            SDL_FreeSurface(tab_surface[7]);
        }
        if(interface_affichee == FLOTTE)
        {
			tab_surface[7] = affichage_flotte(un_jeu, un_terrain_espace);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
            SDL_FreeSurface(tab_surface[7]);
        }
        if(interface_affichee == FLOTTE_ENNEMIE)
        {
			tab_surface[7] = affichage_flotte_ennemie(un_jeu);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
            SDL_FreeSurface(tab_surface[7]);
        }
        if(interface_affichee == PANNEAU_UNITE)
        {
			tab_surface[7] = affichage_planete(get_planete_en_cours(un_jeu));
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
            SDL_FreeSurface(tab_surface[7]);
            tab_surface[8] = affichage_creation_unite(get_planete_en_cours(un_jeu));
            SDL_BlitSurface(tab_surface[8], NULL, ecran, &position_panneau_unite);
            SDL_FreeSurface(tab_surface[8]);
        }

    SDL_Flip(ecran);
 }


/************************************************************************/
/* Boucle principale                                                    */
/************************************************************************/


/**
 * \brief      Boucle principale de la partie gestion
 * \details    Cette boucle va gérer l'affichage et la gestion des évènements de la partie gestion. De nombreux tests y sont faits, en fonction des actions des joueurs et de ce qu'il y faut afficher
 * \param      un_jeu                Pointeur sur le jeu
 * \param      un_terrain_espace     Pointeur sur le terrain espace
 * \param      system                Pointeur sur une variable FMOD qui va gérer le son
 * \param      musique               Pointeur sur une variable FMOD qui va gérer le son
 */
void affichage_ecran(Jeu *un_jeu, Terrain_espace *un_terrain_espace, FMOD_SYSTEM *system, FMOD_SOUND *musique)
{
	/************************************************************************/
	/* Initialisation des variables                                         */
	/************************************************************************/

	/*variables SDL*/
	SDL_Surface *ecran = NULL;
	SDL_Surface *icone = NULL;
	SDL_Surface **tab_surface;
    SDL_Surface *Noir = SDL_LoadBMP("../data/graphiques/images/Noir.bmp");
	SDL_Rect bouton_tour = {TAILLE_FENETRE_X -207, TAILLE_TERRAIN_ESPACE_Y - 8, 200, 33};
	SDL_Rect position_affichage_carte = {0, TAILLE_BARRE_RESSOURCE, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 300, 20, 300, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect test;
	SDL_Event event;

	/*variables diverses*/
	int continuer = 1;
	int x = 0, y = 0, x_bis = 0, y_bis = 0;
	int i, j, combat;
	int flotte_planete = 0;
	bool infobulle = false;
	int tps_ancien = 10,tps_nouveau = 0, timer = 0, x_info = 0, y_info = 0;
	INTERFACE_AFFICHEE interface_affichee = RIEN; /*1 pour une planete, 2 pour une planete ennemie, 3 pour une flotte, 4 pour une flotte ennemie, 5 pour la création d'unités sur une planète*/
	Case_terrain_espace *une_case_terrain_espace;
	Animation *saut_ftl = NULL;
	char nom_fichier_saut_ftl[] = "../data/graphiques/images/effet_teleportation.png";

	/*variables pour le son*/
	FMOD_SOUND *son_saut_debut = NULL;
	FMOD_SOUND *son_saut_fin = NULL;
	char **tab_chanson = NULL;


	/************************************************************************/
	/* Début de la fonction, initialisation des différentes valeurs         */
	/************************************************************************/

	/*on initialise le tableau de chansons puis on utilise la fonction qui va mettre les noms dedans (pour plus de clarté dans le code)*/
	tab_chanson = (char **)malloc(sizeof(char *) * 6);
	initialiser_tableau_chanson(tab_chanson);

	/*on lance les musiques du jeu et on initialise les sons*/
	lire_musique(system, musique, tab_chanson);
	FMOD_System_CreateSound(system, "../data/audio/son/FTL_Saut.mp3", FMOD_CREATESAMPLE, 0, &son_saut_debut);
	FMOD_System_CreateSound(system, "../data/audio/son/FTL_Exit.mp3", FMOD_CREATESAMPLE, 0, &son_saut_fin);

	/*démarrage des modules, mise en place de la fenêtre principale*/
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_EnableKeyRepeat(10, 10); /*active la répétition des touches, principalement pour un déplacement de la map plus fluide*/
	icone = IMG_Load("../data/graphiques/images/icone.png");
	SDL_WM_SetIcon(icone, NULL);
	ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, NOMBRE_BITS_COULEUR, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Conquest of Space", NULL);

	/*on initialise le tableau de surfaces et les différentes surfaces*/
	tab_surface = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 13);
	initialiser_affichage(un_jeu, un_terrain_espace, ecran, tab_surface);

	saut_ftl = creer_animation(5, 100, 100, 50, nom_fichier_saut_ftl);
	tps_ancien = SDL_GetTicks();


	/************************************************************************/
	/* Boucle principale                                                    */
	/************************************************************************/

	while (continuer) /*boucle d'événement principale*/
	{
		/*mise à jour de valeurs "globales"*/
		SDL_PollEvent(&event);
		maj_musique(system, musique, tab_chanson);

		/*pour afficher les infobulles*/
		tps_nouveau = SDL_GetTicks();
		timer = tps_nouveau - tps_ancien;
		if(timer >= TEMPS_INFOBULLE)
		{
			afficher_infobulle(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee, x_info, y_info);
			tps_ancien = tps_nouveau;
			infobulle = true;
		}

		/*maj des animations*/
		if(un_jeu->animation_en_cours != NULL)
		{
			maj_animation(un_jeu, un_terrain_espace, un_jeu->animation_en_cours, timer, ecran, tab_surface, interface_affichee);
		}

	    switch(event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;
        case SDL_MOUSEMOTION:
			x_info = event.motion.x;
			y_info = event.motion.y;
			tps_ancien = SDL_GetTicks();
			if(infobulle == true)
			{
				maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, une_case_terrain_espace, tab_surface);
				maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
				infobulle = false;
			}
            break;
		case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x;
                y = event.button.y;
                if(test_souris_rectangle(position_affichage_carte,x,y)) /*test des clics ayant lieu sur le terrain*/
                {
                    une_case_terrain_espace = case_pointeur_souris(un_terrain_espace, x, y);
					/*si la case est une planète, on affiche l'interface correspondante et qu'il n'y a pas de flotte*/
                    if((get_type_case_terrain_espace(une_case_terrain_espace) == 'P') && (get_presence_flotte(une_case_terrain_espace) == false))
                    {
                        set_selection_planete(un_jeu, get_planete(une_case_terrain_espace));
						if(get_indice_joueur_planete(get_planete_en_cours(un_jeu))== get_indice_joueur_en_cours(un_jeu))
						{
							interface_affichee = PLANETE;
						}
						else
						{
							interface_affichee = PLANETE_ENNEMIE;
						}
						maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, une_case_terrain_espace, tab_surface);
                        reinitialiser_tableau_selection_unite(un_jeu);
                    }
					/*si une flotte est présente*/
					if((get_presence_flotte(une_case_terrain_espace)== true) && (get_type_case_terrain_espace(une_case_terrain_espace)!= 'P'))
					{
						set_selection_flotte(un_jeu, get_flotte(une_case_terrain_espace));
						if(get_indice_joueur_flotte(get_flotte_en_cours(un_jeu)) == get_indice_joueur_en_cours(un_jeu))
						{
							interface_affichee = FLOTTE;
						}
						else
						{
							interface_affichee = FLOTTE_ENNEMIE;
						}
						maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, NULL, tab_surface);
						reinitialiser_tableau_selection_unite(un_jeu);
					}

					/*si les deux sont vrais, qu'il y a une planète et une flotte sur la même case, on va passer de l'un à l'autre à chaque fois qu'on clique*/
					if((get_type_case_terrain_espace(une_case_terrain_espace) == 'P') && (get_presence_flotte(une_case_terrain_espace) == true) && (flotte_planete%2 == 0))
					{
						set_selection_planete(un_jeu, get_planete(une_case_terrain_espace));
                        if(get_flotte_en_cours(un_jeu) != NULL)
                        {
                            if(get_indice_joueur_flotte(get_flotte_en_cours(un_jeu)) == get_indice_joueur_en_cours(un_jeu))
                            {
                                interface_affichee = PLANETE;
                            }
                            else
                            {
                                interface_affichee = PLANETE_ENNEMIE;
                            }
                        }
						maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, une_case_terrain_espace, tab_surface);
						reinitialiser_tableau_selection_unite(un_jeu);
					}
					if((get_type_case_terrain_espace(une_case_terrain_espace) == 'P') && (get_presence_flotte(une_case_terrain_espace) == true) && (flotte_planete%2 == 1))
					{
						set_selection_flotte(un_jeu, get_flotte(une_case_terrain_espace));
						if(get_indice_joueur_flotte(get_flotte_en_cours(un_jeu)) == get_indice_joueur_en_cours(un_jeu))
						{
							interface_affichee = FLOTTE;
						}
						else
						{
							interface_affichee = FLOTTE_ENNEMIE;
						}
						maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, NULL, tab_surface);
						reinitialiser_tableau_selection_unite(un_jeu);
						flotte_planete = true;
					}
					if((get_type_case_terrain_espace(une_case_terrain_espace)== 'P') && (get_presence_flotte(une_case_terrain_espace)== true))
					{
						flotte_planete++;
					}

					/*si rien de cela, on va revenir à l'interface simple, sans informations*/
                    if(test_souris_rectangle(position_affichage_carte, x, y) && (get_type_case_terrain_espace(une_case_terrain_espace) != 'P') && (get_presence_flotte(une_case_terrain_espace) == false))
                    {
						if(interface_affichee == PANNEAU_UNITE)
						{
							 if(!test_souris_rectangle(position_panneau_unite, x, y))
							 {
                                 set_selection_flotte(un_jeu, NULL);
								 interface_affichee = RIEN;
								 maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, NULL, tab_surface);
								 maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
								 reinitialiser_tableau_selection_unite(un_jeu);
							 }
						}
						if(interface_affichee != PANNEAU_UNITE)
						{
                            set_selection_flotte(un_jeu, NULL);
							interface_affichee = RIEN;
							maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, NULL, tab_surface);
							maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
							reinitialiser_tableau_selection_unite(un_jeu);
						}
                    }
					/*pour passer au joueur suivant*/
					if (test_souris_rectangle(bouton_tour, x, y))
					{
						if(get_indice_joueur_en_cours(un_jeu) == 0)
						{
							set_affichage(un_terrain_espace, 2000 - TAILLE_TERRAIN_ESPACE_X, 1500 - TAILLE_TERRAIN_ESPACE_Y);
						}
						if(get_indice_joueur_en_cours(un_jeu) == 1)
						{
							set_affichage(un_terrain_espace, 0, 0);
						}

						interface_affichee = RIEN;
						joueur_suivant(un_jeu, un_terrain_espace);
                        
                        /* Mise à jour de la bordure */
                        SDL_FreeSurface(tab_surface[3]);
                        if (get_numero_joueur(get_joueur_en_cours(un_jeu)) == 0)
                        {
                            tab_surface[3] = IMG_Load("../data/graphiques/images/bordure_bleue.png");
                        }
                        else
                        {
                            tab_surface[3] = IMG_Load("../data/graphiques/images/bordure_rouge.png");
                        }
                        SDL_BlitSurface(tab_surface[3], NULL, ecran, &position_affichage_carte);
						/*creation de l'affichage de la visibilité*/
						SDL_FreeSurface(tab_surface[11]);
						tab_surface[11] = creer_affichage_vision(un_jeu, get_ieme_joueur_jeu(un_jeu, get_indice_joueur_en_cours(un_jeu)));
						maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
						maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, NULL, tab_surface);
						maj_affichage_flotte(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
					}
				}

				/*on va tester les clics en fonction des interfaces affichées*/
				if(interface_affichee == RIEN)
				{
					if(booleen_minimap_pointeur_souris(x, y))
					{
						test_minimap_souris(un_terrain_espace, x, y);
						maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
					}
				}

				/*une planete avec, ou non, le panneau de création d'unités*/
				if(interface_affichee == PLANETE || interface_affichee == PANNEAU_UNITE)
				{
				    reinitialiser_tableau_selection_unite(un_jeu);
				    /*test d'appui sur l'une des cases de batiment, pour le construire si les conditions sont respectées*/
				    for(i=0;i<6;i++)
				    {
				        initialise_sdl_rect(&test, 10+ 120*i, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
                        if(test_souris_rectangle(test, x, y))
                        {
                            une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, get_x_planete(get_planete_en_cours(un_jeu)), get_y_planete(get_planete_en_cours(un_jeu)));
                            if(condition_creation_batiment (get_planete_en_cours(un_jeu), i))
							{
								creation_batiment(get_planete_en_cours(un_jeu), i);
								maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, une_case_terrain_espace, tab_surface);
							}

						}
				    }
                    /*pour ouvrir le panneau d'unités*/
                    initialise_sdl_rect(&test, TAILLE_FENETRE_X -150, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
                    if(test_souris_rectangle(test, x, y))
                    {
                        une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, get_x_planete(get_planete_en_cours(un_jeu)), get_y_planete(get_planete_en_cours(un_jeu)));
                        interface_affichee = PANNEAU_UNITE;
                        maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, NULL, tab_surface);
                    }
				}

				/*une flotte*/
				if(interface_affichee == FLOTTE)
				{
					/*test d'appui sur l'une des cases d'unité, pour les sélectionner séparemment de la flotte*/
					for(i=0;i<get_flotte_en_cours(un_jeu)->taille_flotte;i++)
					{
						initialise_sdl_rect(&test, 10+ 120*i, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
						if(test_souris_rectangle(test, x, y) && (SDL_GetModState() & KMOD_LCTRL)) /*la deuxième condition indique l'état courant de la touche LCTRL*/
						{
							if(get_ieme_unite_selectionnee(un_jeu, i)== true)
							{
								set_ieme_unite_selectionne(un_jeu, i, false);
							}
							else
							{
								set_ieme_unite_selectionne(un_jeu, i, true);
							}
						}
						if(test_souris_rectangle(test, x, y) && !(SDL_GetModState() & KMOD_LCTRL))
						{
							for(j=0;j<10;j++)
							{
								set_ieme_unite_selectionne(un_jeu, j, false);
							}
							set_ieme_unite_selectionne(un_jeu, i, true);
						}
					}
					initialise_sdl_rect(&test, TAILLE_FENETRE_X - 150, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
					if(get_type_case_terrain_espace(get_case_terrain_espace(un_terrain_espace, get_x_flotte(get_flotte_en_cours(un_jeu)), get_y_flotte(get_flotte_en_cours(un_jeu)))))
					{
						if(test_souris_rectangle(test, x, y)) /*va coloniser la planète*/
						{
							if((get_indice_joueur_planete(get_planete_terrain_espace(un_terrain_espace, get_x_flotte(get_flotte_en_cours(un_jeu)), get_y_flotte(get_flotte_en_cours(un_jeu))))) == -1)
							{
								colonisation_planete_flotte(un_terrain_espace, get_flotte_en_cours(un_jeu), un_jeu);
							}
							if((get_indice_joueur_planete(get_planete_terrain_espace(un_terrain_espace, get_x_flotte(get_flotte_en_cours(un_jeu)),
								get_y_flotte(get_flotte_en_cours(un_jeu))))) != get_indice_joueur_flotte(get_flotte_en_cours(un_jeu)) && (get_indice_joueur_planete(get_planete_terrain_espace(un_terrain_espace, get_x_flotte(get_flotte_en_cours(un_jeu)),
								get_y_flotte(get_flotte_en_cours(un_jeu))))) != -1)
							{
								capture_planete(un_jeu, un_terrain_espace, get_flotte_en_cours(un_jeu));
                                if(get_planete_principale(get_planete_terrain_espace(un_terrain_espace, get_x_flotte(get_flotte_en_cours(un_jeu)), get_y_flotte(get_flotte_en_cours(un_jeu)))) == true)
                                {
                                    continuer = 0;
                                    if (get_numero_joueur((get_joueur_en_cours(un_jeu))) == 0)
                                    {
                                        game_over(get_nom_joueur(get_ieme_joueur_jeu(un_jeu, 0)), get_nom_joueur(get_ieme_joueur_jeu(un_jeu, 1)), system, musique);
                                    }
                                    else
                                    {
                                        game_over(get_nom_joueur(get_ieme_joueur_jeu(un_jeu, 1)), get_nom_joueur(get_ieme_joueur_jeu(un_jeu, 0)), system, musique);
                                    }
                                }
							}
						}
						maj_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
						maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, NULL, tab_surface);

					}
				}

				/*panneau de création d'unités*/
				if(interface_affichee == PANNEAU_UNITE)
				{
                    /*test d'appui sur l'une des cases d'unité*/
                    for(i=0;i<3;i++)
                    {
                        initialise_sdl_rect(&test, TAILLE_TERRAIN_ESPACE_X - 190, 40 + 120*i, 100, 100);
                        if(test_souris_rectangle(test, x, y))
                        {
                            une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, get_x_planete(get_planete_en_cours(un_jeu)), get_y_planete(get_planete_en_cours(un_jeu)));
							if(condition_creation_unite(get_joueur_en_cours(un_jeu), get_planete(une_case_terrain_espace), i + 1))
							{
								creation_unite_planete(get_joueur_en_cours(un_jeu), get_planete(une_case_terrain_espace), i + 1);
								maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, NULL, tab_surface);
							}
                        }
                    }
				}
			}

			if(event.button.button == SDL_BUTTON_RIGHT)
            {
                x = event.button.x;
                y = event.button.y;
				une_case_terrain_espace = case_pointeur_souris(un_terrain_espace, x, y);
                if(get_flotte_en_cours(un_jeu)!= NULL)
                {
                    if((get_indice_joueur_flotte(get_flotte_en_cours(un_jeu)) == get_indice_joueur_en_cours(un_jeu)) && (get_pt_mouvement_espace_flotte(get_flotte_en_cours(un_jeu))>= 0))
                    {
                        if(test_unite_selectionnee(un_jeu, get_flotte_en_cours(un_jeu)))
                        {
							booleen_coordonnees_case(un_terrain_espace, get_x_flotte(get_flotte_en_cours(un_jeu)), get_y_flotte(get_flotte_en_cours(un_jeu)), &x_bis, &y_bis);
							lire_son(system, son_saut_debut);
							lancer_animation_bloquante(un_jeu, un_terrain_espace, saut_ftl, ecran, x_bis, y_bis);
							deplacement_unite_flotte(un_jeu, get_joueur_en_cours(un_jeu), un_terrain_espace, get_flotte_en_cours(un_jeu), get_x_espace(une_case_terrain_espace), get_y_espace(une_case_terrain_espace));
							interface_affichee = RIEN;
							set_selection_flotte(un_jeu, get_flotte(get_case_terrain_espace(un_terrain_espace, get_x_espace(une_case_terrain_espace), get_y_espace(une_case_terrain_espace))));
							maj_affichage_flotte(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
							booleen_coordonnees_case(un_terrain_espace, get_x_flotte(get_flotte_en_cours(un_jeu)), get_y_flotte(get_flotte_en_cours(un_jeu)), &x_bis, &y_bis);
							lire_son(system, son_saut_fin);
							lancer_animation_bloquante(un_jeu, un_terrain_espace, saut_ftl, ecran, x_bis, y_bis);
                        }
						else
                        {
							/*déplacement avec l'animation et le son*/
							booleen_coordonnees_case(un_terrain_espace, get_x_flotte(get_flotte_en_cours(un_jeu)), get_y_flotte(get_flotte_en_cours(un_jeu)), &x_bis, &y_bis);
							lire_son(system, son_saut_debut);
							lancer_animation_bloquante(un_jeu, un_terrain_espace, saut_ftl, ecran, x_bis, y_bis);
							deplacement_flotte(get_joueur_en_cours(un_jeu), un_terrain_espace, get_flotte_en_cours(un_jeu), get_x_espace(une_case_terrain_espace), get_y_espace(une_case_terrain_espace));
							maj_affichage_flotte(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
							booleen_coordonnees_case(un_terrain_espace, get_x_flotte(get_flotte_en_cours(un_jeu)), get_y_flotte(get_flotte_en_cours(un_jeu)), &x_bis, &y_bis);
							lire_son(system, son_saut_fin);
							lancer_animation_bloquante(un_jeu, un_terrain_espace, saut_ftl, ecran, x_bis, y_bis);
                        }
                    }
					if(get_flotte(case_pointeur_souris(un_terrain_espace, x, y)) != NULL)
					{
						if((un_jeu->joueur_en_cours != get_indice_joueur_flotte(get_flotte(case_pointeur_souris(un_terrain_espace, x, y)))) && (un_jeu->selection_flotte->pt_mouvement_espace_flotte >= 0))
						{
							//combat_automatique(un_jeu, un_terrain_espace, get_flotte_en_cours(un_jeu), get_flotte(get_case_terrain_espace(un_terrain_espace, x/100, y/100)))
                            combat = lancer_combat_ecran(un_jeu, un_terrain_espace, get_flotte_en_cours(un_jeu), get_flotte(case_pointeur_souris(un_terrain_espace, x, y)), ecran, system, musique);
							if(combat == 1)
							{
								lire_musique(system, musique, tab_chanson);
								deplacement_flotte(get_joueur_en_cours(un_jeu), un_terrain_espace, get_flotte_en_cours(un_jeu), get_x_espace(une_case_terrain_espace), get_y_espace(une_case_terrain_espace));
								maj_affichage(un_jeu, un_terrain_espace, ecran,interface_affichee,NULL, tab_surface);
								maj_affichage_flotte(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
								booleen_coordonnees_case(un_terrain_espace, get_x_flotte(get_flotte_en_cours(un_jeu)), get_y_flotte(get_flotte_en_cours(un_jeu)), &x_bis, &y_bis);
								lire_son(system, son_saut_fin);
								lancer_animation_bloquante(un_jeu, un_terrain_espace, saut_ftl, ecran, x_bis, y_bis);
							}
							if (combat == 2)
							{
								maj_affichage_flotte(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
							}
							else if(combat == 0)
							{
								continuer = 0;
							}
						}
					}
                }
            }
            break;


		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				continuer = 0;
                    for (i=0; i<30; i++)
                    {
                        SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    menu_pause(un_terrain_espace, un_jeu, &continuer);
                    maj_affichage(un_jeu, un_terrain_espace, ecran, interface_affichee, une_case_terrain_espace, tab_surface);
                    maj_affichage_ressource(un_jeu, ecran, tab_surface);
				break;
			case SDLK_UP:
				if((un_terrain_espace->affichage_y - DEPLACEMENT_AFFICHAGE> 0) && (un_terrain_espace->affichage_y - DEPLACEMENT_AFFICHAGE<= (un_terrain_espace->taille_espace_y *100) - TAILLE_TERRAIN_ESPACE_Y ))
				{un_terrain_espace->affichage_y-=DEPLACEMENT_AFFICHAGE;}
				break;
			case SDLK_DOWN:
				if((un_terrain_espace->affichage_y + DEPLACEMENT_AFFICHAGE>=0) && (un_terrain_espace->affichage_y + DEPLACEMENT_AFFICHAGE< (un_terrain_espace->taille_espace_y *100) - TAILLE_TERRAIN_ESPACE_Y ))
				{un_terrain_espace->affichage_y+=DEPLACEMENT_AFFICHAGE;}
				break;
			case SDLK_RIGHT:
				if((un_terrain_espace->affichage_x + DEPLACEMENT_AFFICHAGE>= 0) && (un_terrain_espace->affichage_x + DEPLACEMENT_AFFICHAGE< (un_terrain_espace->taille_espace_x * 100) - TAILLE_TERRAIN_ESPACE_X))
				{un_terrain_espace->affichage_x+=DEPLACEMENT_AFFICHAGE;}
				break;
			case SDLK_LEFT:
				if((un_terrain_espace->affichage_x - DEPLACEMENT_AFFICHAGE>0) && (un_terrain_espace->affichage_x - DEPLACEMENT_AFFICHAGE<= (un_terrain_espace->taille_espace_x *100) - TAILLE_TERRAIN_ESPACE_X))
				{un_terrain_espace->affichage_x-=DEPLACEMENT_AFFICHAGE;}
				break;
			default :
				break;
			}
			tps_ancien = SDL_GetTicks();
			maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
		default:
			break;
		}
		event.type=0; /*on place l'évènement à 0 pour éviter la répétition de celui-ci tant qu'il n'y a pas eu d'action*/
	}


	/************************************************************************/
	/* Libération des variables et fermetures de SDL                        */
	/************************************************************************/

    SDL_FreeSurface(tab_surface[0]);
    SDL_FreeSurface(tab_surface[1]);
    SDL_FreeSurface(tab_surface[3]);
    SDL_FreeSurface(tab_surface[5]);
    SDL_FreeSurface(tab_surface[9]);
    SDL_FreeSurface(tab_surface[10]);
    SDL_FreeSurface(tab_surface[11]);
	free(tab_surface);
    
    SDL_FreeSurface(Noir);
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(icone);

	FMOD_Sound_Release(son_saut_debut);
	FMOD_Sound_Release(son_saut_fin);

	detruire_animation(&saut_ftl);

	TTF_Quit();
	SDL_Quit();
}


/************************************************************************/
/* Fonctions liées au combat                                             */
/************************************************************************/
/**
 * \brief      crée l'affichage carte du combat à partir  du terrain crée
 * \details    
 * \param      terrain_combat         Pointeur sur Terrain_combat 
 * \return     un surface sdl corrrespondant au terrain du combat
 */
SDL_Surface * affiche_ecran_terrain_combat(const Terrain_combat *terrain_combat)
{
	
	SDL_Surface * fond =NULL;
	SDL_Surface * quadrillage =NULL;
	SDL_Surface * vaisseau =NULL;
    SDL_Surface * vaisseau2 =NULL;
	SDL_Surface * selection =NULL;
	SDL_Surface * carte =NULL;
	SDL_Rect pos,pos_plan;
	int i, j,x,y;
    Case_terrain_combat *une_case;
	x=get_taille_combat_x(terrain_combat);
	y=get_taille_combat_y(terrain_combat);
	carte =SDL_CreateRGBSurface(SDL_HWSURFACE, x* 100, y* 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	
	pos.x = 0 ;pos_plan.x=0;
	pos.y = 0;pos_plan.y=0;
	
	fond = IMG_Load("../data/graphiques/images/Fond_terraincombat.png");
    SDL_BlitSurface(fond, NULL, carte, &pos);
	quadrillage = IMG_Load("../data/graphiques/images/quadrillage.png");
	selection = IMG_Load("../data/graphiques/images/selection.png");

    for(j=0;j<terrain_combat->taille_combat_y;j++)
    {
        for(i=0;i<terrain_combat->taille_combat_x;i++)
        {
            pos.x=i*100;pos.y=j*100;
            une_case = get_case_terrain_combat(terrain_combat, i, j);
            if(get_presence_unite(une_case)&&(get_indice_joueur_unite(get_unite(une_case))==0))
            {
                if(get_type_vaisseau(get_unite(une_case))==Chasseur)
                {
                    vaisseau = IMG_Load("../data/graphiques/images/unite1_bleu.png");
                    pos_plan.x=i*100;pos_plan.y=j*100;
                    SDL_BlitSurface(vaisseau,NULL,carte,&pos_plan);
                    SDL_FreeSurface(vaisseau);
                }
                else if(get_type_vaisseau(get_unite(une_case))==Destroyer)
                {
                    vaisseau = IMG_Load("../data/graphiques/images/unite2_bleu.png");
                    pos_plan.x=i*100;pos_plan.y=j*100;
                    SDL_BlitSurface(vaisseau,NULL,carte,&pos_plan);
                    SDL_FreeSurface(vaisseau);
                }
                else if(get_type_vaisseau(get_unite(une_case))==Destructeur)
                {
                    vaisseau = IMG_Load("../data/graphiques/images/unite3_bleu.png");
                    pos_plan.x=i*100;pos_plan.y=j*100;
                    SDL_BlitSurface(vaisseau,NULL,carte,&pos_plan);
                    SDL_FreeSurface(vaisseau);
                }
            }
            else if(get_presence_unite(une_case)&&(get_indice_joueur_unite(get_unite(une_case))==1))
            {
                if(get_type_vaisseau(get_unite(une_case))==Chasseur)
                {
                    vaisseau = IMG_Load("../data/graphiques/images/unite1_rouge.png");
                    pos_plan.x=i*100;pos_plan.y=j*100;
                    vaisseau2 = rotozoomSurface (vaisseau, 180, 1.0, 1);
                    SDL_BlitSurface(vaisseau2,NULL,carte,&pos_plan);
                    SDL_FreeSurface(vaisseau);
                    SDL_FreeSurface(vaisseau2);
                }
                else if(get_type_vaisseau(get_unite(une_case))==Destroyer)
                {
                    vaisseau = IMG_Load("../data/graphiques/images/unite2_rouge.png");
                    pos_plan.x=i*100;pos_plan.y=j*100;
                    vaisseau2 = rotozoomSurface (vaisseau, 180, 1.0, 1);
                    SDL_BlitSurface(vaisseau2,NULL,carte,&pos_plan);
                    SDL_FreeSurface(vaisseau);
                    SDL_FreeSurface(vaisseau2);
                }
                else if(get_type_vaisseau(get_unite(une_case))==Destructeur)
                {
                    vaisseau = IMG_Load("../data/graphiques/images/unite3_rouge.png");
                    pos_plan.x=i*100;pos_plan.y=j*100;
                    vaisseau2 = rotozoomSurface (vaisseau, 180, 1.0, 1);
                    SDL_BlitSurface(vaisseau2,NULL,carte,&pos_plan);
                    SDL_FreeSurface(vaisseau);
                    SDL_FreeSurface(vaisseau2);
                }
            }
            else if(get_presence_unite(une_case))
            {
                vaisseau = IMG_Load("../data/graphiques/images/vaisseau_3.png");
                pos_plan.x=i*100;pos_plan.y=j*100;
                SDL_BlitSurface(vaisseau,NULL,carte,&pos_plan);
                SDL_FreeSurface(vaisseau);
            }
            if(get_selection_unite(une_case))
            {
                SDL_BlitSurface(selection,NULL,carte,&pos);
            }
            else
            {
                SDL_BlitSurface(quadrillage,NULL,carte,&pos);
            }
        }
    }
    SDL_FreeSurface(selection);
    SDL_FreeSurface(quadrillage);
    SDL_FreeSurface(fond);
    return carte;
}

/**
 * \brief      donne les coordonnée de la case sur laquelle est la souris en pixel 
 * \details     
 * \param      position       SDl_Rect qui contient les coordonées de la souris
 * \return     SDL_rect qui contient les coordonée de la case en pixel
 */
SDL_Rect coordonnee_clic(SDL_Rect position)
{

	if(position.x>=100){
		position.x = ceil(position.x/100)*100;}
	else{position.x=0;}
	if(position.y>=100){
		position.y = ceil(position.y/100)*100;}
	else{position.y=0;}
	return position;
}

/**
 * \brief      donne les coordonnée de la case sur laquelle est la souris
 * \details    
 * \param      position         SDl_Rect qui contient les coordonées de la souris
 * \return     SDL_rect qui contient les coordonée de la case
 */
SDL_Rect coordonnee_case_du_clic(SDL_Rect position)
{

	if(position.x>=100){
		position.x = ceil(position.x/100);}
	else{position.x=0;}
	if(position.y>=100){
		position.y = ceil(position.y/100);}
	else{position.y=0;}
	return position;
}

/**
 * \brief      affiche le déplacement de l'unité
 * \details    
 * \param      un_terrain_combat        Pointeur sur Terrain_combat 
 * \param      jeu        Pointeur sur Jeu 
 * \param      position         SDl_Rect qui contient les coordonées de la souris
 * \param      position_affichage_carte         SDl_Rect qui contient la position de la carte
 * \param      pos_bordure         SDl_Rect qui contient la position de la bordure
 * \param      carte        Pointeur sur SDL_Surface 
 * \param      bordure        Pointeur sur SDL_Surface 
 * \param      ecran        Pointeur sur SDL_Surface  
 * \param      infos2        Pointeur sur char
 */
void affiche_deplacement_unite(Jeu * jeu,Terrain_combat *un_terrain_combat,SDL_Rect position,SDL_Surface * carte,SDL_Surface * bordure,SDL_Surface * ecran,SDL_Rect position_affichage_carte,SDL_Rect pos_bordure, char* infos2,FMOD_SYSTEM *system,FMOD_SOUND *son_saut_debut,FMOD_SOUND *son_saut_fin)
{
	SDL_Rect pos;
	int i,x = 0 ,y = 0;
	bool p;
	Case_terrain_combat * une_case;
	Unite * une_unite;
	p=0;
	pos =coordonnee_case_du_clic(position);

	if(get_une_case_selectionnee(un_terrain_combat)&& get_pt_action_joueur(get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu)))>0)
	{
		x=get_x_combat(get_selection(un_terrain_combat)); y = get_y_combat(get_selection(un_terrain_combat));
		une_case = get_selection(un_terrain_combat);
		une_unite = get_unite(une_case);
		p=deplacement_unite(un_terrain_combat, une_unite ,pos.x,pos.y);
		if(p)
	{
		pos.y = 100*y + position_affichage_carte.y;
		pos.x = 100*x + position_affichage_carte.x;
				FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, son_saut_debut, 0, NULL);
		animation_avant_deplacement_unite(un_terrain_combat,jeu, carte,ecran,position_affichage_carte,pos.x,pos.y);
		i=get_joueur_en_cours_combat(jeu);
		enlever_pt_action_ieme_joueur(jeu,i,1);
		deselectionner(un_terrain_combat);
		carte=affiche_ecran_terrain_combat(un_terrain_combat);
		SDL_BlitSurface(carte, NULL,  ecran,&position_affichage_carte);
        SDL_FreeSurface(carte);
        SDL_BlitSurface(bordure, NULL, ecran, &pos_bordure);
		SDL_Flip(ecran);
		pos = coordonnee_clic(position);
		pos.y = pos.y + position_affichage_carte.y;
		pos.x = pos.x + position_affichage_carte.x;
				FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, son_saut_fin, 0, NULL);
		animation_avant_deplacement_unite(un_terrain_combat,jeu, carte,ecran,position_affichage_carte,pos.x,pos.y);
	}else if(!(x==pos.x) || !(y==pos.y)){
		sprintf(infos2,"Déplacement impossible !");
	}

	}
	
}

/**
 * \brief      permet de sélectionner ou désélectionner une case
 * \details    
 * \param      position         SDl_Rect qui contient les coordonées de la souris
 * \param      un_terrain_combat        Pointeur sur Terrain_combat 
 * \param      jeu        Pointeur sur Jeu 
 */
void selection(Jeu * jeu,Terrain_combat *un_terrain_combat,SDL_Rect position)
{
	SDL_Rect pos;
	pos=position;
	pos=coordonnee_case_du_clic(pos);
  	selectionner_case_combat(jeu,un_terrain_combat, pos.x, pos.y);
}
void affiche_info_unite(Jeu * jeu,Terrain_combat *un_terrain_combat,char * infos,SDL_Rect position)
{
	Unite * unite;
	Case_terrain_combat * une_case;
	int a,c,d,e,h;
	position = coordonnee_case_du_clic(position);
	une_case = get_case_terrain_combat(un_terrain_combat , position.x,position.y);

	if(get_presence_unite(une_case))
	{
		unite = get_unite(une_case);
		a = get_pt_vie(unite);
        c = get_portee(unite);
		d = get_pt_deplacement(unite);
		e = get_pt_attaque(unite);
		h = get_pt_action_joueur(get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu)));
		sprintf(infos,"Pt de vie = %d   Portée=%d   Pt déplacement=%d   Puissance d'attaque=%d",a,c,d,e);
	}
	else
	{

		sprintf(infos," ");
	}

}

/**
 * \brief      met en pause l'application
 * \details    
 */
void pause()
{

    int continuer;
    SDL_Event event;
    continuer = 1;
	SDL_Init(SDL_INIT_VIDEO);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}


void input_handle(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        switch (event.type) {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;
        }
    }
}

/**
 * \brief      menu de chargement d'une sauvegarde
 * \details
 * \param un_terrain_espace Double pointeur sur terrain_espace
 * \param un_jeu Double pointeur sur jeu
 * \param system Pointeur sur FMOD_SYSTEM (pour la musique)
 * \param musique Pointeur sur FMOD_SOUND (pour la musique)
 */
void menu_chargement_sauvegarde(Terrain_espace **un_terrain_espace, Jeu **un_jeu, FMOD_SYSTEM *system, FMOD_SOUND *musique)
{
    /*Initialisation des variables*/
    SDL_Surface *ecran, *imageDeFond, *Texte, *Texte2, *Noir;
    TTF_Font *police;
    SDL_Color couleur= {255, 255, 255};
    SDL_Rect positionTexte, positionTexte2, position_saisie_texte;
    Sauvegarde *une_sauvegarde;
    int b = 255;
    char chaine[50];
	double longueurTexte, longueurTexte2;


    /*CHARGEMENT*/

    /*Initialisation de l'écran et des images */
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../data/graphiques/images/Sauvegarde_Fond.png");
    Noir = SDL_LoadBMP("../data/graphiques/images/Noir.bmp");

    /*Chargement du titre*/
    TTF_Init();
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 60);
    Texte = TTF_RenderText_Blended(police, "Charger une partie", couleur);
    longueurTexte = Texte->w;
    initialise_sdl_rect(&positionTexte, ((TAILLE_FENETRE_X/2.0) - (longueurTexte/2.0)), 1*(TAILLE_FENETRE_Y)/10, 0, 0);
    TTF_CloseFont(police);
    
    /*Chargement du texte*/
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 40);
    Texte2 = TTF_RenderText_Blended(police, "Tapez le nom de la sauvegarde", couleur);
    longueurTexte2 = Texte2->w;
    initialise_sdl_rect(&positionTexte2, ((TAILLE_FENETRE_X/2.0) - (longueurTexte2/2.0)), 9*(TAILLE_FENETRE_Y)/10, 0, 0);
    TTF_CloseFont(police);


    /*AFFICHAGE*/

    /*Animation de l'apparition du menu*/
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-20;
        SDL_Flip(ecran);
        SDL_FreeSurface(ecran);
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
        SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
        SDL_BlitSurface(Texte2, NULL, ecran, &positionTexte2);
    }

    /*Scan du nom et chargement de la sauvegarde*/
    initialise_sdl_rect(&position_saisie_texte, 350, (TAILLE_FENETRE_Y)/5, 0, 0);
	saisie_texte_sdl(chaine, ecran, position_saisie_texte);
    une_sauvegarde = selection_ouverture(chaine);
    *un_jeu = une_sauvegarde->jeu;
    *un_terrain_espace = une_sauvegarde->terrain_espace;

    /*Disparition du menu et affichage du jeu*/
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(Texte);
    SDL_FreeSurface(Texte2);
    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(Noir);
    affichage_ecran(*un_jeu, *un_terrain_espace, system, musique);
}

/**
 * \brief      menu de création d'une sauvegarde
 * \details
 * \param un_terrain_espace pointeur sur terrain_espace
 * \param un_jeu pointeur sur jeu
 */
void menu_creation_sauvegarde(Terrain_espace *un_terrain_espace, Jeu *un_jeu)
{
    /*Initialisation des variables*/
    SDL_Surface *ecran, *imageDeFond, *Texte, *Texte2, *Noir;
    TTF_Font *police;
    SDL_Color couleur= {255, 255, 255};
    SDL_Rect positionTexte, positionTexte2, position_saisie_texte;
    int b = 255;
    char chaine[50];
	double longueurTexte, longueurTexte2;


    /*CHARGEMENT*/

    /*Initialisation de l'écran et des images */
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../data/graphiques/images/Sauvegarde_Fond.png");
    Noir = SDL_LoadBMP("../data/graphiques/images/Noir.bmp");

    /*Chargement du titre*/
    TTF_Init();
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 60);
    Texte = TTF_RenderText_Blended(police, "Sauvegarder une partie", couleur);
    longueurTexte = Texte->w;
    initialise_sdl_rect(&positionTexte, ((TAILLE_FENETRE_X/2.0) - (longueurTexte/2.0)), 1*(TAILLE_FENETRE_Y)/10, 0, 0);
    TTF_CloseFont(police);
    
    /*Chargement du texte*/
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 40);
    Texte2 = TTF_RenderText_Blended(police, "Tapez le nom de la sauvegarde", couleur);
    longueurTexte2 = Texte2->w;
    initialise_sdl_rect(&positionTexte2, ((TAILLE_FENETRE_X/2.0) - (longueurTexte2/2.0)), 9*(TAILLE_FENETRE_Y)/10, 0, 0);
    TTF_CloseFont(police);

    /*AFFICHAGE*/

    /*Animation de l'apparition du menu*/
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-20;
        SDL_Flip(ecran);
        SDL_FreeSurface(ecran);
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
        SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
        SDL_BlitSurface(Texte2, NULL, ecran, &positionTexte2);
    }

    /*Scan du nom et sauvegarde*/
    initialise_sdl_rect(&position_saisie_texte, 350, (TAILLE_FENETRE_Y)/5, 0, 0);
	saisie_texte_sdl(chaine, ecran, position_saisie_texte);
    creer_fichier_sauvegarde(chaine, un_terrain_espace, un_jeu);
    
    /*Disparition du menu*/
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(Texte);
    SDL_FreeSurface(Texte2);
    SDL_FreeSurface(Noir);
    SDL_FreeSurface(imageDeFond);
}

/**
 * \brief      menu d'aide
 * \details
 */
void menu_aide(void)
{
    /* Initialisation des variables */
    SDL_Surface *ecran, *imageDeFond_Gauche, *imageDeFond_Droit, *Noir, *Titre, *Deplacer, *Conquerir, *Construire, *Suivant, *Quitter;
    SDL_Rect positionImage_droit, positionDeplacer, positionConquerir, positionConstruire, positionSuivant, positionQuitter;
    SDL_Event evenement;
    double hauteurBouton;
    int i, continuer = 1, aide = 0, b = 255;

    /* Chargement des images */
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, 32, SDL_HWSURFACE);
    imageDeFond_Gauche = IMG_Load("../data/graphiques/images/Fond_Aide_Gauche.png");
    imageDeFond_Droit = IMG_Load("../data/graphiques/images/Fond_Aide_Droit.png");
    Noir = SDL_LoadBMP("../data/graphiques/images/Noir.bmp");
    Titre = IMG_Load("../data/graphiques/images/Titre_Aide.png");
    Deplacer = IMG_Load("../data/graphiques/images/Deplacer.png");
    Conquerir = IMG_Load("../data/graphiques/images/Conquerir.png");
    Construire = IMG_Load("../data/graphiques/images/Construire.png");
    Suivant = IMG_Load("../data/graphiques/images/Suivant.png");
    Quitter = IMG_Load("../data/graphiques/images/Quitter_menu.png");

    /* Affichage des images */
    positionImage_droit.x = 300;
    positionImage_droit.y = 0;
    hauteurBouton = Deplacer->h;
    positionDeplacer.x = 0;
    positionDeplacer.y = 150;
    positionConquerir.x = 0;
    positionConquerir.y = 225;
    positionConstruire.x = 0;
    positionConstruire.y = 300;
    positionSuivant.x = 1080;
    positionSuivant.y = 668;
    positionQuitter.x = 21;
    positionQuitter.y = TAILLE_FENETRE_Y - hauteurBouton - 10;
    
    /*Animation de l'apparition du menu*/
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-20;
        SDL_Flip(ecran);
        SDL_FreeSurface(ecran);
        SDL_BlitSurface(imageDeFond_Gauche, NULL, ecran, NULL);
        SDL_BlitSurface(imageDeFond_Droit, NULL, ecran, &positionImage_droit);
        SDL_BlitSurface(Titre, NULL, ecran, NULL);
        SDL_BlitSurface(Deplacer, NULL, ecran, &positionDeplacer);
        SDL_BlitSurface(Conquerir, NULL, ecran, &positionConquerir);
        SDL_BlitSurface(Construire, NULL, ecran, &positionConstruire);
        SDL_BlitSurface(Quitter, NULL, ecran, &positionQuitter);
    }

    /* Animation des boutons du menu */
    while(continuer)
	{
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
                /*Chargement des menus lors d'un clic sur un bouton */
			case SDL_MOUSEBUTTONUP:

                /* Se déplacer */
                if(test_souris_rectangle(positionDeplacer,evenement.button.x,evenement.button.y))
				{
                    aide = 1;
                    SDL_FreeSurface(imageDeFond_Droit);
                    SDL_FreeSurface(Deplacer);
                    SDL_FreeSurface(Conquerir);
                    SDL_FreeSurface(Construire);
                    imageDeFond_Droit = IMG_Load("../data/graphiques/images/Deplacer1.png");
                    Deplacer = IMG_Load("../data/graphiques/images/Deplacer_Presse.png");
                    Conquerir = IMG_Load("../data/graphiques/images/Conquerir.png");
                    Construire = IMG_Load("../data/graphiques/images/Construire.png");


                    SDL_BlitSurface(imageDeFond_Gauche, NULL, ecran, NULL);
                    SDL_BlitSurface(imageDeFond_Droit, NULL, ecran, &positionImage_droit);
                    SDL_BlitSurface(Titre, NULL, ecran, NULL);
                    SDL_BlitSurface(Deplacer, NULL, ecran, &positionDeplacer);
                    SDL_BlitSurface(Conquerir, NULL, ecran, &positionConquerir);
                    SDL_BlitSurface(Construire, NULL, ecran, &positionConstruire);
                    SDL_BlitSurface(Suivant, NULL, ecran, &positionSuivant);
                    SDL_BlitSurface(Quitter, NULL, ecran, &positionQuitter);
                    SDL_Flip(ecran);
				}

                /* Conquérir */
                if(test_souris_rectangle(positionConquerir,evenement.button.x,evenement.button.y))
				{
                    aide = 2;
                    SDL_FreeSurface(imageDeFond_Droit);
                    SDL_FreeSurface(Deplacer);
                    SDL_FreeSurface(Conquerir);
                    SDL_FreeSurface(Construire);
                    imageDeFond_Droit = IMG_Load("../data/graphiques/images/Conquerir1.png");
                    Deplacer = IMG_Load("../data/graphiques/images/Deplacer.png");
                    Conquerir = IMG_Load("../data/graphiques/images/Conquerir_Presse.png");
                    Construire = IMG_Load("../data/graphiques/images/Construire.png");

                    SDL_BlitSurface(imageDeFond_Gauche, NULL, ecran, NULL);
                    SDL_BlitSurface(imageDeFond_Droit, NULL, ecran, &positionImage_droit);
                    SDL_BlitSurface(Titre, NULL, ecran, NULL);
                    SDL_BlitSurface(Deplacer, NULL, ecran, &positionDeplacer);
                    SDL_BlitSurface(Conquerir, NULL, ecran, &positionConquerir);
                    SDL_BlitSurface(Construire, NULL, ecran, &positionConstruire);
                    SDL_BlitSurface(Suivant, NULL, ecran, &positionSuivant);
                    SDL_BlitSurface(Quitter, NULL, ecran, &positionQuitter);
                    SDL_Flip(ecran);
				}

                /* Construire */
                if(test_souris_rectangle(positionConstruire,evenement.button.x,evenement.button.y))
				{
                    aide = 3;
                    SDL_FreeSurface(imageDeFond_Droit);
                    SDL_FreeSurface(Deplacer);
                    SDL_FreeSurface(Conquerir);
                    SDL_FreeSurface(Construire);
                    imageDeFond_Droit = IMG_Load("../data/graphiques/images/Construire1.png");
                    Deplacer = IMG_Load("../data/graphiques/images/Deplacer.png");
                    Conquerir = IMG_Load("../data/graphiques/images/Conquerir.png");
                    Construire = IMG_Load("../data/graphiques/images/Construire_Presse.png");

                    SDL_BlitSurface(imageDeFond_Gauche, NULL, ecran, NULL);
                    SDL_BlitSurface(imageDeFond_Droit, NULL, ecran, &positionImage_droit);
                    SDL_BlitSurface(Titre, NULL, ecran, NULL);
                    SDL_BlitSurface(Deplacer, NULL, ecran, &positionDeplacer);
                    SDL_BlitSurface(Conquerir, NULL, ecran, &positionConquerir);
                    SDL_BlitSurface(Construire, NULL, ecran, &positionConstruire);
                    SDL_BlitSurface(Suivant, NULL, ecran, &positionSuivant);
                    SDL_BlitSurface(Quitter, NULL, ecran, &positionQuitter);
                    SDL_Flip(ecran);
				}

                /* Bouton suivant*/
                if(test_souris_rectangle(positionSuivant,evenement.button.x,evenement.button.y))
				{
                    if(aide == 1)
                    {
                        aide = 0;
                        SDL_FreeSurface(imageDeFond_Droit);
                        imageDeFond_Droit = IMG_Load("../data/graphiques/images/Deplacer2.png");
                        SDL_BlitSurface(imageDeFond_Droit, NULL, ecran, &positionImage_droit);
                        SDL_Flip(ecran);
                    }
                    if(aide == 2)
                    {
                        aide = 0;
                        SDL_FreeSurface(imageDeFond_Droit);
                        imageDeFond_Droit = IMG_Load("../data/graphiques/images/Conquerir2.png");
                        SDL_BlitSurface(imageDeFond_Droit, NULL, ecran, &positionImage_droit);
                        SDL_Flip(ecran);
                    }
                    if(aide == 3)
                    {
                        aide = 0;
                        SDL_FreeSurface(imageDeFond_Droit);
                        imageDeFond_Droit = IMG_Load("../data/graphiques/images/Construire2.png");
                        SDL_BlitSurface(imageDeFond_Droit, NULL, ecran, &positionImage_droit);
                        SDL_Flip(ecran);
                    }
                }

                /* Quitter le menu */
                if(test_souris_rectangle(positionQuitter,evenement.button.x,evenement.button.y))
				{
                    continuer = 0;
                    for (i=0; i<30; i++)
                    {
                        SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(imageDeFond_Gauche);
                    SDL_FreeSurface(imageDeFond_Droit);
                    SDL_FreeSurface(Noir);
                    SDL_FreeSurface(Titre);
                    SDL_FreeSurface(Deplacer);
                    SDL_FreeSurface(Conquerir);
                    SDL_FreeSurface(Construire);
                    SDL_FreeSurface(Suivant);
                    SDL_FreeSurface(Quitter);
                    SDL_FreeSurface(ecran);
				}
        }
    }
}

/**
 * \brief      menu pause
 * \details
 * \param un_terrain_espace pointeur sur terrain_espace
 * \param un_jeu pointeur sur jeu
 * \param exit entier déterminant si le jeu se termine ou non
 */
void menu_pause(Terrain_espace *un_terrain_espace, Jeu *un_jeu, int * exit)
{
    /* Initialisation des variables */
    SDL_Surface *ecran, *imageDeFond, *Texte, *Noir, *Retour, *Aide, *Sauvegarder, *Quitter;
    TTF_Font *police;
    SDL_Color couleur= {255, 255, 255};
    SDL_Rect positionTexte, positionRetour, positionAide, positionSauvegarder, positionQuitter;
    SDL_Event evenement;
    int continuer = 1, xm = 0, ym = 0, i, b = 255;
    double longueurTexte, longueurBouton, hauteurBouton;

    /* Chargement des images */
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../data/graphiques/images/Fond_titre.png");
    Noir = SDL_LoadBMP("../data/graphiques/images/Noir.bmp");
    Retour = IMG_Load("../data/graphiques/images/Retour.png");
    Aide = IMG_Load("../data/graphiques/images/Aide.png");
    Sauvegarder = IMG_Load("../data/graphiques/images/Sauvegarder.png");
    Quitter = IMG_Load("../data/graphiques/images/Quitter.png");

    /* Chargement de la police */
    TTF_Init();
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 60);
    Texte = TTF_RenderText_Blended(police, "Pause", couleur);
    longueurTexte = Texte->w;
    positionTexte.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte/2.0));
    positionTexte.y = 1*(TAILLE_FENETRE_Y)/10;
    TTF_CloseFont(police);
    longueurBouton = Sauvegarder->w;
    hauteurBouton = Sauvegarder->h;
    positionRetour.x = ((TAILLE_FENETRE_X/2.0) - (longueurBouton/2.0));
    positionRetour.y = ((TAILLE_FENETRE_Y/2.2) - (hauteurBouton/2.0));
    positionAide.x = positionRetour.x;
    positionAide.y = positionRetour.y + 75;
    positionSauvegarder.x = positionAide.x;
    positionSauvegarder.y = positionAide.y + 75;
    positionQuitter.x = positionSauvegarder.x;
    positionQuitter.y = positionSauvegarder.y + 75;
    
    /*Animation de l'apparition du menu*/
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-20;
        SDL_Flip(ecran);
        SDL_FreeSurface(ecran);
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
        SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
        SDL_BlitSurface(Retour, NULL, ecran, &positionRetour);
        SDL_BlitSurface(Aide, NULL, ecran, &positionAide);
        SDL_BlitSurface(Sauvegarder, NULL, ecran, &positionSauvegarder);
        SDL_BlitSurface(Quitter, NULL, ecran, &positionQuitter);
    }
    SDL_Flip(ecran);

    /* Animation des boutons du menu */
    continuer = 1;
    while(continuer)
	{
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
            case SDL_MOUSEMOTION :
                SDL_GetMouseState(&xm, &ym);
                SDL_FreeSurface(Retour);
                SDL_FreeSurface(Aide);
                SDL_FreeSurface(Sauvegarder);
                SDL_FreeSurface(Quitter);
                SDL_FreeSurface(ecran);
                if(test_souris_rectangle(positionRetour,xm,ym))
                {
                    Retour = IMG_Load("../data/graphiques/images/Retour_Presse.png");
                }
                if(!test_souris_rectangle(positionRetour,xm,ym))
                {
                    Retour = IMG_Load("../data/graphiques/images/Retour.png");
                }
                if(test_souris_rectangle(positionAide,xm,ym))
                {
                    Aide = IMG_Load("../data/graphiques/images/Aide_Presse.png");
                }
                if(!test_souris_rectangle(positionAide,xm,ym))
                {
                    Aide = IMG_Load("../data/graphiques/images/Aide.png");
                }
                if(test_souris_rectangle(positionSauvegarder,xm,ym))
                {
                    Sauvegarder = IMG_Load("../data/graphiques/images/Sauvegarder_Presse.png");
                }
                if(!test_souris_rectangle(positionSauvegarder,xm,ym))
                {
                    Sauvegarder = IMG_Load("../data/graphiques/images/Sauvegarder.png");
                }
                if(test_souris_rectangle(positionQuitter,xm,ym))
                {
                    Quitter = IMG_Load("../data/graphiques/images/Quitter_Presse.png");
                }
                if(!test_souris_rectangle(positionQuitter,xm,ym))
                {
                    Quitter = IMG_Load("../data/graphiques/images/Quitter.png");
                }
                SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
                SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
                SDL_BlitSurface(Retour, NULL, ecran, &positionRetour);
                SDL_BlitSurface(Aide, NULL, ecran, &positionAide);
                SDL_BlitSurface(Sauvegarder, NULL, ecran, &positionSauvegarder);
                SDL_BlitSurface(Quitter, NULL, ecran, &positionQuitter);
                SDL_Flip(ecran);
                break;

                /*Chargement des menus lors d'un clic sur un bouton */
			case SDL_MOUSEBUTTONUP:

                /* Retour au jeu */
                if(test_souris_rectangle(positionRetour,evenement.button.x,evenement.button.y))
				{
                    continuer = 0;
                    *exit = 1;
                    SDL_FreeSurface(imageDeFond);
                    SDL_FreeSurface(Texte);
                    SDL_FreeSurface(Retour);
                    SDL_FreeSurface(Aide);
                    SDL_FreeSurface(Sauvegarder);
                    SDL_FreeSurface(Quitter);
                    SDL_FreeSurface(ecran);
                    SDL_FreeSurface(Noir);
				}
                
                /* Aide */
                if(test_souris_rectangle(positionAide,evenement.button.x,evenement.button.y))
				{
                    continuer = 0;
                    SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                    for (i=0; i<30; i++)
                    {
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(imageDeFond);
                    SDL_FreeSurface(Texte);
                    SDL_FreeSurface(Retour);
                    SDL_FreeSurface(Aide);
                    SDL_FreeSurface(Sauvegarder);
                    SDL_FreeSurface(Quitter);
                    SDL_FreeSurface(ecran);
                    SDL_FreeSurface(Noir);
                    menu_aide();
                    menu_pause(un_terrain_espace, un_jeu, exit);
				}

                /* Sauvegarder */
                if(test_souris_rectangle(positionSauvegarder,evenement.button.x,evenement.button.y))
				{
                    continuer = 0;
                    SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                    for (i=0; i<30; i++)
                    {
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(imageDeFond);
                    SDL_FreeSurface(Texte);
                    SDL_FreeSurface(Retour);
                    SDL_FreeSurface(Aide);
                    SDL_FreeSurface(Sauvegarder);
                    SDL_FreeSurface(Quitter);
                    SDL_FreeSurface(ecran);
                    SDL_FreeSurface(Noir);
                    menu_creation_sauvegarde(un_terrain_espace, un_jeu);
                    menu_pause(un_terrain_espace, un_jeu, exit);
				}

                /* Quitter le jeu */
                if(test_souris_rectangle(positionQuitter,evenement.button.x,evenement.button.y))
				{
                    continuer = 0;
                    SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                    for (i=0; i<30; i++)
                    {
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(imageDeFond);
                    SDL_FreeSurface(Texte);
                    SDL_FreeSurface(Retour);
                    SDL_FreeSurface(Aide);
                    SDL_FreeSurface(Sauvegarder);
                    SDL_FreeSurface(Quitter);
                    SDL_FreeSurface(ecran);
                    SDL_FreeSurface(Noir);
                    *exit = 0;
				}
        }
    }
}

/**
 * \brief      initialisation d'une nouvelle partie
 * \details
 * \param nom1 Nom du joueur 1
 * \param nom2 Nom du joueur 2
 * \param un_terrain_espace Double pointeur sur terrain_espace
 * \param un_jeu Double pointeur sur jeu
 */
void init_nouvelle_partie(char nom1[], char nom2[], Terrain_espace **un_terrain_espace, Jeu **jeu)
{
    Flotte *flotte;
    Unite *unite1;
    Unite *unite2;
    
	Flotte *flotte2;
    Unite *unite3;
    Unite *unite4;
    
	/*Liste des planètes*/
	Planete* Terre;
	Planete* Caprica;
    
	Joueur *joueur;
	Joueur *joueur2;
    
    modification_terrain_espace(*un_terrain_espace, 'E');
    
    ajouter_planete_terrain_espace(*un_terrain_espace, 1, 1, "Terre", 300, 300, 300, 300);
    ajouter_planete_terrain_espace(*un_terrain_espace, 4, 4, "Jupiter", 50, 25, 300, 25);
	ajouter_planete_terrain_espace(*un_terrain_espace, 0, 4, "Mars", 150, 100, 20, 150);
	ajouter_planete_terrain_espace(*un_terrain_espace, 0, 6, "Venus", 200, 200, 10, 50);
	ajouter_planete_terrain_espace(*un_terrain_espace, 1, 8, "Saturne", 20, 30, 200, 50);
    
	ajouter_planete_terrain_espace(*un_terrain_espace, 10, 7, "Kobol", 200, 300, 150, 50);
    
	ajouter_planete_terrain_espace(*un_terrain_espace, 18, 13, "Caprica", 300, 300, 300, 300);
	ajouter_planete_terrain_espace(*un_terrain_espace, 15, 14, "Gemenon", 50, 25, 300, 25);
	ajouter_planete_terrain_espace(*un_terrain_espace, 19, 9, "Picon", 150, 100, 20, 150);
	ajouter_planete_terrain_espace(*un_terrain_espace, 14, 11, "Sagitarron", 200, 200, 10, 50);
	ajouter_planete_terrain_espace(*un_terrain_espace, 10, 13, "Tauron", 20, 30, 200, 50);
    
    Terre = get_planete_terrain_espace(*un_terrain_espace, 1, 1);
    Caprica = get_planete_terrain_espace(*un_terrain_espace, 18, 13);
    
	joueur = creer_joueur(nom1, 0, false);
	joueur2 = creer_joueur(nom2, 1, false);
	
    ajouter_joueur(*jeu, joueur);
	ajouter_joueur(*jeu, joueur2);
    
    flotte = creer_flotte();
    unite1 = creer_unite(Chasseur);
    unite2 = creer_unite(Chasseur);
    
	flotte2 = creer_flotte();
	unite3 = creer_unite(Chasseur);
	unite4 = creer_unite(Chasseur);

	ajouter_planete_joueur(get_ieme_joueur_jeu(*jeu, 0), Terre);
    
	ajouter_planete_joueur(get_ieme_joueur_jeu(*jeu, 1), Caprica);
    
    ajouter_unite_flotte(flotte, unite1);
    ajouter_unite_flotte(flotte, unite2);
    
	ajouter_unite_flotte(flotte2, unite3);
    ajouter_unite_flotte(flotte2, unite4);
	
	ajouter_flotte_jeu(*jeu, *un_terrain_espace, flotte, 0, 1, 2);
	ajouter_flotte_jeu(*jeu, *un_terrain_espace, flotte2, 1, 18, 13);
}

/**
 * \brief      Ecran de Game Over
 * \details
 * \param nom1 Nom du joueur 1
 * \param nom2 Nom du joueur 2
 * \param system Pointeur sur FMOD_SYSTEM (pour la musique)
 * \param musique Pointeur sur FMOD_SOUND (pour la musique)
 */
void game_over(char nom1[30], char nom2[30], FMOD_SYSTEM* system, FMOD_SOUND* musique)
{
    /*Initialisation des variables*/
    SDL_Surface *ecran, *imageDeFond, *Texte, *Texte2, *Noir;
    TTF_Font *police;
    SDL_Color couleur= {255, 255, 255};
    SDL_Rect positionTexte, positionTexte2;
    int b = 255, continuer = 1, i;
	double longueurTexte, longueurTexte2;
    char gagnant[60] = "Merci d'avoir joué ";
    char perdant[60] = "Merci d'avoir été nul ";
	char **tab_chanson = NULL;
    SDL_Event evenement;
    strcat(gagnant, nom1);
    strcat(perdant, nom2);

    /*CHARGEMENT*/
    
    /*Initialisation de l'écran et des images */
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../data/graphiques/images/Game_over.png");
    Noir = SDL_LoadBMP("../data/graphiques/images/Noir.bmp");
	tab_chanson = (char **)malloc(sizeof(char *) * 6);
	initialiser_tableau_chanson_game_over(tab_chanson);
	lire_musique(system, musique, tab_chanson);
    
    /*Chargement du titre*/
    TTF_Init();
    
    /*Chargement du texte*/
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 40);
    Texte = TTF_RenderUTF8_Blended(police, gagnant, couleur);
    longueurTexte = Texte->w;
    initialise_sdl_rect(&positionTexte, ((TAILLE_FENETRE_X/2.0) - (longueurTexte/2.0)), 8*(TAILLE_FENETRE_Y)/10, 0, 0);
    Texte2 = TTF_RenderUTF8_Blended(police, perdant, couleur);
    longueurTexte2 = Texte2->w;
    initialise_sdl_rect(&positionTexte2, ((TAILLE_FENETRE_X/2.0) - (longueurTexte2/2.0)), 9*(TAILLE_FENETRE_Y)/10, 0, 0);
    TTF_CloseFont(police);
    
    
    /*AFFICHAGE*/
    
    /*Animation de l'apparition du menu*/
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-20;
        SDL_Flip(ecran);
        SDL_FreeSurface(ecran);
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
        SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
        SDL_BlitSurface(Texte2, NULL, ecran, &positionTexte2);
    }
    while(continuer)
	{
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
            case SDL_MOUSEBUTTONUP :
                continuer = 0;
                SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                for (i=0; i<30; i++)
                {
                    SDL_BlitSurface(Noir, NULL, ecran, NULL);
                    SDL_Flip(ecran);
                }
        }
    }
    SDL_FreeSurface(Texte);
    SDL_FreeSurface(Texte2);
    SDL_FreeSurface(imageDeFond);
    continuer = 1;
    b = 255;
    imageDeFond = IMG_Load("../data/graphiques/images/Credits.png");
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-20;
        SDL_Flip(ecran);
        SDL_FreeSurface(ecran);
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
    }
    while(continuer)
	{
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
            case SDL_MOUSEBUTTONUP :
                continuer = 0;
                SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                for (i=0; i<30; i++)
                {
                    SDL_BlitSurface(Noir, NULL, ecran, NULL);
                    SDL_Flip(ecran);
                }
        }
    }
    /*Disparition du menu et affichage du jeu*/
    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(Noir);
    SDL_FreeSurface(ecran);
	free(tab_chanson);
}

/**
 * \brief      Ecran de nouvelle partie
 * \details
 * \param un_terrain_espace Double pointeur sur terrain_espace
 * \param un_jeu Double pointeur sur jeu
 * \param system Pointeur sur FMOD_SYSTEM (pour la musique)
 * \param musique Pointeur sur FMOD_SOUND (pour la musique)
 */
void nouvelle_partie(Terrain_espace ** un_terrain_espace, Jeu **un_jeu, FMOD_SYSTEM *system, FMOD_SOUND *musique)
{
    /*Initialisation des variables*/
    SDL_Surface *ecran, *imageDeFond, *Texte, *Texte2, *Texte3, *Texte4, *Texte5, *Noir;
    TTF_Font *police;
    SDL_Color couleur= {255, 255, 255};
    SDL_Rect positionTexte, positionTexte2, positionTexte3, positionTexte4, positionTexte5;
	SDL_Rect position_saisie_texte = {0, 0, 0, 0};
    SDL_Event evenement;
    
    int b = 255, i, continuer = 1;
	double longueurTexte, longueurTexte2, longueurTexte3, longueurTexte4, longueurTexte5;

	char nom1[30];
    char nom2[30];
    
    
    *un_terrain_espace = creer_terrain_espace(20, 15);
    *un_jeu = creer_jeu();

    /*CHARGEMENT*/

    /* Initialisation de l'écran et des images */
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../data/graphiques/images/Fond_Nouvelle_Partie.png");
    Noir = SDL_LoadBMP("../data/graphiques/images/Noir.bmp");

    /* Chargement du titre */
    TTF_Init();
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 60);
    Texte = TTF_RenderUTF8_Blended(police, "Conquest Of Space", couleur);
    longueurTexte = Texte->w;
    positionTexte.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte/2.0));
    positionTexte.y = 1*(TAILLE_FENETRE_Y)/10;
    TTF_CloseFont(police);

    /* Chargement du texte */
    police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf", 30);
    Texte2 = TTF_RenderUTF8_Blended(police, "En l'an 2157, les chercheurs découvrent, aux frontières du", couleur);
    longueurTexte2 = Texte2->w;
    positionTexte2.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte2/2.0));
    positionTexte2.y = 3*(TAILLE_FENETRE_Y)/10;

    Texte3 = TTF_RenderUTF8_Blended(police, "sytème solaire, une espèce en tout point similaire à la nôtre", couleur);
    longueurTexte3 = Texte3->w;
    positionTexte3.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte3/2.0));
    positionTexte3.y = 4*(TAILLE_FENETRE_Y)/10;

    Texte4 = TTF_RenderUTF8_Blended(police, "Seulement, celle-ci ne cherchait pas la paix...", couleur);
    longueurTexte4 = Texte4->w;
    positionTexte4.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte4/2.0));
    positionTexte4.y = 6*(TAILLE_FENETRE_Y)/10;
    TTF_CloseFont(police);

    /* Chargement du "Cliquez pour continuer" */
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 40);
    Texte5 = TTF_RenderText_Blended(police, "Cliquez pour continuer", couleur);
    longueurTexte5 = Texte5->w;
    positionTexte5.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte5/2.0));
    positionTexte5.y = 9*(TAILLE_FENETRE_Y)/10;
    TTF_CloseFont(police);


    /*AFFICHAGE*/

    /*Animation de l'apparition du menu*/
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-50;
        SDL_Flip(ecran);
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
        SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
        SDL_BlitSurface(Texte2, NULL, ecran, &positionTexte2);
        SDL_BlitSurface(Texte3, NULL, ecran, &positionTexte3);
        SDL_BlitSurface(Texte4, NULL, ecran, &positionTexte4);
        SDL_BlitSurface(Texte5, NULL, ecran, &positionTexte5);
    }


    /* Attente du clic */
    while(continuer)
	{
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
            case SDL_MOUSEBUTTONUP :
                continuer = 0;
                /*Disparition du menu et affichage du jeu*/
                SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                for (i=0; i<10; i++)
                {
                    SDL_BlitSurface(Noir, NULL, ecran, NULL);
                    SDL_Flip(ecran);
                }
                SDL_FreeSurface(Texte);
                SDL_FreeSurface(Texte2);
                SDL_FreeSurface(Texte3);
                SDL_FreeSurface(Texte4);
                SDL_FreeSurface(Texte5);
                SDL_FreeSurface(imageDeFond);
        }
    }
    /*Initialisation des variables*/
    
    
    /*CHARGEMENT*/
    
    /*Initialisation de l'écran et des images */
    imageDeFond = IMG_Load("../data/graphiques/images/Fond_Nouvelle_Partie.png");
    
    /*Chargement du titre*/
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 60);
    Texte = TTF_RenderText_Blended(police, "Noms des joueurs", couleur);
    longueurTexte = Texte->w;
    positionTexte.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte/2.0));
    positionTexte.y = 1*(TAILLE_FENETRE_Y)/10;
    TTF_CloseFont(police);
    
    /*Chargement du texte*/
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 40);
    Texte2 = TTF_RenderText_Blended(police, "Noms des joueurs", couleur);
    longueurTexte2 = Texte2->w;
	initialise_sdl_rect(&positionTexte2, (TAILLE_FENETRE_X/2.0) - (longueurTexte2/2.0), (TAILLE_FENETRE_Y)/5, 0, 0);
    TTF_CloseFont(police);
    
    /*AFFICHAGE*/
    b = 255;
    /*Animation de l'apparition du menu*/
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-20;
        SDL_Flip(ecran);
        SDL_FreeSurface(ecran);
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
        SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
        SDL_BlitSurface(Texte2, NULL, ecran, &positionTexte2);
    }
    
    /*Scan du nom et sauvegarde*/
	initialise_sdl_rect(&position_saisie_texte, 350, 200, 0, 0);
	saisie_texte_sdl(nom1, ecran, position_saisie_texte);
	initialise_sdl_rect(&position_saisie_texte, 350, 250, 0, 0);
	saisie_texte_sdl(nom2, ecran, position_saisie_texte);
    
    /*Disparition du menu*/
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(Texte);
    SDL_FreeSurface(Texte2);
    SDL_FreeSurface(Noir);
    SDL_FreeSurface(imageDeFond);
    menu_aide();
    init_nouvelle_partie(nom1, nom2, un_terrain_espace, un_jeu);
    creer_vision_jeu(*un_jeu, *un_terrain_espace);
    affichage_ecran(*un_jeu, *un_terrain_espace, system, musique);
}

/**
 * \brief      Ecran titre
 * \details
 */
void ecran_titre(void)
{
    /* Initialisation des variables */
    SDL_Surface *ecran, *imageDeFond, *Titre, *Titre_Anime, *Texte, *Noir, *FondMenu, *Petit_Titre, *NouvellePartie, *Charger, *Quitter;
    TTF_Font *police;
    double a = 0.0, b = 1, X = TAILLE_FENETRE_X, Y = TAILLE_FENETRE_Y;
	double longueurTitre, hauteurTitre, longueurTexte;
    int continuer = 1, xm = 0, ym = 0, i, partie;
	SDL_Rect positionTitre, positionTexte, positionPetit_Titre, positionNouvellePartie, positionCharger, positionQuitter;
    SDL_Event clic_touche;
	SDL_Color couleur= {255, 255, 255};
    Terrain_espace *un_terrain_espace = NULL;
    Jeu * un_jeu = NULL;
    FMOD_SYSTEM *system = NULL;
	FMOD_SOUND *musique = NULL;
    char **tab_chanson;
    
    /*initialiser le son*/
	FMOD_System_Create(&system);
	FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, NULL);
	tab_chanson = (char **)malloc(sizeof(char *) * 6);
    initialiser_tableau_chanson(tab_chanson);
    
    /*CHARGEMENT*/

    /* Chargement des images */
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(X, Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../data/graphiques/images/Fond_titre.png");
    Titre = IMG_Load("../data/graphiques/images/Titre.png");
    Noir = SDL_LoadBMP("../data/graphiques/images/Noir.bmp");
    FondMenu = IMG_Load("../data/graphiques/images/FondMenu.png");
    Petit_Titre = IMG_Load("../data/graphiques/images/Petit_Titre.png");
    NouvellePartie = IMG_Load("../data/graphiques/images/Nouvelle_Partie.png");
    Charger = IMG_Load("../data/graphiques/images/Charger.png");
    Quitter = IMG_Load("../data/graphiques/images/Quitter.png");


    /*AFFICHAGE*/

    /* Affichage du titre de la fenêtre */
    SDL_WM_SetCaption("Conquest Of Space", NULL);
    
    /* Boucle pour le zoom du titre */
    while (a<1) {
        a = a+0.008;
        Titre_Anime = rotozoomSurface(Titre, 0, a, 2);
        longueurTitre = Titre_Anime->w;
        hauteurTitre = Titre_Anime->h;
        positionTitre.x = ((X/2.0) - (longueurTitre/2.0));
        positionTitre.y = ((Y/2.0) - (hauteurTitre/2.0));
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
        SDL_BlitSurface(Titre_Anime, NULL, ecran, &positionTitre);
        SDL_Flip(ecran);
        SDL_FreeSurface(Titre_Anime);
        input_handle();
    }

    /* Titre fixe et attente d'un clic */
    Titre_Anime = Titre;
    longueurTitre = Titre_Anime->w;
    hauteurTitre = Titre_Anime->h;
    positionTitre.x = ((X/2.0) - (longueurTitre/2.0));
    positionTitre.y = ((Y/2.0) - (hauteurTitre/2.0));
    SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
    SDL_BlitSurface(Titre_Anime, NULL, ecran, &positionTitre);
    TTF_Init();
    police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 40);
    Texte = TTF_RenderText_Blended(police, "Cliquez pour continuer", couleur);
    longueurTexte = Texte->w;
    positionTexte.x = ((X/2.0) - (longueurTexte/2.0));
    positionTexte.y = 9*(Y)/10;
    TTF_CloseFont(police);
    SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
    SDL_Flip(ecran);

    while(continuer)
    {
        SDL_WaitEvent(&clic_touche);

        /*Chargement du menu au clic */
        switch (clic_touche.type) {
            case SDL_MOUSEBUTTONDOWN:
                continuer = 0;

                /* Disparition du titre */
                initialiser_tableau_chanson_menu(tab_chanson);
                lire_musique(system, musique, tab_chanson);
                while (b<256) {
                    a = a+0.01;
                    Titre_Anime = rotozoomSurface(Titre, 0, a, 2);
                    longueurTitre = Titre_Anime->w;
                    hauteurTitre = Titre_Anime->h;
                    positionTitre.x = ((X/2.0) - (longueurTitre/2.0));
                    positionTitre.y = ((Y/2.0) - (hauteurTitre/2.0));
                    SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
                    SDL_BlitSurface(Titre_Anime, NULL, ecran, &positionTitre);
                    SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
                    SDL_BlitSurface(Noir, NULL, ecran, NULL);
                    b = b+15;
                    SDL_Flip(ecran);
                    SDL_FreeSurface(Titre_Anime);
                    SDL_FreeSurface(ecran);
                    input_handle();
                }
                SDL_FreeSurface(imageDeFond);
                SDL_FreeSurface(Texte);
                SDL_FreeSurface(Titre);
                
                /* Animation à l'affichage du menu */
                while (b>=0) {
                    double longueurPetit_Titre = Petit_Titre->w;
                    double longueurBouton = NouvellePartie->w;
                    double hauteurBouton = NouvellePartie->h;
                    SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
                    SDL_BlitSurface(Noir, NULL, ecran, NULL);
                    b = b-20;
                    SDL_Flip(ecran);
                    SDL_FreeSurface(ecran);
                    SDL_BlitSurface(FondMenu, NULL, ecran, NULL);
                    positionPetit_Titre.x = ((X/2.0) - (longueurPetit_Titre/2.0));
                    positionPetit_Titre.y = 100;
                    positionNouvellePartie.x = ((X/2.0) - (longueurBouton/2.0));
                    positionNouvellePartie.y = ((Y/2.0) - (hauteurBouton/2.0));
                    positionCharger.x = positionNouvellePartie.x;
                    positionCharger.y = positionNouvellePartie.y + 75;
                    positionQuitter.x = positionCharger.x;
                    positionQuitter.y = positionCharger.y + 75;
                    SDL_BlitSurface(Petit_Titre, NULL, ecran, &positionPetit_Titre);
                    SDL_BlitSurface(NouvellePartie, NULL, ecran, &positionNouvellePartie);
                    SDL_BlitSurface(Charger, NULL, ecran, &positionCharger);
                    SDL_BlitSurface(Quitter, NULL, ecran, &positionQuitter);
                    input_handle();
                }

                SDL_Flip(ecran);
                break;
        }
    }

    /* Animation des boutons du menu */
    continuer = 1, partie = 0;
    while(continuer)
	{
		SDL_WaitEvent(&clic_touche);
		switch(clic_touche.type)
		{
            case SDL_MOUSEMOTION :
                SDL_GetMouseState(&xm, &ym);
                SDL_FreeSurface(NouvellePartie);
                SDL_FreeSurface(Charger);
                SDL_FreeSurface(Quitter);
                if(test_souris_rectangle(positionNouvellePartie,xm,ym))
                {
                    NouvellePartie = IMG_Load("../data/graphiques/images/Nouvelle_Partie_Presse.png");
                }
                if(!test_souris_rectangle(positionNouvellePartie,xm,ym))
                {
                    NouvellePartie = IMG_Load("../data/graphiques/images/Nouvelle_Partie.png");
                }
                if(test_souris_rectangle(positionCharger,xm,ym))
                {
                    Charger = IMG_Load("../data/graphiques/images/Charger_Presse.png");
                }
                if(!test_souris_rectangle(positionCharger,xm,ym))
                {
                    Charger = IMG_Load("../data/graphiques/images/Charger.png");
                }
                if(test_souris_rectangle(positionQuitter,xm,ym))
                {
                    Quitter = IMG_Load("../data/graphiques/images/Quitter_Presse.png");
                }
                if(!test_souris_rectangle(positionQuitter,xm,ym))
                {
                    Quitter = IMG_Load("../data/graphiques/images/Quitter.png");
                }
                SDL_BlitSurface(FondMenu, NULL, ecran, NULL);
                SDL_BlitSurface(Petit_Titre, NULL, ecran, &positionPetit_Titre);
                SDL_BlitSurface(NouvellePartie, NULL, ecran, &positionNouvellePartie);
                SDL_BlitSurface(Charger, NULL, ecran, &positionCharger);
                SDL_BlitSurface(Quitter, NULL, ecran, &positionQuitter);
                SDL_Flip(ecran);
                break;
                
            /*Chargement des menus lors d'un clic sur un bouton */
			case SDL_MOUSEBUTTONUP:

                /* Nouvelle Partie */
                if(test_souris_rectangle(positionNouvellePartie,clic_touche.button.x,clic_touche.button.y))
				{
                    continuer = 0;
                    partie = 1;
                    SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                    for (i=0; i<10; i++)
                    {
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(FondMenu);
                    SDL_FreeSurface(Petit_Titre);
                    SDL_FreeSurface(NouvellePartie);
                    SDL_FreeSurface(Charger);
                    SDL_FreeSurface(Quitter);
                    SDL_FreeSurface(ecran);
                    SDL_FreeSurface(Noir);
                    nouvelle_partie(&un_terrain_espace, &un_jeu, system, musique);
				}

                /* Charger une partie */
				if(test_souris_rectangle(positionCharger,clic_touche.button.x,clic_touche.button.y))
				{
                    continuer = 0;
                    partie = 1;
                    SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                    for (i=0; i<10; i++)
                    {
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(FondMenu);
                    SDL_FreeSurface(Petit_Titre);
                    SDL_FreeSurface(NouvellePartie);
                    SDL_FreeSurface(Charger);
                    SDL_FreeSurface(Quitter);
                    SDL_FreeSurface(ecran);
                    SDL_FreeSurface(Noir);
                    menu_chargement_sauvegarde(&un_terrain_espace, &un_jeu, system, musique);
                    
				}

                /* Quitter le jeu */
                if(test_souris_rectangle(positionQuitter,clic_touche.button.x,clic_touche.button.y))
				{
                    continuer = 0;
                    SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                    for (i=0; i<10; i++)
                    {
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(FondMenu);
                    SDL_FreeSurface(Petit_Titre);
                    SDL_FreeSurface(NouvellePartie);
                    SDL_FreeSurface(Charger);
                    SDL_FreeSurface(Quitter);
                    SDL_FreeSurface(ecran);
                    SDL_FreeSurface(Noir);
                    free(tab_chanson);
                    fermer_systeme_son(system, musique);
                    SDL_Quit();
				}
        }
    }
    if (continuer == 0)
    {
        if (partie == 1)
        {
            detruire_jeu(&un_jeu);
            detruire_terrain_espace(&un_terrain_espace);
        }
    }
}

/**
 * \brief      Saisie sur la fenetre sdl
 * \details
 * \param nom chaine de caractères
 * \param ecran Pointeur sur SDL_Surface
 * \param position_saisie_texte Détermine l'emplacement de la saisie sur l'écran
 */
void saisie_texte_sdl(char nom[50], SDL_Surface* ecran, SDL_Rect position_saisie_texte)
{
	SDL_Surface* fond_texte = NULL;
	SDL_Surface* surface_texte = NULL;
	SDL_Rect position_texte = {5, 5, 0, 0};
	TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
	char c[10];
	int i = 0;
	bool saisie_en_cours = true;
	SDL_Event evenement;

	police = TTF_OpenFont("../data/graphiques/fonts/space_age.ttf", 40);

	fond_texte = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 50, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(fond_texte, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
	SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
	SDL_Flip(ecran);
    SDL_EnableKeyRepeat(200, 100);
	while(saisie_en_cours)
	{
        evenement.type = 0;
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
		case SDL_KEYDOWN:
			switch(evenement.key.keysym.sym)
			{
			case SDLK_a:
				nom[i] = 'A';
				sprintf(c, "A");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_b:
				nom[i] = 'B';
				sprintf(c, "B");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_c:
				nom[i] = 'C';
				sprintf(c, "C");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_d:
				nom[i] = 'D';
				sprintf(c, "D");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_e:
				nom[i] = 'E';
				sprintf(c, "E");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_f:
				nom[i] = 'F';
				sprintf(c, "F");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_g:
				nom[i] = 'G';
				sprintf(c, "G");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_h:
				nom[i] = 'H';
				sprintf(c, "H");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_i:
				nom[i] = 'I';
				sprintf(c, "I");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_j:
				nom[i] = 'J';
				sprintf(c, "J");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_k:
				nom[i] = 'K';
				sprintf(c, "K");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_l:
				nom[i] = 'L';
				sprintf(c, "L");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_m:
				nom[i] = 'M';
				sprintf(c, "M");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_n:
				nom[i] = 'N';
				sprintf(c, "N");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_o:
				nom[i] = 'O';
				sprintf(c, "O");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_p:
				nom[i] = 'P';
				sprintf(c, "P");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_q:
				nom[i] = 'Q';
				sprintf(c, "Q");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_r:
				nom[i] = 'R';
				sprintf(c, "R");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_s:
				nom[i] = 'S';
				sprintf(c, "S");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_t:
				nom[i] = 'T';
				sprintf(c, "T");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_u:
				nom[i] = 'U';
				sprintf(c, "U");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_v:
				nom[i] = 'V';
				sprintf(c, "V");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_w:
				nom[i] = 'W';
				sprintf(c, "W");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_x:
				nom[i] = 'X';
				sprintf(c, "X");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_y:
				nom[i] = 'Y';
				sprintf(c, "Y");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_z:
				nom[i] = 'Z';
				sprintf(c, "Z");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_SPACE:
				nom[i] = ' ';
				sprintf(c, " ");
				i++;
				surface_texte = TTF_RenderText_Blended(police, c, couleur_blanche);
				SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
				SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
				initialise_sdl_rect(&position_texte, position_texte.x + surface_texte->w + 2, 5, 0, 0);
				SDL_Flip(ecran);
				SDL_FreeSurface(surface_texte);
				break;
			case SDLK_BACKSPACE:
				if(i>1)
				{
					i--;
					surface_texte = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, position_texte.x - 10, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
					SDL_FillRect(surface_texte, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
					initialise_sdl_rect(&position_texte, position_texte.x - surface_texte->w, 5, 0, 0);
					SDL_BlitSurface(surface_texte, NULL, fond_texte, &position_texte);
					SDL_BlitSurface(fond_texte, NULL, ecran, &position_saisie_texte);
					SDL_Flip(ecran);
					SDL_FreeSurface(surface_texte);
				}
				break;
			case SDLK_RETURN:
				nom[i] = '\0';
				saisie_en_cours = false;
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
    TTF_CloseFont(police);
    SDL_FreeSurface(fond_texte);
}

/**
 * \brief      affiche l'attaque 
 * \details    
 * \param      un_terrain_combat        Pointeur sur Terrain_combat 
 * \param      jeu        Pointeur sur Jeu  
 * \param      flotte1        Pointeur sur Flotte 
 * \param      flotte2        Pointeur sur Flotte 
 * \return     1 si l'attaque à réussi, 0 sinon
 */
bool attaque_ecran(Jeu * jeu,Terrain_combat * un_terrain_combat, SDL_Rect pos,Flotte* flotte1,Flotte * flotte2)
{/*tentative d'attaque*/
	int p;
	int i;
	Case_terrain_combat * une_case;
	Unite * unite;
	une_case = get_selection(un_terrain_combat);
	pos=coordonnee_case_du_clic(pos);/*on récupère les coordonnées de la case ou on a cliqué */
	p=0;
	if(((peut_attaquer_hor_vert(un_terrain_combat, get_unite(une_case),pos.x,pos.y))||(peut_attaquer_diag(un_terrain_combat, get_unite(une_case),pos.x,pos.y)))&&get_pt_action_joueur(get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu)))>0)
	{/*si l'unité sélectionnée peut attaquer en diagonale ou à l'horizontale et verticale, et si le joueur à au moins un point d'action */
		p=attaquer(un_terrain_combat,get_unite(une_case),pos.x,pos.y); /*on essais dattaquer*/
	}
	if((p==0)||(p==1)){/*que l'attaque ait réussi ou pas , si il reste des points de vie à la "victime"*/
		return p;/*retourne 1 si l'attaque à réussi , 0 sinon*/
	}
	else if(p==-2)/*une unité n'a plus de point de vie*/
	{
		une_case = get_case_terrain_combat(un_terrain_combat,pos.x,pos.y);
		unite=get_unite(une_case);
		i=get_indice_joueur_unite(unite);
		if(i==0)
		{
			supprimer_unite_flotte(un_terrain_combat,flotte1,unite);
		}
		else if(i==1){supprimer_unite_flotte(un_terrain_combat,flotte2,unite);}
		return 1;
	}
	return 0;
}

/**
 * \brief      animation du déplacement en (x,y)
 * \details    
 * \param      un_terrain_combat        Pointeur sur Terrain_combat 
 * \param      jeu        Pointeur sur Jeu  
 * \param      ecran        Pointeur sur SDL_Surface  
 * \param      ecran2        Pointeur sur SDL_Surface 
 * \param      pos        SDL_Rect
 * \param      x        abscisse
 * \param      y        ordonnée
 */
void animation_avant_deplacement_unite(Terrain_combat * un_terrain_combat,Jeu * jeu, SDL_Surface * ecran,SDL_Surface * ecran2,SDL_Rect pos,int x, int y)
{
	Animation * deplacement = creer_animation(5, 100, 100,100, "../data/graphiques/images/effet_teleportation.png");
	lancer_animation_bloquante_combat(jeu, un_terrain_combat, deplacement, ecran2, x, y);
    free(deplacement);
}

/**
 * \brief      animation d'une explosion en (x,y)
 * \details    
 * \param      un_terrain_combat        Pointeur sur Terrain_combat 
 * \param      jeu        Pointeur sur Jeu  
 * \param      ecran        Pointeur sur SDL_Surface  
 * \param      x        abscisse
 * \param      y        ordonnée
 */
void animation_explosion(Terrain_combat * un_terrain_combat,Jeu * jeu, SDL_Surface * ecran,int x, int y)
{
	Animation * explosion;
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos = coordonnee_case_du_clic(pos);
	pos.x = pos.x *100 + X_CARTE;
	pos.y = pos.y * 100 +Y_CARTE;
	explosion = creer_animation(48, 100, 100,20, "../data/graphiques/images/explosion.png");
	lancer_animation_bloquante_combat(jeu, un_terrain_combat, explosion, ecran, pos.x, pos.y);
    free(explosion);
}

/**
 * \brief      animation de l'attaque
 * \details    
 * \param      un_terrain_combat        Pointeur sur Terrain_combat 
 * \param      jeu        Pointeur sur Jeu  
 * \param      ecran        Pointeur sur SDL_Surface  
 * \param      une_case        Pointeur sur Case_terrain_combat 
 * \param      pos_arrivee        SDL_Rect
 */
void animation_attaque(Terrain_combat * un_terrain_combat,Jeu * jeu, SDL_Surface * ecran,Case_terrain_combat *une_case,SDL_Rect pos_arrivee)
{/*animation de l'attaque*/
	SDL_Rect pos_laser,pos;
	SDL_Surface * laser =NULL;
	SDL_Surface * copie =NULL;
	int x_arrivee, y_arrivee,x_depart, y_depart;
	pos=coordonnee_case_du_clic(pos_arrivee);
	x_arrivee = pos.x *100 +X_CARTE;
	y_arrivee = pos.y *100 + Y_CARTE;
	x_depart = get_x_combat(une_case) *100 + X_CARTE;
	y_depart = get_y_combat(une_case) *100 + Y_CARTE;
	laser = IMG_Load("../data/graphiques/images/Laser.png");
	copie = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_ECRAN_COMBAT_X , TAILLE_ECRAN_COMBAT_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	initialise_sdl_rect(&pos_laser,0,0,TAILLE_ECRAN_COMBAT_X,TAILLE_ECRAN_COMBAT_Y);
	SDL_BlitSurface(ecran, &pos_laser,  copie,NULL);

	if((x_depart < x_arrivee)&&(y_depart == y_arrivee))
	{
		while(x_depart < x_arrivee)
		{
			initialise_sdl_rect(&pos_laser,x_depart,y_depart,0,0);
			SDL_BlitSurface(laser, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
			SDL_Delay(50);
			x_depart = x_depart +10;
			initialise_sdl_rect(&pos_laser,0,0,0,0);
			SDL_BlitSurface(copie, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
		}
	}
	else if((x_depart > x_arrivee)&&(y_depart == y_arrivee))
	{
		while(x_depart > x_arrivee){
			initialise_sdl_rect(&pos_laser,x_depart,y_depart,0,0);
			SDL_BlitSurface(laser, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
			SDL_Delay(50);
			x_depart = x_depart -10;
			initialise_sdl_rect(&pos_laser,0,0,0,0);
			SDL_BlitSurface(copie, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
		}
	}
	else if((x_depart == x_arrivee)&&(y_depart < y_arrivee))
	{
		while(y_depart < y_arrivee){
			initialise_sdl_rect(&pos_laser,x_depart,y_depart,0,0);
			SDL_BlitSurface(laser, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
			SDL_Delay(50);
			y_depart = y_depart +10;
			initialise_sdl_rect(&pos_laser,0,0,0,0);
			SDL_BlitSurface(copie, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
		}
	}
	else if((x_depart == x_arrivee)&&(y_depart > y_arrivee))
	{
		while(y_depart > y_arrivee){
			initialise_sdl_rect(&pos_laser,x_depart,y_depart,0,0);
			SDL_BlitSurface(laser, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
			SDL_Delay(50);
			y_depart = y_depart -10;
			initialise_sdl_rect(&pos_laser,0,0,0,0);
			SDL_BlitSurface(copie, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
		}
	}
	else if((x_depart < x_arrivee)&&(y_depart < y_arrivee))
	{
		while(x_depart < x_arrivee){
			initialise_sdl_rect(&pos_laser,x_depart,y_depart,0,0);
			SDL_BlitSurface(laser, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
			SDL_Delay(50);
			x_depart = x_depart +10;
			y_depart = y_depart +10;
			initialise_sdl_rect(&pos_laser,0,0,0,0);
			SDL_BlitSurface(copie, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
		}
	}
	else if((x_depart < x_arrivee)&&(y_depart > y_arrivee))
	{
		while(x_depart < x_arrivee){
			initialise_sdl_rect(&pos_laser,x_depart,y_depart,0,0);
			SDL_BlitSurface(laser, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
			SDL_Delay(50);
			x_depart = x_depart +10;
			y_depart = y_depart -10;
			initialise_sdl_rect(&pos_laser,0,0,0,0);
			SDL_BlitSurface(copie, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
		}
	}
	else if((x_depart > x_arrivee)&&(y_depart < y_arrivee))
	{
		while(x_depart > x_arrivee){
			initialise_sdl_rect(&pos_laser,x_depart,y_depart,0,0);
			SDL_BlitSurface(laser, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
			SDL_Delay(50);
			x_depart = x_depart -10;
			y_depart = y_depart +10;
			initialise_sdl_rect(&pos_laser,0,0,0,0);
			SDL_BlitSurface(copie, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
		}
	}
	else if((x_depart > x_arrivee)&&(y_depart > y_arrivee))
	{
		while(x_depart > x_arrivee){
			initialise_sdl_rect(&pos_laser,x_depart,y_depart,0,0);
			SDL_BlitSurface(laser, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
			SDL_Delay(50);
			x_depart = x_depart -10;
			y_depart = y_depart -10;
			initialise_sdl_rect(&pos_laser,0,0,0,0);
			SDL_BlitSurface(copie, NULL,  ecran,&pos_laser);SDL_Flip(ecran);
		}
	}
	SDL_Delay(100);
	SDL_FreeSurface(laser);
	SDL_FreeSurface(copie);
}

/**
 * \brief      vérifie si le combat est terminé
 * \details    
 * \param      un_terrain_combat        Pointeur sur Terrain_combat 
 * \param      jeu        Pointeur sur Jeu  
 * \param      flotte1        Pointeur sur Flotte  
 * \param      flotte2        Pointeur sur Flotte  
 * \param      infos2        Pointeur sur char  
 */
bool verifie_etat_combat(Jeu *jeu,Terrain_combat *un_terrain_combat,Flotte *flotte1,Flotte *flotte2,char * infos2,int* gagnant){
/*vérifie si le combat est fini et quel joueur l'a remporté*/
	int taille_flotte1,taille_flotte2,i;
	Joueur * joueur;
	taille_flotte1 = get_taille_flotte(flotte1);
	taille_flotte2 = get_taille_flotte(flotte2);
	if(taille_flotte1 == 0)
	{
		i= get_indice_joueur_flotte(flotte2);
		joueur = get_ieme_joueur_jeu(jeu,i);
		sprintf(infos2,"Gagné %s!",joueur->nom_joueur);
		
		*gagnant = 2;
		return 0;
	}
	else if(taille_flotte2 == 0)
	{
		i= get_indice_joueur_flotte(flotte1);
		joueur = get_ieme_joueur_jeu(jeu,i);
		sprintf(infos2,"Gagné %s !",joueur->nom_joueur);
		
		*gagnant = 1;
		return 0;
	}
	return 1;
}

/**
 * \brief      affichage du combat
 * \details    
 * \param      un_terrain_combat        Pointeur sur Terrain_combat 
 * \param      jeu        Pointeur sur Jeu  
 * \param      flotte1        Pointeur sur Flotte  
 * \param      flotte2        Pointeur sur Flotte 
 */
int affichage_ecran_combat(Jeu* jeu, Terrain_combat *un_terrain_combat, Flotte* flotte1,Flotte* flotte2,SDL_Surface* ecran, FMOD_SYSTEM* system, FMOD_SOUND* musique)
{
	SDL_Rect pos_clic,pos_bordure,pos_texte,pos_texte2,pos_texte3,pos_interface,pos_interface_haut, position_affichage_carte,position_passer,pos_attaquer,pos_interface_carte;
	SDL_Surface *interface = NULL;
	SDL_Surface *interface_haut = NULL;
	SDL_Surface *bordure = NULL;
	SDL_Surface *carte = NULL;
	SDL_Surface* passer, *attaquer =NULL;
	SDL_Surface* texte, *texte2,*texte3 ;

	TTF_Font *police = NULL;
	SDL_Color couleur_police = {255,255,255};
	char infos[255] = "",infos2[255]="",infos3[255]="OK";

	int gagnant = 0;
	bool continuer,attend_attaque,attaque_reussi;
	SDL_Event evenement;

	Uint32 couleur;

	/*variables pour le son*/
	FMOD_SOUND *son_saut_debut = NULL;
	FMOD_SOUND *son_saut_fin = NULL;
	FMOD_SOUND *tir_laser = NULL;
	FMOD_SOUND *explosion = NULL;
	FMOD_SOUND *son_selection = NULL;
	char **tab_chanson = NULL;

	/************************************************************************/
	/* Début de la fonction, initialisation des différentes valeurs         */
	/************************************************************************/

	/*on initialise le tableau de chansons puis on utilise la fonction qui va mettre les noms dedans (pour plus de clarté dans le code)*/
	tab_chanson = (char **)malloc(sizeof(char *) * 6);
	initialiser_tableau_chanson_combat(tab_chanson);

	/*on lance les musiques du jeu et on initialise les sons*/

	FMOD_System_CreateSound(system, "../data/audio/son/FTL_Saut.mp3", FMOD_CREATESAMPLE, 0, &son_saut_debut);
	FMOD_System_CreateSound(system, "../data/audio/son/FTL_Exit.mp3", FMOD_CREATESAMPLE, 0, &son_saut_fin);
	FMOD_System_CreateSound(system, "../data/audio/son/laser.mp3", FMOD_CREATESAMPLE, 0, &tir_laser);
	FMOD_System_CreateSound(system, "../data/audio/son/Explosion.mp3", FMOD_CREATESAMPLE, 0, &explosion);
	
	lire_musique(system, musique, tab_chanson);

	texte=NULL;
	texte2=NULL;
	texte3=NULL;

	continuer=1;attend_attaque=1;attaque_reussi=0;
	initialise_sdl_rect(&pos_texte3,10,5,0,0);
	initialise_sdl_rect(&pos_interface_haut,0,0,TAILLE_FENETRE_X,400);
	initialise_sdl_rect(&pos_bordure,X_CARTE,Y_CARTE,TAILLE_FENETRE_X,400);
	initialise_sdl_rect(&pos_interface_carte,X_CARTE,Y_CARTE,TAILLE_FENETRE_X,400);
	initialise_sdl_rect(&pos_interface,X_INTERFACE,Y_INTERFACE,0,0);
	initialise_sdl_rect(&position_affichage_carte,X_CARTE,Y_CARTE,0,0);
	initialise_sdl_rect(&pos_attaquer,X_BOUTON_ATTAQUER,Y_BOUTON_ATTAQUER,TAILLE_X_BOUTON_ATTAQUER,TAILLE_Y_BOUTON_ATTAQUER);
	initialise_sdl_rect(&position_passer,X_BOUTON_PASSER,Y_BOUTON_PASSER,TAILLE_X_BOUTON_ATTAQUER,TAILLE_Y_BOUTON_ATTAQUER);

	couleur = SDL_MapRGB(ecran->format,0,0,0);
	SDL_FillRect(ecran, NULL, couleur);
	SDL_Flip(ecran);

	couleur = NOIR;

	interface = IMG_Load("../data/graphiques/images/interface_combat_bas.png");
	interface_haut=	IMG_Load("../data/graphiques/images/interface_combat_haut.png");
    if (get_joueur_en_cours_combat(jeu) == 0)
    {
        bordure = IMG_Load("../data/graphiques/images/bordure_bleue.png");
    }
    else
    {
        bordure = IMG_Load("../data/graphiques/images/bordure_rouge.png");
    }
	attaquer= IMG_Load("../data/graphiques/images/Attaquer.png");
	passer= IMG_Load("../data/graphiques/images/Passer.png");

	carte =affiche_ecran_terrain_combat(un_terrain_combat);

	SDL_BlitSurface(carte, NULL, ecran, &position_affichage_carte);
	SDL_BlitSurface(bordure, NULL, ecran, &pos_bordure);
	SDL_BlitSurface(interface, NULL, ecran, &pos_interface);
	SDL_BlitSurface(interface_haut, NULL, ecran, &pos_interface_haut);
    SDL_BlitSurface(attaquer, NULL, interface, &pos_attaquer);
	SDL_BlitSurface(passer, NULL, interface, &position_passer);
	SDL_Flip(ecran);

	position_passer.y =Y_BOUTON_PASSER+Y_INTERFACE;
	pos_attaquer.y =Y_BOUTON_ATTAQUER+Y_INTERFACE;/*Position des boutons sur l'écran (et non pas leur position sur l'interface)*/

	police = TTF_OpenFont("../data/graphiques/fonts/charcoalcy.ttf",16);

	pos_texte.x=X_TEXTE;pos_texte.y=Y_TEXTE;
	pos_texte2.x=X_TEXTE;pos_texte2.y=Y_TEXTE - 20;

	SDL_EnableKeyRepeat(100, 5);/*autorise la répétition de l'appui sur une touche du clavier*/

	pos_interface_carte.w=carte->w;pos_interface_carte.h=carte->h;
	texte = TTF_RenderUTF8_Blended(police,infos,couleur_police);
	texte2 = TTF_RenderUTF8_Blended(police,infos2,couleur_police);
	sprintf(infos3," %s !",get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu))->nom_joueur);
	texte3 = TTF_RenderUTF8_Blended(police,infos3,couleur_police);
	SDL_BlitSurface(texte3, NULL, ecran, &pos_texte3);
    SDL_FreeSurface(texte3);
	SDL_Flip(ecran);


	/************************************************************************/
	/* Boucle principale                                                    */
	/************************************************************************/

	while(continuer)
	{
		SDL_PollEvent(&evenement);
		continuer = verifie_etat_combat(jeu,un_terrain_combat,flotte1,flotte2,infos2, &gagnant); /*on vérifie si le combat est fini*/
		switch(evenement.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEMOTION: /*mouvement de la souris*/
				pos_clic.x=evenement.motion.x - position_affichage_carte.x; /*la position de la souris sur la carte*/
				pos_clic.y=evenement.motion.y - position_affichage_carte.y;

				if((pos_clic.x+X_CARTE<=get_taille_combat_x(un_terrain_combat)*100)&&(pos_clic.x+X_CARTE>=0)&&(pos_clic.y+Y_CARTE>=0)
&&(pos_clic.y+Y_CARTE <= get_taille_combat_y(un_terrain_combat)*100)) 
				/*si la souris est à l'intérieur de la partie ou s'affiche la carte*/
				{
					sprintf(infos," ");
					if(get_presence_unite(get_case_terrain_combat(un_terrain_combat , coordonnee_case_du_clic(pos_clic).x,coordonnee_case_du_clic(pos_clic).y)))
					{
						affiche_info_unite(jeu,un_terrain_combat,infos,pos_clic);
					} /*on affiche les infos de l'unité */
					SDL_FreeSurface(texte);
					texte = TTF_RenderUTF8_Blended(police,infos,couleur_police);
					SDL_FreeSurface(texte2);
					texte2 = TTF_RenderUTF8_Blended(police,infos2,couleur_police);
				}
				break;
			case SDL_MOUSEBUTTONUP: /* Clic de la souris */
				if(test_souris_rectangle(position_passer,evenement.motion.x,evenement.motion.y)) /*clic sur le bouton "passer"*/
				{
					passer_tour_combat(jeu,un_terrain_combat);
					sprintf(infos2,"Passe le tour !");
					SDL_FreeSurface(texte2);
					texte2 = TTF_RenderUTF8_Blended(police,infos2,couleur_police);
                    SDL_FreeSurface(bordure);
                    if (get_joueur_en_cours_combat(jeu) == 0)
                    {
                        bordure = IMG_Load("../data/graphiques/images/bordure_bleue.png");
                    }
                    else
                    {
                        bordure = IMG_Load("../data/graphiques/images/bordure_rouge.png");
                    }
                    SDL_BlitSurface(bordure, NULL, ecran, &position_affichage_carte);
				}
				else if(test_souris_rectangle(pos_attaquer,evenement.motion.x,evenement.motion.y))/*clic sur le bouton "attaquer"*/
				{
					if(get_une_case_selectionnee(un_terrain_combat))/*si une unité est sélectionnée*/
					{
						sprintf(infos2,"Préparation de l'attaque");
						SDL_FreeSurface(texte2);
						texte2 = TTF_RenderUTF8_Blended(police,infos2,couleur_police);
						SDL_BlitSurface(texte2, NULL, ecran, &pos_texte2);SDL_Flip(ecran);
						SDL_FreeSurface(carte);
						carte = affiche_ecran_terrain_combat(un_terrain_combat);

						while(attend_attaque)
						{
							SDL_WaitEvent(&evenement); /*attente d'un évênement*/
							switch (evenement.type)
							{	
								case SDL_QUIT:
									continuer =0;
									attend_attaque=0;
									break;
								case SDL_MOUSEMOTION:
									pos_clic.x=evenement.motion.x;
									pos_clic.y=evenement.motion.y;
									if((pos_clic.x+X_CARTE<=get_taille_combat_x(un_terrain_combat)*100)&&(pos_clic.x+X_CARTE>=0)&&(pos_clic.y+Y_CARTE>=0)&&(pos_clic.y+Y_CARTE <= get_taille_combat_y(un_terrain_combat)*100))
									{
										sprintf(infos2," ");
										if(get_presence_unite(get_case_terrain_combat(un_terrain_combat, coordonnee_case_du_clic(pos_clic).x, coordonnee_case_du_clic(pos_clic).y)))
										{
											affiche_info_unite(jeu,un_terrain_combat,infos,pos_clic);
										}
										SDL_FreeSurface(texte);
										texte = TTF_RenderUTF8_Blended(police,infos,couleur_police);
										SDL_BlitSurface(texte, NULL, ecran, &pos_texte);
										SDL_Flip(ecran);
									}
									break;
								case SDL_MOUSEBUTTONUP: /* Clic de la souris */
									pos_clic.x=evenement.button.x - position_affichage_carte.x;
									pos_clic.y=evenement.button.y - position_affichage_carte.y;

									attaque_reussi=attaque_ecran(jeu,un_terrain_combat,pos_clic,flotte1, flotte2); /*tentative d'attaque*/
									if(attaque_reussi)/*si on réussit l'attaque on lance l'animation et on retire un point d'action au joueur*/
									{
										sprintf(infos2,"Attaquons !");
										SDL_FreeSurface(texte2);
										texte2 = TTF_RenderUTF8_Blended(police,infos2,couleur_police);
										SDL_BlitSurface(interface, NULL, ecran, &pos_interface);
										SDL_BlitSurface(texte2, NULL, ecran, &pos_texte2);
										SDL_Flip(ecran);
										lire_son(system, tir_laser);
										animation_attaque(un_terrain_combat,jeu, ecran,get_selection(un_terrain_combat),pos_clic);
										lire_son(system, explosion);
										animation_explosion(un_terrain_combat,jeu, ecran,pos_clic.x,pos_clic.y);
										enlever_pt_action_joueur(get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu)), 1);
									}
									else
									{
										sprintf(infos2,"Imposible d'attaquer !");
										SDL_FreeSurface(texte2);
										texte2 = TTF_RenderUTF8_Blended(police,infos2,couleur_police);
									}
									attend_attaque=0;
									if(get_pt_action_joueur(get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu)))<=0) 
									/*si le joueur n'as plus de points d'action on passe le tour*/
									{
										passer_tour_combat(jeu,un_terrain_combat);
									}
									SDL_FreeSurface(carte);
									carte=affiche_ecran_terrain_combat(un_terrain_combat);/*on refais le terrain*/
									SDL_BlitSurface(carte, NULL,  ecran,&position_affichage_carte);
									SDL_BlitSurface(bordure, NULL, ecran, &pos_bordure);
									SDL_BlitSurface(interface_haut, NULL, ecran, &pos_interface_haut);
									SDL_Flip(ecran);
									break;
							}
							SDL_BlitSurface(interface, NULL, ecran, &pos_interface);
							SDL_BlitSurface(texte, NULL, ecran, &pos_texte);
							SDL_BlitSurface(texte2, NULL, ecran, &pos_texte2);
							SDL_Flip(ecran);
						}
						attend_attaque=1;
					}
					SDL_BlitSurface(carte,NULL,  ecran, &position_affichage_carte);
					SDL_BlitSurface(bordure, NULL, ecran, &pos_bordure);
					SDL_BlitSurface(interface_haut, NULL, ecran, &pos_interface_haut);SDL_Flip(ecran);
				}
				else if(test_souris_rectangle(pos_interface_carte,pos_clic.x - position_affichage_carte.x,pos_clic.y - position_affichage_carte.y))
				{ /*si on clique à l'intérieur de l'endroit ou est la carte*/
					sprintf(infos2," ");
					SDL_FreeSurface(texte2);
					texte2 = TTF_RenderUTF8_Blended(police,infos2,couleur_police);
					selection(jeu,un_terrain_combat,pos_clic);/*on sélectionne ou désélectionne */
                    if(evenement.button.button == SDL_BUTTON_RIGHT)
                    {
                        affiche_deplacement_unite(jeu,un_terrain_combat, pos_clic,carte,bordure,ecran,position_affichage_carte,pos_bordure,infos2,system,son_saut_debut,son_saut_fin);/*on essaie de déplacer*/
                    }
					SDL_FreeSurface(texte2);
					texte2 = TTF_RenderUTF8_Blended(police,infos2,couleur_police);
					SDL_FreeSurface(carte);
					carte=affiche_ecran_terrain_combat(un_terrain_combat);/*on refait le terrain*/
					if(get_pt_action_joueur(get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu)))<=0)
					{
						passer_tour_combat(jeu,un_terrain_combat);
						SDL_FreeSurface(carte);
						carte=affiche_ecran_terrain_combat(un_terrain_combat);
					}
				}
				else
				{/*si on clique ailleurs*/
					sprintf(infos2," ");/*on vérifie si le combat est fini*/
					SDL_FreeSurface(texte2);
					texte2 = TTF_RenderUTF8_Blended(police,infos2,couleur_police);
					if(get_pt_action_joueur(get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu)))<=0)
					{/*si le joueur n'as plus de point d'action*/
						passer_tour_combat(jeu,un_terrain_combat);
						SDL_FreeSurface(carte);
						carte=affiche_ecran_terrain_combat(un_terrain_combat);
					}
				}
				break;
			case SDL_KEYUP:
				break;
			case SDL_KEYDOWN: /* Si appui sur une touche */
            	switch (evenement.key.keysym.sym)
            	{
            	case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
              	    continuer = 0;
					break;
				default:
                    break;
            	}
            break;
		}
		
		evenement.type=0;
		
		sprintf(infos3," %s  points d'action restant : %d",get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu))->nom_joueur,get_pt_action_joueur(get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu))));
		texte3 = TTF_RenderUTF8_Blended(police,infos3,couleur_police);
		SDL_FillRect(ecran, NULL, couleur);
		SDL_BlitSurface(carte, NULL,  ecran,&position_affichage_carte);
		SDL_BlitSurface(bordure, NULL, ecran, &pos_bordure);
		SDL_BlitSurface(interface_haut, NULL, ecran, &pos_interface_haut);
		SDL_BlitSurface(interface, NULL, ecran, &pos_interface);
		SDL_BlitSurface(texte, NULL, ecran, &pos_texte);
		SDL_BlitSurface(texte2, NULL, ecran, &pos_texte2);
		SDL_BlitSurface(texte3, NULL, ecran, &pos_texte3);
        SDL_FreeSurface(texte3);
		SDL_Flip(ecran);	
	}
	
	SDL_FillRect(ecran, NULL, couleur);
	SDL_Flip(ecran);

	TTF_CloseFont(police);
	SDL_FreeSurface(interface);
	SDL_FreeSurface(interface_haut);

	SDL_FreeSurface(texte);
    SDL_FreeSurface(texte2);
	SDL_FreeSurface(carte);
	SDL_FreeSurface(passer);
	SDL_FreeSurface(attaquer);
	SDL_FreeSurface(bordure);

	FMOD_Sound_Release(son_saut_debut);
	FMOD_Sound_Release(son_saut_fin);
	FMOD_Sound_Release(tir_laser);
	FMOD_Sound_Release(son_selection);
	FMOD_Sound_Release(explosion);
    free(tab_chanson);
	return gagnant;
}

/**
 * \brief      lancement du combat à partir de deux flottes
 * \details    
 * \param      un_terrain_combat        Pointeur sur Terrain_combat 
 * \param      jeu        Pointeur sur Jeu  
 * \param      flotte1        Pointeur sur Flotte  
 * \param      flotte2        Pointeur sur Flotte 
 */
int lancer_combat_ecran(Jeu *jeu, Terrain_espace* un_terrain_espace, Flotte* flotte1,  Flotte * flotte2, SDL_Surface * ecran, FMOD_SYSTEM* system, FMOD_SOUND* musique)/*lance un combat à partir de deux flottes*/
{
	int gagnant;
	Terrain_combat * un_combat; 
	un_combat=creer_terrain_combat(X_CASE_COMBAT, Y_CASE_COMBAT);
	modification_terrain_combat(un_combat, 'E');
	if(get_indice_joueur_flotte(flotte1) == 0)
	{
		placer_unite_flotte_en_haut(un_combat, flotte1);
		placer_unite_flotte_en_bas(un_combat, flotte2);
		gagnant = affichage_ecran_combat(jeu, un_combat, flotte1, flotte2, ecran, system, musique);
	}
	else
	{
		placer_unite_flotte_en_haut(un_combat, flotte2);
		placer_unite_flotte_en_bas(un_combat, flotte1);
		gagnant = affichage_ecran_combat(jeu, un_combat, flotte2, flotte1, ecran, system, musique);
	}
	
	detruit_terrain_combat(&un_combat);

	if(gagnant == 1)
	{
		retirer_flotte(get_case_terrain_espace(un_terrain_espace, get_x_flotte(flotte2), get_y_flotte(flotte2)));
		retirer_flotte_joueur(get_ieme_joueur_jeu(jeu, get_indice_joueur_flotte(flotte2)), get_indice_tableau_joueur(flotte2));
		return 1;
	}
	if(gagnant == 2)
	{
		retirer_flotte(get_case_terrain_espace(un_terrain_espace, get_x_flotte(flotte1), get_y_flotte(flotte1)));
		retirer_flotte_joueur(get_ieme_joueur_jeu(jeu, get_indice_joueur_flotte(flotte1)), get_indice_tableau_joueur(flotte1));
		return 2;
	}
	return 0;
}
