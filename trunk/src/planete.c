#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "planete.h"

void initialise_planete(Planete *une_planete, char nom_planete[30])
{
    une_planete->x = 0;
    une_planete->y = 0;
    strcpy(une_planete->nom_planete, nom_planete); 
    une_planete->planete_colonisee = 0;
    une_planete->planete_principale = 0;
	une_planete->habitabilite = 0;
    une_planete->taille_planete = 0; /* a modifier*/
    une_planete->taille_utilisee = 0;
    une_planete->metal = 0;
    une_planete->argent = 0;
    une_planete->carburant = 0;
    une_planete->population = 0;
}

Planete *creer_planete(char nom_planete[30])
{
    Planete *une_planete=(Planete *)malloc(sizeof(Planete));
    initialise_planete(une_planete, nom_planete);
    return une_planete;
}

void libere_planete(Planete *une_planete)
{
    une_planete->x = 0;
    une_planete->y = 0;
    free(une_planete->nom_planete);
    une_planete->planete_colonisee = 0;
    une_planete->planete_principale = 0;
	une_planete->habitabilite = 0;
    une_planete->taille_planete = 0;
    une_planete->taille_utilisee = 0;
    une_planete->metal = 0;
    une_planete->argent = 0;
    une_planete->carburant = 0;
    une_planete->population = 0;
}

void detruit_planete(Planete **une_planete)
{
    libere_planete(*une_planete);
    free(*une_planete);
    *une_planete = NULL;
}

void set_nom_planete(Planete *une_planete, char nom[30])
{
    strcpy(une_planete->nom_planete, nom);
}

void set_taille_utilisee(Planete *une_planete, int taille_utilisee)
{
    une_planete->taille_utilisee = taille_utilisee;
}

int get_taille_utilisee(Planete *une_planete)
{
    return une_planete->taille_utilisee;
}

void set_taille_planete(Planete *une_planete, int taille_planete)
{
    une_planete->taille_planete = taille_planete;
}

int get_taille_planete(Planete *une_planete)
{
    return une_planete->taille_planete;
}

void set_habitabilite(Planete *une_planete, int nb)
{
	une_planete->habitabilite=nb;
}

int get_habitabilite(Planete *une_planete)
{
	return une_planete->habitabilite;
}

void set_planete_principale(Planete *une_planete, int booleen)
{
    if ((booleen == 0) || (booleen == 1))
    {
        une_planete->planete_principale = booleen;
    }
}

int get_planete_principale(Planete *une_planete)
{
    return une_planete->planete_principale;
}

void set_planete_colonisee(Planete *une_planete, int booleen)
{
    if ((booleen == 0) || (booleen == 1))
    {
        une_planete->planete_colonisee = booleen;
    }
}

int get_planete_colonisee(Planete *une_planete)
{
    return une_planete->planete_colonisee;
}

void set_metal(Planete *une_planete, int nb)
{
    une_planete->metal = nb;
}

int get_metal(Planete *une_planete)
{
    return une_planete->metal;
}

void set_argent(Planete *une_planete, int nb)
{
    une_planete->argent = nb;
}

int get_argent(Planete *une_planete)
{
    return une_planete->argent;
}

void set_carburant(Planete *une_planete, int nb)
{
    une_planete->carburant = nb;
}

int get_carburant(Planete *une_planete)
{
    return une_planete->carburant;
}

void set_population(Planete *une_planete, int nb)
{
    une_planete->population = nb;
}

int get_population(Planete *une_planete)
{
    return une_planete->population;
}

void modification_production_planete(Planete *une_planete, int metal, int argent, int carburant, int population)
{
	une_planete->metal = metal;
	une_planete->argent = argent;
	une_planete->carburant = carburant;
	une_planete->population = population;
}

void affiche_planete(Planete *une_planete)
{
    printf("Infos planete %s:\n", une_planete->nom_planete);
    printf("Coordonnes: x = %d, y = %d \n", une_planete->x, une_planete->y);
    printf("Taille: %d/%d \n", une_planete->taille_utilisee, une_planete->taille_planete);
    printf("Planete colonisee: %d, planete principale: %d \n", une_planete->planete_colonisee, une_planete->planete_principale);
    printf("\n");
}

void test_module_planete()
{
    Planete *terre;
	char nom_planete[] = "terre";
    printf("Verif de la création de planètes\n");
    terre = creer_planete(nom_planete);
    if((terre->taille_planete == 0))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}
    detruit_planete(&terre);
}
