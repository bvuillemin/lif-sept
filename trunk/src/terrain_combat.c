#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "case_terrain_combat.h"
#include "terrain_combat.h"
#include "flotte.h"
#include "unite.h"
void set_taille_combat_x(Terrain_combat *terrain_jeu_combat, int x)
{
    terrain_jeu_combat->taille_combat_x = x;
}

int get_taille_combat_x(const Terrain_combat *terrain_jeu_combat)
{
    return terrain_jeu_combat->taille_combat_x;
}

void set_taille_combat_y(Terrain_combat *terrain_jeu_combat, int y)
{
    terrain_jeu_combat->taille_combat_y = y;
}

int get_taille_combat_y(const Terrain_combat *terrain_jeu_combat)
{
    return terrain_jeu_combat->taille_combat_y;
}

Case_terrain_combat* get_case_terrain_combat(const Terrain_combat *terrain_combat, const int x, const int y)
{
    return terrain_combat->tab_terrain_combat+(y*(terrain_combat->taille_combat_x)+x);
}

void modifie_type_case_terrain_combat(const Terrain_combat *terrain_combat, int x, int y, char c)
{
    set_type_case_terrain_combat(terrain_combat->tab_terrain_combat+(y*(terrain_combat->taille_combat_x)+x),c);
}

void initilalise_terrain_combat(Terrain_combat *terrain_jeu_combat, int taille_combat_x, int taille_combat_y)
{
    int i, j;
    terrain_jeu_combat->taille_combat_x = taille_combat_x;
    terrain_jeu_combat->taille_combat_y = taille_combat_y;
    terrain_jeu_combat->tab_terrain_combat = (Case_terrain_combat *)malloc(sizeof(Case_terrain_combat)*(taille_combat_x*taille_combat_y+taille_combat_x));
    for(i=0;i<terrain_jeu_combat->taille_combat_y;i++)
    {
        for(j=0;j<terrain_jeu_combat->taille_combat_x;j++)
        {
			initialise_case_combat(terrain_jeu_combat->tab_terrain_combat+(i*(terrain_jeu_combat->taille_combat_x)+j));
           terrain_jeu_combat->tab_terrain_combat[i*(terrain_jeu_combat->taille_combat_x)+j].x_combat = j;
           terrain_jeu_combat->tab_terrain_combat[i*(terrain_jeu_combat->taille_combat_x)+j].y_combat = i;
        }
    }

}

Terrain_combat *creer_terrain_combat(int taille_combat_x, int taille_combat_y)
{
    Terrain_combat *terrain_combat = (Terrain_combat *)malloc(sizeof(Terrain_combat));
    initilalise_terrain_combat(terrain_combat, taille_combat_x, taille_combat_y);
    return terrain_combat;
}

void libere_terrain_combat(Terrain_combat *terrain_jeu_combat)
{
    free(terrain_jeu_combat->tab_terrain_combat);
    terrain_jeu_combat->taille_combat_x=0;
    terrain_jeu_combat->taille_combat_y=0;
}

void detruit_terrain_combat(Terrain_combat **terrain_jeu_combat)
{
    libere_terrain_combat(*terrain_jeu_combat);
    free(*terrain_jeu_combat);
    *terrain_jeu_combat = NULL;
}

void affiche_terrain_combat(const Terrain_combat *terrain_combat)
{
    int i, j;
    Case_terrain_combat *une_case;
    for(j=0;j<terrain_combat->taille_combat_y;j++)
    {
        for(i=0;i<terrain_combat->taille_combat_x;i++)
        {
            une_case = get_case_terrain_combat(terrain_combat, i, j);
            if(une_case->presence_unite == true)
            {
				printf("|U|");
            }
            else{printf("|%c|", une_case->type_case_terrain_combat);}
        }
        printf("\n");
    }
    printf("\n");
}

void modification_terrain_combat(const Terrain_combat *terrain_combat, const char c)
{
    int i, j;
    for(i=0;i<terrain_combat->taille_combat_x;i++)
    {
        for(j=0;j<terrain_combat->taille_combat_y;j++)
        {
            modifie_type_case_terrain_combat(terrain_combat, i, j, c);
        }
    }
}






bool deplacement_unite(Terrain_combat *un_terrain_combat, Unite *une_unite, int x, int y)
{
    if(unite_peut_se_deplacer(une_unite, x, y))
    {
        int distance;
        int x_depart, y_depart;
        Case_terrain_combat *case_depart;
        Case_terrain_combat *case_arrivee;

        x_depart = get_x_unite(une_unite);
        y_depart = get_y_unite(une_unite);
        case_depart = get_case_terrain_combat(un_terrain_combat, x_depart, y_depart);
        case_arrivee = get_case_terrain_combat(un_terrain_combat, x, y);
        ajouter_unite(case_arrivee, une_unite);
        retirer_unite(case_depart);
        distance = calcul_distance_unite(x_depart, y_depart, x, y);
        enlever_pt_mouvement_combat_unite(une_unite, distance);
        return true;
    }
    else { printf("\nimpossible de déplacer l'unité\n");return false;}

}

void ajoute_unite_terrain(Terrain_combat * un_terrain_combat, Unite * unite, int x, int y)
{
	Case_terrain_combat * une_case;
	une_case = get_case_terrain_combat(un_terrain_combat,x,y);
	ajouter_unite(une_case,unite);
}

bool case_libre(Terrain_combat * un_terrain_combat,int x, int y)
{
	bool p;
	p = get_presence_unite(un_terrain_combat->tab_terrain_combat+(y*(un_terrain_combat->taille_combat_x)+x));
	return p;
}

void placer_unite_flotte_en_haut(Terrain_combat * un_terrain_combat, Flotte * flotte)
{
	int i,m,n;
	Unite * une_unite;
	for(i=0;i<(flotte->taille_flotte);i++)
	{
		une_unite=get_unite_i_flotte(flotte,i);
		m=get_x_unite(une_unite);
		n=get_y_unite(une_unite);
		while(case_libre(un_terrain_combat, m,n))
		{
			set_y_unite(une_unite,n+1);
			m=get_x_unite(une_unite);
			n=get_y_unite(une_unite);
		}
			ajoute_unite_terrain(un_terrain_combat, une_unite,m,n);
	}
	
}

void placer_unite_flotte_en_bas(Terrain_combat * un_terrain_combat, Flotte * flotte)
{
	int i,m,n;
	Unite * une_unite;
	for(i=0;i<(flotte->taille_flotte);i++)
	{
		une_unite=get_unite_i_flotte(flotte,i);
		m=(un_terrain_combat->taille_combat_x)-1;
		n=(un_terrain_combat->taille_combat_y)-1;
		set_x_unite(une_unite,m);
		set_y_unite(une_unite,n);
		while(case_libre(un_terrain_combat, m,n))
		{
			set_y_unite(une_unite,n-1);
			m=get_x_unite(une_unite);
			n=get_y_unite(une_unite);
		}
			ajoute_unite_terrain(un_terrain_combat, une_unite,m,n);
	}
	
}

/*void test_module_terrain_combat()
{
    Terrain_combat *terrain_combat;
    terrain_combat = creer_terrain(20, 20);
    modification_terrain(terrain_combat, 'E');
    affiche_terrain(terrain_combat);

    affiche_terrain(terrain_combat);

    detruit_terrain_combat(&terrain_combat);

}

*/

