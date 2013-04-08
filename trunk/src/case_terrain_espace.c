#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "case_terrain_espace.h"
#include "planete.h"
#include "flotte.h"

void initialise_case_espace(Case_terrain_espace *une_case_terrain_espace)
{
    une_case_terrain_espace->x_espace=0;
    une_case_terrain_espace->y_espace=0;
    une_case_terrain_espace->type_case_terrain_espace='N';
    une_case_terrain_espace->presence_flotte=0;
	une_case_terrain_espace->planete = NULL;
	une_case_terrain_espace->flotte = NULL;
}

Case_terrain_espace *creer_case_espace()
{
    Case_terrain_espace *une_case_terrain_espace=(Case_terrain_espace *)malloc(sizeof(Case_terrain_espace));
    initialise_case_espace(une_case_terrain_espace);
    return une_case_terrain_espace;
}

void set_x_espace(Case_terrain_espace *une_case_terrain_espace, int x)
{
    une_case_terrain_espace->x_espace = x;
}

int get_x_espace(const Case_terrain_espace *une_case_terrain_espace)
{
    return une_case_terrain_espace->x_espace;
}

void set_y_espace(Case_terrain_espace *une_case_terrain_espace, int y)
{
    une_case_terrain_espace->y_espace = y;
}

int get_y_espace(const Case_terrain_espace *une_case_terrain_espace)
{
    return une_case_terrain_espace->y_espace;
}

void set_type_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace, char type)
{
	une_case_terrain_espace->type_case_terrain_espace = type;
}

char get_type_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace)
{
	return une_case_terrain_espace->type_case_terrain_espace;
}

Planete * get_planete(Case_terrain_espace *une_case_terrain_espace)
{
	return une_case_terrain_espace->planete;
}

Flotte * get_flotte(Case_terrain_espace *une_case_terrain_espace)
{
	return une_case_terrain_espace->flotte;
}

void definir_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace, char c)
{
    if((c == 'E')||(c == 'F')||(c == 'P'))
    {
        c = get_type_case_terrain_espace(une_case_terrain_espace);
    }
}

void libere_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace)
{
    detruire_planete(&(une_case_terrain_espace->planete));
    une_case_terrain_espace->x_espace=0;
    une_case_terrain_espace->y_espace=0;
    une_case_terrain_espace->type_case_terrain_espace='N';
    une_case_terrain_espace->presence_flotte=0;
}

void detruit_case_terrain_espace(Case_terrain_espace **une_case_terrain_espace)
{
    libere_case_terrain_espace(*une_case_terrain_espace);
    free(*une_case_terrain_espace);
    *une_case_terrain_espace = NULL;
}

void affiche_case_terrain_espace(const Case_terrain_espace *une_case_terrain_espace)
{
    printf("|%c|", une_case_terrain_espace->type_case_terrain_espace);
}

void ajouter_planete(Case_terrain_espace *une_case_terrain_espace, Planete *une_planete)
{
    une_case_terrain_espace->type_case_terrain_espace = 'P';
    une_case_terrain_espace->planete = une_planete;
    une_case_terrain_espace->planete->x = une_case_terrain_espace->x_espace;
    une_case_terrain_espace->planete->y = une_case_terrain_espace->y_espace;
}

void ajouter_flotte(Case_terrain_espace *une_case_terrain_espace, Flotte *une_flotte)
{
    une_case_terrain_espace->flotte = une_flotte;
    une_case_terrain_espace->presence_flotte = true;
    une_case_terrain_espace->flotte->x_flotte = une_case_terrain_espace->x_espace;
    une_case_terrain_espace->flotte->y_flotte = une_case_terrain_espace->y_espace;
}

void retirer_flotte(Case_terrain_espace *une_case_terrain_espace)
{
    une_case_terrain_espace->flotte = NULL;
    une_case_terrain_espace->presence_flotte = false;
}

void test_module_case_terrain_espace()
{
    Case_terrain_espace *une_case_terrain_espace;
    printf("Verif de la création de cases\n");
    une_case_terrain_espace = creer_case_espace();
    definir_case_terrain_espace(une_case_terrain_espace, 'E');
    affiche_case_terrain_espace(une_case_terrain_espace);
    if((une_case_terrain_espace->x_espace == 0) && (une_case_terrain_espace->y_espace == 0))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}
}

