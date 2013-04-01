#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "jeu.h"
#include "joueur.h"

void initialise_jeu(Jeu *un_jeu)
{
	un_jeu->tour_en_cours = 0;
	un_jeu->nb_joueur = 0;
	*(un_jeu->tab_joueur) =(Joueur *)malloc(sizeof(Joueur *) * 10);
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
	Joueur *temp[1];
	i = un_jeu->nb_joueur;
	if(un_jeu->nb_joueur < 10)
	{
		temp[0] = un_joueur;
		un_jeu->tab_joueur[i] = temp[0];
		un_jeu->nb_joueur ++;
	}
}

void tour_suivant(Jeu *un_jeu)
{
	int metal = 0;
	int argent = 0;
	int carburant = 0;
	int population = 0;

	recuperer_ressource_planete( un_jeu->tab_joueur[0], &metal, &argent, &carburant, &population);
	printf("Ressources au tour %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n", un_jeu->tour_en_cours, metal, argent, carburant, population);
	
	un_jeu->tour_en_cours++;

}