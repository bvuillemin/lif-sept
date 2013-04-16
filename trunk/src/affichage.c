#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
#include "SDL_image.h"
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
    SDL_Surface *texte;
    SDL_Rect position;
    TTF_Font *police = NULL;
    char ressource[200] = "";

    TTF_Init();
    police = TTF_OpenFont("space_age.ttf", 14);
    SDL_Color couleur_blanche = {255, 255, 255};

    sprintf(ressource, "Ressources:  Metal:%d  Argent:%d  Carburant:%d  Population:%d", get_metal_joueur(&un_jeu->tab_joueur[0]), get_argent_joueur(&un_jeu->tab_joueur[0]), get_carburant_joueur(&un_jeu->tab_joueur[0]), get_population_joueur(&un_jeu->tab_joueur[0]));
    texte = TTF_RenderText_Blended(police, ressource, couleur_blanche);
    position.x = 10;
    position.y = 2;
    SDL_BlitSurface(texte, NULL, surface_ressource, &position);
    return surface_ressource;

    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    TTF_Quit();
}


SDL_Surface* creer_affichage_terrain(Terrain_espace *un_terrain_espace)
{
	SDL_Surface *carte = NULL;
	SDL_Surface *planete = NULL;
	SDL_Surface *planete2 = NULL;
	SDL_Rect position_planete;
	SDL_Rect position_planete2;
	SDL_Rect position;
	SDL_Surface *image_une_case = NULL;
    SDL_Surface *fond = NULL;
	int i, j;
	Case_terrain_espace *une_case;

	position_planete.x = 0;
	position_planete.y = 0;
	position_planete2.x = 0;
	position_planete2.y = 0;
	position.x = 0;
	position.y = 0;

	carte = SDL_CreateRGBSurface(SDL_HWSURFACE, un_terrain_espace->taille_espace_x * 100, un_terrain_espace->taille_espace_y * 100, 32, 0, 0, 0, 0);
	planete = IMG_Load("2.png");
	planete2 = IMG_Load("3.png");
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
    SDL_FreeSurface(planete2);
    SDL_FreeSurface(image_une_case);
    SDL_FreeSurface(fond);

	return carte;
}

SDL_Surface* affichage_terrain(Terrain_espace *un_terrain_espace, SDL_Surface *carte, SDL_Surface *resultat)
{
	SDL_Rect affichage;
	SDL_Rect position;

	affichage.w = 1080;
	affichage.h = 600;

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
	SDL_Surface *deplacement_carte = NULL;
    SDL_Surface *interface = NULL;
	SDL_Rect position1;
	SDL_Rect position2;
    SDL_Rect position3;
	SDL_Event event;
	int continuer = 1;

	position1.x = 200;
	position1.y = 20;

	position2.x = 0;
	position2.y = 0;

    position3.x = 0;
	position3.y = 20;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_EnableKeyRepeat(10, 10);
	ecran = SDL_SetVideoMode(1280, 720, 32, SDL_SWSURFACE);
	interface = IMG_Load("interface.png");
    SDL_BlitSurface(interface, NULL, ecran, &position3);

	ressource = IMG_Load("ressource.png");
	ressource = affichage_ressource(un_jeu, ressource);
	SDL_BlitSurface(ressource, NULL, ecran, &position2);

	carte = creer_affichage_terrain(un_terrain_espace);
	deplacement_carte = SDL_CreateRGBSurface(SDL_SWSURFACE, 1080, 600, 32, 0, 0, 0, 0);
	deplacement_carte = affichage_terrain(un_terrain_espace, carte, deplacement_carte);
	SDL_BlitSurface(deplacement_carte, NULL, ecran, &position1);

	SDL_Flip(ecran);

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_UP:
				if((un_terrain_espace->affichage_y > 0) && (un_terrain_espace->affichage_y <= (un_terrain_espace->taille_espace_y *100) -600 ))
				{un_terrain_espace->affichage_y--;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position1);
				SDL_Flip(ecran);}
				break;
			case SDLK_DOWN:
				if((un_terrain_espace->affichage_y>=0) && (un_terrain_espace->affichage_y < (un_terrain_espace->taille_espace_y *100) - 600 ))
				{un_terrain_espace->affichage_y++;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position1);
				SDL_Flip(ecran);}
				break;
			case SDLK_RIGHT:
				if((un_terrain_espace->affichage_x >= 0) && (un_terrain_espace->affichage_x < (un_terrain_espace->taille_espace_x * 100) -1080))
				{un_terrain_espace->affichage_x++;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position1);
				SDL_Flip(ecran);}
				break;
			case SDLK_LEFT:
				if((un_terrain_espace->affichage_x>0) && (un_terrain_espace->affichage_x <= (un_terrain_espace->taille_espace_x *100) -1080))
				{un_terrain_espace->affichage_x--;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position1);
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
  	SDL_SetVideoMode(TAILLE_ECRAN_COMBAT_X,TAILLE_ECRAN_COMBAT_Y,32,SDL_HWSURFACE|SDL_RESIZABLE|SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Conquest Of Space","combat");
  	pause();
    SDL_Quit();
}


