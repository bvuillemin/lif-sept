#ifndef _CASE_TERRAIN_COMBAT_H_
#define _CASE_TERRAIN_COMBAT_H_

#include "joueur.h"

/**
 * \file      Module case_terrain_combat
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Case du Terrain_combat et ses particularités
 *
 * \details
 */

/**
 * \struct Case_terrain_combat
 * \brief case du terrain du combat
 */
typedef struct
{
    /**abscisse et ordonnée de la case*/
    int x_combat,y_combat;
    /**type de la case*/
    char type_case_terrain_combat;/* N si non initialisé*/
    /**1 si la case contient une unité, 0 sinon*/
    bool presence_unite;
    /**1 si la case est sélectionnée 0 sinon*/
	bool selection_unite;
    /**une unité*/
	Unite *unite;
	/*int id_joueur;*/
}Case_terrain_combat;

void initialise_case_combat(Case_terrain_combat *une_case_terrain_combat);
Case_terrain_combat *creer_case_combat();

void set_x_combat(Case_terrain_combat *une_case_terrain_combat, const int x_combat);
int get_x_combat(const Case_terrain_combat *une_case_terrain_combat);
void set_y_combat(Case_terrain_combat *une_case_terrain_combat, const int y_combat);
int get_y_combat(const Case_terrain_combat *une_case_terrain_combat);
void set_type_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat, const char type);
char get_type_case_terrain_combat(const Case_terrain_combat *une_case_terrain_combat);

/*void set_id_joueur(Case_terrain_combat *une_case_terrain_combat, int id_joueur);
int get_id_joueur(const Case_terrain_combat *une_case_terrain_combat);*/

void set_selection_unite(Case_terrain_combat *une_case_terrain_combat,const bool p);
bool get_selection_unite(const Case_terrain_combat *une_case_terrain_combat);

void set_presence_unite(Case_terrain_combat *une_case_terrain_combat,const bool p);
bool get_presence_unite(const Case_terrain_combat *une_case_terrain_combat);

void detruit_case_terrain_combat(Case_terrain_combat **une_case_terrain_combat);
void libere_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat);

void definir_case_terrain_combat(Case_terrain_combat *une_case_terrain_combat, const char c);

void set_unite(Case_terrain_combat *une_case_terrain_combat, Unite *une_unite);
Unite * get_unite(const Case_terrain_combat *une_case_terrain_combat);

void ajouter_unite(Case_terrain_combat *une_case_terrain_combat, Unite *une_unite);
void retirer_unite(Case_terrain_combat *une_case_terrain_combat);

void affiche_case_terrain_combat(const Case_terrain_combat *une_case_terrain_combat);
void test_module_case_terrain_combat();


#endif


