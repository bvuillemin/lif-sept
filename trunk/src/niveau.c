#include <stdlib.h>
#include <stdio.h>
#include "unite.h"
#include "niveau.h"

void initilalise_niveau(Niveau *niveau, int niv, int exp)
{
    niveau -> niveau_unite = niv;
	niveau -> experience = exp;
}

Niveau *creer_niveau(int niv, int exp)
{
    Niveau *niveau=(Niveau *)malloc(sizeof(Niveau));
    initilalise_niveau(niveau, niv, exp);
    return niveau;
}

void set_niveau_unite(Niveau * niveau, int niv)
{
	niveau->niveau_unite=niv;
}
int get_niveau_unite(const Niveau * niveau)
{
	return niveau->niveau_unite;
}
void set_experience(Niveau *niveau, int exp)
{
	niveau -> experience=exp;
}
int get_experience(const Niveau *niveau)
{
	return niveau -> experience;
}

void augmenter_niveau(Niveau *niveau){}
void augmenter_experience(Niveau *niveau){}


void libere_niveau(Niveau *niveau)
{
	niveau->niveau_unite=0;
	niveau->experience=0;
}
void detruit_niveau(Niveau **niveau)
{
	libere_niveau(*niveau);
	free(*niveau);
	*niveau=NULL;
}

