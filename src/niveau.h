#ifndef _NIVEAU_H_
#define _NIVEAU_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



/**
 * \file      Module terrain
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Niveau des unites
 *
 * \details
 */


typedef struct
{
	/* Unite unite; */
	int niveau_unite;
	int experience;
}Niveau;

void initilalise_niveau(Niveau *niveau, int niv, int exp);
Niveau *creer_niveau(int niv, int exp);

void set_niveau_unite(Niveau *niveau, int niv);
int get_niveau_unite(const Niveau *niveau);

void set_experience(Niveau *niveau, int exp);
int get_experience(const Niveau *niveau);

void augmenter_niveau(Niveau *niveau);
void augmenter_experience(Niveau *niveau);

void libere_niveau(Niveau *niveau);
void detruit_niveau(Niveau **niveau);

void sauvegarde_niveau(const Niveau *un_niveau, FILE* f);
Niveau* ouverture_niveau(FILE *f);

#endif
