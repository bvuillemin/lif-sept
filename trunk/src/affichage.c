#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
#include "SDL_image.h"
#include "SDL_ttf.h"
#else
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

bool booleen_case_pointeur_souris(Terrain_espace *un_terrain_espace, int x, int y) /*Fonction qui va renvoyer la case pointée par la souris, les coordonnées x et y sont en pixels*/
{
	x = (un_terrain_espace->affichage_x + x - (TAILLE_FENETRE_X - TAILLE_TERRAIN_ESPACE_X)) / 100;
	y = (un_terrain_espace->affichage_y + y - 20) / 100;
	if ((x >= 0) && (x < un_terrain_espace->taille_espace_x) && (y >= 0) && (y < un_terrain_espace->taille_espace_y))
	{
		return true;
	}
	else return false;
}

Case_terrain_espace* case_pointeur_souris(Terrain_espace *un_terrain_espace, int x, int y) /*Fonction qui va renvoyer la case pointée par la souris, les coordonnées x et y sont en pixels*/
{
	x = (un_terrain_espace->affichage_x + x - (TAILLE_FENETRE_X - TAILLE_TERRAIN_ESPACE_X)) / 100;
	y = (un_terrain_espace->affichage_y + y - 20) / 100;
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

SDL_Surface* affichage_ressource(Jeu *un_jeu, SDL_Surface *surface_ressource)
{
    SDL_Surface *nom_ressource;
    SDL_Surface *texte_ressource;
    SDL_Surface *nombre_tour;
    SDL_Surface *bouton_passer_tour;
    SDL_Rect position;
    TTF_Font *police = NULL;
    SDL_Color couleur_blanche = {255, 255, 255};
    char ressource[200] = "";
    char tour[50] = "";

    TTF_Init();
    police = TTF_OpenFont("charcoalcy.ttf", 18);
    texte_ressource = IMG_Load("interface_ressources_g.png");

    sprintf(ressource, "Ressources :   Metal : %d   Argent : %d   Carburant : %d   Population : %d", get_metal_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]), get_argent_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]), get_carburant_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]), get_population_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]));
    nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
    position.x = 45;
    position.y = 4;
    SDL_BlitSurface(nom_ressource, NULL, texte_ressource, &position);

    sprintf(tour, "Tour en cours : %d   Joueur en cours : %d", un_jeu->tour_en_cours, un_jeu->joueur_en_cours);
    nombre_tour = TTF_RenderText_Blended(police, tour, couleur_blanche);
    position.x = TAILLE_FENETRE_X - 410;
    SDL_BlitSurface(nombre_tour, NULL, texte_ressource, &position);

    position.x = TAILLE_FENETRE_X - 70;
    bouton_passer_tour = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    SDL_FillRect(bouton_passer_tour, NULL, SDL_MapRGB(surface_ressource->format, 0, 200, 0));
    SDL_BlitSurface(bouton_passer_tour, NULL, texte_ressource, &position);

    SDL_FreeSurface(nom_ressource);
    SDL_FreeSurface(nombre_tour);
    SDL_FreeSurface(bouton_passer_tour);
    SDL_FreeSurface(surface_ressource);
    TTF_CloseFont(police);
    TTF_Quit();

    return texte_ressource;
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

    police = TTF_OpenFont("charcoalcy.ttf", 14);
    SDL_FillRect(panneau_unite, NULL, SDL_MapRGB(panneau_unite->format, 0, 0, 0));

    unite = SDL_CreateRGBSurface(SDL_SWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
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

    police = TTF_OpenFont("charcoalcy.ttf", 14);
    fond_planete = SDL_CreateRGBSurface(SDL_SRCALPHA, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    SDL_FillRect(fond_planete, NULL, SDL_MapRGB(info_planete->format, 0, 00, 0));

    sprintf(texte_planete, "Nom de la planete: %s Occupation de la planete: %d/%d Production: Metal:%d Argent:%d Carburant:%d Population:%d",
get_nom_planete(une_planete), get_taille_utilisee(une_planete), get_taille_planete(une_planete),
get_metal(une_planete), get_argent(une_planete), get_carburant(une_planete), get_population(une_planete));
    planete = TTF_RenderText_Blended(police, texte_planete, couleur_blanche);
    initialise_sdl_rect(&position_texte, 10, 10, 0, 0);
    SDL_BlitSurface(planete, NULL, fond_planete, &position_texte);

    bouton_unite = SDL_CreateRGBSurface(SDL_SWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    initialise_sdl_rect(&position_bouton_unite, TAILLE_FENETRE_X -150, 35, 100, 100);
    SDL_FillRect(bouton_unite, NULL, SDL_MapRGB(info_planete->format, 0, 0, 100));
    SDL_BlitSurface(bouton_unite, NULL, fond_planete, &position_bouton_unite);

    batiment = SDL_CreateRGBSurface(SDL_SWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    for(i=0;i<5;i++)
    {
        if((i == une_planete->batiment_en_cours) && (une_planete->batiment_nb_tour_restant != 0))
        {
            SDL_FillRect(batiment, NULL, SDL_MapRGB(info_planete->format, 100, 0, 0));
        }
        else
        {
            SDL_FillRect(batiment, NULL, SDL_MapRGB(info_planete->format, 0, 200, 0));
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

SDL_Surface* affichage_flotte(Jeu *un_jeu, SDL_Surface *info_flotte)
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

    police = TTF_OpenFont("charcoalcy.ttf", 14);
    fond_flotte = SDL_CreateRGBSurface(SDL_SWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    SDL_FillRect(fond_flotte, NULL, SDL_MapRGB(info_flotte->format, 0, 0, 0));

    sprintf(texte_flotte, "Coordonnes de la flotte: %d %d, pt mouvement %d, taille : %d", une_flotte->x_flotte, une_flotte->y_flotte, une_flotte->pt_mouvement_espace_flotte,une_flotte->taille_flotte);
    flotte = TTF_RenderText_Blended(police, texte_flotte, couleur_blanche);
    initialise_sdl_rect(&position, 10, 10, 0, 0);
    SDL_BlitSurface(flotte, NULL, fond_flotte, &position);

    une_unite = SDL_CreateRGBSurface(SDL_SWSURFACE, 100, 100, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
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
        SDL_BlitSurface(une_unite, NULL, fond_flotte, &position_une_unite);
        sprintf(texte_flotte, "%d/%d", une_flotte->tab_unite[i].pt_vie, une_flotte->tab_unite[i].pt_vie_total);
        flotte = TTF_RenderText_Blended(police, texte_flotte, couleur_blanche);
        initialise_sdl_rect(&position, 15 + 120*i, 40, 0, 0);
        SDL_BlitSurface(flotte, NULL, fond_flotte, &position);
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
	planete = IMG_Load("2.png");
	image_une_case = IMG_Load("quadrillage.png");
    fond = IMG_Load("fond.png");
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
	flotte = IMG_Load("vaisseau_bleu.png");
	image_une_case = IMG_Load("quadrillage.png");
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

void maj_affichage(Jeu *un_jeu, Terrain_espace *un_terrain_espace, SDL_Surface *ecran, SDL_Surface *carte, int interface_affichee, Case_terrain_espace *une_case_terrain_espace)
 {
	SDL_Surface *carte_flotte = NULL;
	SDL_Surface *ressource_g = NULL;
    SDL_Surface *ressource_d = NULL;
	SDL_Surface *deplacement_carte = NULL;
    SDL_Surface *interface = NULL;
    SDL_Surface *mini_carte = NULL;
    SDL_Surface *info = NULL;
    SDL_Surface *panneau_unite = NULL;
    SDL_Rect position = {0, 0, 0, 0};
    SDL_Rect position_interface = {0, TAILLE_FENETRE_Y - 158};
    SDL_Rect position_mini_carte = {TAILLE_FENETRE_X - 240, TAILLE_FENETRE_Y - 158};
	SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 20 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect affichage_carte = {0, 0, 0, 0};
	SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 300, 20, 300, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect bordure_g = {0, 50, 4, TAILLE_FENETRE_Y - 208};
    SDL_Rect bordure_d = {TAILLE_FENETRE_X - 4, 50, 4, TAILLE_FENETRE_Y - 208};
    SDL_Rect position_ressource_d = {TAILLE_FENETRE_X - 50, 0};

	info = SDL_CreateRGBSurface(SDL_SWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(info, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(info, NULL, ecran, &position_affichage_info);

    /*Creation du terrain en entier, celui-ci est stocké en mémoire*/
	carte_flotte = creer_affichage_flotte(un_terrain_espace);
	initialise_sdl_rect(&affichage_carte, 0, 0, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y);
	SDL_BlitSurface(carte, &affichage_carte, ecran, &position_affichage_carte);
	SDL_SetColorKey(carte_flotte, SDL_SRCCOLORKEY, SDL_MapRGB(carte_flotte->format, 0, 0, 0));
	SDL_BlitSurface(carte_flotte, &affichage_carte, ecran, &position_affichage_carte);

    /*affichage de la barre de ressources*/
	ressource_g = IMG_Load("interface_ressources_g.png");
	ressource_g = affichage_ressource(un_jeu, ressource_g);
	SDL_BlitSurface(ressource_g, NULL, ecran, &position);
    ressource_d = IMG_Load("interface_ressources_d.png");
	SDL_BlitSurface(ressource_d, NULL, ecran, &position_ressource_d);

    /*affichage de l'interface*/
    interface = IMG_Load("interface_bas.png");
    SDL_BlitSurface(interface, NULL, ecran, &position_interface);
    mini_carte = IMG_Load("interface_carte.png");
    SDL_BlitSurface(mini_carte, NULL, ecran, &position_mini_carte);

    /*affichage des bordures sur les côtés de la carte*/
    SDL_FillRect(ecran, &bordure_g, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_FillRect(ecran, &bordure_d, SDL_MapRGB(ecran->format, 255, 255, 255));

    panneau_unite = SDL_CreateRGBSurface(SDL_SWSURFACE, 200, TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
    SDL_FillRect(panneau_unite, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    initialise_sdl_rect(&position_panneau_unite, TAILLE_FENETRE_X - 200, 20, 200, TAILLE_TERRAIN_ESPACE_Y);

	if(interface_affichee == 1)
	{
	    info = affichage_planete(une_case_terrain_espace, info);
        SDL_BlitSurface(info, NULL, ecran, &position_affichage_info);
	}
	if(interface_affichee == 2)
	{
	    info = affichage_flotte(un_jeu, info);
        SDL_BlitSurface(info, NULL, ecran, &position_affichage_info);
	}
	if(interface_affichee == 3)
	{
	    info = affichage_planete(une_case_terrain_espace, info);
	    SDL_BlitSurface(info, NULL, ecran, &position_affichage_info);
	    panneau_unite = affichage_creation_unite(une_case_terrain_espace, panneau_unite);
        SDL_BlitSurface(panneau_unite, NULL, ecran, &position_panneau_unite);
	}

    SDL_Flip(ecran);
    SDL_FreeSurface(interface);
	SDL_FreeSurface(carte_flotte);
	SDL_FreeSurface(ressource_g);
	SDL_FreeSurface(ressource_d);
	SDL_FreeSurface(info);
	SDL_FreeSurface(panneau_unite);
	SDL_FreeSurface(mini_carte);
	SDL_FreeSurface(deplacement_carte);
 }

void affichage_ecran(Jeu *un_jeu, Terrain_espace *un_terrain_espace)
{
	SDL_Surface *ecran = NULL;
	SDL_Surface *carte = NULL;
	SDL_Rect position = {0, 0, 0, 0};
    SDL_Rect bouton_tour = {TAILLE_FENETRE_X - 30, 0, 300, 50};
	SDL_Rect position_affichage_carte = {0, 30, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect position_panneau_unite = {TAILLE_FENETRE_X - 300, 20, 300, TAILLE_TERRAIN_ESPACE_Y};
	SDL_Rect test;
	SDL_Event event;
	int continuer = 1;
	int x = 0, y = 0;
	int i, j;
	int interface_affichee =0; /*1 pour une planete, 2 pour une flotte, 3 pour la création d'unités sur une planète*/
	Case_terrain_espace *une_case_terrain_espace;

	initialise_sdl_rect(&position, 0, 20, 0, 0);
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_EnableKeyRepeat(10, 10);

	ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, NOMBRE_BITS_COULEUR, SDL_SWSURFACE); /*Chargement du fond*/
	carte = creer_affichage_terrain(un_terrain_espace);

	initialise_sdl_rect(&position, 0, 0, 0, 0);
    maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL);

	while (continuer) /*boucle d'événement principale*/
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
		case SDL_QUIT:
			continuer = 0;
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
                        interface_affichee = 1;
                        maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace);
                        reinitialiser_tableau_selection_unite(un_jeu);
                    }
                    if(une_case_terrain_espace->presence_flotte == true)
                    {
                        un_jeu->selection_flotte = une_case_terrain_espace->flotte;
                        interface_affichee = 2;
                        maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL);
                        reinitialiser_tableau_selection_unite(un_jeu);
                    }
                    if(test_souris_rectangle(position_affichage_carte, x, y) && (une_case_terrain_espace->type_case_terrain_espace != 'P') && (une_case_terrain_espace->presence_flotte == false) && !(test_souris_rectangle(position_panneau_unite, x, y)))
                    {
                        interface_affichee = 0;
                        maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL);
                        reinitialiser_tableau_selection_unite(un_jeu);
                    }
				}
				if (test_souris_rectangle(bouton_tour, x, y)) /*pour passer au joueur suivant*/
				{
				    interface_affichee = 0;
					joueur_suivant(un_jeu, un_terrain_espace);
					maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL);
				}
				if(interface_affichee == 1 || interface_affichee==3)
				{
				    reinitialiser_tableau_selection_unite(un_jeu);
				    /*test d'appui sur l'une des cases de batiment*/
				    for(i=0;i<5;i++)
				    {
				        initialise_sdl_rect(&test, 10+ 120*i, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
                        if(test_souris_rectangle(test, x, y))
                        {
                            une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->selection_planete->x, un_jeu->selection_planete->y);
                            creation_batiment(un_jeu->selection_planete, i);
                            maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace);
                        }
				    }
                    /*test d'appui sur le bouton unité*/
                    initialise_sdl_rect(&test, TAILLE_FENETRE_X -150, TAILLE_TERRAIN_ESPACE_Y + 55, 100, 100);
                    if(test_souris_rectangle(test, x, y))
                    {
                        une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->selection_planete->x, un_jeu->selection_planete->y);
                        interface_affichee = 3;
                        maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace);
                    }
				}
				if(interface_affichee == 3)
				{
                    /*test d'appui sur l'une des cases d'unité*/
                    for(i=0;i<1;i++)
                    {
                        initialise_sdl_rect(&test, TAILLE_TERRAIN_ESPACE_X - 190, 40 + 120*i, 100, 100);
                        if(test_souris_rectangle(test, x, y))
                        {
                            une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->selection_planete->x, un_jeu->selection_planete->y);
                            creation_unite_planete(&un_jeu->tab_joueur[un_jeu->joueur_en_cours], get_planete(une_case_terrain_espace), i + 1);
                            maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace);
                        }
                    }
				}
				if(interface_affichee == 2)
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
				    maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL);
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
							maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL);
                        }
						else
                        {
							deplacement_flotte(&un_jeu->tab_joueur[un_jeu->joueur_en_cours], un_terrain_espace, un_jeu->selection_flotte, x/100, y/100);
                            maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, NULL);
                        }
                    }
                }
            }
            break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_UP:
				if((un_terrain_espace->affichage_y > 0) && (un_terrain_espace->affichage_y <= (un_terrain_espace->taille_espace_y *100) - TAILLE_TERRAIN_ESPACE_Y ))
				{un_terrain_espace->affichage_y--;}
				break;
			case SDLK_DOWN:
				if((un_terrain_espace->affichage_y>=0) && (un_terrain_espace->affichage_y < (un_terrain_espace->taille_espace_y *100) - TAILLE_TERRAIN_ESPACE_Y ))
				{un_terrain_espace->affichage_y++;}
				break;
			case SDLK_RIGHT:
				if((un_terrain_espace->affichage_x >= 0) && (un_terrain_espace->affichage_x < (un_terrain_espace->taille_espace_x * 100) - TAILLE_TERRAIN_ESPACE_X))
				{un_terrain_espace->affichage_x++;}
				break;
			case SDLK_LEFT:
				if((un_terrain_espace->affichage_x>0) && (un_terrain_espace->affichage_x <= (un_terrain_espace->taille_espace_x *100) - TAILLE_TERRAIN_ESPACE_X))
				{un_terrain_espace->affichage_x--;}
				break;
			default :
				break;
			}

            if(interface_affichee == 3)
            {
                une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->selection_planete->x, un_jeu->selection_planete->y);
                maj_affichage(un_jeu, un_terrain_espace, ecran, carte, interface_affichee, une_case_terrain_espace);
            }
			break;
		}

	}
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(carte);
	TTF_Quit();
	SDL_Quit();
}

/*void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}*/




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
	fond = IMG_Load("fond.png");
    SDL_BlitSurface(fond, NULL, carte, &pos);
	quadrillage = IMG_Load("quadrillage.png");
	selection = IMG_Load("../Graphics/selection.png");

    for(j=0;j<terrain_combat->taille_combat_y;j++)
    {
        for(i=0;i<terrain_combat->taille_combat_x;i++)
        {
			pos.x=i*100;pos.y=j*100;
            une_case = get_case_terrain_combat(terrain_combat, i, j);
            if(get_presence_unite(une_case)&&(get_indice_joueur_unite(get_unite(une_case))==0))
            {	planete = IMG_Load("../Graphics/vaisseau_1.png");
				pos_plan.x=i*100;pos_plan.y=j*100;
				SDL_BlitSurface(planete,NULL,carte,&pos_plan);
            }
			else if(get_presence_unite(une_case)&&(get_indice_joueur_unite(get_unite(une_case))==1))
            {	planete = IMG_Load("../Graphics/vaisseau_2.png");
				pos_plan.x=i*100;pos_plan.y=j*100;
				SDL_BlitSurface(planete,NULL,carte,&pos_plan);
            }else if(get_presence_unite(une_case))
            {	planete = IMG_Load("../Graphics/vaisseau_3.png");
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
//	selectionner_case_combat(jeu,un_terrain_combat, pos.x, pos.y);

}
void affiche_info_unite(Terrain_combat *un_terrain_combat,char * infos)
{
	Unite * unite;
	int a,b,c,d;
	if(get_une_case_selectionnee(un_terrain_combat))
	{
		unite = get_unite(get_selection(un_terrain_combat));
		a = get_pt_vie(unite);
		b = get_pt_action(unite);
		d = get_pt_deplacement(unite);
		c = get_portee(unite);

		sprintf(infos,"pv = %d pa=%d po=%d pd=%d ",a,b,c,d);
	}
	else
	{

		sprintf(infos," ");
	}

}

void affichage_ecran_acceuil(Terrain_combat *un_terrain_combat)
{
	SDL_Surface *ecran = NULL;
	SDL_Surface *nouveau_jeu = NULL;
	SDL_Surface *charger = NULL;
	SDL_Surface* quitter =NULL;
	SDL_Rect pos_jeu,pos_charger,pos_quitter;

	Uint32 couleur;

	bool continuer;
	SDL_Event evenement;

	continuer=1;
	nouveau_jeu = IMG_Load("../Graphics/Nouvelle_Partie.png");
	charger = IMG_Load("../Graphics/Charger.png");
	quitter = IMG_Load("../Graphics/Quitter.png");
	if (SDL_Init(SDL_INIT_VIDEO) == -1) /*Démarrage de la SDL. Si erreur :*/
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); /* Écriture de l'erreur*/
        exit(EXIT_FAILURE); /* On quitte le programme*/
    }

	SDL_WM_SetCaption("Conquest of Space", "COS");
  	ecran =SDL_SetVideoMode(TAILLE_FENETRE_X,TAILLE_FENETRE_Y,NOMBRE_BITS_COULEUR,SDL_HWSURFACE|SDL_RESIZABLE|SDL_DOUBLEBUF);
	couleur = SDL_MapRGB(ecran->format,0,0,0);
	SDL_FillRect(ecran, NULL, couleur);

	pos_jeu.x=100;pos_jeu.y=2*TAILLE_FENETRE_Y/3;
	pos_charger.x=500;pos_charger.y=2*TAILLE_FENETRE_Y/3;
	pos_quitter.x=900;pos_quitter.y=2*TAILLE_FENETRE_Y/3;
	SDL_BlitSurface(nouveau_jeu, NULL, ecran, &pos_jeu);
	SDL_BlitSurface(charger, NULL, ecran, &pos_charger);
	SDL_BlitSurface(quitter, NULL, ecran, &pos_quitter);
	SDL_Flip(ecran);
	while(continuer)
	{
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
			case SDL_QUIT:
			continuer =0;
			break;
		}
	}
	SDL_FreeSurface(nouveau_jeu);
	SDL_FreeSurface(charger);
	SDL_FreeSurface(quitter);
    SDL_Quit();

}
void attaque_ecran(Terrain_combat * un_terrain_combat, SDL_Rect pos)
{
	Case_terrain_combat * une_case;
	une_case = get_selection(un_terrain_combat);
	coordonnee_case_du_clic(pos);
	attaquer(un_terrain_combat,get_unite(une_case),pos.x,pos.y);
}

void affichage_ecran_combat(Jeu* jeu ,Terrain_combat *un_terrain_combat)
{
	SDL_Rect pos_clic,pos_texte,pos_interface, position_affichage_carte;
	SDL_Surface *ecran = NULL;
	SDL_Surface *interface = NULL;
	SDL_Surface *carte = NULL;
	SDL_Surface* texte =NULL;

	TTF_Font *police = NULL;
	SDL_Color couleur_police = {255,255,255};
	char infos[255] = "";

	bool continuer;
	SDL_Event evenement;

	Uint32 couleur;
	continuer=1;
	pos_interface.x=0;
	pos_interface.y=TAILLE_FENETRE_Y - TAILLE_FENETRE_Y/3;
	position_affichage_carte.x=0;
	position_affichage_carte.y=0;

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


	couleur = SDL_MapRGB(ecran->format,0,0,0);
	interface = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y/3, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(interface, NULL, couleur);
	carte = affiche_ecran_terrain_combat(un_terrain_combat);
	SDL_BlitSurface(carte, NULL, ecran, &position_affichage_carte);
	SDL_BlitSurface(interface, NULL, ecran, &pos_interface);

	SDL_Flip(ecran);
	SDL_EnableKeyRepeat(5, 5);

	police = TTF_OpenFont("charcoalcy.ttf",16);TTF_SetFontStyle(police, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

	pos_texte.x=100;pos_texte.y=TAILLE_FENETRE_Y - TAILLE_FENETRE_Y/3;


	while(continuer)
	{
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
			case SDL_QUIT:
			continuer =0;
			break;
			case SDL_MOUSEBUTTONUP: /* Clic de la souris */
				pos_clic.x=evenement.button.x + position_affichage_carte.x;
				pos_clic.y=evenement.button.y + position_affichage_carte.y;
				selection(jeu,un_terrain_combat,pos_clic);
				affiche_deplacement_unite(un_terrain_combat, pos_clic);
				carte=affiche_ecran_terrain_combat(un_terrain_combat);
				affiche_info_unite(un_terrain_combat,infos);
				texte = TTF_RenderText_Solid(police,infos,couleur_police);
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
  	      	    case SDLK_p:
//					passer_tour_combat(jeu,un_terrain_combat);
             	    break;
  	      	    case SDLK_a:
					if(get_une_case_selectionnee(un_terrain_combat)){
					switch (evenement.type)
					{
						case SDL_MOUSEBUTTONUP: /* Clic de la souris */
							pos_clic.x=evenement.button.x + position_affichage_carte.x;
							pos_clic.y=evenement.button.y + position_affichage_carte.y;
							attaque_ecran(un_terrain_combat,pos_clic);

						break;
					}}
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


