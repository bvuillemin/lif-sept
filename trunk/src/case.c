#include <stdlib.h>
#include <stdio.h>

#include "case.h"
#include "planete.h"

void initialise_case(Case_terrain *une_case_terrain)
{
    une_case_terrain->x=0;
    une_case_terrain->y=0;
    une_case_terrain->type_case='N';
    une_case_terrain->presence_unite=0;
	une_case_terrain->planete = NULL;
}

Case_terrain *creer_case()
{
    Case_terrain *une_case_terrain=(Case_terrain *)malloc(sizeof(Case_terrain));
    initialise_case(une_case_terrain);
    return une_case_terrain;
}

void set_x(Case_terrain *une_case_terrain, int x)
{
    une_case_terrain->x = x;
}

int get_x(const Case_terrain *une_case_terrain)
{
    return une_case_terrain->x;
}

void set_y(Case_terrain *une_case_terrain, int y)
{
    une_case_terrain->y = y;
}

int get_y(const Case_terrain *une_case_terrain)
{
    return une_case_terrain->y;
}

void definir_case_terrain(Case_terrain *une_case_terrain, char c)
{
    if((c == 'E')||(c == 'S')||(c == 'P'))
    {
        une_case_terrain->type_case = c;
    }
}

void libere_case_terrain(Case_terrain *une_case_terrain)
{
    free(une_case_terrain->planete);
    une_case_terrain->x=0;
    une_case_terrain->y=0;
    une_case_terrain->type_case='N';
    une_case_terrain->presence_unite=0;
}

void detruit_case_terrain(Case_terrain **une_case_terrain)
{
    libere_case_terrain(*une_case_terrain); /* libere_terrain(*une_case_terrain); */
    free(*une_case_terrain);
    *une_case_terrain = NULL;
}

void affiche_case_terrain(const Case_terrain *une_case_terrain)
{
    printf("|%c|", une_case_terrain->type_case);
}

void ajouter_planete(Case_terrain *une_case_terrain, Planete *une_planete)
{
    une_case_terrain->type_case = 'P';
    une_case_terrain->planete = une_planete;
    une_case_terrain->planete->x = une_case_terrain->x;
    une_case_terrain->planete->y = une_case_terrain->y;
}

void test_module_case_terrain()
{
    Case_terrain *une_case_terrain;
    printf("Verif de la création de cases\n");
    une_case_terrain = creer_case();
    definir_case_terrain(une_case_terrain, 'E');
    affiche_case_terrain(une_case_terrain);
    if((une_case_terrain->x == 0) && (une_case_terrain->y == 0))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}
}
