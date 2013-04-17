#include <stdlib.h>
#include <stdio.h>
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


SDL_Surface* affichage_ressource(Jeu *un_jeu, SDL_Surface *surface_ressource)
{
    SDL_Surface *nom_ressource;
	SDL_Surface *texte_ressource;
	SDL_Surface *nombre_tour;
	SDL_Surface *bouton_passer_tour = NULL;
    SDL_Rect position;
    TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
    char ressource[200] = "";
	char tour[50] = "";

    TTF_Init();
    police = TTF_OpenFont("space_age.ttf", 14);
	texte_ressource = IMG_Load("ressource.png");

    sprintf(ressource, "Ressources:  Metal:%d  Argent:%d  Carburant:%d  Population:%d", get_metal_joueur(&un_jeu->tab_joueur[0]), get_argent_joueur(&un_jeu->tab_joueur[0]), get_carburant_joueur(&un_jeu->tab_joueur[0]), get_population_joueur(&un_jeu->tab_joueur[0]));
    nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
    position.x = 10;
    position.y = 2;
    SDL_BlitSurface(nom_ressource, NULL, texte_ressource, &position);

	sprintf(tour, "Tour en cours: %d", un_jeu->tour_en_cours);
	nombre_tour = TTF_RenderText_Blended(police, tour, couleur_blanche);
	position.x = TAILLE_FENETRE_X - 250;
	SDL_BlitSurface(nombre_tour, NULL, texte_ressource, &position);
    
	position.x = TAILLE_FENETRE_X - 30;
	bouton_passer_tour = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(bouton_passer_tour, NULL, SDL_MapRGB(surface_ressource->format, 62, 210, 76));
	SDL_BlitSurface(bouton_passer_tour, NULL, texte_ressource, &position);

    SDL_FreeSurface(nom_ressource);
	SDL_FreeSurface(nombre_tour);
	SDL_FreeSurface(bouton_passer_tour);
	SDL_FreeSurface(surface_ressource);
    TTF_CloseFont(police);
    TTF_Quit();

	return texte_ressource;
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

SDL_Surface* affichage_terrain(Terrain_espace *un_terrain_espace, SDL_Surface *carte, SDL_Surface *resultat)
{
	SDL_Rect affichage;
	SDL_Rect position;

	affichage.w = TAILLE_TERRAIN_ESPACE_X;
	affichage.h = TAILLE_TERRAIN_ESPACE_Y;

	position.x = 0;
	position.y = 0;

	affichage.x = un_terrain_espace->affichage_x;
	affichage.y = un_terrain_espace->affichage_y;

	/*SDL_FillRect(resultat, &position, SDL_MapRGB(resultat->format, 255, 255, 255));*/
	SDL_BlitSurface(carte, &affichage, resultat, &position);

	return resultat;
}

void affichage_ecran(Jeu *un_jeu, Terrain_espace *un_terrain_espace)
{
	SDL_Surface *ecran = NULL;
	SDL_Surface *carte = NULL;
	SDL_Surface *ressource = NULL;
	SDL_Surface *texte_ressource = NULL;
	SDL_Surface *deplacement_carte = NULL;
    SDL_Surface *interface = NULL;
	SDL_Rect position;
	SDL_Event event;
	int continuer = 1;

	position.x = 0;
	position.y = 20;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_EnableKeyRepeat(10, 10);
	ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, NOMBRE_BITS_COULEUR, SDL_SWSURFACE);
	interface = IMG_Load("interface.png");
    SDL_BlitSurface(interface, NULL, ecran, &position);

	position.x = 0;
	position.y = 0;
	ressource = IMG_Load("ressource.png");
	ressource = affichage_ressource(un_jeu, ressource);
	SDL_BlitSurface(ressource, NULL, ecran, &position);

	position.x = 200;
	position.y = 20;
	carte = creer_affichage_terrain(un_terrain_espace);
	deplacement_carte = SDL_CreateRGBSurface(SDL_SWSURFACE, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	deplacement_carte = affichage_terrain(un_terrain_espace, carte, deplacement_carte);
	SDL_BlitSurface(deplacement_carte, NULL, ecran, &position);

	SDL_Flip(ecran);

	while (continuer)
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
				if ((event.button.x > TAILLE_FENETRE_X - 30) && (event.button.x < TAILLE_FENETRE_X - 10) && (event.button.y > 0) && (event.button.y < 20))
				{
					joueur_suivant(un_jeu);
					position.x = 0;
					position.y = 0;
					ressource = affichage_ressource(un_jeu, ressource);
					SDL_BlitSurface(ressource, NULL, ecran, &position);
					SDL_Flip(ecran);
					position.x = 200;
					position.y = 20;
				}
			}
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_UP:
				if((un_terrain_espace->affichage_y > 0) && (un_terrain_espace->affichage_y <= (un_terrain_espace->taille_espace_y *100) -600 ))
				{un_terrain_espace->affichage_y--;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position);
				SDL_Flip(ecran);}
				break;
			case SDLK_DOWN:
				if((un_terrain_espace->affichage_y>=0) && (un_terrain_espace->affichage_y < (un_terrain_espace->taille_espace_y *100) - 600 ))
				{un_terrain_espace->affichage_y++;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position);
				SDL_Flip(ecran);}
				break;
			case SDLK_RIGHT:
				if((un_terrain_espace->affichage_x >= 0) && (un_terrain_espace->affichage_x < (un_terrain_espace->taille_espace_x * 100) -1080))
				{un_terrain_espace->affichage_x++;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position);
				SDL_Flip(ecran);}
				break;
			case SDLK_LEFT:
				if((un_terrain_espace->affichage_x>0) && (un_terrain_espace->affichage_x <= (un_terrain_espace->taille_espace_x *100) -1080))
				{un_terrain_espace->affichage_x--;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position);
				SDL_Flip(ecran);}
				break;
			default :
				break;
			}
			break;
		}
	}

	SDL_FreeSurface(interface);
	SDL_FreeSurface(ressource);
	SDL_FreeSurface(carte);
	SDL_FreeSurface(deplacement_carte);
	SDL_FreeSurface(ecran);
	SDL_Quit();
}

void pause()
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
}

void affichage_ecran_combat(Terrain_combat *un_terrain_combat)
{

	 if (SDL_Init(SDL_INIT_VIDEO) == -1) /*Démarrage de la SDL. Si erreur :*/
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); /* Écriture de l'erreur*/
        exit(EXIT_FAILURE); /* On quitte le programme*/
    }
  	SDL_SetVideoMode(TAILLE_ECRAN_COMBAT_X,TAILLE_ECRAN_COMBAT_Y,NOMBRE_BITS_COULEUR,SDL_HWSURFACE|SDL_RESIZABLE|SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Conquest Of Space","combat");
  	pause();
    SDL_Quit();
}


