#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "case_terrain_combat.h"
#include "planete.h"

void initialise_case_combat(Case_terrain_combat *une_case_terrain_combat)
{
    une_case_terrain_combat->x_combat=0;
    une_case_terrain_combat->y_combat=0;
    une_case_terrain_combat->type_case_terrain_combat='N';
    une_case_terrain_combat->presence_unite=0;
	une_case_terrain_combat->unite = NULL;
}

Case_terrain_combat *creer_case_combat()
{
    Case_terrain_combat *une_case_terrain_combat=(Case_terrain_combat *)malloc(sizeof(Case_terrain_combat));
    initialise_case_combat(une_case_terrain_combat);
    return une_case_terrain_combat;
}

void set_x_combat(Case_terrain_combat *une_case_terrain_combat, int x)
{
    une_case_terrain_combat->x_combat = x;
}

int get_x_combat(const Case_terrain_combat *une_case_terrain_combat)
{
    return une_case_terrain_combat->x_combat;
}

void set_y_combat(Case_terrain_combat *une_case_terrain_combat, int y)
{
    une_case_terrain_combat->y_combat = y;
}

int get_y_combat(const Case_terrain_combat *une_case_terrain_combat)
{
    return une_case_terrain_combat->y_combat;
}

void set_type_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat, char type)
{
	une_case_terrain_combat->type_case_terrain_combat = type;
}

char get_type_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat)
{
	return une_case_terrain_combat->type_case_terrain_combat;
}

void set_presence_unite(Case_terrain_combat *une_case_terrain_combat,bool p)
{
	une_case_terrain_combat->presence_unite = p;
}
bool get_presence_unite(Case_terrain_combat *une_case_terrain_combat)
{
	return une_case_terrain_combat->presence_unite;
}
/*
void set_id_joueur(Case_terrain_combat *une_case_terrain_combat, int id_joueur)
{
	une_case_terrain_combat->id_joueur = id_joueur;
}
int get_id_joueur(const Case_terrain_combat *une_case_terrain_combat)
{
	return une_case_terrain_combat->id_joueur;
}*/

void definir_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat, char c)
{
    if((c == 'E')||(c == '1')||(c == '2')) /*'2' pour les unites du joueur 2, '1' pour les unités du joueur 1, 'E' pour l'espace */
    {
        une_case_terrain_combat->type_case_terrain_combat = c;
    }
}

void libere_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat)
{
    free(une_case_terrain_combat->unite);
    une_case_terrain_combat->x_combat=0;
    une_case_terrain_combat->y_combat=0;
    une_case_terrain_combat->type_case_terrain_combat='N';
    une_case_terrain_combat->presence_unite=0;
}

void detruit_case_terrain_combat(Case_terrain_combat **une_case_terrain_combat)
{
    libere_case_terrain_combat(*une_case_terrain_combat);
    free(*une_case_terrain_combat);
    *une_case_terrain_combat = NULL;
}

void affiche_case_terrain_combat(const Case_terrain_combat *une_case_terrain_combat)
{
    printf("|%c|", une_case_terrain_combat->type_case_terrain_combat);
}


void set_unite(Case_terrain_combat *une_case_terrain_combat, Unite *une_unite)
{
    une_case_terrain_combat->unite = une_unite;
    une_case_terrain_combat->presence_unite = true;
    une_case_terrain_combat->unite->x_unite = une_case_terrain_combat->x_combat;
    une_case_terrain_combat->unite->y_unite = une_case_terrain_combat->y_combat;
}

Unite * get_unite(Case_terrain_combat *une_case_terrain_combat)
{
	return une_case_terrain_combat->unite;
}

void ajouter_unite(Case_terrain_combat *une_case_terrain_combat, Unite *une_unite)
{
    une_case_terrain_combat->unite = une_unite;
    une_case_terrain_combat->presence_unite = true;
    une_case_terrain_combat->unite->x_unite = une_case_terrain_combat->x_combat;
    une_case_terrain_combat->unite->y_unite = une_case_terrain_combat->y_combat;
}

void retirer_unite(Case_terrain_combat *une_case_terrain_combat)
{
    une_case_terrain_combat->unite = NULL;
    une_case_terrain_combat->presence_unite = false;
}

void test_module_case_terrain_combat()
{
    Case_terrain_combat *une_case_terrain_combat;
    printf("Verif de la création de cases\n");
    une_case_terrain_combat = creer_case_combat();
    definir_case_terrain_combat(une_case_terrain_combat, 'E');
    affiche_case_terrain_combat(une_case_terrain_combat);
    if((une_case_terrain_combat->x_combat == 0) && (une_case_terrain_combat->y_combat == 0))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}
}

