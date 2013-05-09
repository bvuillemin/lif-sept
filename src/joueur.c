#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "planete.h"
#include "joueur.h"
#include "constante.h"

void set_nom_joueur(Joueur *un_joueur, char nom[20])
{
    strcpy(un_joueur->nom_joueur, nom);
}

void set_couleur(Joueur *un_joueur, int i)
{
    if((i==0)||(i==1))
    {
        un_joueur->couleur_joueur = i;
    }
}

int get_couleur(const Joueur *un_joueur)
{
    return un_joueur->couleur_joueur;
}

void set_pt_action_joueur(Joueur *un_joueur, int i)
{
    un_joueur->pt_action_joueur = i;
}

int get_pt_action_joueur(const Joueur *un_joueur)
{
    return un_joueur->pt_action_joueur;
}
int get_pt_action_joueur_total(const Joueur *un_joueur)
{
    return un_joueur->pt_action_joueur_total;
}
void set_numero_joueur(Joueur *un_joueur, int i)
{
        un_joueur->numero_joueur = i;
}

int get_numero_joueur(const Joueur *un_joueur)
{
    return un_joueur->numero_joueur;
}
void set_metal_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->metal = nb;
}

int get_metal_joueur(const Joueur *un_joueur)
{
    return un_joueur->metal;
}

void set_argent_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->argent = nb;
}

int get_argent_joueur(const Joueur *un_joueur)
{
    return un_joueur->argent;
}

void set_carburant_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->carburant = nb;
}

int get_carburant_joueur(const Joueur *un_joueur)
{
    return un_joueur->carburant;
}

void set_population_joueur(Joueur *un_joueur, int nb)
{
    un_joueur->population = nb;
}

int get_population_joueur(const Joueur *un_joueur)
{
    return un_joueur->population;
}

void set_nb_planete(Joueur *un_joueur, int nb)
{

}

int get_nb_planete(Joueur *un_joueur)
{
	return un_joueur->nb_planete;
}

void ajouter_planete_joueur(Joueur *un_joueur, Planete *une_planete)
{
	/*int i;

	if(un_joueur->nb_planete == un_joueur->nb_planete_possible)
	{
		Planete *temp;
		temp = *(un_joueur->tab_planete);

		*(un_joueur->tab_planete) =(Planete *)malloc(sizeof(Planete *) * (un_joueur->nb_planete_possible +10));
		for(i=0;i<un_joueur->nb_planete_possible;i++)
		{
			*(un_joueur->tab_planete[i]) = temp[i];
		}

		free(temp);
		un_joueur->nb_planete_possible = un_joueur->nb_planete_possible +10;
	}

	i = un_joueur->nb_planete;

	temp[0] = une_planete;
	un_joueur->tab_planete[i] = temp[0];
	un_joueur->nb_planete ++;*/

    int i = un_joueur->nb_planete;
    if(i< un_joueur->nb_planete_possible)
    {
        (un_joueur->tab_planete)[i] = une_planete;
        un_joueur->nb_planete ++;
        une_planete->planete_colonisee = true;
        if(i==0)
        {
            une_planete->planete_principale = true;
        }
		une_planete->indice_joueur = un_joueur->numero_joueur;
    }
}

int get_nb_flotte_joueur(Joueur *un_joueur)
{
	return un_joueur->nb_flotte;
}

void ajouter_flotte_joueur(Joueur *un_joueur, Flotte *une_flotte)
{
	int i ;
	i= un_joueur->nb_flotte;
    une_flotte->indice_joueur = un_joueur->numero_joueur;
    if(i< un_joueur->nb_flotte_possible)
    {
        une_flotte->indice_tableau_joueur = i;
        un_joueur->tab_flotte[i] = *une_flotte;
        un_joueur->nb_flotte ++;
        /*free(une_flotte);*/
    }
}

void retirer_flotte_joueur(Joueur *un_joueur, int indice_flotte)
{
    int i;
    if(indice_flotte < un_joueur->nb_flotte - 1)
    {
        for(i=indice_flotte;i<un_joueur->nb_flotte - 1;i++)
        {
            un_joueur->tab_flotte[i] = un_joueur->tab_flotte[i+1];
            un_joueur->tab_flotte[i].indice_tableau_joueur = i;
        }
       /* liberer_flotte(&un_joueur->tab_flotte[un_joueur->nb_flotte - 1]);*/
    }
}

Flotte * get_ieme_flotte_joueur(const Joueur *un_joueur,int i)
{
	return un_joueur->tab_flotte+i;
}

void ajouter_unite_ieme_flotte_joueur(Joueur *un_joueur, Unite * unite, int i)
{
	Flotte * flotte;
	flotte=creer_flotte();
	flotte = get_ieme_flotte_joueur(un_joueur,i);
	ajouter_unite_flotte(flotte, unite);
}

void recuperer_ressource_planete(Joueur *un_joueur, int *metal, int *argent, int *carburant, int *population)
{
	int i;
	for(i = 0; i < un_joueur->nb_planete;i++)
	{
		*metal = *metal + un_joueur->tab_planete[i]->metal;
		*argent = *argent + un_joueur->tab_planete[i]->argent;
		*carburant = *carburant + un_joueur->tab_planete[i]->carburant;
		*population = *population + un_joueur->tab_planete[i]->population;
	}
}


void initialise_joueur(Joueur *un_joueur, char nom[20])
{
    un_joueur->numero_joueur = -1;
	/*un_joueur->bleu;
	strcpy(un_joueur->nom_joueur, nom);*/
	un_joueur->metal = 0;
	un_joueur->argent = 0;
	un_joueur->carburant = 0;
	un_joueur->population = 0;
	un_joueur->nb_planete = 0;
	un_joueur->nb_planete_possible = 10;
	un_joueur->tab_planete = (Planete **)malloc(sizeof(Planete *) * 10);
	un_joueur->nb_flotte = 0;
	un_joueur->nb_flotte_possible = 10;
	un_joueur->tab_flotte = (Flotte *)malloc(sizeof(Flotte) * 10);
	un_joueur->pt_action_joueur = 3;
	un_joueur->pt_action_joueur_total = 3;

}

Joueur *creer_joueur(char nom[30])
{
    Joueur *un_joueur=(Joueur *)malloc(sizeof(Joueur));
    initialise_joueur(un_joueur,nom);
    return un_joueur;
}


void liberer_joueur(Joueur *un_joueur)
{
    int i;
    for(i=0;i<un_joueur->nb_flotte;i++)
    {
        liberer_flotte(&(un_joueur->tab_flotte[i]));
    }
    un_joueur->numero_joueur = 0;
    un_joueur->metal = 0;
    un_joueur->argent = 0;
    un_joueur->carburant = 0;
    un_joueur->population = 0;
    free(un_joueur->tab_planete);

    free(un_joueur->tab_flotte);
    un_joueur->nb_planete = 0;
    un_joueur->nb_planete_possible = 0;
    un_joueur->tab_planete = NULL;
    un_joueur->nb_flotte = 0;
    un_joueur->nb_flotte_possible = 0;
    un_joueur->tab_flotte = NULL;
}

void detruire_joueur(Joueur **un_joueur)
{
    liberer_joueur(*un_joueur);
    free(*un_joueur);
    *un_joueur = NULL;
}


void ajouter_metal(Joueur *un_joueur, int nb)
{
    un_joueur->metal = un_joueur->metal + nb;
}

void retirer_metal(Joueur *un_joueur, int nb)
{
    un_joueur->metal = un_joueur->metal - nb;
}

void ajouter_argent(Joueur *un_joueur, int nb)
{void set_couleur(Joueur *un_joueur, int i);

    un_joueur->argent = un_joueur->argent + nb;
}

void retirer_argent(Joueur *un_joueur, int nb)
{
    un_joueur->argent = un_joueur->argent - nb;
}
void ajouter_carburant(Joueur *un_joueur, int nb)
{
    un_joueur->carburant = un_joueur->carburant + nb;
}

void retirer_carburant(Joueur *un_joueur, int nb)
{
    un_joueur->carburant = un_joueur->carburant - nb;
}
void ajouter_population(Joueur *un_joueur, int nb)
{
    un_joueur->population = un_joueur->population + nb;
}

void retirer_population(Joueur *un_joueur, int nb)
{
    un_joueur->population = un_joueur->population - nb;
}


void colonisation_planete(Joueur *un_joueur, Planete *une_planete)
{
    int i = un_joueur->nb_planete;

    if(une_planete->planete_colonisee == true)
    {
        printf("Colonisation impossible\n\n");
    }

    else
    {
        if(i< un_joueur->nb_planete_possible)
        {
            (un_joueur->tab_planete)[i] = une_planete;
            un_joueur->nb_planete ++;
            une_planete->planete_colonisee = true;
			une_planete->indice_joueur = un_joueur->numero_joueur;
            if(i==0)
            {
                une_planete->planete_principale = true;
            }
        }
        else
        {
            printf("Vous possédez trop de planètes!!\n\n");
        }
    }
}

void creation_unite_planete(Joueur *un_joueur, Planete *une_planete, int choix)
{
    if(une_planete->unite_nb_tour_restant <= 0)
    {
        if(choix == 1)
        {
          une_planete->unite_nb_tour_restant = NB_TOUR_UNITE_1;
          une_planete->unite_en_cours = 1;
          un_joueur->metal -= NB_METAL_UNITE_1;
        }
    }

}

void enlever_pt_action_joueur(Joueur *un_joueur, const int point)
{
	int temp = get_pt_action_joueur(un_joueur);
    temp = temp - point;
    set_pt_action_joueur(un_joueur, temp);
}

void reinitialiser_pt_action_joueur(Joueur *un_joueur)
{
	un_joueur->pt_action_joueur=un_joueur->pt_action_joueur_total;
}

void sauvegarde_joueur(const Joueur *un_joueur, FILE*f)
{
    int i;
    /*fprintf(f, "%s\n", un_joueur->nom_joueur);
     A mettre quand le nom d'un joueur aura été implémenté*/
    fprintf(f, "Marcel\n");
    fprintf(f, "%d\n", un_joueur->numero_joueur);
    fprintf(f, "%d\n", (int)un_joueur->couleur_joueur);
    fprintf(f, "%d\n", un_joueur->metal);
    fprintf(f, "%d\n", un_joueur->argent);
    fprintf(f, "%d\n", un_joueur->carburant);
    fprintf(f, "%d\n", un_joueur->population);
    fprintf(f, "%d\n", un_joueur->nb_planete);
    fprintf(f, "%d\n", un_joueur->nb_planete_possible);
    for(i=0;i<un_joueur->nb_planete;i++)
    {
        sauvegarde_planete(un_joueur->tab_planete[i], f);
    }
    fprintf(f, "%d\n", un_joueur->nb_flotte);
    fprintf(f, "%d\n", un_joueur->nb_flotte_possible);
    for(i=0;i<un_joueur->nb_flotte;i++)
    {
        sauvegarde_flotte(&un_joueur->tab_flotte[i], f);
    }
    fprintf(f, "%d\n", un_joueur->pt_action_joueur);
    fprintf(f, "%d\n", un_joueur->pt_action_joueur_total);
}

Joueur* ouverture_joueur(FILE *f)
{
    Joueur *joueur_ouvert;
    char chaine[50];
    int b, i;
    fgets(chaine, 50, f);
    joueur_ouvert = creer_joueur(chaine);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->numero_joueur = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->couleur_joueur = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->metal = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->argent = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->carburant = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->population = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->nb_planete = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->nb_planete_possible = b;
    for(i=0;i<joueur_ouvert->nb_planete;i++)
    {
        fgets(chaine, 50, f);
        joueur_ouvert->tab_planete[i] = ouverture_planete(f);
    }
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->nb_flotte = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->nb_flotte_possible = b;
    for(i=0;i<joueur_ouvert->nb_flotte;i++)
    {
        fgets(chaine, 50, f);
        joueur_ouvert->tab_flotte[i] = *ouverture_flotte(f);
    }
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->pt_action_joueur = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->pt_action_joueur_total = b;
    return joueur_ouvert;
}