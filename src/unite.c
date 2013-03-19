#include <stdlib.h>
#include <stdio.h>
#include "unite.h"

void initialise_unite(Unite *unite_jeu)
{
    unite_jeu->pt_vie=0;
    unite_jeu->pt_attaque=0;
    unite_jeu->pt_action=0;
    unite_jeu->pt_deplacement=0;
    initialise_niveau(unite_jeu->niveau_unite, machin, machin);
}

Unite creer_unite()
{
    Unite *nouvelle_unite = (Unite *)malloc(sizeof(Unite));
    initialise_unite(nouvelle_unite);
    return nouvelle_unite;
}

void libere_unite(Unite *unite_jeu)
{
    unite_jeu->pt_vie=0;
    unite_jeu->pt_attaque=0;
    unite_jeu->pt_action=0;
    unite_jeu->pt_deplacement=0;
    detruit_niveau(unite_jeu->niveau_unite);
}

void detruit(Unite **unite_jeu)
{
    libere_unite(*unite_jeu);
    free(*unite_jeu);
    *unite_jeu = NULL;
}

void set_pt_vie(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_vie = x;
}

int get_pt_vie(Unite *unite_jeu)
{
    return unite_jeu->pt_vie;
}


void set_pt_attaque(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_attaque = x;
}

int get_pt_attaque(Unite *unite_jeu)
{
    return unite_jeu->pt_attaque;
}

void set_pt_action(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_action = x;
}

int get_pt_action(Unite *unite_jeu)
{
    return unite_jeu->pt_action;
}

void set_pt_deplacement(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_deplacement = x;
}

int get_pt_deplacement(Unite *unite_jeu)
{
    return unite_jeu->pt_deplacement;
}