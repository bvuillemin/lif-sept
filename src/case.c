#include <stdlib.h>
#include <stdio.h>
#include "case.h"

void initialise_case(Case_terrain *case_terrain)
{
    case_terrain->x=0;
    case_terrain->y=0;
    case_terrain->type_case='N';
    case_terrain->presence_unite=0;
}

Case_terrain *creer_case()
{
    Case_terrain *case_terrain=(Case_terrain *)malloc(sizeof(Case_terrain));
    initialise_case(case_terrain);
    return case_terrain;
}

void set_x(Case_terrain *case_terrain, int x)
{
    case_terrain->x = x;
}

int get_x(const Case_terrain *case_terrain)
{
    return case_terrain->x;
}

void set_y(Case_terrain *case_terrain, int y)
{
    case_terrain->y = y;
}

int get_y(const Case_terrain *case_terrain)
{
    return case_terrain->y;
}

void definir_case_terrain(Case_terrain *case_terrain, char c)
{
    if((c == 'E')||(c == 'S')||(c == 'P'))
    {
        case_terrain->type_case = c;
    }
}

void affiche_case_terrain(const Case_terrain *case_terrain)
{
    printf("|%c|", case_terrain->type_case);
}

void test_module_case_terrain()
{
    Case_terrain *case_terrain;
    printf("Verif de la création de cases\n");
    case_terrain = creer_case();
    definir_case_terrain(case_terrain, 'E');
    affiche_case_terrain(case_terrain);
    if((case_terrain->x == 0) && (case_terrain->y == 0))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}
}
