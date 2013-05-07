#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"
#include "SDL_framerate.h"
#else
/*#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_framerate.h>*/
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#endif

#include "jeu.h"
#include "constante.h"
#include "terrain_espace.h"
#include "terrain_combat.h"
#include <math.h>

bool test_souris_rectangle (SDL_Rect taille_surface, int x, int y) /*Va tester si le clic souris c'est fait dans un rectangle, utile pour les menus*/
{
	if((x > taille_surface.x) && (x< taille_surface.x + taille_surface.w) && (y > taille_surface.y) && (y< taille_surface.y + taille_surface.h))
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

void afficher_infobulle(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, int x, int y)
{
    SDL_Surface *infobulle = NULL;
    SDL_Rect position_infobulle = {x, y, 200, 100};

    infobulle = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    SDL_FillRect(infobulle, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
    SDL_BlitSurface(infobulle, NULL, ecran, &position_infobulle);
    SDL_Flip(ecran);
}

/*fonctions d'affichage de la carte*/
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

SDL_Surface* affichage_creation_unite(Case_terrain_espace *une_case_terrain_espace, SDL_Surface *panneau_unite)
{
    SDL_Surface *unite;
    SDL_Surface *surface_texte_unite;
    SDL_Rect position_unite;
    SDL_Rect position_texte_unite;
    char texte_unite[100];
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    Planete *une_planete = get_planete(une_case_terrain_espace);
    int i;

    police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 14);
    unite = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    SDL_FillRect(unite, NULL, SDL_MapRGB(unite->format, 60, 60, 60));
    SDL_SetColorKey(unite, SDL_SRCCOLORKEY, SDL_MapRGB(unite->format, 60, 60, 60));

    for(i=0;i<1;i++)
    {
        if(((i + 1)== une_planete->unite_en_cours) && (une_planete->unite_nb_tour_restant != 0))
        {
            SDL_FillRect(unite, NULL, SDL_MapRGB(panneau_unite->format, 100, 0, 0));
        }
        else
        {
            SDL_FillRect(unite, NULL, SDL_MapRGB(panneau_unite->format, 0, 200, 0));
        }
        sprintf(texte_unite, "Unite %d", i + 1);
        surface_texte_unite = TTF_RenderText_Blended(police, texte_unite, couleur_blanche);
        initialise_sdl_rect(&position_unite, 10, 20 + 120*i, 0, 0);
        SDL_BlitSurface(unite, NULL, panneau_unite, &position_unite);
        initialise_sdl_rect(&position_texte_unite, 10, 20 + 120 *i, 0, 0);
        SDL_BlitSurface(surface_texte_unite, NULL, panneau_unite, &position_texte_unite);
        if(une_planete->unite_nb_tour_restant > 0)
        {
            sprintf(texte_unite, "Tour %d", une_planete->unite_nb_tour_restant);
            surface_texte_unite = TTF_RenderText_Blended(police, texte_unite, couleur_blanche);
            initialise_sdl_rect(&position_texte_unite, 10, 40 + 120 *i, 0, 0);
            SDL_BlitSurface(surface_texte_unite, NULL, panneau_unite, &position_texte_unite);
        }
    }

    TTF_CloseFont(police);
    SDL_FreeSurface(unite);
    SDL_FreeSurface(surface_texte_unite);

    return panneau_unite;
}

SDL_Surface* affichage_planete(Case_terrain_espace *une_case_terrain_espace, SDL_Surface *info_planete)
{
    SDL_Surface *planete = NULL;
    SDL_Surface *fond_planete = NULL;
    SDL_Surface *batiment;
    SDL_Surface *bouton_unite;
    SDL_Rect position_texte;
    SDL_Rect position_batiment;
    SDL_Rect position_bouton_unite;
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    char texte_planete[200] = "";
    char texte_batiment[100] = "";
    Planete *une_planete = get_planete(une_case_terrain_espace);
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
		if((i == une_planete->batiment_en_cours) && (une_planete->batiment_nb_tour_restant != 0))
		{
			batiment = IMG_Load("../graphiques/images/batiment_selectionne.png");
		}

        sprintf(texte_batiment, "%d", une_planete->batiment[i]);
        planete = TTF_RenderText_Blended(police, texte_batiment, couleur_blanche);
        initialise_sdl_rect(&position_texte, 15 + 120 * i, 40, 0, 0);
        initialise_sdl_rect(&position_batiment, 10 + 120*i, 35, 0, 0);
        SDL_BlitSurface(batiment, NULL, fond_planete, &position_batiment);
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
	SDL_Surface *une_unite = NULL;
	SDL_Surface *bouton_coloniser = NULL;
	SDL_Rect position_texte = {10, 10, 0, 0};
    SDL_Rect position_une_unite;
	SDL_Rect position_bouton_coloniser = {TAILLE_FENETRE_X - 150, 35, 0, 0};
    int i;
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    char texte_flotte[200] = "";
    Flotte *une_flotte = un_jeu->selection_flotte;
	Planete *une_planete = get_planete_terrain_espace(un_terrain_espace, une_flotte->x_flotte, une_flotte->y_flotte);

	/*affichage des informations d'une flotte*/
    police = TTF_OpenFont("../graphiques/fonts/charcoalcy.ttf", 14);
    info_flotte = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    SDL_FillRect(info_flotte, NULL, SDL_MapRGB(info_flotte->format, 60, 60, 60));
    SDL_SetColorKey(info_flotte, SDL_SRCCOLORKEY, SDL_MapRGB(info_flotte->format, 60, 60, 60));

    sprintf(texte_flotte, "Coordonnes de la flotte: %d %d, pt mouvement %d, taille : %d", une_flotte->x_flotte, une_flotte->y_flotte, une_flotte->pt_mouvement_espace_flotte,une_flotte->taille_flotte);
    flotte = TTF_RenderText_Blended(police, texte_flotte, couleur_blanche);
    SDL_BlitSurface(flotte, NULL, info_flotte, &position_texte);

	/*affichage des unités*/
    une_unite = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    for(i=0; i<une_flotte->taille_flotte;i++)
    {
        if(un_jeu->tab_unite_selectionnee[i] == true)
        {
            SDL_FillRect(une_unite, NULL, SDL_MapRGB(info_flotte->format, 100, 0, 0));
        }
        else
        {
            SDL_FillRect(une_unite, NULL, SDL_MapRGB(info_flotte->format, 0, 200, 0));
        }
        initialise_sdl_rect(&position_une_unite, 10 + 120*i, 35, 0, 0);
        SDL_BlitSurface(une_unite, NULL, info_flotte, &position_une_unite);
        sprintf(texte_flotte, "%d/%d", une_flotte->tab_unite[i].pt_vie, une_flotte->tab_unite[i].pt_vie_total);
        flotte = TTF_RenderText_Blended(police, texte_flotte, couleur_blanche);
        initialise_sdl_rect(&position_texte, 15 + 120*i, 40, 0, 0);
        SDL_BlitSurface(flotte, NULL, info_flotte, &position_texte);
    }

	/*affichage du bouton pour coloniser une planète*/
	if((une_planete != NULL) && (!get_planete_colonisee(une_planete)))
	{
		bouton_coloniser = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
		SDL_FillRect(bouton_coloniser, NULL, SDL_MapRGB(info_flotte->format, 0, 0, 200));
		SDL_BlitSurface(bouton_coloniser, NULL, info_flotte, &position_bouton_coloniser);
	}

    TTF_CloseFont(police);
    SDL_FreeSurface(flotte);
    SDL_FreeSurface(une_unite);
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
	SDL_Surface *planete = NULL;
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
	planete = IMG_Load("../graphiques/images/2.png");
	image_une_case = IMG_Load("../graphiques/images/quadrillage.png");
    fond = IMG_Load("../graphiques/images/fond.png");
    SDL_BlitSurface(fond, NULL, carte, &position);
	for(i=0;i< un_terrain_espace->taille_espace_x;i++)
	{
		for(j=0;j< un_terrain_espace->taille_espace_y;j++)
		{
			position.x = i * 100;
			position.y = j *100;
			une_case = get_case_terrain_espace(un_terrain_espace, i, j);
			if(une_case->type_case_terrain_espace == 'P')
			{
			    position_planete.x = (i * 100);
                position_planete.y = (j * 100);
                SDL_BlitSurface(planete, NULL, carte, &position_planete);
			}
			SDL_BlitSurface(image_une_case, NULL, carte, &position);
		}
	}

    SDL_FreeSurface(planete);
    SDL_FreeSurface(image_une_case);
    SDL_FreeSurface(fond);

	return carte;
}

SDL_Surface* creer_affichage_flotte(Terrain_espace *un_terrain_espace)
{
    SDL_Surface *carte = NULL;
	SDL_Surface *flotte = NULL;
	SDL_Rect position_flotte;
	SDL_Rect position;
	SDL_Surface *image_une_case = NULL;
	int i, j;
	Case_terrain_espace *une_case;

	position_flotte.x = 0;
	position_flotte.y = 0;
	position.x = 0;
	position.y = 0;

	carte = SDL_CreateRGBSurface(SDL_HWSURFACE, un_terrain_espace->taille_espace_x * 100, un_terrain_espace->taille_espace_y * 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	flotte = IMG_Load("../graphiques/images/vaisseau_bleu.png");
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
			    position_flotte.x = (i * 100);
                position_flotte.y = (j * 100);
                SDL_BlitSurface(flotte, NULL, carte, &position_flotte);
			}
			SDL_BlitSurface(image_une_case, NULL, carte, &position);
		}
	}

    SDL_FreeSurface(flotte);
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

	SDL_Rect position = {0, 0, 0, 0};
	SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
	SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 25 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect affichage_carte = {0, 0, 0, 0};
	SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 300, 20, 300, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};
	SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -300, TAILLE_TERRAIN_ESPACE_Y - 20, 0, 0};

	carte = creer_affichage_terrain(un_terrain_espace);

	info = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(info, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_BlitSurface(info, NULL, ecran, &position_affichage_info);

	/*Creation du terrain en entier, celui-ci est stocké en mémoire*/
	carte_flotte = creer_affichage_flotte(un_terrain_espace);
	initialise_sdl_rect(&affichage_carte, un_terrain_espace->affichage_x, un_terrain_espace->affichage_y, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y);
	SDL_BlitSurface(carte, &affichage_carte, ecran, &position_affichage_carte);
	SDL_SetColorKey(carte_flotte, SDL_SRCCOLORKEY, SDL_MapRGB(carte_flotte->format, 0, 0, 0));
	SDL_BlitSurface(carte_flotte, &affichage_carte, ecran, &position_affichage_carte);

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
	bouton_passer_tour = IMG_Load("../graphiques/images/bouton_reset.png");
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
}

void maj_affichage_carte_terrain(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, int interface_affichee)
{
    SDL_Rect position = {0, 0, 0, 0};
    SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};
    SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect affichage_carte = {0, 0, 0, 0};
    SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -300, TAILLE_TERRAIN_ESPACE_Y - 20, 0, 0};

    /*Creation du terrain en entier, celui-ci est stocké en mémoire*/
    /*carte_flotte = creer_affichage_flotte(un_terrain_espace);*/
    initialise_sdl_rect(&affichage_carte, un_terrain_espace->affichage_x, un_terrain_espace->affichage_y, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y);
    SDL_BlitSurface(tab_surface[0], &affichage_carte, ecran, &position_affichage_carte);
    SDL_SetColorKey(tab_surface[1], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(tab_surface[1], &affichage_carte, ecran, &position_affichage_carte);

    /*affichage de la barre de ressources*/
    SDL_BlitSurface(tab_surface[2], NULL, ecran, &position);

    /*affichage de la bordure*/
    SDL_BlitSurface(tab_surface[3], NULL, ecran, &position_affichage_carte);

    /*affichage bouton passer tour*/
    SDL_BlitSurface(tab_surface[10], NULL, ecran, &position_bouton_tour);

        if(interface_affichee == 0)
        {
                /*affichage de la minimap*/
                tab_surface[9] = affichage_minimap(un_terrain_espace);
                SDL_BlitSurface(tab_surface[9], NULL, ecran, &position_minimap);
        }

    SDL_Flip(ecran);
}

void maj_affichage_flotte(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface **tab_surface, int interface_affichee)
{
    SDL_Rect position = {0, 0, 0, 0};
    SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
    SDL_Rect position_mini_carte = {TAILLE_FENETRE_X - 240, TAILLE_FENETRE_Y - 158};
    SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 25 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect affichage_carte = {0, 0, 0, 0};
    SDL_Rect position_bouton_tour = {TAILLE_FENETRE_X -300, TAILLE_TERRAIN_ESPACE_Y - 20, 0, 0};

    /*Creation du terrain en entier, celui-ci est stocké en mémoire*/
    tab_surface[1] = creer_affichage_flotte(un_terrain_espace);
    initialise_sdl_rect(&affichage_carte, un_terrain_espace->affichage_x, un_terrain_espace->affichage_y, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y);
    SDL_BlitSurface(tab_surface[0], &affichage_carte, ecran, &position_affichage_carte);
    SDL_SetColorKey(tab_surface[1], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(tab_surface[1], &affichage_carte, ecran, &position_affichage_carte);

    /*affichage de l'interface*/
    SDL_BlitSurface(tab_surface[5], NULL, ecran, &position_interface);
    SDL_BlitSurface(tab_surface[6], NULL, ecran, &position_mini_carte);

    /*affichage de la barre de ressources*/
    SDL_BlitSurface(tab_surface[2], NULL, ecran, &position);

    /*affichage de la bordure*/
    SDL_BlitSurface(tab_surface[3], NULL, ecran, &position_affichage_carte);

    /*affichage bouton passer tour*/
    SDL_BlitSurface(tab_surface[10], NULL, ecran, &position_bouton_tour);

    if(interface_affichee == 3)
    {
        tab_surface[7] = affichage_flotte(un_jeu, un_terrain_espace,tab_surface[7]);
      SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
    }

    SDL_Flip(ecran);
}

void maj_affichage(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface *carte, int interface_affichee, Case_terrain_espace *une_case_terrain_espace, SDL_Surface **tab_surface)
 {
    SDL_Rect position = {0, 0, 0, 0};
    SDL_Rect position_interface = {0, TAILLE_TERRAIN_ESPACE_Y + 30, 0, 0};
    SDL_Rect position_mini_carte = {TAILLE_FENETRE_X - 240, TAILLE_FENETRE_Y - 158};
    SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 25 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
    SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 214, 35, 200, TAILLE_TERRAIN_ESPACE_Y-300};
    SDL_Rect position_minimap = {TAILLE_FENETRE_X - TAILLE_MINIMAP_X, TAILLE_FENETRE_Y - TAILLE_MINIMAP_Y, 0, 0};

   /*affichage de l'interface*/
    SDL_BlitSurface(tab_surface[5], NULL, ecran, &position_interface);
    SDL_BlitSurface(tab_surface[6], NULL, ecran, &position_mini_carte);

    /*affichage de la barre de ressources*/
    SDL_BlitSurface(tab_surface[2], NULL, ecran, &position);

        if(interface_affichee == 0)
        {
            /*affichage de la minimap*/
            tab_surface[9] = affichage_minimap(un_terrain_espace);
            SDL_BlitSurface(tab_surface[9], NULL, ecran, &position_minimap);
        }
        if(interface_affichee == 1)
        {
            tab_surface[7] = affichage_planete(une_case_terrain_espace, tab_surface[7]);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
        }
        if(interface_affichee == 2)
        {
            tab_surface[7] = affichage_planete_ennemie(une_case_terrain_espace, tab_surface[7]);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
        }
        if(interface_affichee == 3)
        {
            tab_surface[7] = affichage_flotte(un_jeu, un_terrain_espace, tab_surface[7]);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
        }
        if(interface_affichee == 4)
        {
            tab_surface[7] = affichage_flotte_ennemie(un_jeu, tab_surface[7]);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
        }
        if(interface_affichee == 5)
        {
            tab_surface[7] = affichage_planete(une_case_terrain_espace, tab_surface[7]);
            SDL_BlitSurface(tab_surface[7], NULL, ecran, &position_affichage_info);
            tab_surface[8] = affichage_creation_unite(une_case_terrain_espace, tab_surface[8]);
            SDL_BlitSurface(tab_surface[8], NULL, ecran, &position_panneau_unite);
        }

    SDL_Flip(ecran);
 }

void affichage_ecran(Jeu *un_jeu, Terrain_espace *un_terrain_espace)
{
	SDL_Surface *ecran = NULL;
	SDL_Surface *carte = NULL;
	SDL_Surface *icone = NULL;
	SDL_Surface **tab_surface;
	SDL_Rect position = {0, 0, 0, 0};
    SDL_Rect bouton_tour = {TAILLE_FENETRE_X - 30, 0, 300, 50};
	SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 300, 20, 300, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect test;
	SDL_Event event;
	int continuer = 1;
	int x = 0, y = 0;
	int i, j;
	int tps_ancien = 10,tps_nouveau = 0, timer = 0, x_info = 0, y_info = 0;
	int interface_affichee =0; /*1 pour une planete, 2 pour une planete ennemie, 3 pour une flotte, 4 pour une flotte ennemie, 5 pour la création d'unités sur une planète*/
	Case_terrain_espace *une_case_terrain_espace;

	tab_surface = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 11);
	for(j=0;j<11;j++)
	{
		tab_surface[j] = (SDL_Surface *)malloc(sizeof(SDL_Surface));
	}

	initialise_sdl_rect(&position, 0, 20, 0, 0);
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_EnableKeyRepeat(10, 10);

    icone = SDL_LoadBMP("../graphics/images/logo.bmp");
	SDL_WM_SetIcon(icone, NULL);
	ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, NOMBRE_BITS_COULEUR, SDL_HWSURFACE | SDL_DOUBLEBUF); /*Chargement du fond*/

	SDL_WM_SetCaption("Conquest of Space", NULL);
	carte = creer_affichage_terrain(un_terrain_espace);

	initialise_sdl_rect(&position, 0, 0, 0, 0);
    maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);

	initialiser_affichage(un_jeu, un_terrain_espace, ecran, carte, tab_surface);
	SDL_Flip(ecran);

	while (continuer) /*boucle d'événement principale*/
	{
/*	    tps_nouveau = SDL_GetTicks();
	    timer = tps_nouveau - tps_ancien;
	    if(timer > 10)
	    {
	        x_info = event.motion.x;
            y_info = event.motion.y;
	        afficher_infobulle(un_jeu, un_terrain_espace, ecran, tab_surface, x_info, y_info);
	    }
*/
		SDL_PollEvent(&event);
		switch(event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;
        case SDL_MOUSEMOTION:
            timer = 0;
            tps_ancien = SDL_GetTicks();
            break;
		case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
			{
                x = event.button.x;
                y = event.button.y;
                if(booleen_case_pointeur_souris(un_terrain_espace, x, y)) /*test des clics ayant lieu sur le terrain*/
                {
                    une_case_terrain_espace = case_pointeur_souris(un_terrain_espace, x, y);
                    if(une_case_terrain_espace->type_case_terrain_espace == 'P')
                    {
                        un_jeu->selection_planete = une_case_terrain_espace->planete;
						if(un_jeu->selection_planete->indice_joueur == get_indice_joueur_en_cours(un_jeu))
						{
							interface_affichee = 1;
						}
						else
						{
							interface_affichee = 2;
						}
						maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace, tab_surface);
                        reinitialiser_tableau_selection_unite(un_jeu);
                    }
                    if(une_case_terrain_espace->presence_flotte == true)
                    {
                        un_jeu->selection_flotte = une_case_terrain_espace->flotte;
						if(un_jeu->selection_flotte->indice_joueur == un_jeu->joueur_en_cours)
						{
							interface_affichee = 3;
						}
						else
						{
							interface_affichee = 4;
						}
						maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);
                        reinitialiser_tableau_selection_unite(un_jeu);
                    }
                    if(test_souris_rectangle(position_affichage_carte, x, y) && (une_case_terrain_espace->type_case_terrain_espace != 'P') && (une_case_terrain_espace->presence_flotte == false) && !(test_souris_rectangle(position_panneau_unite, x, y)))
                    {
                        interface_affichee = 0;
                        maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);
                        maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
                        reinitialiser_tableau_selection_unite(un_jeu);
                    }
				}
				if(booleen_minimap_pointeur_souris(x, y))
				{
                    test_minimap_souris(un_terrain_espace, x, y);
                    maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
				}
				if (test_souris_rectangle(bouton_tour, x, y)) /*pour passer au joueur suivant*/
				{
				    interface_affichee = 0;
					joueur_suivant(un_jeu, un_terrain_espace);
					maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);
				}
				if(interface_affichee == 1 || interface_affichee==5)
				{
				    reinitialiser_tableau_selection_unite(un_jeu);
				    /*test d'appui sur l'une des cases de batiment*/
				    for(i=0;i<6;i++)
				    {
				        initialise_sdl_rect(&test, 10+ 120*i, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
                        if(test_souris_rectangle(test, x, y))
                        {
                            une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->selection_planete->x, un_jeu->selection_planete->y);
                            creation_batiment(un_jeu->selection_planete, i);
                            maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace, tab_surface);
                        }
				    }
                    /*test d'appui sur le bouton unité*/
                    initialise_sdl_rect(&test, TAILLE_FENETRE_X -150, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
                    if(test_souris_rectangle(test, x, y))
                    {
                        une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->selection_planete->x, un_jeu->selection_planete->y);
                        interface_affichee = 5;
                        maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace, tab_surface);
                    }
				}
				if(interface_affichee == 3)
				{
					/*test d'appui sur l'une des cases d'unité*/
					for(i=0;i<5;i++)
					{
						initialise_sdl_rect(&test, 10+ 120*i, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
						if(test_souris_rectangle(test, x, y) && (SDL_GetModState() & KMOD_LCTRL))
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
					if(test_souris_rectangle(test, x, y))
					{
						colonisation_planete_flotte(un_terrain_espace, get_flotte_en_cours(un_jeu), un_jeu);
					}
					maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL, tab_surface);
				}
				if(interface_affichee == 5)
				{
                    /*test d'appui sur l'une des cases d'unité*/
                    for(i=0;i<1;i++)
                    {
                        initialise_sdl_rect(&test, TAILLE_TERRAIN_ESPACE_X - 190, 40 + 120*i, 100, 100);
                        if(test_souris_rectangle(test, x, y))
                        {
                            une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->selection_planete->x, un_jeu->selection_planete->y);
                            creation_unite_planete(&un_jeu->tab_joueur[un_jeu->joueur_en_cours], get_planete(une_case_terrain_espace), i + 1);
                            maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace, tab_surface);
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
                            deplacement_unite_flotte(un_jeu, &un_jeu->tab_joueur[un_jeu->joueur_en_cours], un_terrain_espace, un_jeu->selection_flotte, x/100, y/100);
							/*maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL);*/
							maj_affichage_flotte(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
                        }
						else
                        {
							deplacement_flotte(&un_jeu->tab_joueur[un_jeu->joueur_en_cours], un_terrain_espace, un_jeu->selection_flotte, x/100, y/100);
                            /*maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL);*/
                            maj_affichage_flotte(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
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
            maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
            break;
		}

	}
	for(i=0;i<11;i++)
	{
	    SDL_FreeSurface(tab_surface[i]);
	}
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(carte);
	SDL_FreeSurface(icone);
	TTF_Quit();
	SDL_Quit();
}


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
/*
void ecran_titre(void)
{
    SDL_Surface *ecran, *imageDeFond_Depart, *imageDeFond, *Titre, *Titre2, *Texte, *Noir, *FondMenu_Depart, *FondMenu, *Petit_Titre_Depart, *Petit_Titre, *NouvellePartie, *Charger, *Quitter;
    TTF_Font *police;
	double longueurPetit_Titre_Depart;
    double a = 0.0, b = 1, X = TAILLE_FENETRE_X, Y = TAILLE_FENETRE_Y;
	double longueurTitre;
	double hauteurTitre;
	double largeurFondMenu_Depart;
	double largeurFond2;
	double longueurTexte;
	int hauteurFond;
	SDL_Rect positionFond;
	SDL_Rect positionTitre, positionTexte, positionPetit_Titre, positionNouvellePartie, positionCharger, positionQuitter;
    SDL_Event clic_touche;
	SDL_Color couleur= {255, 255, 255};
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(X, Y, 32, SDL_HWSURFACE);
    imageDeFond_Depart = IMG_Load("../graphiques/images/Fond_titre.png");
    Titre = IMG_Load("../graphiques/images/Titre.png");
    Noir = SDL_LoadBMP("../graphiques/images/Noir.bmp");
    FondMenu_Depart = IMG_Load("../graphiques/images/FondMenu.png");
    Petit_Titre_Depart = IMG_Load("../graphiques/images/Petit_Titre.png");
    longueurPetit_Titre_Depart = Petit_Titre_Depart->w;
    Petit_Titre = rotozoomSurface(Petit_Titre_Depart, 0, (X/(1.3*longueurPetit_Titre_Depart)), 0);
    NouvellePartie = IMG_Load("../graphiques/images/Nouvelle_Partie.png");
    Charger = IMG_Load("../graphiques/images/Charger.png");
    Quitter = IMG_Load("../graphiques/images/Quitter.png");

    positionFond.y = 0;
    hauteurFond = imageDeFond_Depart->h;
    imageDeFond = rotozoomSurface(imageDeFond_Depart, 0, Y/hauteurFond, 0);
    FondMenu = rotozoomSurface(FondMenu_Depart, 0, Y/hauteurFond, 0);
    largeurFond2 = imageDeFond->w;
    positionFond.x = (X-largeurFond2)/2;
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_WM_SetCaption("Conquest Of Space", NULL);

    largeurFondMenu_Depart = imageDeFond->w;
    positionFond.x = (X - largeurFondMenu_Depart)/2.0;
    positionFond.y = 0;
    while (a<(Y/hauteurFond)) {
        positionFond.x = (X - largeurFondMenu_Depart)/2.0;
        a = a+0.005;
        Titre2 = rotozoomSurface(Titre, 0, a, 2);
        longueurTitre = Titre2->w;
        hauteurTitre = Titre2->h;
        positionTitre.x = ((X/2.0) - (longueurTitre/2.0));
        positionTitre.y = ((Y/2.0) - (hauteurTitre/2.0));
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
        SDL_BlitSurface(Titre2, NULL, ecran, &positionTitre);
        SDL_Flip(ecran);
        SDL_FreeSurface(Titre2);
        SDL_FreeSurface(ecran);
        input_handle();
    }
    Titre2 = rotozoomSurface(Titre, 0, (Y/hauteurFond), 2);
    longueurTitre = Titre2->w;
    hauteurTitre = Titre2->h;
    positionTitre.x = ((X/2.0) - (longueurTitre/2.0));
    positionTitre.y = ((Y/2.0) - (hauteurTitre/2.0));
    positionFond.x = (X - largeurFondMenu_Depart)/2.0;
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_BlitSurface(Titre2, NULL, ecran, &positionTitre);
    TTF_Init();
    police = TTF_OpenFont("../graphiques/fonts/space_age.ttf", 40);
    Texte = TTF_RenderText_Blended(police, "Appuyez sur une touche", couleur);
    longueurTexte = Texte->w;
    positionTexte.x = ((X/2.0) - (longueurTexte/2.0));
    positionTexte.y = 9*(Y)/10;
    SDL_BlitSurface(Texte, NULL, ecran, &positionTexte);
    SDL_Flip(ecran);

    SDL_WaitEvent(&clic_touche);

    switch (clic_touche.type) {
        case SDL_KEYDOWN:
            while (b<256) {
                positionFond.x = (X - largeurFondMenu_Depart)/2.0;
                a = a+0.005;
                Titre2 = rotozoomSurface(Titre, 0, a, 2);
                longueurTitre = Titre2->w;
                hauteurTitre = Titre2->h;
                positionTitre.x = ((X/2.0) - (longueurTitre/2.0));
                positionTitre.y = ((Y/2.0) - (hauteurTitre/2.0));
                SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                SDL_BlitSurface(Titre2, NULL, ecran, &positionTitre);
                SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
                SDL_BlitSurface(Noir, NULL, ecran, &positionFond);
                b = b+5;
                SDL_Flip(ecran);
                SDL_FreeSurface(Titre2);
                SDL_FreeSurface(ecran);
                input_handle();
            }
            while (b>=0) {
                double longueurPetit_Titre = Petit_Titre->w;
                double longueurBouton = NouvellePartie->w;
                double hauteurBouton = NouvellePartie->h;
                SDL_SetAlpha(Noir, SDL_SRCALPHA, b);
                SDL_BlitSurface(Noir, NULL, ecran, &positionFond);
                b = b-5;
                SDL_Flip(ecran);
                SDL_FreeSurface(ecran);
                positionFond.x = (X - largeurFondMenu_Depart)/2.0;
                SDL_BlitSurface(FondMenu, NULL, ecran, &positionFond);
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
        case SDL_QUIT:
            exit(0);
    }
    pause();
}
*/

void attaque_ecran(Terrain_combat * un_terrain_combat, SDL_Rect pos)
{
	Case_terrain_combat * une_case;
	une_case = get_selection(un_terrain_combat);
	pos=coordonnee_case_du_clic(pos);
	if((peut_attaquer_hor_vert(un_terrain_combat, get_unite(une_case),pos.x,pos.y))||(peut_attaquer_diag(un_terrain_combat, get_unite(une_case),pos.x,pos.y))){
	attaquer(un_terrain_combat,get_unite(une_case),pos.x,pos.y);}
}

void affichage_ecran_combat(Jeu* jeu ,Terrain_combat *un_terrain_combat)
{
	SDL_Rect pos_clic,pos_texte,pos_interface, position_affichage_carte,position_passer,pos_attaquer;
	SDL_Surface *ecran = NULL;
	SDL_Surface *interface = NULL;
	SDL_Surface *carte = NULL;
	SDL_Surface* passer, *attaquer =NULL;
	SDL_Surface* texte =NULL;

	TTF_Font *police = NULL;
	SDL_Color couleur_police = {255,255,255};
	char infos[255] = "";

	bool continuer,attend_attaque;
	SDL_Event evenement;

	Uint32 couleur;
	continuer=1;attend_attaque=1;
	pos_interface.x=X_INTERFACE;
	pos_interface.y=Y_INTERFACE;
	position_affichage_carte.x=0;
	position_affichage_carte.y=0;
	initialise_sdl_rect(&pos_attaquer,X_BOUTON_ATTAQUER,Y_BOUTON_ATTAQUER,200,50);
	initialise_sdl_rect(&position_passer,X_BOUTON_PASSER,X_BOUTON_PASSER,200,50);

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
						printf("préparation attaque\n");
						while(attend_attaque){
							SDL_WaitEvent(&evenement);
							switch (evenement.type)
							{
								case SDL_MOUSEBUTTONUP: /* Clic de la souris */
								printf("attaquons?\n");
								pos_clic.x=evenement.button.x + position_affichage_carte.x;
								pos_clic.y=evenement.button.y + position_affichage_carte.y;
								attaque_ecran(un_terrain_combat,pos_clic);
								printf("attaquons!\n");
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
							printf("préparation attaque\n");
							while(attend_attaque){
								SDL_WaitEvent(&evenement);
								switch (evenement.type)
								{
									case SDL_MOUSEBUTTONUP: /* Clic de la souris */
									printf("attaquons?\n");
									pos_clic.x=evenement.button.x + position_affichage_carte.x;
									pos_clic.y=evenement.button.y + position_affichage_carte.y;
									attaque_ecran(un_terrain_combat,pos_clic);
									printf("attaquons!\n");
									attend_attaque=0;
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


