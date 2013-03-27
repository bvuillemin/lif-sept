#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char nom_joueur[20];
    enum {bleu, rouge} couleur_joueur;
    int ressource_1;
}Joueur;

void set_nom_joueur(Joueur *un_joueur, char nom[20]);
void set_couleur(Joueur *un_joueur, int i);
int get_couleur(const Joueur *un_joueur);
void set_ressource(Joueur *un_joueur, int nb);
int get_ressource(const Joueur *un_joueur);

void ajouter_ressource(Joueur *un_joueur, int nb);
void retirer_ressource(Joueur *un_joueur, int nb);












#endif
