/**
 * \file      TableauDynamique.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les tableaux dynamiques
 * \details   Cette classe définit les tableaux dynamiques et permet leur implémentation dans le jeu (dans joueur)
 */

#include <stdlib.h>
#include <stdio.h>

#include "TableauDynamique.h"

void initialiserTabDyn(TableauDynamique *t)
{
	(*t).capacite = 1;
	(*t).ad = malloc(sizeof(Flotte));
	(*t).taille_utilisee = 0;
}


void testamentTabDyn(TableauDynamique *t)
{
	if((*t).ad !=0)
	{
		free ((*t).ad);
		(*t).ad = 0;
		(*t).capacite = 0;
		(*t).taille_utilisee = 0;
	}
}

void ajouterElementTabDyn(TableauDynamique *t, Flotte* e)
{
	if (((*t).capacite)==((*t).taille_utilisee))
	{
		int i;
		Flotte *temp = (*t).ad;
		(*t).ad = malloc (2* (*t).capacite * sizeof(Flotte));
		for (i=0;i<(*t).taille_utilisee;i++)
		{
			(*t).ad[i]=temp[i];
		}
		(*t).capacite=(*t).capacite * 2;
		free(temp);
	}
	(*t).ad[(*t).taille_utilisee] = *e;
	(*t).taille_utilisee++;

}


Flotte* valeurIemeElementTabDyn(const TableauDynamique *t, unsigned int i)
{
	return &(*t).ad[i-1];
}

void modifierValeurIemeElementTabDyn(TableauDynamique *t, Flotte e, unsigned int i)
{
	(*t).ad[i-1]=e;
}

void supprimerElementTabDyn( TableauDynamique *t, int position )
{
	int i;
	for(i=position-1;i<(*t).taille_utilisee-1;i++)
	{
		(*t).ad[i]=(*t).ad[i+1];
	}
	(*t).taille_utilisee--;

	if ((*t).taille_utilisee < ((*t).capacite / 3))
	{
		Flotte *temp = (*t).ad;
		(*t).ad= malloc (((*t).capacite / 2)*sizeof(Flotte));
		for (i=0;i<(*t).taille_utilisee;i++)
		{
			(*t).ad[i]=temp[i];
		}
		(*t).capacite=(*t).capacite/2;
		free(temp);
	}
}

void insererElementTabDyn(TableauDynamique *t, Flotte e, unsigned int i)
{
	int j;
	if (((*t).capacite)==((*t).taille_utilisee + 1))
	{
		Flotte *temp = (*t).ad;
		(*t).ad = malloc (2* (*t).capacite * sizeof(Flotte));
		for (j=0;j<(*t).capacite;j++)
		{
			(*t).ad[j]=temp[j];
		}
		(*t).capacite=(*t).capacite * 2;
		free(temp);
	}

	for(j=(*t).taille_utilisee;j>=i;j--)
	{
		(*t).ad[j]=(*t).ad[j-1];
	}
	(*t).ad[i-1]=e;
	(*t).taille_utilisee++;

}
