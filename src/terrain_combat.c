/**
 * \file      terrain_combat.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit un terrain de combat
 * \details   Cette classe définit un terrain de combat et ses caractéristiques
 */

#include <math.h>
#include "case_terrain_combat.h"
#include "terrain_combat.h"




/************************************************************************/
/* Initialisation, création et destruction                              */
/************************************************************************/

void initilalise_terrain_combat(Terrain_combat *terrain_jeu_combat,const int taille_combat_x,const int taille_combat_y)
{
    int i, j;
    terrain_jeu_combat->taille_combat_x = taille_combat_x;
    terrain_jeu_combat->taille_combat_y = taille_combat_y;
	terrain_jeu_combat->une_case_selectionnee=0;
	terrain_jeu_combat->selection=NULL;
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

Terrain_combat *creer_terrain_combat(const int taille_combat_x, const int taille_combat_y)
{
    Terrain_combat *terrain_combat = (Terrain_combat *)malloc(sizeof(Terrain_combat));
    initilalise_terrain_combat(terrain_combat, taille_combat_x, taille_combat_y);
    return terrain_combat;
}

void libere_terrain_combat(Terrain_combat *terrain_jeu_combat)
{
	int i, j;
	for(i=0;i<terrain_jeu_combat->taille_combat_y;i++)
	{
		for(j=0;j<terrain_jeu_combat->taille_combat_x;j++)
		{
			libere_case_terrain_combat(terrain_jeu_combat->tab_terrain_combat + (i*(terrain_jeu_combat->taille_combat_x)+j));
		}
	}
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

/************************************************************************/
/* Fonctions set et get                                                 */
/************************************************************************/

void set_taille_combat_x(Terrain_combat *terrain_jeu_combat,const int x)
{
    terrain_jeu_combat->taille_combat_x = x;
}

int get_taille_combat_x(const Terrain_combat *terrain_jeu_combat)
{
    return terrain_jeu_combat->taille_combat_x;
}

void set_taille_combat_y(Terrain_combat *terrain_jeu_combat,const int y)
{
    terrain_jeu_combat->taille_combat_y = y;
}

int get_taille_combat_y(const Terrain_combat *terrain_jeu_combat)
{
    return terrain_jeu_combat->taille_combat_y;
}
void set_une_case_selectionnee(Terrain_combat *terrain_jeu_combat,const bool y)
{
    terrain_jeu_combat->une_case_selectionnee = y;
}

void set_selection(Terrain_combat *terrain_jeu_combat,Case_terrain_combat * un_case_terrain_combat)
{
    terrain_jeu_combat->selection = un_case_terrain_combat;
}
Case_terrain_combat * get_selection(const Terrain_combat *terrain_jeu_combat)
{
    return terrain_jeu_combat->selection;
}

bool get_une_case_selectionnee(const Terrain_combat *terrain_jeu_combat)
{
    return terrain_jeu_combat->une_case_selectionnee;
}
Case_terrain_combat* get_case_terrain_combat(const Terrain_combat *terrain_combat, const int x, const int y)
{
    return terrain_combat->tab_terrain_combat+(y*(terrain_combat->taille_combat_x)+x);
}

void modifie_type_case_terrain_combat(const Terrain_combat *terrain_combat, const int x, const int y, const char c)
{
    set_type_case_terrain_combat(terrain_combat->tab_terrain_combat+(y*(terrain_combat->taille_combat_x)+x),c);
}


/************************************************************************/
/* Fonctions diverses                                                   */
/************************************************************************/

/**
 * \brief      affiche le terrain en texte
 * \details    affiche "|E|" pour une case vide , "|U|" pour une unité présente
 * \param      terrain_combat         Pointeur sur Terrain_combat 
 */
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


/**
 * \brief      modifie le terrain
 * \details    rempli le terrain avec le char c
 * \param      terrain_combat         Pointeur sur Terrain_combat 
 * \param      c        char
 */
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


/**
 * \brief      déplace une unité
 * \details    deplace une_unite vers la case de coordonées (x,y)
 * \param      terrain_combat         Pointeur sur Terrain_combat 
 * \param      une_Unite       Pointeur vers Unite 
 * \param      x       abscisse
 * \param      y       ordonnée
 * \return     1 si on a réussi le déplacement, 0 sinon
 */
bool deplacement_unite(Terrain_combat *un_terrain_combat, Unite *une_unite,const int x,const int y)
{
    if((unite_peut_se_deplacer(une_unite, x, y))&& (!get_presence_unite(get_case_terrain_combat(un_terrain_combat,x,y))) &&(x<un_terrain_combat->taille_combat_x) && (y<un_terrain_combat->taille_combat_y)&&(x>=0)&&(y>=0))/*si l'unité peux se déplacer et qu'il n'y a pas d'unité sur la case d'arrivé et que les coordonnées de la case d'arrivée ne sortent pas du terrain*/
    {
        int distance;
        int x_depart, y_depart;
        Case_terrain_combat *case_depart;
        Case_terrain_combat *case_arrivee;

        x_depart = get_x_unite(une_unite);
        y_depart = get_y_unite(une_unite);

        case_depart = get_case_terrain_combat(un_terrain_combat, x_depart, y_depart);
        case_arrivee = get_case_terrain_combat(un_terrain_combat, x, y);

        ajouter_unite(case_arrivee, une_unite);/*on ajoute l'unité sur la case d'arrivée*/
        retirer_unite(case_depart);/*on retire l'unité de la case de départ*/

        distance = calcul_distance_unite(x_depart, y_depart, x, y);/*calcule la distance */
        enlever_pt_mouvement_combat_unite(une_unite, distance);/*retire des points de déplacement selon la distance parcourue*/

        return true;
    }
    else { printf("\nimpossible de déplacer l'unité\n");return false;}

}


/**
 * \brief      ajoute une unité sur la case de coordonnée (x,y)
 * \details    
 * \param      terrain_combat         Pointeur sur Terrain_combat 
 * \param      une_Unite       Pointeur vers Unite 
 * \param      x       abscisse
 * \param      y       ordonnée
 */
void ajoute_unite_terrain(Terrain_combat * un_terrain_combat, Unite * unite,const int x,const int y)
{
	Case_terrain_combat * une_case;
	une_case = get_case_terrain_combat(un_terrain_combat,x,y);
	ajouter_unite(une_case,unite);
}

/**
 * \brief      vérifie si une case est libre
 * \details     
 * \param      terrain_combat         Pointeur sur Terrain_combat 
 * \param      x       abscisse
 * \param      y       ordonnée
 * \return     1 si la case de coordonnée (x,y) est occupée, 0 sinon
 */
bool case_libre(const Terrain_combat * un_terrain_combat,const int x,const int y)
{
	bool p;
	p = get_presence_unite(un_terrain_combat->tab_terrain_combat+(y*(un_terrain_combat->taille_combat_x)+x));
	return p;
}


void un_tour_combat(Terrain_combat * un_terrain_combat, Flotte * flotte)// à suprimer ? 
{
	int a,b;
	char  controle[] ="control";
	Unite * une_unite;
	bool p;
	do{
		printf("Que voulez vous faire ? jouer ou passer ?");
		scanf("%s", controle);
	}while((strcmp(controle,"jouer"))&&(strcmp(controle,"passer")));
	if((!strcmp(controle,"jouer")))
	{
		do
		{	
			printf("quelle unite voulez vous utiliser ?\n");
			scanf("%d",&a);
			une_unite = get_unite_i_flotte(flotte, a);
		}while(une_unite==NULL);
		do{
		printf("Que voulez vous faire ? attaquer,deplacer ou passer ?");
		scanf("%s", controle);
		}while((strcmp(controle,"attaquer"))&&(strcmp(controle,"deplacer"))&&(strcmp(controle,"passer")));
		if(!strcmp(controle,"deplacer"))
		{
			do{
				printf("Où voulez vous la déplacer ?\n");
				scanf("%d %d",&a,&b);
				p=deplacement_unite(un_terrain_combat, une_unite,a,b);
			}while(!p);
			enlever_pt_action_unite(une_unite, 1);
			affiche_terrain_combat(un_terrain_combat);
			afficher_flotte(flotte);
			
		}
		if(!strcmp(controle,"attaquer"))
		{
			printf("Où voulez vous attaquer ?\n");
			scanf("%d %d",&a,&b);
			p=((peut_attaquer_hor_vert(un_terrain_combat, une_unite,a,b))||(peut_attaquer_diag(un_terrain_combat, une_unite,a,b)));
			if(p==false){printf("impossible\n");} 
			else 
			{printf("on attaque!\n");attaquer(un_terrain_combat,une_unite, a, b);}
			enlever_pt_action_unite(une_unite, 2);
			affiche_terrain_combat(un_terrain_combat);
			afficher_flotte(flotte);
		}

	}
	
}


/**
 * \brief      une_unité attaque l'unité en coordonnées (x,y)
 * \details    
 * \param      terrain_combat         Pointeur sur Terrain_combat  
 * \param      une_Unite       Pointeur vers Unite 
 * \param      x       abscisse
 * \param      y       ordonnée
 * \return     1 si l'unité à attaqué et qu'il reste des points de vie à la "victime", -2 si l'unité à attaqué et qu'il ne reste pas de points de vie à la "victime", 0 si elle n'a pas réussi à attaquer
 */
int attaquer(Terrain_combat * un_terrain_combat,Unite * une_unite,const int x,const int y)
{	
	Unite * victime;/*l'unité attaquée*/
	int pt_attaque_unite, pt_vie_victime;
	int p;
	Case_terrain_combat * une_case;
	une_case = get_case_terrain_combat(un_terrain_combat,x,y);
	p=0;
	if(get_presence_unite(une_case))/*si il y a une unité à la case de coordonnées (x,y)*/
	{
		victime = get_unite(une_case);/*on récupère l'unité de la case*/
		pt_attaque_unite = get_pt_attaque(une_unite);/*on récupère les points d'attaque de une_unite*/
		pt_vie_victime = get_pt_vie(victime);/*on récupère les points de vie de la victime*/
		set_pt_vie(victime ,pt_vie_victime - pt_attaque_unite);

		if (get_pt_vie(victime)<=0)/*si la victime n'a plus de points de vie*/
		{
			p=-2;
			return p;
		}
		else
		{
			p=1;
			return p;
		}
	}
	else/*on n'a pas réussi à attaquer*/
	{
		return p;
	}
}

/**
 * \brief      vérifiesi une_unite peut attaquer horizontalement ou verticalement
 * \details    
 * \param      terrain_combat         Pointeur sur Terrain_combat  
 * \param      une_Unite       Pointeur vers Unite 
 * \param      x       abscisse
 * \param      y       ordonnée
 * \return     1 si l'unité peut attaquer, 0 sinon
 */
bool peut_attaquer_hor_vert(Terrain_combat * un_terrain_combat, const Unite * unite,const int x,const int y)
{
	int x_min, y_min, x_max, y_max, x_un, y_un, portee, pa;
	portee = get_portee(unite);
	pa = get_pt_action(unite);
	x_un=get_x_unite(unite);/*abscisse de une_unite*/
	y_un=get_y_unite(unite);/*ordonnée de une_unite*/

	x_min = x_un - portee;/*abscisse minimum ou une_unite peut attaquer*/
    y_min = y_un - portee;/*ordonnée minimum ou une_unite peut attaquer*/
    x_max = x_un + portee;/*abscisse maximum ou une_unite peut attaquer*/
    y_max = y_un + portee;/*ordonnée maximum ou une_unite peut attaquer*/

    if((((y>=y_min) && (y<=y_max)&&(y!=y_un)&&(x==x_un))||((x>=x_min) && (x<=x_max)&&(x!=x_un)&&(y==y_un)))&& (pa > 0) && (get_presence_unite(get_case_terrain_combat(un_terrain_combat,x,y))))/*si y_min<=y<=y_max et y!=y_un  , ou , x_min<=x<=x_max et x!= x_un,  et si il y a une unité sur la case (x,y) , alors on peut attaquer*/
    {
		return true;
    }
    else /*on ne peut pas attaquer*/ 
	{
		return false;
	}
}


/**
 * \brief      vérifie si une_unite peut attaquer en diagonale
 * \details     
 * \param      terrain_combat         Pointeur sur Terrain_combat  
 * \param      une_Unite       Pointeur vers Unite 
 * \param      x       abscisse
 * \param      y       ordonnée
 * \return     1 si l'unité peut attaquer, 0 sinon
 */
bool peut_attaquer_diag(Terrain_combat * un_terrain_combat, Unite * unite,int x,int y)
{
	int x_un, y_un, x_poss, y_poss, portee, pa;
	portee = get_portee(unite);
	pa = get_pt_action(unite);
	x_un=get_x_unite(unite);y_un=get_y_unite(unite);
	
	x_poss = abs( x - x_un);
	y_poss = abs(y - y_un);

    if((x_poss==y_poss)&&(x_poss<= portee)&&(x_poss>0)&& (pa > 0)&& (get_presence_unite(get_case_terrain_combat(un_terrain_combat,x,y))))
    {
        return true;
    }
    else 
	{
		return false;
	}
}


/**
 * \brief      supprime une unité d'une flotte
 * \details    
 * \param      terrain_combat         Pointeur sur Terrain_combat
 * \param      une_Unite       Pointeur vers Unite 
 * \param      flotte      Pointeur vers Flotte 
 */
void supprimer_unite_flotte(Terrain_combat * un_terrain_combat,Flotte * flotte ,Unite* unite)
{
	int i,x,y;
	Case_terrain_combat * une_case;
	i=get_indice_unite_dans_flotte(unite);
	x=get_x_unite(unite);
	y=get_y_unite(unite);
	une_case = get_case_terrain_combat(un_terrain_combat,x,y);
	retirer_unite(une_case);
	retirer_unite_flotte(flotte,i);
}

/**
 * \brief      Désélectionne la case sélectionnée
 * \details    
 * \param      terrain_combat         Pointeur sur Terrain_combat
 */
void deselectionner(Terrain_combat * un_terrain_combat)
{
	set_selection_unite(get_selection(un_terrain_combat),0);
	set_selection(un_terrain_combat,NULL);
	set_une_case_selectionnee(un_terrain_combat,0);
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

