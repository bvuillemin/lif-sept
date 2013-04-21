#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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

bool test_souris_rectangle (SDL_Rect taille_surface, int x, int y) /*Va tester si le clic souris c'est fait dans un rectangle, utile pour les menus*/
{
	if((x > taille_surface.x) && (x< taille_surface.x + taille_surface.w) && (y > taille_surface.y) && (y< taille_surface.y + taille_surface.h))
	{
		return true;
	}
	else return false;
}

void initialise_sdl_rect(SDL_Rect un_rectangle, int x, int y, int w, int h) /*Va modifier les atrributs d'un SDL_rect*/
{
	un_rectangle.x = x;
	un_rectangle.y = y;
	un_rectangle.w = w;
	un_rectangle.h = h;
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

    sprintf(ressource, "Ressources:  Metal:%d Argent:%d Carburant:%d Population:%d", get_metal_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]), get_argent_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]), get_carburant_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]), get_population_joueur(&un_jeu->tab_joueur[un_jeu->joueur_en_cours]));
    nom_ressource = TTF_RenderText_Blended(police, ressource, couleur_blanche);
    position.x = 10;
    position.y = 2;
    SDL_BlitSurface(nom_ressource, NULL, texte_ressource, &position);

	sprintf(tour, "Tour en cours:%d Joueur en cours:%d", un_jeu->tour_en_cours, un_jeu->joueur_en_cours);
	nombre_tour = TTF_RenderText_Blended(police, tour, couleur_blanche);
	position.x = TAILLE_FENETRE_X - 410;
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

SDL_Surface* affichage_planete(Case_terrain_espace *une_case_terrain_espace, SDL_Surface *info_planete)
{
    SDL_Surface *planete = NULL;
    SDL_Surface *fond_planete = NULL;
    SDL_Rect position;
    TTF_Font *police = NULL;
	SDL_Color couleur_blanche = {255, 255, 255};
    char texte_planete[200] = "";
    Planete *une_planete = une_case_terrain_espace->planete;

    TTF_Init();
    police = TTF_OpenFont("space_age.ttf", 14);
	fond_planete = SDL_CreateRGBSurface(SDL_SWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(fond_planete, NULL, SDL_MapRGB(info_planete->format, 0, 0, 0));;

    sprintf(texte_planete, "Nom de la planete: %s Occupation de la planete: %d/%d Production: Metal:%d Argent:%d Carburant:%d Population:%d",
get_nom_planete(une_planete), get_taille_utilisee(une_planete), get_taille_planete(une_planete),
get_metal(une_planete), get_argent(une_planete), get_carburant(une_planete), get_population(une_planete));
    planete = TTF_RenderText_Blended(police, texte_planete, couleur_blanche);
    position.x = 10;
    position.y = 10;
    SDL_BlitSurface(planete, NULL, fond_planete, &position);

    TTF_CloseFont(police);
    TTF_Quit();

    return fond_planete;
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

SDL_Surface* affichage_terrain(Terrain_espace *un_terrain_espace, SDL_Surface *carte, SDL_Surface *carte_flotte, SDL_Surface *resultat)
{
	SDL_Rect affichage;
	SDL_Rect position;

	affichage.w = TAILLE_TERRAIN_ESPACE_X;
	affichage.h = TAILLE_TERRAIN_ESPACE_Y;

	position.x = 0;
	position.y = 0;

	affichage.x = un_terrain_espace->affichage_x;
	affichage.y = un_terrain_espace->affichage_y;

	SDL_BlitSurface(carte, &affichage, resultat, &position);
	SDL_SetColorKey(carte_flotte, SDL_SRCCOLORKEY, SDL_MapRGB(carte_flotte->format, 0, 0, 0));
	SDL_BlitSurface(carte_flotte, &affichage, resultat, &position);

	return resultat;
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

void affichage_ecran(Jeu *un_jeu, Terrain_espace *un_terrain_espace)
{
	SDL_Surface *ecran = NULL;
	SDL_Surface *carte = NULL;
	SDL_Surface *carte_flotte = NULL;
	SDL_Surface *ressource = NULL;
	SDL_Surface *deplacement_carte = NULL;
    SDL_Surface *interface = NULL;
    SDL_Surface *info = NULL;
	SDL_Rect position = {0, 0, 0, 0};
	SDL_Rect bouton_tour = {TAILLE_FENETRE_X - 30, 0, 300, 50};
	SDL_Rect position_affichage_carte = {0, 20, 0, 0};
	SDL_Rect position_affichage_info = {0,TAILLE_TERRAIN_ESPACE_Y + 20 , TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y};
	SDL_Event event;
	int continuer = 1;
	int x = 0, y = 0;
	Case_terrain_espace *une_case_terrain_espace;

	initialise_sdl_rect(position, 0, 20, 0, 0);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_EnableKeyRepeat(10, 10);

	ecran = SDL_SetVideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y, NOMBRE_BITS_COULEUR, SDL_SWSURFACE); /*Chargement du fond*/
	interface = IMG_Load("interface.png");
    SDL_BlitSurface(interface, NULL, ecran, &position);

	initialise_sdl_rect(position, 0, 0, 0, 0); /*affichage de la barre de ressources*/
	ressource = IMG_Load("ressource.png");
	ressource = affichage_ressource(un_jeu, ressource);
	SDL_BlitSurface(ressource, NULL, ecran, &position);

	info = SDL_CreateRGBSurface(SDL_SWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_FillRect(info, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(info, NULL, ecran, &position_affichage_info);

	carte = creer_affichage_terrain(un_terrain_espace); /*Creation du terrain en entier, celui-ci est stocké en mémoire*/
	carte_flotte = creer_affichage_flotte(un_terrain_espace);
	deplacement_carte = SDL_CreateRGBSurface(SDL_SWSURFACE, TAILLE_TERRAIN_ESPACE_X, TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	deplacement_carte = affichage_terrain(un_terrain_espace, carte, carte_flotte, deplacement_carte); /*affichage d'une partie du terrain*/
	SDL_BlitSurface(deplacement_carte, NULL, ecran, &position_affichage_carte);

	SDL_Flip(ecran);

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
				if(booleen_case_pointeur_souris(un_terrain_espace, x, y))
				{
					une_case_terrain_espace = case_pointeur_souris(un_terrain_espace, x, y);
					if(une_case_terrain_espace->type_case_terrain_espace == 'P')
					{
					    info = affichage_planete(une_case_terrain_espace, info);
					    SDL_BlitSurface(info, NULL, ecran, &position_affichage_info);
					    SDL_Flip(ecran);
					}
					if(une_case_terrain_espace->presence_flotte == true)
                    {
                        un_jeu->selection_flotte = une_case_terrain_espace->flotte;
                    }
					else
					{
					    info = SDL_CreateRGBSurface(SDL_SWSURFACE, TAILLE_FENETRE_X, TAILLE_FENETRE_Y - TAILLE_TERRAIN_ESPACE_Y, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
                        SDL_FillRect(info, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(info, NULL, ecran, &position_affichage_info);
                        SDL_Flip(ecran);
					}
				}
				if (test_souris_rectangle(bouton_tour, x, y))
				{
					joueur_suivant(un_jeu);
					initialise_sdl_rect(position, 0, 0, 0, 0);
					ressource = affichage_ressource(un_jeu, ressource);
					SDL_BlitSurface(ressource, NULL, ecran, &position);
					SDL_Flip(ecran);
				}
			}
			if(event.button.button == SDL_BUTTON_RIGHT)
			{
			    x = event.button.x;
				y = event.button.y;

			    if(un_jeu->selection_flotte->indice_joueur == un_jeu->joueur_en_cours)
			    {
			        deplacement_flotte(un_terrain_espace, un_jeu->selection_flotte, x, y);
			        carte_flotte = creer_affichage_flotte(un_terrain_espace);
                    deplacement_carte = affichage_terrain(un_terrain_espace, carte, carte_flotte, deplacement_carte);
                    SDL_BlitSurface(deplacement_carte, NULL, ecran, &position_affichage_carte);
                    SDL_Flip(ecran);
			    }
			}
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_UP:
				if((un_terrain_espace->affichage_y > 0) && (un_terrain_espace->affichage_y <= (un_terrain_espace->taille_espace_y *100) - TAILLE_TERRAIN_ESPACE_Y ))
				{un_terrain_espace->affichage_y--;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, carte_flotte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position_affichage_carte);
				SDL_Flip(ecran);}
				break;
			case SDLK_DOWN:
				if((un_terrain_espace->affichage_y>=0) && (un_terrain_espace->affichage_y < (un_terrain_espace->taille_espace_y *100) - TAILLE_TERRAIN_ESPACE_Y ))
				{un_terrain_espace->affichage_y++;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, carte_flotte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position_affichage_carte);
				SDL_Flip(ecran);}
				break;
			case SDLK_RIGHT:
				if((un_terrain_espace->affichage_x >= 0) && (un_terrain_espace->affichage_x < (un_terrain_espace->taille_espace_x * 100) - TAILLE_TERRAIN_ESPACE_X))
				{un_terrain_espace->affichage_x++;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, carte_flotte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position_affichage_carte);
				SDL_Flip(ecran);}
				break;
			case SDLK_LEFT:
				if((un_terrain_espace->affichage_x>0) && (un_terrain_espace->affichage_x <= (un_terrain_espace->taille_espace_x *100) - TAILLE_TERRAIN_ESPACE_X))
				{un_terrain_espace->affichage_x--;
				deplacement_carte = affichage_terrain(un_terrain_espace, carte, carte_flotte, deplacement_carte);
				SDL_BlitSurface(deplacement_carte, NULL, ecran, &position_affichage_carte);
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
void affiche_ecran_terrain_combat(const Terrain_combat *terrain_combat, SDL_Surface * une_surface)
{
	SDL_Surface * quadrillage =NULL;
	SDL_Surface * planete =NULL;
	SDL_Rect pos,pos_plan;
	int i, j;
    Case_terrain_combat *une_case;
	pos.x = 0 ;pos_plan.x=0;
	pos.y = 0;pos_plan.y=0;
	quadrillage = IMG_Load("quadrillage.png");
	planete = IMG_Load("vaisseau_bleu.png");
    for(j=0;j<terrain_combat->taille_combat_y;j++)
    {
        for(i=0;i<terrain_combat->taille_combat_x;i++)
        {
			pos.x=i*100;pos.y=j*100;
            une_case = get_case_terrain_combat(terrain_combat, i, j);
			
            if(get_presence_unite(une_case))
            {
				pos_plan.x=i*100;pos_plan.y=j*100;
				SDL_BlitSurface(planete,NULL,une_surface,&pos_plan);
            }
			SDL_BlitSurface(quadrillage,NULL,une_surface,&pos);
        }
        printf("\n");
    }
	SDL_FreeSurface(planete);
	SDL_FreeSurface(quadrillage);
}

void affichage_ecran_combat(const Terrain_combat *un_terrain_combat)
{
	SDL_Surface *ecran = NULL;
	int x,y;
	Uint32 couleur;
	x=get_taille_combat_x(un_terrain_combat);
	y=get_taille_combat_y(un_terrain_combat);
	 if (SDL_Init(SDL_INIT_VIDEO) == -1) /*Démarrage de la SDL. Si erreur :*/
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); /* Écriture de l'erreur*/
        exit(EXIT_FAILURE); /* On quitte le programme*/
    }
  	ecran =SDL_SetVideoMode(x*100+100,y*100+100,32,SDL_HWSURFACE|SDL_RESIZABLE|SDL_DOUBLEBUF);
	  if (ecran == NULL) /*Si l'ouverture a échoué, on le note et on arrête*/
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
	couleur = SDL_MapRGB(ecran->format,0,0,0);
	SDL_FillRect(ecran, NULL, couleur);
	SDL_Flip(ecran);
	
	
	
	affiche_ecran_terrain_combat(un_terrain_combat,ecran);SDL_Flip(ecran);
	
  	pause();
	
    SDL_Quit();
}


