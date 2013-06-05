/**
 * \file      joueur.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les joueurs d'un jeu
 * \details   Cette classe définit les joueurs du jeu (ia ou joueur réel) et leurs caractéristiques
 */

#include "joueur.h"
#include "constante.h"

/************************************************************************/
/* Initialisation, création et destruction                              */
/************************************************************************/

void initialise_joueur(Joueur *un_joueur, char nom[20], int indice_joueur, bool ia)
{
    un_joueur->numero_joueur = indice_joueur;
	un_joueur->ia = ia;
	un_joueur->couleur_joueur = DEFAUT;
	strcpy(un_joueur->nom_joueur, nom);
	un_joueur->metal = 0;
	un_joueur->argent = 0;
	un_joueur->carburant = 0;
	un_joueur->population = 0;
	un_joueur->nb_planete = 0;
	un_joueur->nb_planete_possible = 10;
	un_joueur->tab_planete = (Planete **)malloc(sizeof(Planete *) * 10);
	un_joueur->nb_flotte = 0;
    
	un_joueur->nb_flotte_possible = 10;
	initialiserTabDyn(&un_joueur->tab_flotte);
	un_joueur->pt_action_joueur = 3;
	un_joueur->pt_action_joueur_total = 3;
	un_joueur->vision_terrain = NULL; /*mis à NULL, c'est le jeu qui va se charger de créer la vision pour chaque joueur*/
}

Joueur *creer_joueur(char nom[30], int indice_joueur, bool ia)
{
    Joueur *un_joueur=(Joueur *)malloc(sizeof(Joueur));
    initialise_joueur(un_joueur, nom, indice_joueur, ia);
    return un_joueur;
}

void liberer_joueur(Joueur *un_joueur)
{
    int i;
    un_joueur->numero_joueur = -1;
	un_joueur->couleur_joueur = DEFAUT;
	un_joueur->nom_joueur[0] = '\0';
	un_joueur->metal = 0;
	un_joueur->argent = 0;
	un_joueur->carburant = 0;
	un_joueur->population = 0;
	un_joueur->nb_planete = 0;
	un_joueur->nb_planete_possible = 0;
	free(un_joueur->tab_planete); /*on ne libère pas les planètes, c'est le terrain qui va s'en charger*/
	for(i=0;i<un_joueur->tab_flotte.taille_utilisee;i++)
	{
		liberer_flotte(&un_joueur->tab_flotte.ad[i]);
	}
	testamentTabDyn(&un_joueur->tab_flotte);
	un_joueur->nb_flotte = 0;
	un_joueur->nb_flotte_possible = 0;
	un_joueur->pt_action_joueur = 0;
	un_joueur->pt_action_joueur_total = 0;
    if (un_joueur->vision_terrain != NULL)
    {
        liberer_vision_terrain(un_joueur->vision_terrain);
    }
	free(un_joueur->vision_terrain);
}

void detruire_joueur(Joueur **un_joueur)
{
    liberer_joueur(*un_joueur);
    free(*un_joueur);
    *un_joueur = NULL;
}


/************************************************************************/
/* Fonctions set et get                                                 */
/************************************************************************/

void set_nom_joueur(Joueur *un_joueur, char nom[20])
{
    strcpy(un_joueur->nom_joueur, nom);
}
char* get_nom_joueur(Joueur *un_joueur)
{
    return un_joueur->nom_joueur;
}
void set_couleur(Joueur *un_joueur, Couleur_joueur couleur_joueur)
{
    un_joueur->couleur_joueur = couleur_joueur;
}
Couleur_joueur get_couleur(const Joueur *un_joueur)
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
    un_joueur->nb_planete = nb;
}
int get_nb_planete(Joueur *un_joueur)
{
	return un_joueur->nb_planete;
}
int get_nb_flotte_joueur(Joueur *un_joueur)
{
	return un_joueur->tab_flotte.taille_utilisee;
}
Flotte* get_ieme_flotte_joueur(const Joueur *un_joueur,int i)
{
	return valeurIemeElementTabDyn(&un_joueur->tab_flotte, i + 1); /*on met i+1 car le module tabdyn prend la position, on choisit de prendre les indices dans le tableau*/
}
Vision_terrain* get_vision_terrain(const Joueur* un_joueur)
{
	return un_joueur->vision_terrain;
}
Planete* get_ieme_planete_joueur(const Joueur* un_joueur, int i)
{
	return un_joueur->tab_planete[i];
}
bool get_ia_joueur(Joueur* un_joueur)
{
	return un_joueur->ia;
}


/************************************************************************/
/* Fonctions                                                            */
/************************************************************************/

/**
 * \brief      Ajoute une planète à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      une_planete         Pointeur sur Planete
 */
void ajouter_planete_joueur(Joueur *un_joueur, Planete *une_planete)
{
    int i = un_joueur->nb_planete;
    if(i< un_joueur->nb_planete_possible)
    {
        un_joueur->tab_planete[i] = une_planete;
        un_joueur->nb_planete ++;
        une_planete->planete_colonisee = true;
        if(i==0)
        {
            set_planete_principale(une_planete, true);
        }
		set_indice_joueur_planete(une_planete, un_joueur->numero_joueur);
    }
}

/**
 * \brief      Ajoute une planète à un joueur avec un indice précis pour le placer dans le tableau de planètes
 * \param      un_joueur           Pointeur sur Joueur
 * \param      une_planete         Pointeur sur Planete
 * \param      indice              Indice de la position où placer la flotte
 */
void ajouter_planete_avec_indice_joueur(Joueur* un_joueur, Planete* une_planete, int indice)
{
	if(un_joueur->tab_planete[indice] == NULL)
	{
		un_joueur->nb_planete ++;
	}
	un_joueur->tab_planete[indice] = une_planete;
	set_planete_colonisee(une_planete, true);
	if(indice==0)
	{
		set_planete_principale(une_planete, true);
	}
	set_indice_joueur_planete(une_planete, un_joueur->numero_joueur);
}


/**
 * \brief      Supprime une planète d'un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      une_planete         Pointeur sur Planete
 */
void supprimer_planete_joueur(Joueur* un_joueur, Planete* une_planete)
{
	int i, j;
	for(i=0;i<get_nb_planete(un_joueur);i++)
	{
		if((get_x_planete(get_ieme_planete_joueur(un_joueur, i)) == get_x_planete(une_planete)) && (get_y_planete(get_ieme_planete_joueur(un_joueur, i)) == get_y_planete(une_planete)))
		{
			for(j = i;j<get_nb_planete(un_joueur) - 1;j++)
			{
				ajouter_planete_avec_indice_joueur(un_joueur, get_ieme_planete_joueur(un_joueur, j+1), j);
			}
		}
	}
    set_nb_planete(un_joueur, (get_nb_planete(un_joueur) - 1));
}

/**
 * \brief      Ajoute une flotte à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      une_fotte           Pointeur sur Flotte
 */
void ajouter_flotte_joueur(Joueur *un_joueur, Flotte *une_flotte)
{
	int i = un_joueur->nb_flotte;
    une_flotte->indice_joueur = un_joueur->numero_joueur;
	une_flotte->indice_tableau_joueur = i;
	un_joueur->nb_flotte ++;
	changer_indice_joueur_unite_flotte(une_flotte);
    ajouterElementTabDyn(&un_joueur->tab_flotte, une_flotte);
	free(une_flotte);
}

/**
 * \brief      Retire une flotte à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      une_fotte           Pointeur sur Flotte
 */
void retirer_flotte_joueur(Joueur *un_joueur, int indice_flotte)
{
    int i;
    supprimerElementTabDyn(&un_joueur->tab_flotte, indice_flotte);
    for(i=0;i<un_joueur->tab_flotte.taille_utilisee;i++)
    {
        un_joueur->tab_flotte.ad[i].indice_tableau_joueur = i;
    }
    un_joueur->nb_flotte --;
}

/**
 * \brief      Ajoute unité à une flotte d'un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      une_unité           Pointeur sur Unité
 * \param      i                   Numéro de la flotte
 */
void ajouter_unite_ieme_flotte_joueur(Joueur *un_joueur, Unite * unite, int i)
{
	Flotte * flotte;
	flotte=creer_flotte();
	flotte = get_ieme_flotte_joueur(un_joueur,i);
	ajouter_unite_flotte(flotte, unite);
}

/**
 * \brief      Transfère de ressources d'une planète un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      metal               Ressources en métal
 * \param      argent              Ressources en argent
 * \param      carburant           Ressources en carburant
 * \param      populatio           Ressources en population
 */
void recuperer_ressource_planete(Joueur *un_joueur, int *metal, int *argent, int *carburant, int *population)
{
	int i;
	for(i = 0; i < un_joueur->nb_planete;i++)
	{
		*metal = *metal + get_metal(un_joueur->tab_planete[i]);
		*argent = *argent + get_argent(un_joueur->tab_planete[i]);
		*carburant = *carburant + get_carburant(un_joueur->tab_planete[i]);
		*population = *population + get_population(un_joueur->tab_planete[i]);
	}
}

/**
 * \brief      Transfère de ressources d'un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      metal               Pointeur sur Ressources en métal
 * \param      argent              Pointeur sur Ressources en argent
 * \param      carburant           Pointeur sur Ressources en carburant
 * \param      populatio           Pointeur sur Ressources en population
 */
void recuperer_ressource_joueur(Joueur *un_joueur, int *metal, int *argent, int *carburant, int *population)
{
	*metal = *metal + un_joueur->metal;
	*argent = *argent + un_joueur->argent;
	*carburant = *carburant + un_joueur->carburant;
	*population = *population + un_joueur->population;
}

/**
 * \brief      Ajoute des ressources en métal à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      nb                  Ressources en métal
 */
void ajouter_metal(Joueur *un_joueur, int nb)
{
    un_joueur->metal = un_joueur->metal + nb;
}
/**
 * \brief      Retire des ressources en métal à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      nb                  Ressources en métal
 */
void retirer_metal(Joueur *un_joueur, int nb)
{
    un_joueur->metal = un_joueur->metal - nb;
}

/**
 * \brief      Ajoute des ressources en argent à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      nb                  Ressources en argent
 */
void ajouter_argent(Joueur *un_joueur, int nb)
{
	un_joueur->argent = un_joueur->argent + nb;
}
/**
 * \brief      Retire des ressources en argent à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      nb                  Ressources en argent
 */
void retirer_argent(Joueur *un_joueur, int nb)
{
    un_joueur->argent = un_joueur->argent - nb;
}

/**
 * \brief      Ajoute des ressources en carburant à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      nb                  Ressources en carburant
 */
void ajouter_carburant(Joueur *un_joueur, int nb)
{
    un_joueur->carburant = un_joueur->carburant + nb;
}
/**
 * \brief      Retire des ressources en carburant à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      nb                  Ressources en carburant
 */
void retirer_carburant(Joueur *un_joueur, int nb)
{
    un_joueur->carburant = un_joueur->carburant - nb;
}

/**
 * \brief      Ajoute des ressources en population à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      nb                  Ressources en population
 */
void ajouter_population(Joueur *un_joueur, int nb)
{
    un_joueur->population = un_joueur->population + nb;
}
/**
 * \brief      Retire des ressources en population à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      nb                  Ressources en population
 */
void retirer_population(Joueur *un_joueur, int nb)
{
    un_joueur->population = un_joueur->population - nb;
}

/**
 * \brief      Permet à un Joueur de coloniser une Planete
 * \param      un_joueur           Pointeur sur Joueur
 * \param      une_planete         Pointeur sur Planète
 */
void colonisation_planete(Joueur *un_joueur, Planete *une_planete)
{
    int i = un_joueur->nb_planete;

    if(get_planete_colonisee(une_planete)== true)
    {
        printf("Colonisation impossible\n\n");
    }

    else
    {
        if(i< un_joueur->nb_planete_possible)
        {
            (un_joueur->tab_planete)[i] = une_planete;
            un_joueur->nb_planete ++;
			set_planete_colonisee(une_planete, true);
			set_indice_joueur_planete(une_planete, un_joueur->numero_joueur);
            if(i==0)
            {
                set_planete_principale(une_planete, true);
            }
        }
        else
        {
            printf("Vous possédez trop de planètes!!\n\n");
        }
    }
}

/**
 * \brief      Crée une unité d'un joueur sur une planète
 * \param      un_joueur           Pointeur sur Joueur
 * \param      une_planete         Pointeur sur Planète
 * \param      choix               Choix de l'unité à créer
 */
void creation_unite_planete(Joueur *un_joueur, Planete *une_planete, int choix)
{
    if(get_planete_unite_nb_tour_restant(une_planete)<= 0)
    {
        if(choix == 1)
        {
		  set_planete_unite_en_cours(une_planete, 1);
		  set_planete_unite_nb_tour_restant(une_planete, NB_TOUR_UNITE_1);
          un_joueur->metal -= NB_METAL_UNITE_1;
		  un_joueur->argent -= NB_ARGENT_UNITE_1;
		  un_joueur->carburant -= NB_CARBURANT_UNITE_1;
		  un_joueur->population -= NB_POPULATION_UNITE_1;
        }
		if(choix == 2)
		{
			set_planete_unite_en_cours(une_planete, 2);
			set_planete_unite_nb_tour_restant(une_planete, NB_TOUR_UNITE_2);
			un_joueur->metal -= NB_METAL_UNITE_2;
			un_joueur->argent -= NB_ARGENT_UNITE_2;
			un_joueur->carburant -= NB_CARBURANT_UNITE_2;
			un_joueur->population -= NB_POPULATION_UNITE_2;
		}
		if(choix == 3)
		{
			set_planete_unite_en_cours(une_planete, 3);
			set_planete_unite_nb_tour_restant(une_planete, NB_TOUR_UNITE_3);
			un_joueur->metal -= NB_METAL_UNITE_3;
			un_joueur->argent -= NB_ARGENT_UNITE_3;
			un_joueur->carburant -= NB_CARBURANT_UNITE_3;
			un_joueur->population -= NB_POPULATION_UNITE_3;
		}
    }

}

/**
 * \brief      Retire des points d'action à un joueur
 * \param      un_joueur           Pointeur sur Joueur
 * \param      point               Points d'action à retirer
 */
void enlever_pt_action_joueur(Joueur *un_joueur, const int point)
{
	int temp = get_pt_action_joueur(un_joueur);
    temp = temp - point;
    set_pt_action_joueur(un_joueur, temp);
}

/**
 * \brief      Réinitialise les points d'action d'un joueur
 * \param      un_joueur           Pointeur sur Joueur
 */
void reinitialiser_pt_action_joueur(Joueur *un_joueur)
{
	un_joueur->pt_action_joueur=un_joueur->pt_action_joueur_total;
}


/************************************************************************/
/* Fonctions sauvegarde et chargement                                   */
/************************************************************************/

/**
 * \brief      Sauvegarde un joueur
 * \details    Sauvegarde un joueur dans un fichier déjà ouvert
 * \param      un_joueur           Pointeur sur Joueur à sauvegarder
 * \param      f                   Pointeur sur Fichier de sauvegarde
 */
void sauvegarde_joueur(const Joueur *un_joueur, FILE*f)
{
    int i;
    fprintf(f, "%s\n", un_joueur->nom_joueur);
    fprintf(f, "%d\n", un_joueur->numero_joueur);
    fprintf(f, "%d\n", un_joueur->ia);
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
    for(i=1;i<=un_joueur->nb_flotte;i++)
    {
        sauvegarde_flotte(valeurIemeElementTabDyn(&un_joueur->tab_flotte, i), f);
    }
    fprintf(f, "%d\n", un_joueur->pt_action_joueur);
    fprintf(f, "%d\n", un_joueur->pt_action_joueur_total);
}

/**
 * \brief      Charge un joueur
 * \details    Charge un joueur à partir d'une sauvegarde
 * \param      f                   Pointeur sur Fichier de sauvegarde
 * \return     Un pointeur sur un joueur ayant les informations du fichier de sauvegarde
 */
Joueur* ouverture_joueur(FILE *f)
{
    Joueur *joueur_ouvert;
    char chaine[50], chaine2[50];
    int b, c, i;
    fgets(chaine2, 50, f);
    suppr_retour(chaine2);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    sscanf(fgets(chaine, 50, f), "%d", &c);
    joueur_ouvert = creer_joueur(chaine2, b, c);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    joueur_ouvert->couleur_joueur = b;
    sscanf(fgets(chaine, 50, f), "%d", &joueur_ouvert->metal);
    sscanf(fgets(chaine, 50, f), "%d", &joueur_ouvert->argent);
    sscanf(fgets(chaine, 50, f), "%d", &joueur_ouvert->carburant);
    sscanf(fgets(chaine, 50, f), "%d", &joueur_ouvert->population);
    sscanf(fgets(chaine, 50, f), "%d", &joueur_ouvert->nb_planete);
    sscanf(fgets(chaine, 50, f), "%d", &joueur_ouvert->nb_planete_possible);
    for(i=0;i<joueur_ouvert->nb_planete;i++)
    {
        fgets(chaine, 50, f);
        joueur_ouvert->tab_planete[i] = ouverture_planete(f);
    }
    sscanf(fgets(chaine, 50, f), "%d", &joueur_ouvert->nb_flotte);
    sscanf(fgets(chaine, 50, f), "%d", &joueur_ouvert->nb_flotte_possible);
    for(i=1;i<=joueur_ouvert->nb_flotte;i++)
    {
        fgets(chaine, 50, f);
        ajouterElementTabDyn(&joueur_ouvert->tab_flotte, ouverture_flotte(f));
    }
    sscanf(fgets(chaine, 50, f), "%d", &joueur_ouvert->pt_action_joueur);
    sscanf(fgets(chaine, 50, f), "%d", &joueur_ouvert->pt_action_joueur_total);
    return joueur_ouvert;
}

void testRegression_Joueur()
{
    Joueur *un_joueur;
    un_joueur = creer_joueur("TEST", 0, false);
    assert(strcmp(un_joueur->nom_joueur, "TEST") == 0);
    assert(un_joueur->numero_joueur == 0);
    assert(un_joueur->ia == false);
    detruire_joueur(&un_joueur);
}