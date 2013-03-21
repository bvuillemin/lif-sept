#ifndef _CASE_H_
#define _CASE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "planete.h"

/**
 * \file      Module case
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Case et ses particularités
 *
 * \details
 */

typedef struct
{
    int x,y;
    char type_case;// E pour l'espace, P pour une planète, N si non initialisé
    bool presence_unite;
	Planete *planete;//lien sur une planète si la case est de type planète, sinon NULL
}Case_terrain;

void initialise_case(Case_terrain *une_case_terrain);
Case_terrain *creer_case();

void set_x(Case_terrain *une_case_terrain, int x);
int get_x(const Case_terrain *une_case_terrain);

void set_y(Case_terrain *une_case_terrain, int y);
int get_y(const Case_terrain *une_case_terrain);

void detruit_case_terrain(Terrain **une_case_terrain);
void libere_case_terrain(Case_terrain *une_case_terrain);

void definir_case_terrain(Case_terrain *une_case_terrain, char c);

void affiche_case_terrain(const Case_terrain *une_case_terrain);
void test_module_case_terrain();


#endif
