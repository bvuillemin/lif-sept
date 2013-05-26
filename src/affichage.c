#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#ifdef __APPLE__
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"
#include "SDL_framerate.h"
#include "fmod.h"
#else
/*#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_framerate.h>*/
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <FMOD/fmod.h>
#endif

#include "affichage.h"
#include "jeu.h"
#include "constante.h"
#include "terrain_espace.h"
#include "terrain_combat.h"
#include "son.h"
#include "animation.h"
#include "batiment.h"
#include "sauvegarde.h"

/************************************************************************/
/* Fonctions diverses                                                   */
/************************************************************************/

bool test_souris_rectangle (SDL_Rect taille_surface, int x, int y) /*Va tester si x et y sont dans le rectangle, utile pour les menus*/
{
	if((x >= taille_surface.x) && (x<= taille_surface.x + taille_surface.w) && (y >= taille_surface.y) && (y<= taille_surface.y + taille_surface.h))
	{
		return true;
	}
	else return false;
}

void initialise_sdl_rect(SDL_Rect *un_rectangle, int x, int y, int w, int h) /*Va modifier les atrributs d'un SDL_rect*/
{
	un_rectangle->x = x;
	un_rectangle->y = y;
	un_rectangle->w = w;
	un_rectangle->h = h;
}

bool booleen_case_pointeur_souris(Terrain_espace *un_terrain_espace, int x, int y) /*Fonction qui va tester la case pointée par la souris, les coordonnées x et y sont en pixels*/
{
	x = (un_terrain_espace->affichage_x + x) / 100;
	y = (un_terrain_espace->affichage_y + y - 20) / 100;
	if ((x >= 0) && (x < un_terrain_espace->taille_espace_x) && (y >= 0) && (y < un_terrain_espace->taille_espace_y))
	{
		return true;
	}
	else return false;
}

bool booleen_coordonnees_case(Terrain_espace *un_terrain_espace, int x_case, int y_case, int *x, int *y)/*fonction qui va récuperer les coordonnées sur l'écran d'une case et les mettre dans x et y, ou renvoyer false si elle n'est pas affichee*/
{
	SDL_Rect affichage_map = {un_terrain_espace->affichage_x - 1, un_terrain_espace->affichage_y - 1, un_terrain_espace->affichage_x + TAILLE_TERRAIN_ESPACE_X, un_terrain_espace->affichage_y + TAILLE_TERRAIN_ESPACE_Y};
	if(test_souris_rectangle(affichage_map, x_case * 100, y_case *100))
	{
		*x = (x_case * 100) - affichage_map.x;
		*y = (y_case * 100) + TAILLE_BARRE_RESSOURCE - affichage_map.y;
		return true;
	}
	else return false;
}

bool booleen_minimap_pointeur_souris(int x, int y)
{
	SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, TAILLE_MINIMAP_X, TAILLE_MINIMAP_Y};
	return test_souris_rectangle (position_minimap, x, y);
}

void test_minimap_souris(Terrain_espace *un_terrain_espace, int x, int y)
{
    SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};
    int x_calcule, y_calcule;

    x = x - position_minimap.x;
    y = y - position_minimap.y;

    x_calcule = x * ((float)TAILLE_FENETRE_X/TAILLE_MINIMAP_X);
    y_calcule = y * ((float)TAILLE_FENETRE_Y/TAILLE_MINIMAP_Y);

    if((x_calcule > 0) && (x_calcule <= (un_terrain_espace->taille_espace_x *100) - TAILLE_TERRAIN_ESPACE_X) && (y_calcule > 0) && (y_calcule < (un_terrain_espace->taille_espace_y * 100)- TAILLE_TERRAIN_ESPACE_Y))
    {
        un_terrain_espace->affichage_x = x_calcule;
        un_terrain_espace->affichage_y = y_calcule;
    }
}

Case_terrain_espace* case_pointeur_souris(Terrain_espace *un_terrain_espace, int x, int y) /*Fonction qui va renvoyer la case pointée par la souris, les coordonnées x et y sont en pixels*/
{
	x = (un_terrain_espace->affichage_x + x) / 100;
	y = (un_terrain_espace->affichage_y + y - 33) / 100;
	if ((x >= 0) && (x < un_terrain_espace->taille_espace_x) && (y >= 0) && (y < un_terrain_espace->taille_espace_y))
	{
		return &(un_terrain_espace->tab_terrain_espace[y*(un_terrain_espace->taille_espace_x)+x]);
	}
	else return NULL;
}

void reinitialiser_tableau_selection_unite(Jeu *un_jeu)
{
    int i;
    for(i=0;i<10;i++)
    {
        un_jeu->tab_unite_selectionnee[i] = false;
    }
}


/************************************************************************/
/* Fonctions d'affichage des infobulles                                 */
/************************************************************************/

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
		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Quartier general");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Indispensable a la mise en place");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "d'installations sur la planete, ce");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "batiment  est  a  construire  en");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "priorite");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 16;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_QUARTIER_GENERAL);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
	}
	if(i == 1)
	{
		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Mine de metal");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Le  metal  est  devenu,  avec ");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "l'apparrition   des   vaisseaux");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "spatiaux, un bien indispensable");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 16;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Metal: +100");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_METAL);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
	}
	if(i == 2)
	{
		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Mine d'or");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "L'or   est   la   ressource  la  plus ");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "precieuse, converti en monnaie");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "il   nous   fournira   les   fonds");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "necessaires  a  la  guerre");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 15;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Argent: +100");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_METAL);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
	}
	if(i == 3)
	{
		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Raffinerie");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Le carburant est extrait du sous");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "sol et nous permet  d'emmener");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "nos vaisseaux jusqu'au fin fond");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "de la galaxie");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 15;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Carburant: +100");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_CARBURANT);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
	}
	if(i == 4)
	{
		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Habitations");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "La construction sur nos colonies");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "d'habitations   nous   fournira");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "la  main  d'oeuvre,  vitale  a");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "l'effort   de   guerre");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 15;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Population: +100");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_POPULATION);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
	}
	if(i == 5)
	{
		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Spatioport");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Le  spatioport  nous  autorisera");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "a  un  developpement  toujours");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "plus  grand,  pour  partir  a  la ");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "conquete de l'espace");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 15;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Active construction des unites");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 12;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		sprintf(ligne, "Temps de construction: %d", NB_TOUR_BATIMENT_SPATIOPORT);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
	}
}

void afficher_infobulle_unite(Jeu* un_jeu, SDL_Surface* fond,int i)
{
	SDL_Surface* une_ligne;
	Unite *une_unite;
	SDL_Rect position;
	TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
	char ligne[200] = "";
	int j = 3;

	une_unite = get_unite_i_flotte(get_flotte_en_cours(un_jeu), i);

	police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 15);
	sprintf(ligne, "Type unite");
	une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
	initialise_sdl_rect(&position, 4, j, 0, 0);
	SDL_BlitSurface(une_ligne, NULL, fond, &position);
	j += 18;
	TTF_CloseFont(police);

	police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
	sprintf(ligne, "Point de vie: %d", get_pt_vie(une_unite));
	une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
	initialise_sdl_rect(&position, 4, j, 0, 0);
	j += 13;
	SDL_BlitSurface(une_ligne, NULL, fond, &position);

	police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
	sprintf(ligne, "Attaque: %d", get_pt_attaque(une_unite));
	une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
	initialise_sdl_rect(&position, 4, j, 0, 0);
	j += 13;
	SDL_BlitSurface(une_ligne, NULL, fond, &position);

	police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
	sprintf(ligne, "Action: %d", get_pt_action(une_unite));
	une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
	initialise_sdl_rect(&position, 4, j, 0, 0);
	j += 13;
	SDL_BlitSurface(une_ligne, NULL, fond, &position);

	police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
	sprintf(ligne, "Point de mouvement: %d", get_pt_mouvement_unite(une_unite));
	une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
	initialise_sdl_rect(&position, 4, j, 0, 0);
	j += 13;
	SDL_BlitSurface(une_ligne, NULL, fond, &position);

}

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
		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Type unite");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de vie: %d", PT_VIE_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Attaque: %d", PT_ATTAQUE_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Action: %d", PT_ACTION_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de mouvement: %d", PT_MOUVEMENT_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de mouvement-combat: %d", PT_DEPLACEMENT_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "-----------");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Metal: %d", NB_METAL_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Argent: %d", NB_ARGENT_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Carburant: %d", NB_CARBURANT_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Population: %d", NB_POPULATION_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Temps de construction: %d", NB_TOUR_UNITE_1);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
	}
	if(i==1)
	{
		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Type unite");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de vie: %d", PT_VIE_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Attaque: %d", PT_ATTAQUE_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Action: %d", PT_ACTION_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de mouvement: %d", PT_MOUVEMENT_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de mouvement-combat: %d", PT_DEPLACEMENT_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "-----------");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Metal: %d", NB_METAL_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Argent: %d", NB_ARGENT_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Carburant: %d", NB_CARBURANT_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Population: %d", NB_POPULATION_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Temps de construction: %d", NB_TOUR_UNITE_2);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
	}
	if(i==2)
	{
		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 15);
		sprintf(ligne, "Type unite");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
		j += 18;
		TTF_CloseFont(police);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de vie: %d", PT_VIE_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Attaque: %d", PT_ATTAQUE_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Action: %d", PT_ACTION_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de mouvement: %d", PT_MOUVEMENT_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Point de mouvement-combat: %d", PT_DEPLACEMENT_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "-----------");
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Metal: %d", NB_METAL_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Argent: %d", NB_ARGENT_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Carburant: %d", NB_CARBURANT_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Population: %d", NB_POPULATION_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);

		police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 12);
		sprintf(ligne, "Temps de construction: %d", NB_TOUR_UNITE_3);
		une_ligne = TTF_RenderText_Blended(police, ligne, couleur_blanche);
		initialise_sdl_rect(&position, 4, j, 0, 0);
		j += 13;
		SDL_BlitSurface(une_ligne, NULL, fond, &position);
	}
}

void afficher_infobulle(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee, int x, int y)
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
	}
	SDL_FreeSurface(fond);
}


/************************************************************************/
/* Fonctions d'affichage des éléments de la carte                       */
/************************************************************************/

SDL_Surface* affichage_ressource(Jeu *un_jeu, SDL_Surface *surface_ressource)
{
    SDL_Surface *nom_ressource;
    SDL_Surface *nombre_tour;
    SDL_Rect position;
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    char ressource[200] = "";
    char tour[50] = "";

    police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 18);
    surface_ressource = IMG_Load("../graphiques/images/interface_ressource.png");

	/*affichage des ressources*/
    sprintf(ressource, "%d", get_metal_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]));
    nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
    initialise_sdl_rect(&position, 75, 4, 0, 0);
    SDL_BlitSurface(nom_ressource, NULL, surface_ressource, &position);

	sprintf(ressource, "%d", get_argent_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]));
	nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
	initialise_sdl_rect(&position, 75 + 150, 4, 0, 0);
	SDL_BlitSurface(nom_ressource, NULL, surface_ressource, &position);

	sprintf(ressource, "%d", get_carburant_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]));
	nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
	initialise_sdl_rect(&position, 75 + 300, 4, 0, 0);
	SDL_BlitSurface(nom_ressource, NULL, surface_ressource, &position);

	sprintf(ressource, "%d", get_population_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]));
	nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
	initialise_sdl_rect(&position, 75 + 450, 4, 0, 0);
	SDL_BlitSurface(nom_ressource, NULL, surface_ressource, &position);


    sprintf(tour, "Tour en cours: %d   Joueur en cours: %d", un_jeu->tour_en_cours, un_jeu->joueur_en_cours);
    nombre_tour = TTF_RenderText_Blended(police, tour, couleur_blanche);
    position.x = TAILLE_FENETRE_X - 400;
    SDL_BlitSurface(nombre_tour, NULL, surface_ressource, &position);

    SDL_FreeSurface(nom_ressource);
    SDL_FreeSurface(nombre_tour);
    TTF_CloseFont(police);

    return surface_ressource;
}

SDL_Surface* affichage_creation_unite(Planete* une_planete, SDL_Surface *panneau_unite)
{
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


	unite1 = IMG_Load("../graphiques/images/unite1.png");
	unite2 = IMG_Load("../graphiques/images/unite2.png");
	unite3 = IMG_Load("../graphiques/images/unite3.png");
    police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 14);

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
        if(une_planete->unite_nb_tour_restant > 0)
        {
            sprintf(texte_unite, "Tour %d", une_planete->unite_nb_tour_restant);
            surface_texte_unite = TTF_RenderText_Blended(police, texte_unite, couleur_blanche);
            initialise_sdl_rect(&position_texte_unite, 10, 40 + 120 *i, 0, 0);
            SDL_BlitSurface(surface_texte_unite, NULL, panneau_unite, &position_texte_unite);
        }

		/*if(((i + 1)== une_planete->unite_en_cours) && (une_planete->unite_nb_tour_restant != 0))
		{
			SDL_FillRect(unite, NULL, SDL_MapRGB(panneau_unite->format, 100, 0, 0));
		}*/
    }

    TTF_CloseFont(police);
    SDL_FreeSurface(unite1);
	SDL_FreeSurface(unite2);
	SDL_FreeSurface(unite3);
    SDL_FreeSurface(surface_texte_unite);

    return panneau_unite;
}

SDL_Surface* affichage_planete(Planete* une_planete, SDL_Surface *info_planete)
{
    SDL_Surface *planete = NULL;
    SDL_Surface *fond_planete = NULL;
    SDL_Surface *batiment = NULL;
	SDL_Surface *construction = NULL;
	SDL_Surface *interdiction = NULL;
    SDL_Surface *bouton_unite;
    SDL_Rect position_texte;
    SDL_Rect position_batiment;
    SDL_Rect position_bouton_unite;
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    char texte_planete[200] = "";
    char texte_batiment[100] = "";
    int i;

    police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 14);
    fond_planete = SDL_CreateRGBSurface(SDL_SRCALPHA, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    SDL_FillRect(fond_planete, NULL, SDL_MapRGB(info_planete->format, 60, 60, 60));
    SDL_SetColorKey(fond_planete, SDL_SRCCOLORKEY, SDL_MapRGB(fond_planete->format, 60, 60, 60));

    sprintf(texte_planete, "Nom de la planete: %s Occupation de la planete: %d/%d Production: Metal:%d Argent:%d Carburant:%d Population:%d",
get_nom_planete(une_planete), get_taille_utilisee(une_planete), get_taille_planete(une_planete),
get_metal(une_planete), get_argent(une_planete), get_carburant(une_planete), get_population(une_planete));
    planete = TTF_RenderText_Blended(police, texte_planete, couleur_blanche);
    initialise_sdl_rect(&position_texte, 10, 10, 0, 0);
    SDL_BlitSurface(planete, NULL, fond_planete, &position_texte);

    bouton_unite = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    initialise_sdl_rect(&position_bouton_unite, TAILLE_FENETRE_X -150, 35, 100, 100);
    SDL_FillRect(bouton_unite, NULL, SDL_MapRGB(info_planete->format, 0, 0, 100));
    SDL_BlitSurface(bouton_unite, NULL, fond_planete, &position_bouton_unite);

    batiment = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    for(i=0;i<6;i++)
    {
        switch(i)
		{
		case 0:
			batiment = IMG_Load("../graphiques/images/batiment_mairie.png");
			break;
		case 1:
			batiment = IMG_Load("../graphiques/images/batiment_mine.png");
			break;
		case 2:
			batiment = IMG_Load("../graphiques/images/batiment_mine_or.png");
			break;
		case 3:
			batiment = IMG_Load("../graphiques/images/batiment_raffinerie.png");
			break;
		case 4:
			batiment = IMG_Load("../graphiques/images/batiment_population.png");
			break;
		case 5:
			batiment = IMG_Load("../graphiques/images/batiment_port.png");
			break;
		default :
			break;
		}
		construction = IMG_Load("../graphiques/images/construction.png");
		interdiction = IMG_Load("../graphiques/images/interdit.png");
		
        sprintf(texte_batiment, "%d", une_planete->batiment[i]);
        planete = TTF_RenderText_Blended(police, texte_batiment, couleur_blanche);
        initialise_sdl_rect(&position_texte, 15 + 120 * i, 40, 0, 0);
        initialise_sdl_rect(&position_batiment, 10 + 120*i, 35, 0, 0);
        SDL_BlitSurface(batiment, NULL, fond_planete, &position_batiment);
		if((i == une_planete->batiment_en_cours) && (une_planete->batiment_nb_tour_restant != 0))
		{
			SDL_BlitSurface(construction, NULL, fond_planete, &position_batiment);
		}
		if((i != une_planete->batiment_en_cours) && (une_planete->batiment_nb_tour_restant > 0))
		{
			SDL_BlitSurface(interdiction, NULL, fond_planete, &position_batiment);
		}
        SDL_BlitSurface(planete, NULL, fond_planete, &position_texte);

        if((i == une_planete->batiment_en_cours) && (une_planete->batiment_nb_tour_restant != 0))
        {
            sprintf(texte_batiment, "Tours: %d", une_planete->batiment_nb_tour_restant);
            initialise_sdl_rect(&position_texte, 15 + 120 * i, 60, 0, 0);
            planete = TTF_RenderText_Blended(police, texte_batiment, couleur_blanche);
            SDL_BlitSurface(planete, NULL, fond_planete, &position_texte);
        }
    }

    TTF_CloseFont(police);
    SDL_FreeSurface(planete);
    SDL_FreeSurface(batiment);
	SDL_FreeSurface(construction);
	SDL_FreeSurface(interdiction);
    SDL_FreeSurface(bouton_unite);

    return fond_planete;
}

SDL_Surface* affichage_planete_ennemie(Case_terrain_espace *une_case_terrain_espace, SDL_Surface *info_planete)
{
	SDL_Surface *planete = NULL;
	SDL_Surface *fond_planete = NULL;
	SDL_Rect position_texte;
	/*SDL_Rect position_bouton_unite;*/
	TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
	char texte_planete[200] = "";
	Planete *une_planete = get_planete(une_case_terrain_espace);
	/*int i;*/

	police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 14);
	fond_planete = SDL_CreateRGBSurface(SDL_SRCALPHA, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(fond_planete, NULL, SDL_MapRGB(info_planete->format, 60, 60, 60));
	SDL_SetColorKey(fond_planete, SDL_SRCCOLORKEY, SDL_MapRGB(fond_planete->format, 60, 60, 60));

	sprintf(texte_planete, "Nom de la planete: %s", get_nom_planete(une_planete));
	planete = TTF_RenderText_Blended(police, texte_planete, couleur_blanche);
	initialise_sdl_rect(&position_texte, 10, 10, 0, 0);
	SDL_BlitSurface(planete, NULL, fond_planete, &position_texte);

	TTF_CloseFont(police);
	SDL_FreeSurface(planete);

	return fond_planete;
}

SDL_Surface* affichage_flotte(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *info_flotte)
{
    SDL_Surface *flotte = NULL;
	SDL_Surface *une_unite1 = NULL;
	SDL_Surface *une_unite2 = NULL;
	SDL_Surface *une_unite3 = NULL;
	SDL_Surface *selection = NULL;
	SDL_Surface *bouton_coloniser = NULL;
	SDL_Rect position_texte = {10, 10, 0, 0};
    SDL_Rect position_une_unite;
	SDL_Rect position_bouton_coloniser = {TAILLE_FENETRE_X - 150, 35, 0, 0};
    int i;
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    char texte_flotte[200] = "";
    Flotte *une_flotte = un_jeu->selection_flotte;
	TYPE_VAISSEAU type;

	/*affichage des informations d'une flotte*/
    police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 14);
    info_flotte = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    SDL_FillRect(info_flotte, NULL, SDL_MapRGB(info_flotte->format, 60, 60, 60));
    SDL_SetColorKey(info_flotte, SDL_SRCCOLORKEY, SDL_MapRGB(info_flotte->format, 60, 60, 60));

    sprintf(texte_flotte, "Coordonnes de la flotte: %d %d, pt mouvement %d, taille : %d", une_flotte->x_flotte, une_flotte->y_flotte, une_flotte->pt_mouvement_espace_flotte,une_flotte->taille_flotte);
    flotte = TTF_RenderText_Blended(police, texte_flotte, couleur_blanche);
    SDL_BlitSurface(flotte, NULL, info_flotte, &position_texte);

	/*affichage des unités*/
    une_unite1 = IMG_Load("../graphiques/images/unite1.png");
	une_unite2 = IMG_Load("../graphiques/images/unite2.png");
	une_unite3 = IMG_Load("../graphiques/images/unite3.png");
	selection = IMG_Load("../graphiques/images/selection.png");

    for(i=0; i<une_flotte->taille_flotte;i++)
    {
		initialise_sdl_rect(&position_une_unite, 10 + 120*i, 35, 0, 0);
		type = get_type_vaisseau(get_unite_i_flotte(une_flotte, i));
        if(un_jeu->tab_unite_selectionnee[i] == true)
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
      
        sprintf(texte_flotte, "%d/%d", une_flotte->tab_unite[i].pt_vie, une_flotte->tab_unite[i].pt_vie_total);
        flotte = TTF_RenderText_Blended(police, texte_flotte, couleur_blanche);
        initialise_sdl_rect(&position_texte, 15 + 120*i, 40, 0, 0);
        SDL_BlitSurface(flotte, NULL, info_flotte, &position_texte);
    }

	/*affichage du bouton pour coloniser une planète*/
	if((get_type_case_terrain_espace(get_case_terrain_espace(un_terrain_espace, une_flotte->x_flotte, une_flotte->y_flotte)) == 'P') && (!get_planete_colonisee(get_planete_terrain_espace(un_terrain_espace, une_flotte->x_flotte, une_flotte->y_flotte))))
	{
		bouton_coloniser = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
		SDL_FillRect(bouton_coloniser, NULL, SDL_MapRGB(info_flotte->format, 0, 0, 200));
		SDL_BlitSurface(bouton_coloniser, NULL, info_flotte, &position_bouton_coloniser);
	}

    TTF_CloseFont(police);
    SDL_FreeSurface(flotte);
    SDL_FreeSurface(une_unite1);
	SDL_FreeSurface(une_unite2);
	SDL_FreeSurface(une_unite3);
	SDL_FreeSurface(bouton_coloniser);

    return info_flotte;
}

SDL_Surface* affichage_flotte_ennemie(Jeu *un_jeu, SDL_Surface *info_flotte)
{
	SDL_Surface *flotte = NULL;
	SDL_Surface *fond_flotte = NULL;
	SDL_Surface *une_unite = NULL;
	SDL_Rect position;
	SDL_Rect position_une_unite;
	int i;
	TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
	char texte_flotte[200] = "";
	Flotte *une_flotte = un_jeu->selection_flotte;

	police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 14);
	fond_flotte = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(fond_flotte, NULL, SDL_MapRGB(fond_flotte->format, 60, 60, 60));
	SDL_SetColorKey(fond_flotte, SDL_SRCCOLORKEY, SDL_MapRGB(fond_flotte->format, 60, 60, 60));

	sprintf(texte_flotte, "Coordonnes de la flotte: %d %d, taille : %d", une_flotte->x_flotte, une_flotte->y_flotte, une_flotte->taille_flotte);
	flotte = TTF_RenderText_Blended(police, texte_flotte, couleur_blanche);
	initialise_sdl_rect(&position, 10, 10, 0, 0);
	SDL_BlitSurface(flotte, NULL, fond_flotte, &position);

	une_unite = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	for(i=0; i<une_flotte->taille_flotte;i++)
	{
		SDL_FillRect(une_unite, NULL, SDL_MapRGB(info_flotte->format, 0, 0, 100));
		initialise_sdl_rect(&position_une_unite, 10 + 120*i, 35, 0, 0);
		SDL_BlitSurface(une_unite, NULL, fond_flotte, &position_une_unite);
	}

	TTF_CloseFont(police);
	SDL_FreeSurface(flotte);
	SDL_FreeSurface(une_unite);

	return fond_flotte;
}

SDL_Surface* creer_affichage_terrain(Terrain_espace *un_terrain_espace)
{
	SDL_Surface *carte = NULL;
	SDL_Surface *planete1 = NULL;
	SDL_Surface *planete2 = NULL;
	SDL_Surface *planete3 = NULL;
	SDL_Rect position_planete;
	SDL_Rect position;
	SDL_Surface *image_une_case = NULL;
    SDL_Surface *fond = NULL;
	int i, j;
	Case_terrain_espace *une_case;

	position_planete.x = 0;
	position_planete.y = 0;
	position.x = 0;
	position.y = 0;

	carte = SDL_CreateRGBSurface(SDL_HWSURFACE, un_terrain_espace->taille_espace_x * 100, un_terrain_espace->taille_espace_y * 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	planete1 = IMG_Load("../graphiques/images/1.png");
	planete2 = IMG_Load("../graphiques/images/2.png");
	planete3 = IMG_Load("../graphiques/images/3.png");
	image_une_case = IMG_Load("../graphiques/images/quadrillage.png");
    fond = IMG_Load("../graphiques/images/fond.png");
    SDL_BlitSurface(fond, NULL, carte, &position);
	for(i=0;i< un_terrain_espace->taille_espace_x;i++)
	{
		for(j=0;j< un_terrain_espace->taille_espace_y;j++)
		{
			une_case = get_case_terrain_espace(un_terrain_espace, i, j);
			if(une_case->type_case_terrain_espace == 'P')
			{
				initialise_sdl_rect(&position_planete, i * 100, j * 100, 0, 0);
				if(une_case->planete->planete_colonisee == true)
				{
					if(une_case->planete->indice_joueur == 0)
					{
						SDL_BlitSurface(planete1, NULL, carte, &position_planete);
					}
					if(une_case->planete->indice_joueur == 1)
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

SDL_Surface* creer_affichage_flotte(Terrain_espace *un_terrain_espace)
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

	carte = SDL_CreateRGBSurface(SDL_HWSURFACE, un_terrain_espace->taille_espace_x * 100, un_terrain_espace->taille_espace_y * 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	flotte1_bleu = IMG_Load("../graphiques/images/unite1_bleu.png");
	flotte2_bleu = IMG_Load("../graphiques/images/unite2_bleu.png");
	flotte3_bleu = IMG_Load("../graphiques/images/unite3_bleu.png");

	flotte1_rouge = IMG_Load("../graphiques/images/unite1_rouge.png");
	flotte2_rouge = IMG_Load("../graphiques/images/unite2_rouge.png");
	flotte3_rouge = IMG_Load("../graphiques/images/unite3_rouge.png");

	image_une_case = IMG_Load("../graphiques/images/quadrillage.png");
	for(i=0;i< un_terrain_espace->taille_espace_x;i++)
	{
		for(j=0;j< un_terrain_espace->taille_espace_y;j++)
		{
			position.x = i * 100;
			position.y = j *100;
			une_case = get_case_terrain_espace(un_terrain_espace, i, j);
			if(une_case->presence_flotte == true)
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

SDL_Surface* affichage_minimap(Terrain_espace *un_terrain_espace)
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
	fond_minimap = IMG_Load("../graphiques/images/fond_minimap.png");
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
	x_affichage = ((float)un_terrain_espace->affichage_x/(un_terrain_espace->taille_espace_x * 100)) * TAILLE_MINIMAP_X;
	y_affichage = ((float)un_terrain_espace->affichage_y/(un_terrain_espace->taille_espace_y * 100)) * TAILLE_MINIMAP_Y;
	initialise_sdl_rect(&position_rect_affichage, x_affichage, y_affichage, 0, 0);
	SDL_BlitSurface(rect_affichage, NULL, minimap, &position_rect_affichage);

	SDL_FreeSurface(fond_minimap);
	SDL_FreeSurface(rect_affichage);
	SDL_FreeSurface(un_pixel);
	return minimap;
}

SDL_Surface* creer_affichage_vision(Jeu *un_jeu, Joueur* un_joueur)
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

	une_vision = un_joueur->vision_terrain;
	un_terrain_espace = un_joueur->vision_terrain->terrain_espace;

	fond = SDL_CreateRGBSurface(SDL_HWSURFACE,un_terrain_espace->taille_espace_x * 100, un_terrain_espace->taille_espace_y * 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(fond, NULL, SDL_MapRGB(fond->format, 0, 0, 255));

	jamais_visitee = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(jamais_visitee, NULL, SDL_MapRGB(fond->format, 0, 0, 0));
	
	affichee = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(affichee, NULL, SDL_MapRGB(fond->format, 255, 255, 255));
	
	visitee = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(visitee, NULL, SDL_MapRGB(fond->format, 0, 255, 0));
	SDL_SetAlpha(visitee, SDL_SRCALPHA, 128);
	
	for(i=0;i< un_terrain_espace->taille_espace_y;i++)
	{
		for(j=0;j< un_terrain_espace->taille_espace_x;j++)
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
	//SDL_SetColorKey(fond, 128, SDL_MapRGB(fond->format, 0, 255, 0));

	SDL_FreeSurface(visitee);
	SDL_FreeSurface(jamais_visitee);
	SDL_FreeSurface(affichee);

	return fond;
}

void maj_affichage_vision(Jeu *un_jeu, Joueur* un_joueur, SDL_Surface *ecran, SDL_Surface **tab_surface)
{
	SDL_Surface *affichee = NULL;
	SDL_Surface *jamais_visitee = NULL;
	SDL_Surface *visitee = NULL;
	SDL_Rect position = {0, TAILLE_BARRE_RESSOURCE, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_affichage;
	int i, j;
	Terrain_espace* un_terrain_espace;
	Vision_terrain* une_vision;
	Vision_case *une_case;

	une_vision = un_joueur->vision_terrain;
	un_terrain_espace = un_joueur->vision_terrain->terrain_espace;
	maj_vision_joueur(un_jeu, un_terrain_espace, 0);
	
	tab_surface[11] = SDL_CreateRGBSurface(SDL_HWSURFACE,un_terrain_espace->taille_espace_x * 100, un_terrain_espace->taille_espace_y * 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(tab_surface[11], NULL, SDL_MapRGB(tab_surface[11]->format, 0, 0, 255));
	SDL_SetColorKey(tab_surface[11], SDL_SRCCOLORKEY, SDL_MapRGB(tab_surface[11]->format, 0, 0, 255));

	jamais_visitee = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(jamais_visitee, NULL, SDL_MapRGB(tab_surface[11]->format, 0, 0, 0));

	affichee = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(affichee, NULL, SDL_MapRGB(tab_surface[11]->format, 255, 255, 255));
	SDL_SetColorKey(affichee, SDL_SRCCOLORKEY, SDL_MapRGB(tab_surface[11]->format, 255, 255, 255));

	visitee = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(visitee, NULL, SDL_MapRGB(tab_surface[11]->format, 0, 0, 0));
	//SDL_SetColorKey(visitee, SDL_SRCCOLORKEY, SDL_MapRGB(tab_surface[11]->format, 0, 255, 0));
	SDL_SetAlpha(visitee, SDL_SRCALPHA, 100);

	for(i=0;i< un_terrain_espace->taille_espace_y;i++)
	{
		for(j=0;j< un_terrain_espace->taille_espace_x;j++)
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

void initialiser_affichage(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface *carte, SDL_Surface **tab_surface)
{
	SDL_Surface *carte_flotte = NULL;
	SDL_Surface *ressource= NULL;
	SDL_Surface *deplacement_carte = NULL;
	SDL_Surface *interface = NULL;
	SDL_Surface *mini_carte = NULL;
	SDL_Surface *info = NULL;
	SDL_Surface *panneau_unite = NULL;
	SDL_Surface *minimap = NULL;
    SDL_Surface *bouton_passer_tour = NULL;
    SDL_Surface *bordure = NULL;
	SDL_Surface *visibilite = NULL;
	SDL_Surface *infobulle = NULL;

	SDL_Rect position = {0, 0, 0, 0};
	SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
	SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 25 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect affichage_carte = {0, 0, 0, 0};
	SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 300, 20, 300, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};
	SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -207, TAILLE_TERRAIN_ESPACE_Y - 8, 0, 0};

	carte = creer_affichage_terrain(un_terrain_espace);

	info = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(info, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_BlitSurface(info, NULL, ecran, &position_affichage_info);

	/*Creation du terrain en entier, celui-ci est stocké en mémoire*/
	carte_flotte = creer_affichage_flotte(un_terrain_espace);
	initialise_sdl_rect(&affichage_carte, un_terrain_espace->affichage_x, un_terrain_espace->affichage_y, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y);
	SDL_SetColorKey(carte_flotte, SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_BlitSurface(carte, &affichage_carte, ecran, &position_affichage_carte);
	SDL_BlitSurface(carte_flotte, &affichage_carte, ecran, &position_affichage_carte);

	/*creation de l'affichage de la visibilité*/
	visibilite = creer_affichage_vision(un_jeu, get_ieme_joueur_jeu(un_jeu, 0));
	SDL_BlitSurface(visibilite, &affichage_carte, ecran, &position_affichage_carte);

	/*affichage de la barre de ressources*/
    ressource = affichage_ressource(un_jeu, ressource);
	SDL_BlitSurface(ressource, NULL, ecran, &position);

	/*affichage de l'interface*/
	interface = IMG_Load("../graphiques/images/interface_bas.png");
	SDL_BlitSurface(interface, NULL, ecran, &position_interface);

	panneau_unite = IMG_Load("../graphiques/images/interface_barrelaterale.png");
	initialise_sdl_rect(&position_panneau_unite, TAILLE_FENETRE_X - 214, 35, 200, TAILLE_TERRAIN_ESPACE_Y-300);

	/*affichage de la minimap*/
	minimap = affichage_minimap(un_terrain_espace);
	SDL_BlitSurface(minimap, NULL, ecran, &position_minimap);

	/*affichage du bouton de tour suivant*/
	bouton_passer_tour = IMG_Load("../graphiques/images/passer_tour.png");
    SDL_BlitSurface(bouton_passer_tour, NULL, ecran, &position_bouton_tour);

    /*affichage du cadre*/
    bordure = IMG_Load("../graphiques/images/bordure.png");
    SDL_BlitSurface(bordure, NULL, ecran, &position_affichage_carte);

	tab_surface[0] = carte;
	tab_surface[1] = carte_flotte;
	tab_surface[2] = ressource;
	tab_surface[3] = bordure;
	tab_surface[4] = deplacement_carte;
	tab_surface[5] = interface;
	tab_surface[6] = mini_carte;
	tab_surface[7] = info;
	tab_surface[8] = panneau_unite;
	tab_surface[9] = minimap;
	tab_surface[10] = bouton_passer_tour;
	tab_surface[11] = visibilite;
	tab_surface[12] = infobulle;

	SDL_Flip(ecran);
}

void maj_carte_terrain(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee)
{
	SDL_Rect position = {0, 0, 0, 0};
	SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
	SDL_Rect position_mini_carte = {TAILLE_FENETRE_X - 240, TAILLE_FENETRE_Y - 158};
	SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 25 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect affichage_carte = {0, 0, 0, 0};
	SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -207, TAILLE_TERRAIN_ESPACE_Y - 8, 0, 0};

	/*Creation du terrain en entier, celui-ci est stocké en mémoire*/
	tab_surface[0] = creer_affichage_terrain(un_terrain_espace);
	initialise_sdl_rect(&affichage_carte, un_terrain_espace->affichage_x, un_terrain_espace->affichage_y, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y);
	SDL_BlitSurface(tab_surface[0], &affichage_carte, ecran, &position_affichage_carte);
	SDL_BlitSurface(tab_surface[1], &affichage_carte, ecran, &position_affichage_carte);
	SDL_BlitSurface(tab_surface[11], &affichage_carte, ecran, &position_affichage_carte);

	/*affichage de l'interface*/
	SDL_BlitSurface(tab_surface[5], NULL, ecran, &position_interface);
	SDL_BlitSurface(tab_surface[6], NULL, ecran, &position_mini_carte);

	/*affichage de la barre de ressources*/
	SDL_BlitSurface(tab_surface[2], NULL, ecran, &position);

	/*affichage de la bordure*/
	SDL_BlitSurface(tab_surface[3], NULL, ecran, &position_affichage_carte);

	/*affichage bouton passer tour*/
	SDL_BlitSurface(tab_surface[10], NULL, ecran, &position_bouton_tour);

	if(interface_affichee == FLOTTE)
	{
		tab_surface[7] = affichage_flotte(un_jeu, un_terrain_espace,tab_surface[7]);
		SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
	}

	SDL_Flip(ecran);


}

void maj_affichage_carte_terrain(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee)
{
    SDL_Rect position = {0, 0, 0, 0};
    SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};
    SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 25 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 214, 35, 200, TAILLE_TERRAIN_ESPACE_Y-300};
    SDL_Rect affichage_carte = {un_terrain_espace->affichage_x, un_terrain_espace->affichage_y, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -207, TAILLE_TERRAIN_ESPACE_Y - 8, 0, 0};
	Case_terrain_espace* une_case_terrain_espace;

    /*Réaffichage des différentes parties de la carte*/
    SDL_BlitSurface(tab_surface[0], &affichage_carte, ecran, &position_affichage_carte);
    SDL_BlitSurface(tab_surface[1], &affichage_carte, ecran, &position_affichage_carte);
	SDL_BlitSurface(tab_surface[11], &affichage_carte, ecran, &position_affichage_carte);

	/*creation de l'affichage de la visibilité*/
	//maj_affichage_vision(un_jeu, un_jeu->tab_joueur, ecran, tab_surface);

    /*affichage de la bordure*/
    SDL_BlitSurface(tab_surface[3], NULL, ecran, &position_affichage_carte);

    /*affichage bouton passer tour*/
    SDL_BlitSurface(tab_surface[10], NULL, ecran, &position_bouton_tour);

    if(interface_affichee == RIEN)
    {
            /*affichage de la minimap*/
            tab_surface[9] = affichage_minimap(un_terrain_espace);
            SDL_BlitSurface(tab_surface[9], NULL, ecran, &position_minimap);
    }
	if(interface_affichee == PANNEAU_UNITE)
	{
		une_case_terrain_espace	= get_case_terrain_espace(un_terrain_espace, get_x_planete(get_planete_en_cours(un_jeu)), get_y_planete(get_planete_en_cours(un_jeu)));
		tab_surface[7] = affichage_planete(get_planete_en_cours(un_jeu), tab_surface[7]);
		SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
		tab_surface[8] = affichage_creation_unite(get_planete_en_cours(un_jeu), tab_surface[8]);
		SDL_BlitSurface(tab_surface[8], NULL, ecran, &position_panneau_unite);
	}

    SDL_Flip(ecran);
}

void maj_affichage_flotte(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, INTERFACE_AFFICHEE interface_affichee)
{
    SDL_Rect position = {0, 0, 0, 0};
    SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
    SDL_Rect position_mini_carte = {TAILLE_FENETRE_X - 240, TAILLE_FENETRE_Y - 158};
    SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 25 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect affichage_carte = {0, 0, 0, 0};
    SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -207, TAILLE_TERRAIN_ESPACE_Y - 8, 0, 0};

    /*Creation du terrain en entier, celui-ci est stocké en mémoire*/
    tab_surface[1] = creer_affichage_flotte(un_terrain_espace);
    initialise_sdl_rect(&affichage_carte, un_terrain_espace->affichage_x, un_terrain_espace->affichage_y, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y);
    SDL_BlitSurface(tab_surface[0], &affichage_carte, ecran, &position_affichage_carte);
    SDL_SetColorKey(tab_surface[1], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(tab_surface[1], &affichage_carte, ecran, &position_affichage_carte);

	/*creation de l'affichage de la visibilité*/
	maj_affichage_vision(un_jeu, un_jeu->tab_joueur, ecran, tab_surface);
	SDL_BlitSurface(tab_surface[11], &affichage_carte, ecran, &position_affichage_carte);

    /*affichage de l'interface*/
    SDL_BlitSurface(tab_surface[5], NULL, ecran, &position_interface);
    SDL_BlitSurface(tab_surface[6], NULL, ecran, &position_mini_carte);

    /*affichage de la barre de ressources*/
    SDL_BlitSurface(tab_surface[2], NULL, ecran, &position);

    /*affichage de la bordure*/
    SDL_BlitSurface(tab_surface[3], NULL, ecran, &position_affichage_carte);

    /*affichage bouton passer tour*/
    SDL_BlitSurface(tab_surface[10], NULL, ecran, &position_bouton_tour);

    if(interface_affichee == FLOTTE)
    {
        tab_surface[7] = affichage_flotte(un_jeu, un_terrain_espace,tab_surface[7]);
      SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
    }

    SDL_Flip(ecran);
}

void maj_affichage_ressource(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface)
{
	SDL_Rect position = {0, 0, 0, 0};
	tab_surface[2] = affichage_ressource(un_jeu, ecran);
	SDL_BlitSurface(tab_surface[2], NULL, ecran, &position);
}

void maj_affichage(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface *carte, INTERFACE_AFFICHEE interface_affichee, Case_terrain_espace *une_case_terrain_espace, SDL_Surface **tab_surface)
 {
    SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
    SDL_Rect position_mini_carte = {TAILLE_FENETRE_X - 240, TAILLE_FENETRE_Y - 158};
    SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 25 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 214, 35, 200, TAILLE_TERRAIN_ESPACE_Y-300};
    SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};

   /*affichage de l'interface*/
    SDL_BlitSurface(tab_surface[5], NULL, ecran, &position_interface);
    SDL_BlitSurface(tab_surface[6], NULL, ecran, &position_mini_carte);

    /*affichage de la barre de ressources*/
	maj_affichage_ressource(un_jeu, un_terrain_espace, ecran, tab_surface);

        if(interface_affichee == RIEN)
        {
            /*affichage de la minimap*/
            tab_surface[9] = affichage_minimap(un_terrain_espace);
            SDL_BlitSurface(tab_surface[9], NULL, ecran, &position_minimap);
        }
        if(interface_affichee == PLANETE)
        {
            tab_surface[7] = affichage_planete(get_planete_en_cours(un_jeu), tab_surface[7]);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
        }
        if(interface_affichee == PLANETE_ENNEMIE)
        {
            tab_surface[7] = affichage_planete_ennemie(une_case_terrain_espace, tab_surface[7]);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
        }
        if(interface_affichee == FLOTTE)
        {
            tab_surface[7] = affichage_flotte(un_jeu, un_terrain_espace, tab_surface[7]);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
        }
        if(interface_affichee == FLOTTE_ENNEMIE)
        {
            tab_surface[7] = affichage_flotte_ennemie(un_jeu, tab_surface[7]);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
        }
        if(interface_affichee == PANNEAU_UNITE)
        {
            tab_surface[7] = affichage_planete(get_planete_en_cours(un_jeu), tab_surface[7]);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
            tab_surface[8] = affichage_creation_unite(get_planete_en_cours(un_jeu), tab_surface[8]);
            SDL_BlitSurface(tab_surface[8], NULL, ecran, &position_panneau_unite);
        }

    SDL_Flip(ecran);
 }


/************************************************************************/
/* Boucle principale                                                    */
/************************************************************************/

void affichage_ecran(Jeu *un_jeu, Terrain_espace *un_terrain_espace)
{
	/************************************************************************/
	/* Initialisation des variables                                         */
	/************************************************************************/

	/*variable SDL*/
	SDL_Surface *ecran = NULL;
	SDL_Surface *carte = NULL;
	SDL_Surface *icone = NULL;
	SDL_Surface **tab_surface;
	SDL_Rect bouton_tour = {TAILLE_FENETRE_X -207, TAILLE_TERRAIN_ESPACE_Y - 8, 200, 33};
	SDL_Rect position_affichage_carte = {0, TAILLE_BARRE_RESSOURCE, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 300, 20, 300, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect test;
	SDL_Event event;

	/*variable diverses*/
	int continuer = 1;
	int x = 0, y = 0, x_bis = 0, y_bis = 0;
	int i, j;
	bool infobulle = false;
	int tps_ancien = 10,tps_nouveau = 0, timer = 0, x_info = 0, y_info = 0;
	INTERFACE_AFFICHEE interface_affichee = RIEN; /*1 pour une planete, 2 pour une planete ennemie, 3 pour une flotte, 4 pour une flotte ennemie, 5 pour la création d'unités sur une planète*/
	Case_terrain_espace *une_case_terrain_espace;
	Animation *saut_ftl = NULL;
	char nom_fichier_saut_ftl[] = "../graphiques/images/effet téléportation.png";

	/*varirables pour le son*/
	FMOD_SYSTEM *system = NULL;
	FMOD_SOUND *musique = NULL;
	FMOD_SOUND *son_saut_debut = NULL;
	FMOD_SOUND *son_saut_fin = NULL;
	char **tab_chanson = NULL;


	/************************************************************************/
	/* Début de la fonction, initialisation des différentes valeurs         */
	/************************************************************************/

	/*initialiser le son*/
	FMOD_System_Create(&system);
	FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, NULL);
	
	/*on initialise le tableau de chansons puis on utilise la fonction qui va mettre les noms dedans (pour plus de clarté dans le code)*/
	tab_chanson = (char **)malloc(sizeof(char *) * 6);
	for(j=0;j<6;j++)
	{
		tab_chanson[j] = (char *)malloc(sizeof(char) * 50);
	}
	initialiser_tableau_chanson(tab_chanson);
	
	/*on lance les musiques du jeu et on initialise les sons*/
	//lire_musique(system, musique, tab_chanson);
	FMOD_System_CreateSound(system, "../audio/son/FTL_Saut.mp3", FMOD_CREATESAMPLE, 0, &son_saut_debut);
	FMOD_System_CreateSound(system, "../audio/son/FTL_Exit.mp3", FMOD_CREATESAMPLE, 0, &son_saut_fin);
	

	/*démarrage des modules, mise en place de la fenêtre principale*/
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_EnableKeyRepeat(10, 10); /*active la répétition des touches, principalement pour un déplacement de la map plus fluide*/
	icone = IMG_Load("../graphiques/images/icone.png");
	SDL_WM_SetIcon(icone, NULL);
	ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, NOMBRE_BITS_COULEUR, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Conquest of Space", NULL);

	/*on initialise le tableau de surfaces et les différentes surfaces*/
	tab_surface = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 13);
	carte = creer_affichage_terrain(un_terrain_espace);
	initialiser_affichage(un_jeu, un_terrain_espace, ecran, carte, tab_surface);

	saut_ftl = creer_animation(5, 100, 100, 50, nom_fichier_saut_ftl);
	tps_ancien = SDL_GetTicks();


	/************************************************************************/
	/* Boucle principale                                                    */
	/************************************************************************/

	while (continuer) /*boucle d'événement principale*/
	{
		/*mise à jour de valeurs "globales"*/
		SDL_PollEvent(&event);
		//maj_musique(system, musique, tab_chanson);

		/*pour afficher les infobulles*/
		tps_nouveau = SDL_GetTicks();
		timer = tps_nouveau - tps_ancien;
		if(timer >= TEMPS_INFOBULLE)
		{
			/*maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);
			maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);*/
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
				maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace, tab_surface);
				maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
				infobulle = false;
			}
            break;
		case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x;
                y = event.button.y;
                if(booleen_case_pointeur_souris(un_terrain_espace, x, y)) /*test des clics ayant lieu sur le terrain*/
                {
                    une_case_terrain_espace = case_pointeur_souris(un_terrain_espace, x, y);
					/*si la case est une planète, on affiche l'interface correspondante*/
                    if(une_case_terrain_espace->type_case_terrain_espace == 'P') 
                    {
                        un_jeu->selection_planete = get_planete(une_case_terrain_espace);
						if(un_jeu->selection_planete->indice_joueur == get_indice_joueur_en_cours(un_jeu))
						{
							interface_affichee = PLANETE;
						}
						else
						{
							interface_affichee = PLANETE_ENNEMIE;
						}
						maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace, tab_surface);
                        reinitialiser_tableau_selection_unite(un_jeu);
                    }
					/*si une flotte est présente*/
                    if(une_case_terrain_espace->presence_flotte == true) 
                    {
                        un_jeu->selection_flotte = une_case_terrain_espace->flotte;
						if(un_jeu->selection_flotte->indice_joueur == un_jeu->joueur_en_cours)
						{
							interface_affichee = FLOTTE;
						}
						else
						{
							interface_affichee = FLOTTE_ENNEMIE;
						}
						maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);
                        reinitialiser_tableau_selection_unite(un_jeu);
                    }
					/*si rien de cela, on va revenir à l'interface simple, sans informations*/
                    if(test_souris_rectangle(position_affichage_carte, x, y) && (une_case_terrain_espace->type_case_terrain_espace != 'P') && (une_case_terrain_espace->presence_flotte == false))
                    {
						if(interface_affichee == PANNEAU_UNITE)
						{
							 if(!test_souris_rectangle(position_panneau_unite, x, y))
							 {
								 interface_affichee = RIEN;
								 maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);
								 maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
								 reinitialiser_tableau_selection_unite(un_jeu);
							 }
						}
						if(interface_affichee != PANNEAU_UNITE)
						{
							interface_affichee = RIEN;
							maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);
							maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
							reinitialiser_tableau_selection_unite(un_jeu);
						}
                    }
					/*pour passer au joueur suivant*/
					if (test_souris_rectangle(bouton_tour, x, y)) 
					{
						interface_affichee = RIEN;
						joueur_suivant(un_jeu, un_terrain_espace);
						maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
						maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);
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
                            une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->selection_planete->x, un_jeu->selection_planete->y);
                            if(condition_creation_batiment (un_jeu->selection_planete, i))
							{
								creation_batiment(un_jeu->selection_planete, i);
								maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace, tab_surface);
							}

						}
				    }
                    /*pour ouvrir le panneau d'unités*/
                    initialise_sdl_rect(&test, TAILLE_FENETRE_X -150, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
                    if(test_souris_rectangle(test, x, y))
                    {
                        une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->selection_planete->x, un_jeu->selection_planete->y);
                        interface_affichee = 5;
                        maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace, tab_surface);
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
							if(un_jeu->tab_unite_selectionnee[i] == true)
							{
								un_jeu->tab_unite_selectionnee[i] = false;
							}
							else
							{
								un_jeu->tab_unite_selectionnee[i] = true;
							}
						}
						if(test_souris_rectangle(test, x, y) && !(SDL_GetModState() & KMOD_LCTRL))
						{
							for(j=0;j<10;j++)
							{
								un_jeu->tab_unite_selectionnee[j] = false;
							}
							un_jeu->tab_unite_selectionnee[i] = true;
						}
					}
					initialise_sdl_rect(&test, TAILLE_FENETRE_X - 150, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
					if(test_souris_rectangle(test, x, y)) /*va coloniser la planète*/
					{
						colonisation_planete_flotte(un_terrain_espace, get_flotte_en_cours(un_jeu), un_jeu);
					}
					maj_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
					maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);
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
                            une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->selection_planete->x, un_jeu->selection_planete->y);
							if(condition_creation_unite(get_joueur_en_cours(un_jeu), get_planete(une_case_terrain_espace), i + 1))
							{
								creation_unite_planete(&un_jeu->tab_joueur[un_jeu->joueur_en_cours], get_planete(une_case_terrain_espace), i + 1);
								maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace, tab_surface);
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
                if(un_jeu->selection_flotte != NULL)
                {
                    if((un_jeu->selection_flotte->indice_joueur == un_jeu->joueur_en_cours) && (un_jeu->selection_flotte->pt_mouvement_espace_flotte >= 0))
                    {
                        if(test_unite_selectionnee(un_jeu))
                        {
							booleen_coordonnees_case(un_terrain_espace, un_jeu->selection_flotte->x_flotte, un_jeu->selection_flotte->y_flotte, &x_bis, &y_bis);
							lire_son(system, son_saut_debut);
							lancer_animation_bloquante(un_jeu, un_terrain_espace, saut_ftl, ecran, x_bis, y_bis);
							deplacement_unite_flotte(un_jeu, &un_jeu->tab_joueur[un_jeu->joueur_en_cours], un_terrain_espace, un_jeu->selection_flotte, x/100, y/100);
							interface_affichee = RIEN;
							un_jeu->selection_flotte = NULL;
							/*un_jeu->selection_flotte = get_flotte(get_case_terrain_espace(un_terrain_espace, x/100, y/100));*/
							maj_affichage_flotte(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
							booleen_coordonnees_case(un_terrain_espace, un_jeu->selection_flotte->x_flotte, un_jeu->selection_flotte->y_flotte, &x_bis, &y_bis);
							lire_son(system, son_saut_fin);
							lancer_animation_bloquante(un_jeu, un_terrain_espace, saut_ftl, ecran, x_bis, y_bis);
                        }
						else
                        {
							/*déplacement avec l'animation et le son*/
							booleen_coordonnees_case(un_terrain_espace, un_jeu->selection_flotte->x_flotte, un_jeu->selection_flotte->y_flotte, &x_bis, &y_bis);
							lire_son(system, son_saut_debut);
							lancer_animation_bloquante(un_jeu, un_terrain_espace, saut_ftl, ecran, x_bis, y_bis);
							deplacement_flotte(&un_jeu->tab_joueur[un_jeu->joueur_en_cours], un_terrain_espace, un_jeu->selection_flotte, une_case_terrain_espace->x_espace, une_case_terrain_espace->y_espace);
							//un_jeu->selection_flotte = get_flotte(get_case_terrain_espace(un_terrain_espace, x/100, y/100));
							maj_affichage_flotte(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
							booleen_coordonnees_case(un_terrain_espace, un_jeu->selection_flotte->x_flotte, un_jeu->selection_flotte->y_flotte, &x_bis, &y_bis);
							lire_son(system, son_saut_fin);
							lancer_animation_bloquante(un_jeu, un_terrain_espace, saut_ftl, ecran, x_bis, y_bis);
                        }
                    }
                    if((un_jeu->selection_flotte->indice_joueur != un_jeu->joueur_en_cours) && (un_jeu->selection_flotte->pt_mouvement_espace_flotte >= 0))
                    {
                        /*mettre fonction attaque prenant en param le terrain, le jeu, les 2 flottes*/
                    }
                }
            }
            break;


		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				continuer = 0;
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
		event.type=0; /*on place cela à 0 pour éviter la répétition de l'évenement tant qu'il n'y a pas eu d'action*/
	}


	/************************************************************************/
	/* Libération des variables et fermetures de SDL                        */
	/************************************************************************/

	for(i=0;i<13;i++)
	{
	    SDL_FreeSurface(tab_surface[i]);
	}
	free(tab_surface);
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(carte);
	SDL_FreeSurface(icone);

	fermer_systeme_son(system, musique);
	/*for(i=0;i<6;i++)
	{
		free(&tab_chanson[i]);
	}*/
	free(tab_chanson);

	detruire_animation(&saut_ftl);

	TTF_Quit();
	SDL_Quit();
}


/************************************************************************/
/* Fonctions liées au combat                                             */
/************************************************************************/

SDL_Surface * affiche_ecran_terrain_combat(const Terrain_combat *terrain_combat)
{
	SDL_Surface * carte =NULL;
	SDL_Surface * fond =NULL;
	SDL_Surface * quadrillage =NULL;
	SDL_Surface * planete =NULL;
	SDL_Surface * selection =NULL;
	SDL_Rect pos,pos_plan;
	int i, j, x,y;
    Case_terrain_combat *une_case;

	x=get_taille_combat_x(terrain_combat);
	y=get_taille_combat_y(terrain_combat);
	carte =SDL_CreateRGBSurface(SDL_HWSURFACE, x* 100, y* 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	pos.x = 0 ;pos_plan.x=0;
	pos.y = 0;pos_plan.y=0;
	fond = IMG_Load("../graphiques/images/Fond_terraincombat.png");
    SDL_BlitSurface(fond, NULL, carte, &pos);
	quadrillage = IMG_Load("../graphiques/images/quadrillage.png");
	selection = IMG_Load("../graphiques/images/selection.png");

    for(j=0;j<terrain_combat->taille_combat_y;j++)
    {
        for(i=0;i<terrain_combat->taille_combat_x;i++)
        {
			pos.x=i*100;pos.y=j*100;
            une_case = get_case_terrain_combat(terrain_combat, i, j);
            if(get_presence_unite(une_case)&&(get_indice_joueur_unite(get_unite(une_case))==0))
            {	planete = IMG_Load("../graphiques/images/vaisseau_1.png");
				pos_plan.x=i*100;pos_plan.y=j*100;
				SDL_BlitSurface(planete,NULL,carte,&pos_plan);
            }
			else if(get_presence_unite(une_case)&&(get_indice_joueur_unite(get_unite(une_case))==1))
            {	planete = IMG_Load("../graphiques/images/vaisseau_2.png");
				pos_plan.x=i*100;pos_plan.y=j*100;
				SDL_BlitSurface(planete,NULL,carte,&pos_plan);
            }else if(get_presence_unite(une_case))
            {	planete = IMG_Load("../graphiques/images/vaisseau_3.png");
				pos_plan.x=i*100;pos_plan.y=j*100;
				SDL_BlitSurface(planete,NULL,carte,&pos_plan);
            }
			if(get_selection_unite(une_case))
			{
				SDL_BlitSurface(selection,NULL,carte,&pos);
			}else{SDL_BlitSurface(quadrillage,NULL,carte,&pos);}
        }
        printf("\n");
    }
	SDL_FreeSurface(selection);
	SDL_FreeSurface(planete);
	SDL_FreeSurface(quadrillage);
	return carte;
}
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
void affiche_deplacement_unite(Terrain_combat *un_terrain_combat,SDL_Rect position)
{
	SDL_Rect pos;
	bool p;
	Case_terrain_combat * une_case;
	Unite * une_unite;
	p=0;
	pos =coordonnee_case_du_clic(position);
	if(get_une_case_selectionnee(un_terrain_combat))
	{
		une_case = get_selection(un_terrain_combat);
		une_unite = get_unite(une_case);
		p=deplacement_unite(un_terrain_combat, une_unite ,pos.x,pos.y);
	}
	if(p)
	{
		set_selection_unite(une_case, 0);set_selection(un_terrain_combat,NULL);set_une_case_selectionnee(un_terrain_combat,0);
	}
}

void selection(Jeu * jeu,Terrain_combat *un_terrain_combat,SDL_Rect position)
{
	SDL_Rect pos;
	pos=position;
	pos=coordonnee_case_du_clic(pos);
  	selectionner_case_combat(jeu,un_terrain_combat, pos.x, pos.y);
	printf("joueur en cours : %d \n",  get_joueur_en_cours_combat(jeu));
}
void affiche_info_unite(Terrain_combat *un_terrain_combat,char * infos)
{
	Unite * unite;
	int a,b,c,d,e,f,g;
	if(get_une_case_selectionnee(un_terrain_combat))
	{
		unite = get_unite(get_selection(un_terrain_combat));
		a = get_pt_vie(unite);
		b = get_pt_action(unite);
		d = get_pt_deplacement(unite);
		c = get_portee(unite);
		e = get_pt_attaque(unite);
		f = get_x_unite(unite);
		g = get_y_unite(unite);
		sprintf(infos,"(%d,%d) pv = %d pa=%d po=%d pd=%d pw=%d",f,g,a,b,c,d,e);
	}
	else
	{

		sprintf(infos," ");
	}

}

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

void menu_chargement_sauvegarde(void)
{
    /*Initialisation des variables*/
    SDL_Surface *ecran, *imageDeFond, *Texte, *Texte2, *Noir;
    TTF_Font *police;
    SDL_Color couleur= {255, 255, 255};
    SDL_Rect positionTexte, positionTexte2;
    Terrain_espace *un_terrain_espace;
    Jeu *jeu;
    Sauvegarde *une_sauvegarde;
    int b = 255;
    char chaine[50];
	double longueurTexte, longueurTexte2;
    
    
    /*CHARGEMENT*/
    
    /*Initialisation de l'écran et des images */
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../graphiques/images/Sauvegarde_Fond.png");
    Noir = SDL_LoadBMP("../graphiques/images/Noir.bmp");
    
    /*Chargement du titre*/
    TTF_Init();
    police = TTF_OpenFont("../graphiques/fonts/space_age.ttf", 60);
    Texte = TTF_RenderText_Blended(police, "Charger une partie", couleur);
    longueurTexte = Texte->w;
    positionTexte.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte/2.0));
    positionTexte.y = 1*(TAILLE_FENETRE_Y)/10;
    
    /*Chargement du texte*/
    police = TTF_OpenFont("../graphiques/fonts/space_age.ttf", 40);
    Texte2 = TTF_RenderText_Blended(police, "Tapez le nom de la sauvegarde", couleur);
    longueurTexte2 = Texte2->w;
    positionTexte2.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte2/2.0));
    positionTexte2.y = 2*(TAILLE_FENETRE_Y)/10;
    
    
    /*AFFICHAGE*/
    
    /*Animation de l'apparition du menu*/
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-10;
        SDL_Flip(ecran);
        SDL_FreeSurface(ecran);
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
        SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
        SDL_BlitSurface(Texte2, NULL, ecran, &positionTexte2);
    }
    
    /*Scan du nom et chargement de la sauvegarde*/
    printf("Tapez ci-dessous le nom de la sauvegarde :\n");
    scanf("%s", chaine);
    une_sauvegarde = selection_ouverture(chaine);
    jeu = une_sauvegarde->jeu;
    un_terrain_espace = une_sauvegarde->terrain_espace;
    
    /*Disparition du menu et affichage du jeu*/
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(Texte);
    SDL_FreeSurface(imageDeFond);
    SDL_Quit();
    affichage_ecran(jeu, un_terrain_espace);
}

void menu_creation_sauvegarde(Terrain_espace *un_terrain_espace, Jeu *un_jeu)
{
    /*Initialisation des variables*/
    SDL_Surface *ecran, *imageDeFond, *Texte, *Texte2, *Noir;
    TTF_Font *police;
    SDL_Color couleur= {255, 255, 255};
    SDL_Rect positionTexte, positionTexte2;
    int b = 255;
    char chaine[50];
	double longueurTexte, longueurTexte2;
    
    
    /*CHARGEMENT*/
    
    /*Initialisation de l'écran et des images */
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../graphiques/images/Sauvegarde_Fond.png");
    Noir = SDL_LoadBMP("../graphiques/images/Noir.bmp");
    
    /*Chargement du titre*/
    TTF_Init();
    police = TTF_OpenFont("../graphiques/fonts/space_age.ttf", 60);
    Texte = TTF_RenderText_Blended(police, "Sauvegarder une partie", couleur);
    longueurTexte = Texte->w;
    positionTexte.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte/2.0));
    positionTexte.y = 1*(TAILLE_FENETRE_Y)/10;
    
    /*Chargement du texte*/
    police = TTF_OpenFont("../graphiques/fonts/space_age.ttf", 40);
    Texte2 = TTF_RenderText_Blended(police, "Tapez le nom de la sauvegarde", couleur);
    longueurTexte2 = Texte2->w;
    positionTexte2.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte2/2.0));
    positionTexte2.y = 2*(TAILLE_FENETRE_Y)/10;
    
    
    /*AFFICHAGE*/
    
    /*Animation de l'apparition du menu*/
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-10;
        SDL_Flip(ecran);
        SDL_FreeSurface(ecran);
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
        SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
        SDL_BlitSurface(Texte2, NULL, ecran, &positionTexte2);
    }
    
    /*Scan du nom et sauvegarde*/
    printf("Tapez ci-dessous le nom de la sauvegarde :\n");
    scanf("%s", chaine);
    creer_fichier_sauvegarde(chaine, un_terrain_espace, un_jeu);
}

void menu_pause(Terrain_espace *un_terrain_espace, Jeu *un_jeu)
{
    /* Initialisation des variables */
    SDL_Surface *ecran, *imageDeFond, *Texte, *Noir, *Sauvegarder, *Quitter;
    TTF_Font *police;
    SDL_Color couleur= {255, 255, 255};
    SDL_Rect positionTexte, positionSauvegarder, positionQuitter;
    SDL_Event evenement;
    int continuer = 1, xm = 0, ym = 0, i;
    double longueurTexte, longueurBouton, hauteurBouton;
    
    /* Chargement des images */
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../graphiques/images/Fond_titre.png");
    Noir = SDL_LoadBMP("../graphiques/images/Noir.bmp");
    Sauvegarder = IMG_Load("../graphiques/images/Quitter.png");
    Quitter = IMG_Load("../graphiques/images/Quitter.png");
    
    /* Chargement de la police */
    TTF_Init();
    police = TTF_OpenFont("../graphiques/fonts/space_age.ttf", 40);
    Texte = TTF_RenderText_Blended(police, "Cliquez pour continuer", couleur);
    longueurTexte = Texte->w;
    positionTexte.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte/2.0));
    positionTexte.y = 9*(TAILLE_FENETRE_Y)/10;
    SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
    longueurBouton = Sauvegarder->w;
    hauteurBouton = Sauvegarder->h;
    positionSauvegarder.x = ((TAILLE_FENETRE_X/2.0) - (longueurBouton/2.0));
    positionSauvegarder.y = ((TAILLE_FENETRE_Y/2.0) - (hauteurBouton/2.0));
    positionQuitter.x = positionSauvegarder.x;
    positionQuitter.y = positionSauvegarder.y + 75;
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
                SDL_FreeSurface(Sauvegarder);
                SDL_FreeSurface(Quitter);
                SDL_FreeSurface(ecran);
                if(test_souris_rectangle(positionSauvegarder,xm,ym))
                {
                    Sauvegarder = IMG_Load("../graphiques/images/Sauvegarder_Pressé.png");
                }
                if(!test_souris_rectangle(positionSauvegarder,xm,ym))
                {
                    Sauvegarder = IMG_Load("../graphiques/images/Sauvegarder.png");
                }
                if(test_souris_rectangle(positionQuitter,xm,ym))
                {
                    Quitter = IMG_Load("../graphiques/images/Quitter_Pressé.png");
                }
                if(!test_souris_rectangle(positionQuitter,xm,ym))
                {
                    Quitter = IMG_Load("../graphiques/images/Quitter.png");
                }
                SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
                SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
                SDL_BlitSurface(Sauvegarder, NULL, ecran, &positionSauvegarder);
                SDL_BlitSurface(Quitter, NULL, ecran, &positionQuitter);
                SDL_Flip(ecran);
                break;
                
                /*Chargement des menus lors d'un clic sur un bouton */
			case SDL_MOUSEBUTTONUP:
                
                /* Sauvegarder */
                if(test_souris_rectangle(positionSauvegarder,evenement.button.x,evenement.button.y))
				{
                    continuer = 0;
                    for (i=0; i<30; i++)
                    {
                        SDL_SetAlpha(Noir, SDL_SRCALPHA, 20);
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(imageDeFond);
                    SDL_FreeSurface(Sauvegarder);
                    SDL_FreeSurface(Quitter);
                    menu_creation_sauvegarde(un_terrain_espace, un_jeu);
				}
                
                /* Quitter le jeu */
                if(test_souris_rectangle(positionQuitter,evenement.button.x,evenement.button.y))
				{
                    continuer = 0;
                    for (i=0; i<30; i++)
                    {
                        SDL_SetAlpha(Noir, SDL_SRCALPHA, 20);
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(imageDeFond);
                    SDL_FreeSurface(Sauvegarder);
                    SDL_FreeSurface(Quitter);
                    exit(0);
				}
        }
    }
}

void nouvelle_partie(void)
{
    /*Initialisation des variables*/
    SDL_Surface *ecran, *imageDeFond, *Texte, *Texte2, *Texte3, *Texte4, *Texte5, *Noir;
    TTF_Font *police;
    SDL_Color couleur= {255, 255, 255};
    SDL_Rect positionTexte, positionTexte2, positionTexte3, positionTexte4, positionTexte5;
    SDL_Event evenement;
    Terrain_espace *un_terrain_espace;
    Jeu *jeu;
    Planete *terre;
	Joueur *joueur;
    Flotte *flotte;
    Unite *unite1;
    Unite *unite2;
    
	Flotte *flotte2;
    Unite *unite3;
    Unite *unite4;
    int b = 255, i, continuer = 1;
	double longueurTexte, longueurTexte2, longueurTexte3, longueurTexte4, longueurTexte5;

	char nom_joueur[]="Pierre";
	char nom_terre[]="terre";
	char nom_jupiter[]="jupiter";
	char nom_venus[]="venus";

    
    
    /*CHARGEMENT*/
    
    /* Initialisation de l'écran et des images */
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../graphiques/images/Fond_Nouvelle_Partie.png");
    Noir = SDL_LoadBMP("../graphiques/images/Noir.bmp");
    
    /* Chargement du titre */
    TTF_Init();
    police = TTF_OpenFont("../graphiques/fonts/space_age.ttf", 60);
    Texte = TTF_RenderText_Blended(police, "Conquest Of Space", couleur);
    longueurTexte = Texte->w;
    positionTexte.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte/2.0));
    positionTexte.y = 1*(TAILLE_FENETRE_Y)/10;
    
    /* Chargement du texte */
    police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 40);
    Texte2 = TTF_RenderText_Blended(police, "Les Etats-Unis veulent a tout prix", couleur);
    longueurTexte2 = Texte2->w;
    positionTexte2.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte2/2.0));
    positionTexte2.y = 4*(TAILLE_FENETRE_Y)/10;
    
    Texte3 = TTF_RenderText_Blended(police, "trouver le secret de la vie pour faire renaitre", couleur);
    longueurTexte3 = Texte3->w;
    positionTexte3.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte3/2.0));
    positionTexte3.y = 5*(TAILLE_FENETRE_Y)/10;
    
    Texte4 = TTF_RenderText_Blended(police, "Billy Mays. BLABLABLABLA. Aidez-les !!", couleur);
    longueurTexte4 = Texte4->w;
    positionTexte4.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte4/2.0));
    positionTexte4.y = 6*(TAILLE_FENETRE_Y)/10;
    
    /* Chargement du "Cliquez pour continuer" */
    police = TTF_OpenFont("../graphiques/fonts/space_age.ttf", 40);
    Texte5 = TTF_RenderText_Blended(police, "Cliquez pour continuer", couleur);
    longueurTexte5 = Texte5->w;
    positionTexte5.x = ((TAILLE_FENETRE_X/2.0) - (longueurTexte5/2.0));
    positionTexte5.y = 9*(TAILLE_FENETRE_Y)/10;
    
    
    /*AFFICHAGE*/
    
    /*Animation de l'apparition du menu*/
    while (b>=0) {
        SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
        SDL_BlitSurface(Noir, NULL, ecran, NULL);
        b = b-50;
        SDL_Flip(ecran);
        SDL_FreeSurface(ecran);
        SDL_BlitSurface(imageDeFond, NULL, ecran, NULL);
        SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
        SDL_BlitSurface(Texte2, NULL, ecran, &positionTexte2);
        SDL_BlitSurface(Texte3, NULL, ecran, &positionTexte3);
        SDL_BlitSurface(Texte4, NULL, ecran, &positionTexte4);
        SDL_BlitSurface(Texte5, NULL, ecran, &positionTexte5);
    }
    
    /*Initialisation du terrain et du jeu (A MODIFIER)*/
    
	un_terrain_espace = creer_terrain_espace(20, 15);
    modification_terrain_espace(un_terrain_espace, 'E');
    
    ajouter_planete_terrain_espace(un_terrain_espace, 2, 1, nom_terre);
    ajouter_planete_terrain_espace(un_terrain_espace, 4, 3, nom_jupiter);
	ajouter_planete_terrain_espace(un_terrain_espace, 0, 3, nom_venus);
    affiche_terrain_espace(un_terrain_espace);
    
    terre = get_planete_terrain_espace(un_terrain_espace, 2, 1);
    
	joueur = creer_joueur(nom_joueur, 0, false);
	jeu = creer_jeu();
    ajouter_joueur(jeu, joueur);
    
    flotte = creer_flotte();
    unite1 = creer_unite(1, 1, 1, 1, 1, 10);
    unite2 = creer_unite(2, 2, 2, 2, 2, 10);
    
	flotte2 = creer_flotte();
    unite3 = creer_unite(3, 3, 3, 3, 3, 10);
    unite4 = creer_unite(4, 4, 4, 4, 4, 10);
    
	ajouter_planete_joueur(&jeu->tab_joueur[0], terre);
	afficher_planete(jeu->tab_joueur[0].tab_planete[0]);
    
    modification_production_planete(jeu->tab_joueur[0].tab_planete[0], 100, 50, 10, 100);
    
    ajouter_unite_flotte(flotte, unite1);
    ajouter_unite_flotte(flotte, unite2);
    
	ajouter_unite_flotte(flotte2, unite3);
    ajouter_unite_flotte(flotte2, unite4);
    
	ajouter_flotte_jeu(jeu, un_terrain_espace, flotte, 0, 2, 2);
	ajouter_flotte_jeu(jeu, un_terrain_espace, flotte2, 0, 5, 5);
    
	creer_vision_jeu(jeu, un_terrain_espace);
    
    /* Attente du clic */
    while(continuer)
	{
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
            case SDL_MOUSEBUTTONUP :
                
                /*Disparition du menu et affichage du jeu*/
                for (i=0; i<10; i++)
                {
                    SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                    SDL_BlitSurface(Noir, NULL, ecran, NULL);
                    SDL_Flip(ecran);
                }
                SDL_FreeSurface(ecran);
                SDL_FreeSurface(Texte);
                SDL_FreeSurface(imageDeFond);
                affichage_ecran(jeu, un_terrain_espace);
        }
    }
}

void ecran_titre(void)
{
    /* Initialisation des variables */
    SDL_Surface *ecran, *imageDeFond, *Titre, *Titre_Anime, *Texte, *Noir, *FondMenu, *Petit_Titre, *NouvellePartie, *Charger, *Quitter;
    TTF_Font *police;
    double a = 0.0, b = 1, X = TAILLE_FENETRE_X, Y = TAILLE_FENETRE_Y;
	double longueurTitre, hauteurTitre, longueurTexte;
    int continuer = 1, xm = 0, ym = 0, i;
	SDL_Rect positionTitre, positionTexte, positionPetit_Titre, positionNouvellePartie, positionCharger, positionQuitter;
    SDL_Event clic_touche;
	SDL_Color couleur= {255, 255, 255};
    
    
    /*CHARGEMENT*/
    
    /* Chargement des images */
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(X, Y, 32, SDL_HWSURFACE);
    imageDeFond = IMG_Load("../graphiques/images/Fond_titre.png");
    Titre = IMG_Load("../graphiques/images/Titre.png");
    Noir = SDL_LoadBMP("../graphiques/images/Noir.bmp");
    FondMenu = IMG_Load("../graphiques/images/FondMenu.png");
    Petit_Titre = IMG_Load("../graphiques/images/Petit_Titre.png");
    NouvellePartie = IMG_Load("../graphiques/images/Nouvelle_Partie.png");
    Charger = IMG_Load("../graphiques/images/Charger.png");
    Quitter = IMG_Load("../graphiques/images/Quitter.png");

    
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
        SDL_FreeSurface(ecran);
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
    police = TTF_OpenFont("../graphiques/fonts/space_age.ttf", 40);
    Texte = TTF_RenderText_Blended(police, "Cliquez pour continuer", couleur);
    longueurTexte = Texte->w;
    positionTexte.x = ((X/2.0) - (longueurTexte/2.0));
    positionTexte.y = 9*(Y)/10;
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
                
                /* Animation à l'affichage du menu */
                while (b>=0) {
                    double longueurPetit_Titre = Petit_Titre->w;
                    double longueurBouton = NouvellePartie->w;
                    double hauteurBouton = NouvellePartie->h;
                    SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
                    SDL_BlitSurface(Noir, NULL, ecran, NULL);
                    b = b-10;
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
    continuer = 1;
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
                SDL_FreeSurface(ecran);
                if(test_souris_rectangle(positionNouvellePartie,xm,ym))
                {
                    NouvellePartie = IMG_Load("../graphiques/images/Nouvelle_Partie_Pressé.png");
                }
                if(!test_souris_rectangle(positionNouvellePartie,xm,ym))
                {
                    NouvellePartie = IMG_Load("../graphiques/images/Nouvelle_Partie.png");
                }
                if(test_souris_rectangle(positionCharger,xm,ym))
                {
                    Charger = IMG_Load("../graphiques/images/Charger_Pressé.png");
                }
                if(!test_souris_rectangle(positionCharger,xm,ym))
                {
                    Charger = IMG_Load("../graphiques/images/Charger.png");
                }
                if(test_souris_rectangle(positionQuitter,xm,ym))
                {
                    Quitter = IMG_Load("../graphiques/images/Quitter_Pressé.png");
                }
                if(!test_souris_rectangle(positionQuitter,xm,ym))
                {
                    Quitter = IMG_Load("../graphiques/images/Quitter.png");
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
                    for (i=0; i<10; i++)
                    {
                        SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(FondMenu);
                    SDL_FreeSurface(Petit_Titre);
                    SDL_FreeSurface(NouvellePartie);
                    SDL_FreeSurface(Charger);
                    SDL_FreeSurface(Quitter);
                    nouvelle_partie();
				}
                
                /* Charger une partie */
				if(test_souris_rectangle(positionCharger,clic_touche.button.x,clic_touche.button.y))
				{
                    continuer = 0;
                    for (i=0; i<10; i++)
                    {
                        SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
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
                    menu_chargement_sauvegarde();
				}
                
                /* Quitter le jeu */
                if(test_souris_rectangle(positionQuitter,clic_touche.button.x,clic_touche.button.y))
				{
                    continuer = 0;
                    for (i=0; i<10; i++)
                    {
                        SDL_SetAlpha(Noir, SDL_SRCALPHA, 50);
                        SDL_BlitSurface(Noir, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                    }
                    SDL_FreeSurface(FondMenu);
                    SDL_FreeSurface(Petit_Titre);
                    SDL_FreeSurface(NouvellePartie);
                    SDL_FreeSurface(Charger);
                    SDL_FreeSurface(Quitter);
                    SDL_Quit();
                    exit(0);
				}
        }
    }
    pause();
}


bool attaque_ecran(Jeu * jeu,Terrain_combat * un_terrain_combat, SDL_Rect pos,Flotte* flotte1,Flotte * flotte2)
{int p;
	int i;
	Case_terrain_combat * une_case;
	Unite * unite;
	une_case = get_selection(un_terrain_combat);
	pos=coordonnee_case_du_clic(pos);
	p=0;
	if(((peut_attaquer_hor_vert(un_terrain_combat, get_unite(une_case),pos.x,pos.y))||(peut_attaquer_diag(un_terrain_combat, get_unite(une_case),pos.x,pos.y)))&&get_pt_action_joueur(get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu)))>0){
	p=attaquer(un_terrain_combat,get_unite(une_case),pos.x,pos.y);}
	if((p==0)||(p==1)){
	return p;
	}else if(p==-2)
	{
		une_case = get_case_terrain_combat(un_terrain_combat,pos.x,pos.y);
		unite=get_unite(une_case);
		i=get_indice_joueur_unite(unite);
		if(i==0)
		{
			supprimer_unite_flotte(un_terrain_combat,flotte1,unite);
		}else if(i==1){supprimer_unite_flotte(un_terrain_combat,flotte2,unite);}
		return 0;
	}
	return 0;
}

void affichage_ecran_combat(Jeu* jeu ,Terrain_combat *un_terrain_combat,Flotte* flotte1,Flotte * flotte2)
{
	SDL_Rect pos_clic,pos_texte,pos_interface, position_affichage_carte,position_passer,pos_attaquer, pos_texte2;
	SDL_Surface *ecran = NULL;
	SDL_Surface *interface = NULL;
	SDL_Surface *carte = NULL;
	SDL_Surface* passer, *attaquer =NULL;
	SDL_Surface* texte =NULL;
	SDL_Surface* texte2 =NULL;

	TTF_Font *police = NULL;
	SDL_Color couleur_police = {255,255,255};
	char infos[255] = "";
	char infos2[255] = "";

	bool continuer,attend_attaque, test, attaque_reussi;
	SDL_Event evenement;

	Uint32 couleur;
	
	continuer=1;attend_attaque=1;
	pos_interface.x=X_INTERFACE;
	pos_interface.y=Y_INTERFACE;
	position_affichage_carte.x=0;
	position_affichage_carte.y=0;
	initialise_sdl_rect(&pos_attaquer,X_BOUTON_ATTAQUER,Y_BOUTON_ATTAQUER,200,50);
	initialise_sdl_rect(&position_passer,X_BOUTON_PASSER,X_BOUTON_PASSER,200,50);
	test=1;
	 if (SDL_Init(SDL_INIT_VIDEO) == -1) /*Démarrage de la SDL. Si erreur :*/
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); /* Écriture de l'erreur*/
        exit(EXIT_FAILURE); /* On quitte le programme*/
    }
	if(TTF_Init() == -1)
	{
    	fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
   		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("Conquest of Space", "COS");
  	ecran =SDL_SetVideoMode(TAILLE_FENETRE_X,TAILLE_FENETRE_Y,NOMBRE_BITS_COULEUR,SDL_HWSURFACE|SDL_RESIZABLE|SDL_DOUBLEBUF);
	  if (ecran == NULL) /*Si l'ouverture a échoué, on le note et on arrête*/
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
	couleur = SDL_MapRGB(ecran->format,150,0,0);
	SDL_FillRect(ecran, NULL, couleur);
	SDL_Flip(ecran);

	couleur = NOIR;
	interface = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y/3, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(interface, NULL, couleur);
	carte = affiche_ecran_terrain_combat(un_terrain_combat);

	attaquer= IMG_Load("../graphiques/images/bouton.png");
	passer= IMG_Load("../graphiques/images/bouton.png");
	SDL_BlitSurface(carte, NULL, ecran, &position_affichage_carte);
	SDL_BlitSurface(interface, NULL, ecran, &pos_interface);
	SDL_BlitSurface(attaquer, NULL, interface, &pos_attaquer);
	SDL_BlitSurface(passer, NULL, interface, &position_passer);
	position_passer.y =Y_BOUTON_PASSER+Y_INTERFACE;
	pos_attaquer.y =Y_BOUTON_ATTAQUER+Y_INTERFACE;
	SDL_Flip(ecran);


	police = TTF_OpenFont("../graphiques/fonts/space_age.ttf",16);TTF_SetFontStyle(police, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

	pos_texte.x=X_TEXTE;pos_texte.y=Y_TEXTE;
	SDL_EnableKeyRepeat(100, 5);

	while(continuer)
	{
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
			case SDL_QUIT:
			continuer =0;
			break;
			case SDL_MOUSEBUTTONUP: /* Clic de la souris */printf("CLIC!");
				pos_clic.x=evenement.button.x + position_affichage_carte.x;
				pos_clic.y=evenement.button.y + position_affichage_carte.y;
				if(test_souris_rectangle(position_passer,pos_clic.x,pos_clic.y))
				{
					passer_tour_combat(jeu,un_terrain_combat);
					printf("Passe le tour ! \n");
				}
				else if(test_souris_rectangle(pos_attaquer,pos_clic.x,pos_clic.y))
				{
					if(get_une_case_selectionnee(un_terrain_combat)){
						sprintf(infos2,"Preparation de l'attaque");
						texte2 = TTF_RenderText_Solid(police,infos2,couleur_police);
						test=SDL_BlitSurface(texte2, NULL, ecran, &pos_texte2);SDL_Flip(ecran);
						printf("BOOL : %d \n",test);
						while(attend_attaque){
							SDL_WaitEvent(&evenement);
							switch (evenement.type)
							{
								case SDL_MOUSEBUTTONUP: /* Clic de la souris */
								printf("attaquons?\n");
								pos_clic.x=evenement.button.x + position_affichage_carte.x;
								pos_clic.y=evenement.button.y + position_affichage_carte.y;
								attaque_reussi=attaque_ecran(jeu,un_terrain_combat,pos_clic,flotte1, flotte2);
								if(attaque_reussi){
									sprintf(infos2,"Attaquons !");
									texte2 = TTF_RenderText_Solid(police,infos2,couleur_police);
									SDL_BlitSurface(texte2, NULL, ecran, &pos_texte2);
								}
								attend_attaque=0;
								break;
							}
						}
						printf("fin du while \n");attend_attaque=1;
					}
				}
				else{
					selection(jeu,un_terrain_combat,pos_clic);
					affiche_deplacement_unite(un_terrain_combat, pos_clic);
					carte=affiche_ecran_terrain_combat(un_terrain_combat);
					affiche_info_unite(un_terrain_combat,infos);
					texte = TTF_RenderText_Solid(police,infos,couleur_police);
				}
			break;
			case SDL_KEYUP:
			printf("%d,%d\n",position_affichage_carte.x,position_affichage_carte.y);
			break;
			case SDL_KEYDOWN: /* Si appui sur une touche */
            	switch (evenement.key.keysym.sym)
            	{
            	    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
              	    	continuer = 0;
                    break;

					case SDLK_z: /*Flèche haut*/
               			position_affichage_carte.y--;
                	break;
            		case SDLK_s: /* Flèche bas*/
            	   		position_affichage_carte.y++;
           		    break;
        	    	case SDLK_d: /* Flèche droite*/
               			position_affichage_carte.x++;
               		break;
  	      	    	case SDLK_q: /*Flèche gauche*/
  	     	        	position_affichage_carte.x--;
             	    break;
					case SDLK_p: /*Flèche gauche*/
  	     	        	passer_tour_combat(jeu,un_terrain_combat);
             	    break;
  	      	    	case SDLK_a:
						printf("appuie sur a\n");
						if(get_une_case_selectionnee(un_terrain_combat)){
						sprintf(infos2,"Preparation de l'attaque");
						texte2 = TTF_RenderText_Solid(police,infos2,couleur_police);
						test=SDL_BlitSurface(texte2, NULL, ecran, &pos_texte2);
						printf("BOOL : %d \n",test);
						while(attend_attaque){
							SDL_WaitEvent(&evenement);
							switch (evenement.type)
							{
								case SDL_MOUSEBUTTONUP: /* Clic de la souris */
								printf("attaquons?\n");
								pos_clic.x=evenement.button.x + position_affichage_carte.x;
								pos_clic.y=evenement.button.y + position_affichage_carte.y;
								attaque_reussi=attaque_ecran(jeu,un_terrain_combat,pos_clic,flotte1, flotte2);
								if(attaque_reussi){
									sprintf(infos2,"Attaquons !");
									texte2 = TTF_RenderText_Solid(police,infos2,couleur_police);
									SDL_BlitSurface(texte2, NULL, ecran, &pos_texte2);
								}
								attend_attaque=0;
								if(get_pt_action_joueur(get_ieme_joueur_jeu(jeu,get_joueur_en_cours_combat(jeu)))<=0){
		passer_tour_combat(jeu,un_terrain_combat);}
								break;
							}
						}
							printf("fin du while \n");attend_attaque=1;
						}
             	    break;
				default:
                    break;

            }
            break;
		}

		SDL_FillRect(ecran, NULL, couleur);
		SDL_BlitSurface(carte, &position_affichage_carte,  ecran,NULL);
		SDL_BlitSurface(interface, NULL, ecran, &pos_interface);
		SDL_BlitSurface(texte, NULL, ecran, &pos_texte);
		SDL_Flip(ecran);
	}





	TTF_CloseFont(police);
	TTF_Quit();
	SDL_FreeSurface(interface);
	SDL_FreeSurface(texte);
	SDL_FreeSurface(carte);
    SDL_Quit();
}

void lancer_combat_ecran(Jeu *jeu,Terrain_combat * un_combat, Flotte* flotte1,Flotte * flotte2)
{
	un_combat=creer_terrain_combat(10,5);
	modification_terrain_combat(un_combat,'E');
	placer_unite_flotte_en_haut(un_combat,flotte1);
	placer_unite_flotte_en_bas(un_combat,flotte2);
	affichage_ecran_combat(jeu ,un_combat,flotte1,flotte2);




}
