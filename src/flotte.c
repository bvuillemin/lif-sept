/**
 * \file      flotte.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les flottes du jeu
 * \details   Cette classe définit les flottes du jeu et leurs caractéristiques
 */

#include "flotte.h"
/************************************************************************/
/* Initialisation, création et destruction                              */
/************************************************************************/

void initialiser_flotte(Flotte *flotte)
{
	flotte->x_flotte = 0;
	flotte->y_flotte = 0;
	flotte->indice_joueur = 0;
	flotte->indice_tableau_joueur = 0;
	flotte->portee_vision = 1;
    flotte->taille_maximum_flotte = 10; /*valeur temporaire qu'il faudra éventuellemnt modifier*/
    flotte->taille_flotte = 0;
	flotte->pt_mouvement_espace_flotte = 0;
    flotte->tab_unite = (Unite **)malloc(sizeof(Unite *)*flotte->taille_maximum_flotte);
}

Flotte *creer_flotte()
{
    Flotte *flotte=(Flotte *)malloc(sizeof(Flotte));
    initialiser_flotte(flotte);
    return flotte;
}

void liberer_flotte(Flotte *flotte)
{
	int i;
	for(i=0;i<flotte->taille_flotte;i++)
	{
		//liberer_unite(flotte->tab_unite[i]);
		detruire_unite(&flotte->tab_unite[i]);
	}
	free(flotte->tab_unite);
	flotte->tab_unite = NULL;
	flotte->taille_maximum_flotte = 10; /*valeur temporaire qu'il faudra éventuellemnt modifier*/
	flotte->taille_flotte = 0;
	flotte->x_flotte = 0;
	flotte->y_flotte = 0;
	flotte->portee_vision = 0;
	flotte->pt_mouvement_espace_flotte = 0;
	flotte->indice_tableau_joueur = 0;
}

void detruire_flotte(Flotte **flotte)
{
	liberer_flotte(*flotte);
	free(*flotte);
	*flotte = NULL;
}


/************************************************************************/
/* Fonctions set et get                                                 */
/************************************************************************/

void set_indice_joueur_flotte(Flotte *flotte,const int i)
{
    flotte->indice_joueur = i;
}

int get_indice_joueur_flotte(const Flotte *flotte)
{
    return flotte->indice_joueur;
}

void set_taille_maximum_flotte(Flotte *flotte,const int max)
{
    flotte->taille_maximum_flotte = max;
}

void set_taille_flotte(Flotte *flotte,const int nb)
{
    flotte->taille_flotte = nb;
}

int get_taille_maximum_flotte(const Flotte *flotte)
{
    return flotte->taille_maximum_flotte;
}

int get_taille_flotte(const Flotte *flotte)
{
    return flotte->taille_flotte;
}

void set_x_flotte(Flotte *une_flotte,const int x)
{
    une_flotte->x_flotte = x;
}

int get_x_flotte(const Flotte *une_flotte)
{
    return une_flotte->x_flotte;
}

void set_y_flotte(Flotte *une_flotte,const int y)
{
    une_flotte->y_flotte = y;
}

int get_y_flotte(const Flotte *une_flotte)
{
    return une_flotte->y_flotte;
}

void set_pt_mouvement_espace_flotte(Flotte *une_flotte,const int pt)
{
    une_flotte->pt_mouvement_espace_flotte = pt;
}

int get_pt_mouvement_espace_flotte(const Flotte *une_flotte)
{
    return une_flotte->pt_mouvement_espace_flotte;
}

Unite * get_unite_i_flotte(const Flotte * flotte, const int i)
{
	if(i< flotte->taille_flotte)
	{
		return flotte->tab_unite[i];
	}
	else
	{
		return NULL;
	}
}

int get_portee_vision_flotte(const Flotte* une_flotte)
{
	return une_flotte->portee_vision;
}


/************************************************************************/
/* Fonctions diverses                                                   */
/************************************************************************/

/**
 * \brief      Ajoute une unite à une flotte
 * \details    Ajoute une unite passée en paramètre à une flotte
 * \param      flotte         Pointeur sur flotte dans laquelle sera l'unite
 * \param      unite          Pointeur sur unite à ajouter
 * \return     1 si l'ajout a eu lieu, 0 sinon
 */
int ajouter_unite_flotte(Flotte *flotte, Unite *unite)
{
	int min = flotte->pt_mouvement_espace_flotte;
	if(flotte->taille_flotte < flotte->taille_maximum_flotte)
    {
		set_indice_joueur_unite(unite, flotte->indice_joueur); /*erreur due je pense a la fonction, a modifier*/
		set_indice_unite_dans_flotte(unite, flotte->taille_flotte);
		if((get_pt_mouvement_unite(unite) < min)||(flotte->pt_mouvement_espace_flotte == 0))
		{
			flotte->pt_mouvement_espace_flotte = get_pt_mouvement_unite(unite);
		}
        flotte->tab_unite[flotte->taille_flotte] = unite;
        flotte->taille_flotte ++;
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * \brief      Transfère unite d'une flotte à une autre
 * \details    Transfère d'une unite passée en paramètre d'une flotte à une autre passée en paramètre
 * \param      flotte         Pointeur sur flotte dans laquelle l'unite sera transférée
 * \param      unite          Pointeur sur unite à transférer
 */
int transferer_unite_flotte(Flotte *flotte, Unite *unite)
{
	if(flotte->taille_flotte < flotte->taille_maximum_flotte)
    {
		set_indice_unite_dans_flotte(unite,flotte->taille_flotte);
        flotte->tab_unite[flotte->taille_flotte] = unite;
        flotte->taille_flotte ++;
		if((get_pt_mouvement_unite(unite))||(flotte->pt_mouvement_espace_flotte == 0))
		{
			flotte->pt_mouvement_espace_flotte = get_pt_mouvement_unite(unite);
		}
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * \brief      Retire une unite d'une flotte
 * \details    Retire une unité d'une flotte passée en paramètre
 * \param      flotte         Pointeur sur flotte dans laquelle est l'unite
 * \param      indice_unite   indice de l'unite à supprimer
 * \return     1 si l'unité a été retirée, 0 sinon
 */
int retirer_unite_flotte(Flotte *flotte,const int indice_unite)
{
    int i;
    if(flotte->taille_flotte > 0)
    {
        for(i=indice_unite;i<flotte->taille_flotte - 1;i++)
        {
            flotte->tab_unite[i] = flotte->tab_unite[i+1];
        }
        flotte-> taille_flotte --;
        return 1;
    }
    else{return 0;}
}

/**
 * \brief      Affiche les informations d'une flotte
 * \details    Affiche les coordonnées de la flotte, ses points de mouvements, sa taille, et ses différentes unités
 * \param      flotte         Pointeur sur flotte à afficher
 */
void afficher_flotte(const Flotte *flotte)
{
    int i;
	printf("Coordonnes de la flotte: %d %d, pt mouvement %d, taille : %d\n", flotte->x_flotte, flotte->y_flotte, flotte->pt_mouvement_espace_flotte,flotte->taille_flotte);
    for(i=0;i<flotte->taille_flotte;i++)
    {

        printf("Unite %d: pv = %d pa = %d pde = %d pme = %d  x= %d y=%d\n", i+1 , flotte->tab_unite[i]->pt_vie, flotte->tab_unite[i]->pt_action, flotte->tab_unite[i]->pt_deplacement, flotte->tab_unite[i]->pt_mouvement_unite, flotte->tab_unite[i]->x_unite, flotte->tab_unite[i]->y_unite);
    }

}

/**
 * \brief      Retire des points de mouvement à une flotte
 * \details    Retire des points de mouvements passés en paramètre à une flotte
 * \param      flotte         Pointeur sur flotte à modifier
 * \param      distance       Points de mouvement à supprimer
 */
void enlever_pt_mouvement_espace_flotte(Flotte *une_flotte,const int distance)
{
    int temp = get_pt_mouvement_espace_flotte(une_flotte);
    temp = temp - distance;
    set_pt_mouvement_espace_flotte(une_flotte, temp);
}

/**
 * \brief      Réinitialise les points de mouvement d'une flotte
 * \details    Réinitialise les points de mouvements de tous les unite d'une flotte passée en paramètre
 * \param      flotte         Pointeur sur flotte à modifier
 */
void reinitialiser_mouvement_flotte(Flotte *une_flotte)
{
	int i;
	int min = 0;
	for(i=0;i<une_flotte->taille_flotte;i++)
	{
		if((une_flotte->tab_unite[i]->pt_mouvement_unite < min)||(min == 0))
		{
			min = une_flotte->tab_unite[i]->pt_mouvement_unite;
		}
	}
	une_flotte->pt_mouvement_espace_flotte = min;
}

/**
 * \brief      Réinitialise les points de déplacement des unite d'une flotte
 * \details    Réinitialise les points de déplacement de tous les unite d'une flotte passée en paramètre
 * \param      flotte         Pointeur sur flotte à modifier
 */
void reinitialiser_deplacement_unite_flotte(Flotte *une_flotte)
{
	int i;
	for(i=0;i<une_flotte->taille_flotte;i++)
	{
		une_flotte->tab_unite[i]->pt_deplacement = une_flotte->tab_unite[i]->pt_deplacement_total;
	}
}

/**
 * \brief      Réinitialise les points d'action des unite d'une flotte
 * \details    Réinitialise les points d'action de tous les unite d'une flotte passée en paramètre
 * \param      flotte         Pointeur sur flotte à modifier
 */
void reinitialiser_pt_action_unite_flotte(Flotte *une_flotte)
{
	int i;
	for(i=0;i<une_flotte->taille_flotte;i++)
	{
		reinitialiser_pt_action(une_flotte->tab_unite[i]);
	}
}


/************************************************************************/
/* Fonctions sauvegarde et chargement                                   */
/************************************************************************/

/**
 * \brief      Sauvegarde une flotte
 * \details    Sauvegarde une flotte dans un fichier déjà ouvert
 * \param      flotte         Pointeur sur flotte à sauvegarder
 * \param      f              Pointeur sur ichier de sauvegarde
 */
void sauvegarde_flotte(const Flotte *une_flotte, FILE*f)
{
    int i;
    fprintf(f, "Flotte\n");
    fprintf(f, "%d\n", une_flotte->x_flotte);
    fprintf(f, "%d\n", une_flotte->y_flotte);
    fprintf(f, "%d\n", une_flotte->indice_joueur);
    fprintf(f, "%d\n", une_flotte->indice_tableau_joueur);
    fprintf(f, "%d\n", une_flotte->taille_maximum_flotte);
    fprintf(f, "%d\n", une_flotte->taille_flotte);
    fprintf(f, "%d\n", une_flotte->pt_mouvement_espace_flotte);
    fprintf(f, "%d\n", une_flotte->portee_vision);
    for(i=0; i<une_flotte->taille_flotte; i++)
    {
        sauvegarde_unite(une_flotte->tab_unite[i], f);
    }
}

/**
 * \brief      Charge une flotte
 * \details    Charge une flotte à partir d'une sauvegarde
 * \param      f              Pointeur sur fichier à charger
 * \return     Un pointeur sur une flotte ayant les informations du fichier de sauvegarde
 */
Flotte* ouverture_flotte(FILE *f)
{
    Flotte* flotte_ouverte;
    char chaine[50];
    int i;
    flotte_ouverte = creer_flotte();
    sscanf(fgets(chaine, 50, f), "%d", &flotte_ouverte->x_flotte);
    sscanf(fgets(chaine, 50, f), "%d", &flotte_ouverte->y_flotte);
    sscanf(fgets(chaine, 50, f), "%d", &flotte_ouverte->indice_joueur);
    sscanf(fgets(chaine, 50, f), "%d", &flotte_ouverte->indice_tableau_joueur);
    sscanf(fgets(chaine, 50, f), "%d", &flotte_ouverte->taille_maximum_flotte);
    sscanf(fgets(chaine, 50, f), "%d", &flotte_ouverte->taille_flotte);
    sscanf(fgets(chaine, 50, f), "%d", &flotte_ouverte->pt_mouvement_espace_flotte);
    sscanf(fgets(chaine, 50, f), "%d", &flotte_ouverte->portee_vision);
    for(i=0; i<flotte_ouverte->taille_flotte; i++)
    {
        *flotte_ouverte->tab_unite[i] = *ouverture_unite(f);
    }
    return flotte_ouverte;
}



/*void test_module_flotte()
{
    Flotte *flotte;
    Unite *unite1;
    Unite *unite2;
    Unite *unite3;
    unite1 = creer_unite();
    unite2 = creer_unite();
    unite3 = creer_unite();

    printf("Verif de la création de flottes\n");
    flotte = creer_flotte();

    ajouter_unite_flotte(flotte, unite1);
    ajouter_unite_flotte(flotte, unite2);
    ajouter_unite_flotte(flotte, unite3);

    set_pt_vie(&(flotte->tab_unite[0]), 10);
    set_pt_vie(&(flotte->tab_unite[1]), 15);
    set_pt_vie(&(flotte->tab_unite[2]), 20);

    afficher_flotte(flotte);

    retirer_unite_flotte(flotte, 1);
    ajouter_unite_flotte(flotte, unite3);
    set_pt_vie(&(flotte->tab_unite[2]), 30);
    afficher_flotte(flotte);

    if((flotte->taille_maximum_flotte == 10) && (flotte->taille_flotte == 3))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}



}*/

