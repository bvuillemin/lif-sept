/**
 * \file      case_terrain_espace.h
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les cases d'un terrain d'espace
 * \details   Cette classe définit les cases d'un terrain d'espace et leurs caractéristiques
 */

#ifndef _CASE_TERRAIN_ESPACE_H_
#define _CASE_TERRAIN_ESPACE_H_

#include <string.h>
#include "planete.h"
#include "flotte.h"

typedef struct
{
    int x_espace,y_espace;
    char type_case_terrain_espace;/* E pour l'espace, P pour une planète, N si non initialisé*/
    bool presence_flotte;
	/*bool est_visible;*/
	Planete *planete;/*lien sur une planète si la case est de type planète, sinon NULL*/
	Flotte *flotte;
}Case_terrain_espace;


void initialiser_case_espace(Case_terrain_espace *une_case_terrain_espace);
Case_terrain_espace *creer_case_espace();
void detruire_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace);
void liberer_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace);

void set_x_espace(Case_terrain_espace *une_case_terrain_espace,const int x);
int get_x_espace(const Case_terrain_espace *une_case_terrain_espace);
void set_y_espace(Case_terrain_espace *une_case_terrain_espace,const int y);
int get_y_espace(const Case_terrain_espace *une_case_terrain_espace);
void set_type_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace, const char type);
char get_type_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace);
Planete * get_planete(const Case_terrain_espace *une_case_terrain_espace);
Flotte * get_flotte(const Case_terrain_espace *une_case_terrain_espace);
bool get_presence_flotte(Case_terrain_espace* une_case);

void definir_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace, const char c);
void ajouter_planete(Case_terrain_espace *une_case_terrain_espace, Planete *une_planete);
void ajouter_flotte(Case_terrain_espace *une_case_terrain_espace, Flotte *une_flotte);
void retirer_flotte(Case_terrain_espace *une_case_terrain_espace);
void affiche_case_terrain_espace(const Case_terrain_espace *une_case_terrain_espace);
void test_module_case_terrain_espace();

void sauvegarde_case_terrain_espace(const Case_terrain_espace *une_case_terrain_espace, FILE*f);
Case_terrain_espace* ouverture_case_terrain_espace(FILE*f);
void testRegression_case_terrain_espace();




#endif

