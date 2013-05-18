#include <stdlib.h>
#include <stdio.h>

#include "flotte.h"
#include "case_terrain_espace.h"
#include "terrain_espace.h"
#include "sauvegarde.h"


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
    flotte->taille_maximum_flotte = 10; /*valeur temporaire qu'il faudra éventuellemnt modifié*/
    flotte->taille_flotte = 0;
	flotte->pt_mouvement_espace_flotte = 0;
    flotte->tab_unite = (Unite *)malloc(sizeof(Unite)*flotte->taille_maximum_flotte);
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
		liberer_unite(&(flotte->tab_unite[i]));
	}
	free(flotte->tab_unite);
	flotte->tab_unite = NULL;
	flotte->taille_maximum_flotte = 10; /*valeur temporaire qu'il faudra éventuellemnt modifié*/
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
		return flotte->tab_unite+i;
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

int ajouter_unite_flotte(Flotte *flotte, Unite *unite)
{
	int min = flotte->pt_mouvement_espace_flotte;
	if(flotte->taille_flotte < flotte->taille_maximum_flotte)
    {
		set_indice_joueur_unite(unite,flotte->indice_joueur);
		set_indice_unite_dans_flotte(unite,flotte->taille_flotte);
        flotte->tab_unite[flotte->taille_flotte] = *unite;
        flotte->taille_flotte ++;

		if((unite->pt_mouvement_unite < min)||(flotte->pt_mouvement_espace_flotte == 0))
		{
			flotte->pt_mouvement_espace_flotte = unite->pt_mouvement_unite;
		}
		//free(unite);
        return 1;
    }
    else
    {
        return 0;
    }
}

int transferer_unite_flotte(Flotte *flotte, Unite *unite)
{
	int min = flotte->pt_mouvement_espace_flotte;
	if(flotte->taille_flotte < flotte->taille_maximum_flotte)
    {
        flotte->tab_unite[flotte->taille_flotte] = *unite;
        flotte->taille_flotte ++;
		if((unite->pt_mouvement_unite < min)||(flotte->pt_mouvement_espace_flotte == 0))
		{
			flotte->pt_mouvement_espace_flotte = unite->pt_mouvement_unite;
		}
		liberer_unite(unite); /*free*/
		/*free(unite);*/
        return 1;
    }
    else
    {
        return 0;
    }
}

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

void afficher_flotte(const Flotte *flotte)
{
    int i;
	printf("Coordonnes de la flotte: %d %d, pt mouvement %d, taille : %d\n", flotte->x_flotte, flotte->y_flotte, flotte->pt_mouvement_espace_flotte,flotte->taille_flotte);
    for(i=0;i<flotte->taille_flotte;i++)
    {

        printf("Unite %d: pv = %d pa = %d pde = %d pme = %d  x= %d y=%d\n", i+1 , flotte->tab_unite[i].pt_vie, flotte->tab_unite[i].pt_action, flotte->tab_unite[i].pt_deplacement, flotte->tab_unite[i].pt_mouvement_unite, flotte->tab_unite[i].x_unite, flotte->tab_unite[i].y_unite);
    }

}

void enlever_pt_mouvement_espace_flotte(Flotte *une_flotte,const int distance)
{
    int temp = get_pt_mouvement_espace_flotte(une_flotte);
    temp = temp - distance;
    set_pt_mouvement_espace_flotte(une_flotte, temp);
}

void reinitialiser_mouvement_flotte(Flotte *une_flotte)
{
	int i;
	int min = 0;
	for(i=0;i<une_flotte->taille_flotte;i++)
	{
		if((une_flotte->tab_unite[i].pt_mouvement_unite < min)||(min == 0))
		{
			min = une_flotte->tab_unite[i].pt_mouvement_unite;
		}
	}
	une_flotte->pt_mouvement_espace_flotte = min;
}

void reinitialiser_deplacement_unite_flotte(Flotte *une_flotte)
{
	int i;
	for(i=0;i<une_flotte->taille_flotte;i++)
	{
		une_flotte->tab_unite[i].pt_deplacement = une_flotte->tab_unite[i].pt_deplacement_total;
	}
}

void reinitialiser_pt_action_unite_flotte(Flotte *une_flotte)
{
	int i;
	for(i=0;i<une_flotte->taille_flotte;i++)
	{
		reinitialiser_pt_action(une_flotte->tab_unite+i);
	}
}


/************************************************************************/
/* Fonctions sauvegarde et chargement                                   */
/************************************************************************/

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
        sauvegarde_unite(&une_flotte->tab_unite[i], f);
    }
}

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
        flotte_ouverte->tab_unite[i] = *ouverture_unite(f);
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

