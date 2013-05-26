#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "jeu.h"
#include "affichage.h"
#include "joueur.h"
#include "ia.h"


/************************************************************************/
/* Initialisation, création et destruction                              */
/************************************************************************/

void initialise_jeu(Jeu *un_jeu)
{
    int i;
	un_jeu->tour_en_cours = 0;
	un_jeu->joueur_en_cours = 0;
	un_jeu->joueur_en_cours_combat =0;
	un_jeu->nb_joueur = 0;
	un_jeu->selection_flotte = NULL;
	un_jeu->selection_planete = NULL;
	un_jeu->animation_en_cours = NULL;
    un_jeu->tab_joueur =(Joueur *)malloc(sizeof(Joueur) * 10);
    for(i=0;i<10;i++)
    {
        un_jeu->tab_unite_selectionnee[i] = false;
    }
}

Jeu *creer_jeu()
{
	Jeu *un_jeu=(Jeu *)malloc(sizeof(Jeu));
    initialise_jeu(un_jeu);
    return un_jeu;
}

void liberer_jeu(Jeu *un_jeu)
{
    int i;
    for(i=0;i<un_jeu->nb_joueur;i++)
    {
        liberer_joueur(&un_jeu->tab_joueur[i]);
    }
    free(un_jeu->tab_joueur);
    un_jeu->tour_en_cours = 0;
    un_jeu->joueur_en_cours = 0;
    un_jeu->nb_joueur = 0;
    un_jeu->selection_flotte = NULL;
    for(i=0;i<10;i++)
    {
        un_jeu->tab_unite_selectionnee[i] = false;
    }
}

void detruire_jeu(Jeu **un_jeu)
{
	liberer_jeu(*un_jeu);
	free(*un_jeu);
	*un_jeu = NULL;
}


/************************************************************************/
/* Fonctions set et get                                                 */
/************************************************************************/

int get_joueur_en_cours_combat(Jeu * jeu)
{
	return jeu->joueur_en_cours_combat;
}
Joueur *get_joueur_en_cours(Jeu *un_jeu)
{
	return &un_jeu->tab_joueur[un_jeu->joueur_en_cours];
}
Flotte *get_flotte_en_cours(Jeu *un_jeu)
{
	return un_jeu->selection_flotte;
}
int get_indice_joueur_en_cours(Jeu *un_jeu)
{
	return un_jeu->joueur_en_cours;
}
Planete *get_planete_en_cours(Jeu *un_jeu)
{
	return un_jeu->selection_planete;
}
Joueur * get_ieme_joueur_jeu(Jeu * un_jeu,int i)
{
	return un_jeu->tab_joueur + i;
}


/************************************************************************/
/* Fonctions liées au jeu                                               */
/************************************************************************/

void ajouter_joueur(Jeu *un_jeu, Joueur *un_joueur)
{
	int i;
	i = un_jeu->nb_joueur;
	if(un_jeu->nb_joueur < 10)
	{
		un_jeu->tab_joueur[i] = *un_joueur;
		un_jeu->nb_joueur ++;
		set_numero_joueur(un_jeu->tab_joueur+i,i);
	}
	free(un_joueur);
}

void joueur_suivant(Jeu *un_jeu, Terrain_espace *un_terrain_espace)
{
	if(un_jeu->joueur_en_cours +1 < un_jeu->nb_joueur)
	{
		un_jeu->joueur_en_cours ++;
	}
	else
	{
		tour_suivant(un_jeu, un_terrain_espace);
		un_jeu->joueur_en_cours = 0;
	}
}

void tour_suivant(Jeu *un_jeu, Terrain_espace *un_terrain_espace)
{
	int metal = 0, argent = 0, carburant = 0, population = 0;
	int i;

	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		if(get_ia_joueur(get_ieme_joueur_jeu(un_jeu, i)))
		{
			appeler_ia(un_terrain_espace, un_jeu->tab_joueur);
		}
		recuperer_ressource_planete(get_ieme_joueur_jeu(un_jeu, i), &metal, &argent, &carburant, &population);
		un_jeu->tab_joueur[i].metal += metal;
		un_jeu->tab_joueur[i].argent += argent;
		un_jeu->tab_joueur[i].carburant += carburant;
		un_jeu->tab_joueur[i].population += population;
		printf("Ressources du tour %d pour le joueur %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n\n", un_jeu->tour_en_cours, i, metal, argent, carburant, population);
		reinitialiser_mouvement_flotte(get_ieme_flotte_joueur(&un_jeu->tab_joueur[i], 0));

		if(un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant > 0)
		{
			un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant --;
		}
		if(un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant == 0) /*a completer pour gerer automatiquement chaque planete de chaque joueur*/
		{
			validation_batiment(un_jeu->tab_joueur[i].tab_planete[0]);
			un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant = -1;
			un_jeu->tab_joueur[i].tab_planete[0]->batiment_en_cours = -1;
		}

		if(un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant > 0)
		{
			un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant --; /*de meme*/
		}
		if(un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant == 0)
		{
			validation_creation_unite_planete(un_jeu, un_terrain_espace, i, un_jeu->tab_joueur[i].tab_planete[0]->x, un_jeu->tab_joueur[i].tab_planete[0]->y);
			un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant = -1;
			un_jeu->tab_joueur[i].tab_planete[0]->unite_en_cours = -1;
		}
	}
	un_jeu->tour_en_cours++;
}

void afficher_info(Jeu *un_jeu)
{
	printf("Joueur en cours %d, tour en cours %d \n", un_jeu->joueur_en_cours, un_jeu->tour_en_cours);
}

void ajouter_toutes_flottes_terrain(Jeu* un_jeu, Terrain_espace* un_terrain_espace)
{
	Flotte* une_flotte;
	Joueur* un_joueur;
	int i, j;
	int x, y;

	for(i=0;i< un_jeu->nb_joueur;i++)
	{
		un_joueur = get_ieme_joueur_jeu(un_jeu, i);
		for(j=0;j<get_nb_flotte_joueur(un_joueur);j++)
		{
			une_flotte = get_ieme_flotte_joueur(un_joueur, j);
			x = get_x_flotte(une_flotte);
			y = get_y_flotte(une_flotte);
			ajouter_flotte(get_case_terrain_espace(un_terrain_espace, x, y), une_flotte);
		}
	}
}

void ajouter_flotte_jeu(Jeu *un_jeu,Terrain_espace *un_terrain_espace, Flotte *une_flotte, int indice_joueur, int x, int y)
{
	set_x_flotte(une_flotte, x);
	set_y_flotte(une_flotte, y);
	ajouter_flotte_joueur(&un_jeu->tab_joueur[indice_joueur], une_flotte);
	ajouter_toutes_flottes_terrain(un_jeu, un_terrain_espace);
}

void afficher_ressource_joueur(Jeu *un_jeu)
{
	int i;
	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		printf("Ressources du joueur %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n\n", i, un_jeu->tab_joueur[i].metal, un_jeu->tab_joueur[i].argent, un_jeu->tab_joueur[i].carburant, un_jeu->tab_joueur[i].population);
	}
}

void creer_vision_joueur(Jeu* un_jeu, Terrain_espace* un_terrain, int indice_joueur)
{
	Vision_terrain *une_vision;
	Joueur *un_joueur;

	une_vision = creer_vision_terrain(un_terrain, indice_joueur);

	parcourir_terrain(une_vision, indice_joueur);
	un_joueur = get_ieme_joueur_jeu(un_jeu, indice_joueur);
	un_joueur->vision_terrain = une_vision;
}

void creer_vision_jeu(Jeu *un_jeu, Terrain_espace* un_terrain_espace)
{
	int i;
	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		creer_vision_joueur(un_jeu, un_terrain_espace, i);
	}
}

void maj_vision_joueur(Jeu* un_jeu, Terrain_espace* un_terrain, int indice_joueur)
{
	Vision_terrain *une_vision;
	Joueur *un_joueur;

	un_joueur = get_ieme_joueur_jeu(un_jeu, indice_joueur);
	une_vision = un_joueur->vision_terrain;
	parcourir_terrain(une_vision, indice_joueur);
	un_joueur = get_ieme_joueur_jeu(un_jeu, indice_joueur);
	un_joueur->vision_terrain = une_vision;
}

void maj_vision_jeu(Jeu *un_jeu, Terrain_espace* un_terrain_espace)
{
	int i;
	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		maj_vision_joueur(un_jeu, un_terrain_espace, i);
	}
}

void affichage_vision_jeu(Jeu *un_jeu, Terrain_espace* un_terrain_espace)
{
	int i, j, k;
	Vision_case* une_case;
	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		printf("Affichage terrain joueur %d\n", i);
		for (j=0;j<=un_terrain_espace->taille_espace_y;j++)
		{
			for(k=0;k<=un_terrain_espace->taille_espace_x;k++)
			{
				if(k == 0)
				{
					printf("|%d|", j%10);
				}
				if((j == 0) && (k != 0))
				{
					printf("|%d|", k%10);
				}
				if((j!=0) && (k!=0))
				{
					une_case = get_vision_case(un_jeu->tab_joueur[i].vision_terrain, k - 1, j - 1);
					if(une_case->champ_vision == AFFICHEE)
					{
						printf("|A|");
					}
					if(une_case->champ_vision == VISITEE)
					{
						printf("|V|");
					}
					if(une_case->champ_vision == JAMAIS_VISITEE)
					{
						printf("|N|");
					}
				}
			}
			printf("\n");
		}
		printf("\n");
	}
}

/************************************************************************/
/* Fonctions liées à la création d'objets du jeu                        */
/************************************************************************/

bool condition_creation_unite(Joueur* un_joueur, Planete *une_planete, int choix)
{
	int metal, argent, carburant, population;

	metal = get_metal_joueur(un_joueur);
	argent = get_argent_joueur(un_joueur);
	carburant = get_carburant_joueur(un_joueur);
	population = get_population_joueur(un_joueur);

	if(une_planete->batiment[5] > 0)
	{
		if(choix == 1)
		{
			if((NB_METAL_UNITE_1 <= metal) && (NB_ARGENT_UNITE_1 <= argent) && (NB_CARBURANT_UNITE_1 <= carburant)  && (NB_POPULATION_UNITE_1 <= population))
			{
				return true;
			}
			else return false;
		}
		if(choix == 2)
		{
			if((NB_METAL_UNITE_2 <= metal) && (NB_ARGENT_UNITE_2 <= argent) && (NB_CARBURANT_UNITE_2 <= carburant)  && (NB_POPULATION_UNITE_2 <= population))
			{
				return true;
			}
			else return false;
		}
		if(choix == 3)
		{
			if((NB_METAL_UNITE_3 <= metal) && (NB_ARGENT_UNITE_3 <= argent) && (NB_CARBURANT_UNITE_3 <= carburant)  && (NB_POPULATION_UNITE_3 <= population))
			{
				return true;
			}
			else return false;
		}
	}
	return false;
}

bool condition_creation_batiment(Planete *une_planete, int choix)
{
	if((choix == 0) && (une_planete->taille_utilisee <= une_planete->taille_planete))
	{
		return true;
	}
	if ((une_planete->taille_utilisee <= une_planete->taille_planete) && (une_planete->batiment[0]))
	{
		return true;
	}
	else return false;
}

void validation_creation_unite_planete(Jeu *un_jeu, Terrain_espace *un_terrain_espace, int indice_joueur_en_cours, int x, int y)
{
    Unite *une_unite;
    Flotte *une_flotte;
    Planete *une_planete = get_planete_terrain_espace(un_terrain_espace, x, y);
    if(une_planete->unite_nb_tour_restant == 0)
    {
        if(une_planete->unite_en_cours == 1)
        {
            une_unite = creer_unite(Chasseur);
        }
		if(une_planete->unite_en_cours == 2)
		{
			une_unite = creer_unite(Destroyer);
		}
		if(une_planete->unite_en_cours == 3)
		{
			une_unite = creer_unite(Destructeur);
		}
		une_flotte = creer_flotte();
		ajouter_unite_flotte(une_flotte, une_unite);
		ajouter_flotte_jeu(un_jeu, un_terrain_espace, une_flotte, indice_joueur_en_cours, x, y);
    }
}

bool construction_batiment_possible(Planete* une_planete)
{
	if((une_planete->batiment_nb_tour_restant <= 0) && (une_planete->taille_utilisee <= une_planete->taille_planete))
	{
		return true;
	}
	return false;
}

bool construction_unite_possible(Planete* une_planete)
{
	if((get_planete_unite_nb_tour_restant(une_planete) <= 0) && (get_ieme_batiment(une_planete, 5)))
	{
		return true;
	}
	return false;
}

/************************************************************************/
/* Fonctions liées aux flottes                                          */
/************************************************************************/

bool test_unite_selectionnee(Jeu *un_jeu)
{
    int i;
    for(i=0;i<10;i++)
    {
        if(un_jeu->tab_unite_selectionnee[i] == true)
        {
            return true;
        }
    }
    return false;
}

void colonisation_planete_flotte(Terrain_espace *un_terrain_espace, Flotte *une_flotte, Jeu *un_jeu)
{
	Planete *une_planete;
	Joueur *un_joueur;

	une_planete = get_planete_terrain_espace(un_terrain_espace, get_x_flotte(une_flotte), get_y_flotte(une_flotte));
	un_joueur = &un_jeu->tab_joueur[get_indice_joueur_flotte(une_flotte)];

	colonisation_planete(un_joueur, une_planete);
}

bool deplacement_flotte(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y)
{
	if(peut_se_deplacer(une_flotte, x, y))
	{
		int distance;
		int x_depart, y_depart;
		Case_terrain_espace *case_depart;
		Case_terrain_espace *case_arrivee;
		x_depart = get_x_flotte(une_flotte);
		y_depart = get_y_flotte(une_flotte);
		case_depart = get_case_terrain_espace(un_terrain_espace, x_depart, y_depart);
		case_arrivee = get_case_terrain_espace(un_terrain_espace, x, y);


		if((x_depart == x) && (y_depart == y))
		{
			return false;
		}
		distance = calcul_distance(x_depart, y_depart, x, y);
		if((case_arrivee->presence_flotte == false) && (une_flotte->pt_mouvement_espace_flotte >= distance))
		{
			ajouter_flotte(case_arrivee, une_flotte);
			retirer_flotte(case_depart);
			enlever_pt_mouvement_espace_flotte(une_flotte, distance);
			return true;
		}
		if(case_arrivee->presence_flotte == true)
		{
			if(fusion_flotte(un_joueur, un_terrain_espace, une_flotte, case_arrivee->flotte))
			{
				/*free(une_flotte);*/
				return true;
			}
		}
	}
	return false;
}
/*
bool fusion_flotte(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y)
{
	int i;
	int nb_unite = une_flotte->taille_flotte;
	int distance;
	int pt_mvt_arrivee;
	int pt_mvt_depart = get_pt_mouvement_espace_flotte(une_flotte);
	int x_depart = get_x_flotte(une_flotte);
	int y_depart = get_y_flotte(une_flotte);
	Case_terrain_espace *case_depart;
	Case_terrain_espace *case_arrivee;
	Flotte *flotte_arrivee;

	case_depart = get_case_terrain_espace(un_terrain_espace, x_depart, y_depart);
	case_arrivee = get_case_terrain_espace(un_terrain_espace, x, y);
	flotte_arrivee = get_flotte(case_arrivee);
	pt_mvt_arrivee = get_pt_mouvement_espace_flotte(flotte_arrivee);

	if((flotte_arrivee->taille_flotte + une_flotte->taille_flotte <= flotte_arrivee->taille_maximum_flotte) && (une_flotte->indice_joueur == flotte_arrivee->indice_joueur))
	{
		for(i=0;i<nb_unite;i++)
		{
			transferer_unite_flotte(flotte_arrivee, &une_flotte->tab_unite[i]);
		}
		retirer_flotte(case_depart);
		if(une_flotte->indice_tableau_joueur < flotte_arrivee->indice_tableau_joueur)
		{
			case_arrivee->flotte = get_ieme_flotte_joueur(un_joueur, flotte_arrivee->indice_tableau_joueur - 1);
		}
		else
		{
			case_arrivee->flotte = get_ieme_flotte_joueur(un_joueur, flotte_arrivee->indice_tableau_joueur);
		}
		retirer_flotte_joueur(un_joueur, une_flotte->indice_tableau_joueur);
		//free(une_flotte);
		/*distance = calcul_distance(x_depart, y_depart, x, y);
		if(pt_mvt_arrivee > (pt_mvt_depart - distance))
		{
			enlever_pt_mouvement_espace_flotte(flotte_arrivee, distance);
		}
		return true;
	}
	return false;
}*/

bool fusion_flotte(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *flotte_depart, Flotte* flotte_arrivee)
{
	int i;
	int nb_unite = flotte_depart->taille_flotte;
	Case_terrain_espace *case_depart;
	Case_terrain_espace *case_arrivee;

	case_depart = get_case_terrain_espace(un_terrain_espace, flotte_depart->x_flotte, flotte_depart->y_flotte);
	case_arrivee = get_case_terrain_espace(un_terrain_espace, flotte_arrivee->x_flotte, flotte_arrivee->y_flotte);

	if((flotte_arrivee->taille_flotte + flotte_depart->taille_flotte <= flotte_arrivee->taille_maximum_flotte) && (flotte_depart->indice_joueur == flotte_arrivee->indice_joueur))
	{
		for(i=0;i<nb_unite;i++)
		{
			ajouter_unite_flotte(flotte_arrivee, &flotte_depart->tab_unite[i]);
		}
		retirer_flotte(case_depart);
		retirer_flotte_joueur(un_joueur, flotte_depart->indice_tableau_joueur);
		free(flotte_depart);
		return true;
	}
	return false;
}


bool deplacement_unite_flotte(Jeu *un_jeu, Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y)
{
	if(peut_se_deplacer(une_flotte, x, y))
	{
		int distance, i;
		int x_depart, y_depart;
		Case_terrain_espace *case_arrivee;
		Flotte *une_nouvelle_flotte;
		x_depart = get_x_flotte(une_flotte);
		y_depart = get_y_flotte(une_flotte);
		une_nouvelle_flotte = creer_flotte();
		case_arrivee = get_case_terrain_espace(un_terrain_espace, x, y);


		if((x_depart == x) && (y_depart == y))
		{
			return false;
		}
		if(case_arrivee->presence_flotte == true)
		{
			if(fusion_flotte(un_joueur, un_terrain_espace, une_flotte, case_arrivee->flotte))
			{
				/*free(une_flotte);*/
				return true;
			}
		}
		if(case_arrivee->presence_flotte == false)
		{
			for(i=0;i<10;i++)
			{
				if(un_jeu->tab_unite_selectionnee[i] == true)
				{
					ajouter_unite_flotte(une_nouvelle_flotte, &une_flotte->tab_unite[i]);
					retirer_unite_flotte(une_flotte, i);
				}
			}
			distance = calcul_distance(x_depart, y_depart, x, y);
			enlever_pt_mouvement_espace_flotte(une_nouvelle_flotte, distance);
			ajouter_flotte_jeu(un_jeu, un_terrain_espace,une_nouvelle_flotte, un_jeu->joueur_en_cours, x, y);
			un_jeu->selection_flotte = get_flotte(get_case_terrain_espace(un_terrain_espace, x, y));
			return true;
		}
	}
	return false;
}


/************************************************************************/
/* Fonctions liées aux animations                                       */
/************************************************************************/

void lancer_animation(Jeu *un_jeu, Animation *une_animation, int temps, SDL_Surface *ecran, int x, int y)
{
	SDL_Surface *frame;
	SDL_Rect position_frame;
	SDL_Rect position_ecran;

	initialise_sdl_rect(&position_frame, une_animation->taille_frame_x * une_animation->frame_en_cours, une_animation->taille_frame_y * une_animation->frame_en_cours, une_animation->taille_frame_x, une_animation->taille_frame_y);
	initialise_sdl_rect(&position_ecran, x, y, 0, 0);
	frame = IMG_Load(une_animation->nom);
	SDL_BlitSurface(frame, &position_frame, ecran, &position_ecran);

	une_animation->tps_debut_anim = temps;
	une_animation->frame_en_cours ++;
	un_jeu->animation_en_cours = une_animation;
	une_animation->x = x;
	une_animation->y = y;

	SDL_FreeSurface(frame);
}

void lancer_animation_bloquante(Jeu *un_jeu, Terrain_espace *un_terrain_espace, Animation *une_animation, SDL_Surface *ecran, int x, int y)
{
	SDL_Surface *frame;
	SDL_Surface * tampon;
	SDL_Rect position_frame;
	SDL_Rect position_ecran = {0, 0, 0, 0};
	SDL_Rect position_tampon = {0, 0, 0, 0};
	int i;

	frame = IMG_Load(une_animation->nom);
	initialise_sdl_rect(&position_ecran, x, y, frame->w, frame->h);
	tampon = SDL_CreateRGBSurface(SDL_HWSURFACE, frame->w, frame->h, NOMBRE_BITS_COULEUR, 0, 0, 0, 0);
	SDL_BlitSurface(ecran, &position_ecran, tampon, &position_tampon);
	for(i=0;i<une_animation->nb_frame;i++)
	{
		initialise_sdl_rect(&position_frame, une_animation->taille_frame_x * une_animation->frame_en_cours, 0, une_animation->taille_frame_x, une_animation->taille_frame_y);
		SDL_BlitSurface(frame, &position_frame, ecran, &position_ecran);
		une_animation->frame_en_cours ++;
		SDL_Flip(ecran);
		SDL_Delay(une_animation->nb_ms);
		SDL_BlitSurface(tampon, &position_tampon, ecran, &position_ecran);
	}
	une_animation->frame_en_cours = 0;
	une_animation->x = 0;
	une_animation->y = 0;
	SDL_FreeSurface(frame);
	SDL_FreeSurface(tampon);
}

void maj_animation(Jeu *un_jeu, Terrain_espace *un_terrain_espace, Animation *une_animation, int temps, SDL_Surface *ecran, SDL_Surface **tab_surface, int interface_affichee)
{
	SDL_Surface *frame;
	SDL_Rect position_frame;
	SDL_Rect position_ecran;

	if((temps - une_animation->tps_debut_anim) >= (une_animation->nb_ms * une_animation->frame_en_cours))
	{
		une_animation->frame_en_cours ++;
	}
	initialise_sdl_rect(&position_frame, une_animation->taille_frame_x * une_animation->frame_en_cours, 0, une_animation->taille_frame_x, une_animation->taille_frame_y);
	initialise_sdl_rect(&position_ecran, une_animation->x, une_animation->y, 0, 0);
	frame = IMG_Load(une_animation->nom);
	SDL_BlitSurface(frame, &position_frame, ecran, &position_ecran);
	SDL_FreeSurface(frame);
	SDL_Flip(ecran);
	if(une_animation->frame_en_cours > une_animation->nb_frame)
	{
		une_animation->frame_en_cours = 0;
		une_animation->tps_debut_anim = temps;
		un_jeu->animation_en_cours = NULL;
		maj_affichage_carte_terrain(un_jeu, un_terrain_espace, ecran, tab_surface, interface_affichee);
	}
}


/************************************************************************/
/* Fonctions liées au combat                                            */
/************************************************************************/
void placer_unite_flotte_en_haut(Terrain_combat * un_terrain_combat, Flotte * flotte)
{
        int i,m,n;
        Unite * une_unite;
        for(i=0;i<(flotte->taille_flotte);i++)
        {
                une_unite=get_unite_i_flotte(flotte,i);
                m=get_x_unite(une_unite);
                n=get_y_unite(une_unite);
                while(case_libre(un_terrain_combat, m,n))
                {
                        set_y_unite(une_unite,n+1);
                        m=get_x_unite(une_unite);
                        n=get_y_unite(une_unite);
                }
                        ajoute_unite_terrain(un_terrain_combat, une_unite,m,n);
        }

}
void placer_unite_flotte_en_bas(Terrain_combat * un_terrain_combat, Flotte * flotte)
{
        int i,m,n;
        Unite * une_unite;
        for(i=0;i<(flotte->taille_flotte);i++)
        {
                une_unite=get_unite_i_flotte(flotte,i);
                m=(un_terrain_combat->taille_combat_x)-1;
                n=(un_terrain_combat->taille_combat_y)-1;
                set_x_unite(une_unite,m);
                set_y_unite(une_unite,n);
                while(case_libre(un_terrain_combat, m,n))
                {
                        set_y_unite(une_unite,n-1);
                        m=get_x_unite(une_unite);
                        n=get_y_unite(une_unite);
                }
                        ajoute_unite_terrain(un_terrain_combat, une_unite,m,n);
        }

}
void selectionner_case_combat(Jeu *jeu,Terrain_combat *un_terrain_combat,const int x, const int y)
{
        Case_terrain_combat *une_case;
        Unite * unite;
        une_case = get_case_terrain_combat(un_terrain_combat, x,y);
        unite = get_unite(une_case);
        if(get_selection_unite(une_case))
        {       set_une_case_selectionnee(un_terrain_combat,0);
                set_selection(un_terrain_combat,NULL);
                set_selection_unite(une_case, 0);
        }else if(get_presence_unite(une_case) && !get_une_case_selectionnee(un_terrain_combat) && (get_indice_joueur_unite(unite)== jeu-> joueur_en_cours)){
                set_selection_unite(une_case, 1);set_selection(un_terrain_combat,une_case);
                set_une_case_selectionnee(un_terrain_combat,1);}
}

void passer_tour_combat(Jeu * jeu, Terrain_combat * un_terrain_combat)
{
        Joueur * joueur;
        Flotte * flotte;
        if(jeu->joueur_en_cours == 0)
        {
                joueur=get_ieme_joueur_jeu(jeu, 0);
                flotte = get_ieme_flotte_joueur(joueur,0);
                reinitialiser_deplacement_unite_flotte(flotte);
                reinitialiser_pt_action_joueur(joueur);

                jeu->joueur_en_cours = 1;
        }
        else if (jeu->joueur_en_cours == 1)
        {
                joueur=get_ieme_joueur_jeu(jeu, 1);
                flotte = get_ieme_flotte_joueur(joueur,0);
                reinitialiser_deplacement_unite_flotte(flotte);
                reinitialiser_pt_action_joueur(joueur);
                jeu->joueur_en_cours = 0;
        }else{printf("ERREUR ! \n");}
}

void enlever_pt_action_ieme_joueur(Jeu * jeu, const int i, const int nb)
{
	Joueur * joueur;
	joueur= get_ieme_joueur_jeu(jeu,i);
	enlever_pt_action_joueur(joueur, nb);
}


/************************************************************************/
/* Fonctions de suvegarde et chargement                                 */
/************************************************************************/
void sauvegarde_jeu(const Jeu *un_jeu, FILE*f)
{
	int i;
    fprintf(f, "Jeu\n");
    fprintf(f, "%d\n", un_jeu->tour_en_cours);
    fprintf(f, "%d\n", un_jeu->joueur_en_cours);
    fprintf(f, "%d\n", un_jeu->joueur_en_cours_combat);
    fprintf(f, "%d\n", un_jeu->nb_joueur);
    for(i=0;i<un_jeu->nb_joueur;i++)
    {
        sauvegarde_joueur(&un_jeu->tab_joueur[i], f);
    }
    if(un_jeu->selection_flotte != NULL)
    {
        fprintf(f, "Flotte_Jeu\n");
        sauvegarde_flotte(un_jeu->selection_flotte, f);
    }
    else{
        fprintf(f, "AUCUNE_SELECTION\n");
    }
    if(un_jeu->selection_planete != NULL)
    {
        fprintf(f, "Planete_Jeu\n");
        sauvegarde_planete(un_jeu->selection_planete, f);
    }
    else{
        fprintf(f, "AUCUNE_SELECTION\n");
    }
    for(i=0;i<10;i++)
    {
        fprintf(f, "%d\n", un_jeu->tab_unite_selectionnee[i]);
    }
}

Jeu* ouverture_jeu(FILE *f)
{
    Jeu *jeu_ouvert;
    char chaine[50];
    int b, i;
    jeu_ouvert = creer_jeu();
    sscanf(fgets(chaine, 50, f), "%d", &jeu_ouvert->tour_en_cours);
    sscanf(fgets(chaine, 50, f), "%d", &jeu_ouvert->joueur_en_cours);
    sscanf(fgets(chaine, 50, f), "%d", &jeu_ouvert->joueur_en_cours_combat);
    sscanf(fgets(chaine, 50, f), "%d", &jeu_ouvert->nb_joueur);
    for(i=0;i<jeu_ouvert->nb_joueur;i++)
    {
        jeu_ouvert->tab_joueur[i] = *ouverture_joueur(f);
    }
    fgets(chaine, 50, f);
    if(strcmp(chaine, "AUCUNE_SELECTION\n")!=0)
    {
        ouverture_flotte(f);
    }
    fgets(chaine, 50, f);
    if(strcmp(chaine, "AUCUNE_SELECTION\n")!=0)
    {
        ouverture_planete(f);
    }
    for(i=0;i<10;i++)
    {
        sscanf(fgets(chaine, 50, f), "%d", &b);
        jeu_ouvert->tab_unite_selectionnee[i] = b;
    }
    return jeu_ouvert;
}
