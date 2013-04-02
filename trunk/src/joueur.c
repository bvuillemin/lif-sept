#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "planete.h"
#include "joueur.h"

void set_nom_joueur(Joueur *un_joueur, char nom[20])
{
    strcpy(un_joueur->nom_joueur, nom);
}

void set_couleur(Joueur *un_joueur, int i)
{
    if((i==0)||(i==1))
    {
        un_joueur->couleur_joueur = i;
    }
}

int get_couleur(const Joueur *un_joueur)
{
    return un_joueur->couleur_joueur;
}

void set_metal_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->metal = nb;
}

int get_metal_joueur(const Joueur *un_joueur)
{
    return un_joueur->metal;
}

void set_argent_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->argent = nb;
}

int get_argent_joueur(const Joueur *un_joueur)
{
    return un_joueur->argent;
}

void set_carburant_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->carburant = nb;
}

int get_carburant_joueur(const Joueur *un_joueur)
{
    return un_joueur->carburant;
}

void set_population_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->population = nb;
}

int get_population_joueur(const Joueur *un_joueur)
{
    return un_joueur->population;
}

void set_nb_planete(Joueur *un_joueur, int nb)
{

}

int get_nb_planete(Joueur *un_joueur)
{
	return un_joueur->nb_planete;
}

void ajouter_planete_joueur(Joueur *un_joueur, Planete *une_planete)
{
	/*int i;

	if(un_joueur->nb_planete == un_joueur->nb_planete_possible)
	{
		Planete *temp;
		temp = *(un_joueur->tab_planete);

		*(un_joueur->tab_planete) =(Planete *)malloc(sizeof(Planete *) * (un_joueur->nb_planete_possible +10));
		for(i=0;i<un_joueur->nb_planete_possible;i++)
		{
			*(un_joueur->tab_planete[i]) = temp[i];
		}

		free(temp);
		un_joueur->nb_planete_possible = un_joueur->nb_planete_possible +10;
	}

	i = un_joueur->nb_planete;

	temp[0] = une_planete;
	un_joueur->tab_planete[i] = temp[0];
	un_joueur->nb_planete ++;*/

    int i = un_joueur->nb_planete;
    if(i< un_joueur->nb_planete_possible)
    {
        (un_joueur->tab_planete)[i] = une_planete;
        un_joueur->nb_planete ++;
    }
}

void ajouter_flotte_joueur(Joueur *un_joueur, Flotte une_flotte)
{
    int i = un_joueur->nb_flotte;
    if(i< un_joueur->nb_flotte_possible)
    {
        un_joueur->tab_flotte[0] = une_flotte;
        un_joueur->nb_flotte ++;
    }

}

void recuperer_ressource_planete(Joueur *un_joueur, int *metal, int *argent, int *carburant, int *population)
{
	int i;
	for(i = 0; i < un_joueur->nb_planete;i++)
	{
		*metal = *metal + un_joueur->tab_planete[i]->metal;
		*argent = *argent + un_joueur->tab_planete[i]->argent;
		*carburant = *carburant + un_joueur->tab_planete[i]->carburant;
		*population = *population + un_joueur->tab_planete[i]->population;
	}
}


void initialise_joueur(Joueur *un_joueur, int num_joueur, char nom[20])
{
    un_joueur->numero_joueur = num_joueur;
	/*un_joueur->bleu;
	strcpy(un_joueur->nom_joueur, nom);*/
	un_joueur->metal = 0;
	un_joueur->argent = 0;
	un_joueur->carburant = 0;
	un_joueur->population = 0;
	un_joueur->nb_planete = 0;
	un_joueur->nb_planete_possible = 10;
	un_joueur->tab_planete = (Planete **)malloc(sizeof(Planete *) * 10);
	un_joueur->nb_flotte = 0;
	un_joueur->nb_flotte_possible = 0;
	un_joueur->tab_flotte = (Flotte *)malloc(sizeof(Flotte) * 10);

}

Joueur *creer_joueur(int num_joueur, char nom[30])
{
    Joueur *un_joueur=(Joueur *)malloc(sizeof(Joueur));
    initialise_joueur(un_joueur,num_joueur, nom);
    return un_joueur;
}



void ajouter_metal(Joueur *un_joueur, int nb)
{
    un_joueur->metal = un_joueur->metal + nb;
}

void retirer_metal(Joueur *un_joueur, int nb)
{
    un_joueur->metal = un_joueur->metal - nb;
}

void ajouter_argent(Joueur *un_joueur, int nb)
{
    un_joueur->argent = un_joueur->argent + nb;
}

void retirer_argent(Joueur *un_joueur, int nb)
{
    un_joueur->argent = un_joueur->argent - nb;
}
void ajouter_carburant(Joueur *un_joueur, int nb)
{
    un_joueur->carburant = un_joueur->carburant + nb;
}

void retirer_carburant(Joueur *un_joueur, int nb)
{
    un_joueur->carburant = un_joueur->carburant - nb;
}
void ajouter_population(Joueur *un_joueur, int nb)
{
    un_joueur->population = un_joueur->population + nb;
}

void retirer_population(Joueur *un_joueur, int nb)
{
    un_joueur->population = un_joueur->population - nb;
}


