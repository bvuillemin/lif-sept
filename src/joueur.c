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

int get_metal_joueur(Joueur *un_joueur)
{
    return un_joueur->metal;
}

void set_argent_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->argent = nb;
}

int get_argent_joueur(Joueur *un_joueur)
{
    return un_joueur->argent;
}

void set_carburant_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->carburant = nb;
}

int get_carburant_joueur(Joueur *un_joueur)
{
    return un_joueur->carburant;
}

void set_population_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->population = nb;
}

int get_population_joueur(Joueur *un_joueur)
{
    return un_joueur->population;
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


