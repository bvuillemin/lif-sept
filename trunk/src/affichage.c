#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constante.h"
#include "terrain_espace.h"
#include "terrain_combat.h"
SDL_Surface* creer_affichage_terrain(Terrain_espace *un_terrain_espace)
{
	SDL_Surface *carte = NULL;
	SDL_Surface *planete = NULL;
	SDL_Surface *planete2 = NULL;
	SDL_Rect position_planete;
	SDL_Rect position_planete2;
	SDL_Rect position;
	SDL_Surface *image_une_case = NULL;
	int i, j;/*
	Case_terrain_espace *une_case;*/

	position_planete.x = 0;
	position_planete.y = 0;
	position_planete2.x = 0;
	position_planete2.y = 0;
	position.x = 0;
	position.y = 0;

	carte = SDL_CreateRGBSurface(SDL_HWSURFACE, un_terrain_espace->taille_espace_x * 100, un_terrain_espace->taille_espace_y * 100, 32, 0, 0, 0, 0);
	planete = IMG_Load("2.png");
	planete2 = IMG_Load("3.png");
	image_une_case = IMG_Load("fond.png");

	for(i=0;i< un_terrain_espace->taille_espace_x;i++)
	{
		for(j=0;j< un_terrain_espace->taille_espace_y;j++)
		{
			position.x = i * 100;
			position.y = j *100;
			SDL_BlitSurface(image_une_case, NULL, carte, &position);
		}
	}

	position_planete.x = (2 * 100);
	position_planete.y = (1 * 100);
	SDL_BlitSurface(planete, NULL, carte, &position_planete);

	position_planete2.x = (8 * 100);
	position_planete2.y = (8 * 100);
	SDL_BlitSurface(planete2, NULL, carte, &position_planete2);

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

void affichage_ecran(Terrain_espace *un_terrain_espace)
{
	SDL_Surface *ecran = NULL;
	SDL_Surface *carte = NULL;
	SDL_Surface *ressource = NULL;
	SDL_Surface *deplacement_carte = NULL;
	SDL_Rect position1;
	SDL_Rect position2;
	SDL_Event event;
	int continuer = 1;

	position1.x = 200;
	position1.y = 20;

	position2.x = 0;
	position2.y = 0;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_EnableKeyRepeat(10, 10);
	ecran = SDL_SetVideoMode(1280, 720, 32, SDL_SWSURFACE);
	SDL_FillRect(ecran , NULL, SDL_MapRGB(ecran->format, 22, 117, 172));
	
	ressource = SDL_CreateRGBSurface(SDL_SWSURFACE, 1280, 20, 32, 0, 0, 0, 0);
	SDL_FillRect(ressource , NULL, SDL_MapRGB(ecran->format, 255, 232, 41));
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
	SDL_Quit();
}


void affichage_ecran_combat(Terrain_combat *un_terrain_combat)
{
	
	 if (SDL_Init(SDL_INIT_VIDEO) == -1) /*Démarrage de la SDL. Si erreur :*/
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); /* Écriture de l'erreur*/
        exit(EXIT_FAILURE); /* On quitte le programme*/
    }
  	SDL_SetVideoMode(TAILLE_ECRAN_COMBAT_X,TAILLE_ECRAN_COMBAT_Y,32,SDL_HWSURFACE|SDL_RESIZABLE|SDL_DOUBLEBUF);
  
    SDL_Quit();
}
