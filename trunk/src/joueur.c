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
	int i;
	int nb_precedent = un_joueur->nb_planete;
	if(nb_precedent<nb)
    {
        Planete *temp = un_joueur->tab_planete;
        un_joueur->tab_planete = malloc (sizeof(Planete)*nb);
        for(i=0;i<nb_precedent;i++)
        {
            un_joueur->tab_planete[i]=temp[i];
        }
        un_joueur->nb_planete = nb;
        free(temp);
    }
}


int get_nb_planete(Joueur *un_joueur)
{
	return un_joueur->nb_planete;
}


void initialise_joueur(Joueur *un_joueur)
{
	//un_joueur->bleu;
	//un_joueur->nom_joueur =(char *)malloc(sizeof(char) * 20);
	un_joueur->metal = 0;
	un_joueur->argent = 0;
	un_joueur->carburant = 0;
	un_joueur->population = 0;
	un_joueur->nb_planete = 1;
	un_joueur->tab_planete = (Planete *)malloc(sizeof(Planete));

}

Joueur *creer_joueur()
{
    Joueur *un_joueur=(Joueur *)malloc(sizeof(Joueur));
    initialise_joueur(un_joueur);
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


