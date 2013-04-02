#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "jeu.h"
#include "joueur.h"
#include "flotte.h"

void initialise_jeu(Jeu *un_jeu)
{
	un_jeu->tour_en_cours = 0;
	un_jeu->nb_joueur = 0;
	un_jeu->tab_joueur =(Joueur *)malloc(sizeof(Joueur *) * 10);
}

Jeu *creer_jeu()
{
	Jeu *un_jeu=(Jeu *)malloc(sizeof(Jeu));
    initialise_jeu(un_jeu);
    return un_jeu;
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
}

void tour_suivant(Jeu *un_jeu)
{
	int metal = 0;
	int argent = 0;
	int carburant = 0;
	int population = 0;

	recuperer_ressource_planete(&(un_jeu->tab_joueur[0]), &metal, &argent, &carburant, &population);

	un_jeu->tab_joueur[0].metal += metal;
	un_jeu->tab_joueur[0].argent += argent;
	un_jeu->tab_joueur[0].carburant += carburant;
	un_jeu->tab_joueur[0].population += population;
	printf("Ressources du tour %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n", un_jeu->tour_en_cours, metal, argent, carburant, population);
	
    reinitialiser_mouvement_flotte(&(un_jeu->tab_joueur[0].tab_flotte[0]));
	un_jeu->tour_en_cours++;
}

void afficher_ressource_joueur(Jeu *un_jeu)
{
	printf("Ressources du joueur %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n\n", un_jeu->tour_en_cours, un_jeu->tab_joueur[0].metal, un_jeu->tab_joueur[0].argent, un_jeu->tab_joueur[0].carburant, un_jeu->tab_joueur[0].population);
}