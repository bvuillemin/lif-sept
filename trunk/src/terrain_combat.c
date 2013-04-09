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
    if((unite_peut_se_deplacer(une_unite, x, y))&& (!get_presence_unite(get_case_terrain_combat(un_terrain_combat,x,y))))
    {
        int distance;
        int x_depart, y_depart;
        Case_terrain_combat *case_depart;
        Case_terrain_combat *case_arrivee;

        x_depart = get_x_unite(une_unite);
        y_depart = get_y_unite(une_unite);
	printf("case départ :(%d,%d) \n",x_depart,y_depart);
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

void un_tour_combat(Terrain_combat * un_terrain_combat, Flotte * flotte)
{
	int a,b,controle;
	Unite * une_unite;
	bool p;
	do{
		printf("Que voulez vous faire ? jouer ou passer ?");
		scanf("%s", &controle);
	}while((controle!="jouer")||(controle!="passer"));
	if((controle=="jouer"))
	{
		do
		{	
			printf("quelle unite voulez vous utiliser ?\n");
			scanf("%d",&a);
			une_unite = get_unite_i_flotte(flotte, a);
		}while(une_unite==NULL);
		do{
		printf("Que voulez vous faire ? attaquer,deplacer ou passer ?");
		scanf("%s", &controle);
		}while((controle!="attaquer")||(controle!="deplacer")||(controle!="passer"));
		if(controle =="deplacer")
		{
			do{
				printf("Où voulez vous la déplacer ?\n");
				scanf("%d %d",&a,&b);
				p=deplacement_unite(un_terrain_combat, une_unite,a,b);
			}while(!p);
			affiche_terrain_combat(un_terrain_combat);
			afficher_flotte(flotte);
		}
		if(controle =="attaquer")
		{
			do{
				printf("Où voulez vous attaquer ?\n");
				scanf("%d %d",&a,&b);
				p=deplacement_unite(un_terrain_combat, une_unite,a,b);
			}while(!p);
			affiche_terrain_combat(un_terrain_combat);
			afficher_flotte(flotte);
		}

	}
	
}
bool peut_attaquer_hor_vert(Terrain_combat * un_terrain_combat, Unite * unite,int x,int y)
{
	int x_min, y_min, x_max, y_max, x_un, y_un, portee, pa;
	portee = get_portee(unite);
	pa = get_pt_action(unite);
	x_un=get_x_unite(unite);y_un=get_y_unite(unite);
   x_min = x_un - portee;
    y_min = y_un - portee;
    x_max = x_un + portee;
    y_max = y_un + portee;
	printf("poss = (%d,%d);min (%d,%d) ; max (%d,%d) ; unite (%d,%d)\n",x,y,x_min,y_min,x_max, y_max,x_un,y_un);
    if((((y>=y_min) && (y<=y_max)&&(y!=y_un)&&(x==x_un))||((x>=x_min) && (x<=x_max)&&(x!=x_un)&&(y==y_un)))&& (pa > 0) && (get_presence_unite(get_case_terrain_combat(un_terrain_combat,x,y))))
    {
        return true;
    }
    else {return false;}
}
bool peut_attaquer_diag(Terrain_combat * un_terrain_combat, Unite * unite,int x,int y)
{
	int x_un, y_un, x_poss, y_poss, portee, pa;
	portee = get_portee(unite);
	pa = get_pt_action(unite);
	x_un=get_x_unite(unite);y_un=get_y_unite(unite);
	
	x_poss = x - x_un;
	y_poss = y - y_un;
	printf("poss = (%d,%d);unite (%d,%d)\n",x,y,x_un,y_un);
    if((x_poss==y_poss)&&(x_poss<= portee)&&(x_poss>0)&& (pa > 0))
    {
        return true;
    }
    else {return false;}
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

