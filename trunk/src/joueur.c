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

void set_ressource(Joueur *un_joueur, int nb)
{
    un_joueur->ressource_1 = nb;
}

int get_ressource(const Joueur *un_joueur)
{
    return un_joueur->ressource_1;
}


void ajouter_ressource(Joueur *un_joueur, int nb)
{
    un_joueur->ressource_1 = un_joueur->ressource_1 + nb;
}

void retirer_ressource(Joueur *un_joueur, int nb)
{
    un_joueur->ressource_1 = un_joueur->ressource_1 - nb;
}




