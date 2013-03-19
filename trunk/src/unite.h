#ifndef _UNITE_H_
#define _UNITE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "niveau.h"


/**
 * \file      Module unité
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Unité et ses particularités
 *
 * \details
 */

typedef struct
{
	int pt_vie;
	int pt_attaque;
	int pt_action;
	int pt_deplacement;
	Niveau niveau_unite;
	//ressources nécessaires
	//compétence spéciale
}Unite;

void initialise_unite(Unite *unite_jeu);

void set_pt_vie(Unite *unite_jeu, const int x);
int get_pt_vie(const Unite *unite_jeu);

void set_pt_attaque(Unite *unite_jeu, const int x);
int get_pt_attaque(const Unite *unite_jeu);

void set_pt_action(Unite *unite_jeu, const int x);
int get_pt_action(const Unite *unite_jeu);

void set_pt_deplacement(Unite *unite_jeu, const int x);
int get_pt_deplacement(const Unite *unite_jeu);


#endif
