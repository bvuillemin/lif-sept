#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "jeu.h"
#include "joueur.h"
#include "flotte.h"

void initialise_jeu(Jeu *un_jeu)
{
	un_jeu->tour_en_cours = 0;
	un_jeu->joueur_en_cours = 0;
	un_jeu->nb_joueur = 0;
	un_jeu->tab_joueur =(Joueur *)malloc(sizeof(Joueur) * 10);
}

Jeu *creer_jeu()
{
	Jeu *un_jeu=(Jeu *)malloc(sizeof(Jeu));
    initialise_jeu(un_jeu);
    return un_jeu;
}


void liberer_jeu(Jeu *un_jeu)
{
    int i;
    for(i=0;i<un_jeu->nb_joueur;i++)
    {
        liberer_joueur(&un_jeu->tab_joueur[i]);
    }
    free(un_jeu->tab_joueur);
    un_jeu->tour_en_cours = 0;
    un_jeu->joueur_en_cours = 0;
    un_jeu->nb_joueur = 0;
}

void detruire_jeu(Jeu **un_jeu)
{
    liberer_jeu(*un_jeu);
    free(*un_jeu);
    *un_jeu = NULL;
}

void ajouter_joueur(Jeu *un_jeu, Joueur *un_joueur)
{
	int i;
	i = un_jeu->nb_joueur;
	if(un_jeu->nb_joueur < 10)
	{
		un_jeu->tab_joueur[i] = *un_joueur;
		un_jeu->nb_joueur ++;
	}
	free(un_joueur);
}

void joueur_suivant(Jeu *un_jeu)
{
	if(un_jeu->joueur_en_cours +1 < un_jeu->nb_joueur)
	{
		un_jeu->joueur_en_cours ++;
	}
	else
	{
		tour_suivant(un_jeu);
		un_jeu->joueur_en_cours = 0;
	}
}

void tour_suivant(Jeu *un_jeu)
{
	int metal = 0;
	int argent = 0;
	int carburant = 0;
	int population = 0;
	int i;

	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		metal = 0;
		argent = 0;
		carburant = 0;
		population = 0;

		recuperer_ressource_planete(&(un_jeu->tab_joueur[i]), &metal, &argent, &carburant, &population);

		un_jeu->tab_joueur[i].metal += metal;
		un_jeu->tab_joueur[i].argent += argent;
		un_jeu->tab_joueur[i].carburant += carburant;
		un_jeu->tab_joueur[i].population += population;
		printf("Ressources du tour %d pour le joueur %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n\n", un_jeu->tour_en_cours, i, metal, argent, carburant, population);
		reinitialiser_mouvement_flotte(&(un_jeu->tab_joueur[i].tab_flotte[0]));
		un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant --;
		un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant --;
	}
	un_jeu->tour_en_cours++;
}

void afficher_info(Jeu *un_jeu)
{
	printf("Joueur en cours %d, tour en cours %d \n", un_jeu->joueur_en_cours, un_jeu->tour_en_cours);
}

void afficher_ressource_joueur(Jeu *un_jeu)
{
	int i;
	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		printf("Ressources du joueur %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n\n", i, un_jeu->tab_joueur[i].metal, un_jeu->tab_joueur[i].argent, un_jeu->tab_joueur[i].carburant, un_jeu->tab_joueur[i].population);
	}
}
