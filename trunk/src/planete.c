/**
 * \file      planete.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les planètes du jeu
 * \details   Cette classe définit les planètes du jeu et leurs caractéristiques
 */

#include <string.h>

#include "planete.h"
#include "batiment.h"


/************************************************************************/
/* Initialisation, création et destruction                              */
/************************************************************************/

void initialise_planete(Planete *une_planete,const char nom_planete[30])
{
    int i;
    une_planete->x = 0;
    une_planete->y = 0;
	une_planete->indice_joueur = -1;
    strcpy(une_planete->nom_planete, nom_planete);
    une_planete->planete_colonisee = false;
    une_planete->planete_principale = false;
	une_planete->taille_planete = 20; /* a modifier*/
    une_planete->taille_utilisee = 0;
    une_planete->metal = 0;
    une_planete->argent = 0;
    une_planete->carburant = 0;
    une_planete->population = 0;
	une_planete->portee_vision = 1;

    for(i=0;i<10;i++)
    {
        une_planete->batiment[i] = 0;
    }

    une_planete->batiment_en_cours = -1;
    une_planete->batiment_nb_tour_restant = -1;
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
    une_planete->unite_nb_tour_restant = -1;
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
	une_planete->taille_planete = 0;
    une_planete->taille_utilisee = 0;
    une_planete->metal = 0;
    une_planete->argent = 0;
    une_planete->carburant = 0;
    une_planete->population = 0;
	une_planete->portee_vision = 0;
}

void detruire_planete(Planete **une_planete)
{
    libere_planete(*une_planete);
    free(*une_planete);
    *une_planete = NULL;
}


/************************************************************************/
/* Fonctions set et get                                                 */
/************************************************************************/

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

int get_x_planete(const Planete *une_planete)
{
    return une_planete->x;
}

int get_y_planete(const Planete *une_planete)
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

void set_portee_planete(Planete* une_planete, int portee)
{
	une_planete->portee_vision = portee;
}

int get_portee_vision(const Planete* une_planete)
{
	return une_planete->portee_vision;
}

int get_ieme_batiment(const Planete* une_planete, int i)
{
	return une_planete->batiment[i];
}

int get_planete_unite_nb_tour_restant(const Planete* une_planete)
{
	return une_planete->unite_nb_tour_restant;
}

void set_planete_unite_nb_tour_restant(Planete* une_planete, int nb)
{
	une_planete->unite_nb_tour_restant = nb;
}

void set_planete_unite_en_cours(Planete* une_planete, int nb)
{
	une_planete->unite_en_cours = nb;
}

int get_planete_batiment_nb_tour_restant(const Planete* une_planete)
{
	return une_planete->batiment_nb_tour_restant;
}

void set_planete_batiment_nb_tour_restant(Planete* une_planete, int nb)
{
	une_planete->batiment_nb_tour_restant = nb;
}

void set_planete_batiment_en_cours(Planete* une_planete, int nb)
{
	une_planete->batiment_en_cours = nb;
}

/************************************************************************/
/* Fonctions diverses                                                   */
/************************************************************************/

/**
 * \brief      Modifie les ressources d'une planète
 * \details    Modifie le niveau de métal, d'argent, de carburant et de population d'une planète mise en paramètre
 * \param      une_planete         Pointeur sur Planete à modifier
 * \param      metal               Nouveau niveau de métal
 * \param      argent              Nouveau niveau d'argent
 * \param      carburant           Nouveau niveau de carburant
 * \param      population          Nouveau niveau de population
 */
void modification_production_planete(Planete *une_planete,const int metal,const int argent,const int carburant,const int population)
{
	une_planete->metal = metal;
	une_planete->argent = argent;
	une_planete->carburant = carburant;
	une_planete->population = population;
}

/**
 * \brief      Enlève un au nombre de tour restant pour construire une unité
 * \details    Utile lorsqu'on atteint le tour suivant
 * \param      une_planete         Pointeur sur Planete à modifier
 */
void reduire_unite_nb_tour_restant(Planete* une_planete)
{
	une_planete->unite_nb_tour_restant --;
}

/**
 * \brief      Enlève un au nombre de tour restant pour construire un bâtiment
 * \details    Utile lorsqu'on atteint le tour suivant
 * \param      une_planete         Pointeur sur Planete à modifier
 */
void reduire_batiment_nb_tour_restant(Planete* une_planete)
{
	une_planete->batiment_nb_tour_restant --;
}

/**
 * \brief      Affiche les détails d'une planète sur la console
 * \details    Affiche le nom, les coordonnées, le niveau de métal, d'argent, de carburant et de population d'une planète mise en paramètre
 * \param      une_planete         Pointeur sur Planete à afficher
 */
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

/**
 * \brief      Affiche les batiments d'une planète sur la console
 * \details    Affiche, sur la console, les batiments d'une planète passée en paramètre
 * \param      une_planete         Pointeur sur Planete sur laquelle sont les bâtiments
 */
void afficher_batiment(Planete *une_planete)
{
    printf("Quartier Général: %d\n", une_planete->batiment[0]);
    printf("Niveau des batiments de production: %d, %d, %d, %d\n", une_planete->batiment[1], une_planete->batiment[2], une_planete->batiment[3], une_planete->batiment[4]);
}

/**
 * \brief      Valide la construction d'un batiment d'une planète
 * \details    Valide la construction d'un batiment d'une planète passée en paramètre lorsque le nombre de tours restants atteint 0
 * \param      une_planete         Pointeur sur Planete sur laquelle est le bâtiment
 */
void validation_batiment(Planete *une_planete)
{
    if(une_planete->batiment_nb_tour_restant == 0)
    {
        (une_planete->tab_fonction_validation[une_planete->batiment_en_cours])(une_planete);
    }
}

/**
 * \brief      Lance la construction d'un batiment d'une planète
 * \details    Lance la construction d'un batiment d'une planète passée en paramètre si un autre batiment n'est pas en cours de construction
 * \param      une_planete         Pointeur sur Planete sur laquelle va être construit le bâtiment
 * \param      choix               Type de bâtiment
 */
void creation_batiment(Planete *une_planete, int choix)
{
    if(une_planete->batiment_nb_tour_restant <= 0)
    {
        (une_planete->tab_fonction_creation[choix])(une_planete);
    }
}

/**
 * \brief      Teste le module Planete
 */
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


/************************************************************************/
/* Fonctions sauvegarde et chargement                                   */
/************************************************************************/

/**
 * \brief      Sauvegarde une planète
 * \details    Sauvegarde une planète dans un fichier déjà ouvert
 * \param      une_planete         Pointeur sur Planete à sauvegarder
 * \param      f                   Pointeur sur Fichier de sauvegarde
 */
void sauvegarde_planete(const Planete *une_planete, FILE*f)
{
    int i;
    fprintf(f, "Planete\n");
    fprintf(f, "%s\n", une_planete->nom_planete);
    fprintf(f, "%d\n", une_planete->x);
    fprintf(f, "%d\n", une_planete->y);
    fprintf(f, "%d\n", une_planete->indice_joueur);
    for(i=0; i<10; i++)
    {
        fprintf(f, "%d\n", une_planete->batiment[i]);
    }
    fprintf(f, "%d\n", une_planete->batiment_en_cours);
    fprintf(f, "%d\n", une_planete->batiment_nb_tour_restant);
    fprintf(f, "%d\n", une_planete->unite_en_cours);
    fprintf(f, "%d\n", une_planete->unite_nb_tour_restant);
    fprintf(f, "%d\n", une_planete->taille_utilisee);
    fprintf(f, "%d\n", une_planete->taille_planete);
    fprintf(f, "%d\n", une_planete->portee_vision);
    fprintf(f, "%d\n", une_planete->planete_principale);
    fprintf(f, "%d\n", une_planete->planete_colonisee);
    fprintf(f, "%d\n", une_planete->metal);
    fprintf(f, "%d\n", une_planete->argent);
    fprintf(f, "%d\n", une_planete->carburant);
    fprintf(f, "%d\n", une_planete->population);
}

/**
 * \brief      Charge une planète
 * \details    Charge une planète à partir d'une sauvegarde
 * \param      f                   Pointeur sur Fichier de sauvegarde
 * \return     Un pointeur sur une planète ayant les informations du fichier de sauvegarde
 */
Planete* ouverture_planete(FILE *f)
{
    Planete *planete_ouverte;
    char chaine[50];
    int b, i;
    fgets(chaine, 50, f);
    planete_ouverte = creer_planete(chaine);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->x);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->y);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->indice_joueur);
    for(i=0; i<10; i++)
    {
        sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->batiment[i]);
    }
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->batiment_en_cours);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->batiment_nb_tour_restant);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->unite_en_cours);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->unite_nb_tour_restant);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->taille_utilisee);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->taille_planete);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->portee_vision);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    planete_ouverte->planete_principale = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    planete_ouverte->planete_colonisee = b;
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->metal);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->argent);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->carburant);
    sscanf(fgets(chaine, 50, f), "%d", &planete_ouverte->population);
    return planete_ouverte;
}
