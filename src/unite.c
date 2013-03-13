#include <stdlib.h>
#include <stdio.h>
#include "unite.h"

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