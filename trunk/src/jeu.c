#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "jeu.h"
#include "joueur.h"
#include "flotte.h"

int get_joueur_en_cours_combat(Jeu * jeu)
{
	return jeu->joueur_en_cours_combat;
}
void initialise_jeu(Jeu *un_jeu)
{
    int i;
	un_jeu->tour_en_cours = 0;
	un_jeu->joueur_en_cours = 0;
	un_jeu->joueur_en_cours_combat =0;
	un_jeu->nb_joueur = 0;
	un_jeu->selection_flotte = NULL;
	un_jeu->selection_planete = NULL;
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

void detruire_jeu(Jeu **un_jeu)
{
    liberer_jeu(*un_jeu);
    free(*un_jeu);
    *un_jeu = NULL;
}

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
	int metal = 0;
	int argent = 0;
	int carburant = 0;
	int population = 0;
	int i;

	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		metal = 0;
		argent = 0;
		carburant = 0;
		population = 0;

		recuperer_ressource_planete(&un_jeu->tab_joueur[i], &metal, &argent, &carburant, &population);

		un_jeu->tab_joueur[i].metal += metal;
		un_jeu->tab_joueur[i].argent += argent;
		un_jeu->tab_joueur[i].carburant += carburant;
		un_jeu->tab_joueur[i].population += population;
		/*printf("Ressources du tour %d pour le joueur %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n\n", un_jeu->tour_en_cours, i, metal, argent, carburant, population);*/
		reinitialiser_mouvement_flotte(&(un_jeu->tab_joueur[i].tab_flotte[0]));

		if(un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant > 0)
		{
			un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant --;
		}
		if(un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant == 0) /*a completer pour gerer automatiquement chaque planete de chaque joueur*/
		{
		    validation_batiment(un_jeu->tab_joueur[i].tab_planete[0]);
			un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant = -1;
		}

		if(un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant > 0)
		{
			un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant --; /*de meme*/
		}
		if(un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant == 0)
		{
		    validation_creation_unite_planete(un_jeu, un_terrain_espace, i, un_jeu->tab_joueur[i].tab_planete[0]->x, un_jeu->tab_joueur[i].tab_planete[0]->y);
			un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant = -1;
		}
	}
	un_jeu->tour_en_cours++;
}

void afficher_info(Jeu *un_jeu)
{
	printf("Joueur en cours %d, tour en cours %d \n", un_jeu->joueur_en_cours, un_jeu->tour_en_cours);
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
            une_unite = creer_unite(PT_VIE_UNITE_1, PT_ATTAQUE_UNITE_1, PT_ACTION_UNITE_1, PT_DEPLACEMENT_UNITE_1, 10, PT_MOUVEMENT_UNITE_1);
            une_flotte = creer_flotte();
            ajouter_unite_flotte(une_flotte, une_unite);
            ajouter_flotte_jeu(un_jeu, un_terrain_espace, une_flotte, indice_joueur_en_cours, x, y);
        }
    }
}

void afficher_ressource_joueur(Jeu *un_jeu)
{
	int i;
	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		printf("Ressources du joueur %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n\n", i, un_jeu->tab_joueur[i].metal, un_jeu->tab_joueur[i].argent, un_jeu->tab_joueur[i].carburant, un_jeu->tab_joueur[i].population);
	}
}

void ajouter_flotte_jeu(Jeu *un_jeu,Terrain_espace *un_terrain_espace, Flotte *une_flotte, int indice_joueur, int x, int y)
{
    ajouter_flotte_joueur(&un_jeu->tab_joueur[indice_joueur], une_flotte);
    ajouter_flotte(get_case_terrain_espace(un_terrain_espace, x, y), &un_jeu->tab_joueur[indice_joueur].tab_flotte[un_jeu->tab_joueur[indice_joueur].nb_flotte - 1]);
}

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
			if(fusion_flotte(un_joueur, un_terrain_espace, une_flotte, x, y))
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
            ajouter_flotte_jeu(un_jeu, un_terrain_espace,une_nouvelle_flotte, un_jeu->joueur_en_cours, x, y);
			distance = calcul_distance(x_depart, y_depart, x, y);
			enlever_pt_mouvement_espace_flotte(une_nouvelle_flotte, distance);
			return true;
		}
    }
    return false;
}

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
Joueur * get_ieme_joueur_jeu(Jeu * un_jeu,int i)
{
        return un_jeu->tab_joueur + i;
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
                reinitialiser_pt_action_unite_flotte(flotte);
                
                jeu->joueur_en_cours = 1;
        }
        else if (jeu->joueur_en_cours == 1)
        {
                joueur=get_ieme_joueur_jeu(jeu, 1);
                flotte = get_ieme_flotte_joueur(joueur,0);
                reinitialiser_deplacement_unite_flotte(flotte);
                reinitialiser_pt_action_unite_flotte(flotte);
                jeu->joueur_en_cours = 0;
        }else{printf("ERREUR ! \n");}
}
