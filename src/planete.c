#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "planete.h"
#include "batiment.h"

void initialise_planete(Planete *une_planete,const char nom_planete[30])
{
    int i;
    une_planete->x = 0;
    une_planete->y = 0;
	une_planete->indice_joueur = 0;
    strcpy(une_planete->nom_planete, nom_planete);
    une_planete->planete_colonisee = false;
    une_planete->planete_principale = false;
	une_planete->habitabilite = 0;
    une_planete->taille_planete = 20; /* a modifier*/
    une_planete->taille_utilisee = 0;
    une_planete->metal = 0;
    une_planete->argent = 0;
    une_planete->carburant = 0;
    une_planete->population = 0;

    for(i=0;i<10;i++)
    {
        une_planete->batiment[i] = 0;
    }

    une_planete->batiment_en_cours = -1;
    une_planete->batiment_nb_tour_restant = 0;
    une_planete->tab_fonction_validation[0] = validation_creer_batiment_quartier_general;
    une_planete->tab_fonction_validation[1] = validation_creer_batiment_metal;
	une_planete->tab_fonction_validation[2] = validation_creer_batiment_argent;
	une_planete->tab_fonction_validation[3] = validation_creer_batiment_carburant;
	une_planete->tab_fonction_validation[4] = validation_creer_batiment_population;
	une_planete->tab_fonction_validation[5] = validation_creer_batiment_spatioport;

    une_planete->tab_fonction_creation[0] = creer_batiment_quartier_general;
    une_planete->tab_fonction_creation[1] = creer_batiment_metal;
	une_planete->tab_fonction_creation[2] = creer_batiment_argent;
	une_planete->tab_fonction_creation[3] = creer_batiment_carburant;
	une_planete->tab_fonction_creation[4] = creer_batiment_population;
	une_planete->tab_fonction_creation[5] = creer_batiment_spatioport;

    une_planete->unite_en_cours =  -1;
    une_planete->unite_nb_tour_restant = 0;
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
	une_planete->indice_joueur = 0;
    /*free(une_planete->nom_planete);*/
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

void detruire_planete(Planete **une_planete)
{
    libere_planete(*une_planete);
    free(*une_planete);
    *une_planete = NULL;
}

void set_nom_planete(Planete *une_planete,const char nom[30])
{
    strcpy(une_planete->nom_planete, nom);
}

char* get_nom_planete(Planete *une_planete)
{
    return une_planete->nom_planete;
}

void set_position_planete(Planete *une_planete,const int x,const int y)
{
    une_planete->x = x;
    une_planete->y = y;
}

int get_position_x_planete(const Planete *une_planete)
{
    return une_planete->x;
}

int get_position_y_planete(const Planete *une_planete)
{
    return une_planete->y;
}

void set_taille_utilisee(Planete *une_planete,const int taille_utilisee)
{
    une_planete->taille_utilisee = taille_utilisee;
}

int get_taille_utilisee(const Planete *une_planete)
{
    return une_planete->taille_utilisee;
}

void set_taille_planete(Planete *une_planete,const int taille_planete)
{
    une_planete->taille_planete = 20;
}

int get_taille_planete(const Planete *une_planete)
{
    return une_planete->taille_planete;
}

void set_habitabilite(Planete *une_planete,const int nb)
{
	une_planete->habitabilite=nb;
}

int get_habitabilite(const Planete *une_planete)
{
	return une_planete->habitabilite;
}

void set_planete_principale(Planete *une_planete,const bool booleen)
{
    une_planete->planete_principale = booleen;
}

bool get_planete_principale(const Planete *une_planete)
{
    return une_planete->planete_principale;
}

void set_planete_colonisee(Planete *une_planete,const bool booleen)
{
   une_planete->planete_colonisee = booleen;
}

bool get_planete_colonisee(const Planete *une_planete)
{
    return une_planete->planete_colonisee;
}

void set_metal(Planete *une_planete,const int nb)
{
    une_planete->metal = nb;
}

int get_metal(const Planete *une_planete)
{
    return une_planete->metal;
}

void set_argent(Planete *une_planete,const int nb)
{
    une_planete->argent = nb;
}

int get_argent(const Planete *une_planete)
{
    return une_planete->argent;
}

void set_carburant(Planete *une_planete,const int nb)
{
    une_planete->carburant = nb;
}

int get_carburant(const Planete *une_planete)
{
    return une_planete->carburant;
}

void set_population(Planete *une_planete,const int nb)
{
    une_planete->population = nb;
}

int get_population(const Planete *une_planete)
{
    return une_planete->population;
}

void modification_production_planete(Planete *une_planete,const int metal,const int argent,const int carburant,const int population)
{
	une_planete->metal = metal;
	une_planete->argent = argent;
	une_planete->carburant = carburant;
	une_planete->population = population;
}

void afficher_planete(Planete *une_planete)
{
    int i;
    printf("Infos planete %s:\n", une_planete->nom_planete);
    printf("Coordonnes: x = %d, y = %d \n", une_planete->x, une_planete->y);
    printf("Taille: %d/%d \n", une_planete->taille_utilisee, une_planete->taille_planete);
    printf("Planete colonisee: %d, planete principale: %d \n", une_planete->planete_colonisee, une_planete->planete_principale);
    for(i=0;i<10;i++)
    {
        printf("%d ", une_planete->batiment[i]);
    }
    printf("\n\n");
}

void afficher_batiment(Planete *une_planete)
{
    printf("Quartier Général: %d\n", une_planete->batiment[0]);
    printf("Niveau des batiments de production: %d, %d, %d, %d\n", une_planete->batiment[1], une_planete->batiment[2], une_planete->batiment[3], une_planete->batiment[4]);
}

void validation_batiment(Planete *une_planete)
{
    if(une_planete->batiment_nb_tour_restant == 0)
    {
        (une_planete->tab_fonction_validation[une_planete->batiment_en_cours])(une_planete);
    }
}

void creation_batiment(Planete *une_planete, int choix)
{
    if(une_planete->batiment_nb_tour_restant == 0)
    {
        (une_planete->tab_fonction_creation[choix])(une_planete);
    }
}

void test_module_planete()
{
    Planete *terre;
	char nom_planete[] = "terre";
    printf("Verif de la création de planètes\n");
    terre = creer_planete(nom_planete);
    if(terre->taille_planete == 0)
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}
    detruire_planete(&terre);
}
