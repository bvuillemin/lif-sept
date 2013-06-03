/**
 * \file      unite.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les unités du jeu
 * \details   Cette classe définit les unités du jeu et leurs caractéristiques
 */
#include <math.h>
#include "constante.h"
#include "unite.h"


/************************************************************************/
/* Initialisation, création et destruction                              */
/************************************************************************/

void initialiser_unite(Unite *unite_jeu, TYPE_VAISSEAU type)
{
	if(type == Chasseur)
	{
		unite_jeu->type = type;
		unite_jeu->x_unite=0;
		unite_jeu->y_unite=0;

		unite_jeu->portee = PT_PORTEE_UNITE_1;
		unite_jeu->pt_vie= PT_VIE_UNITE_1;
		unite_jeu->pt_vie_total = PT_VIE_UNITE_1;

		unite_jeu->pt_attaque= PT_ATTAQUE_UNITE_1;
		unite_jeu->pt_attaque_total = PT_ATTAQUE_UNITE_1;
		unite_jeu->pt_action= PT_ACTION_UNITE_1;
		unite_jeu->pt_action_total= PT_ACTION_UNITE_1;

		unite_jeu->pt_deplacement= PT_DEPLACEMENT_UNITE_1;
		unite_jeu->pt_deplacement_total= PT_DEPLACEMENT_UNITE_1;
		unite_jeu->pt_mouvement_unite= PT_MOUVEMENT_UNITE_1;
	}
	if(type == Destroyer)
	{
		unite_jeu->type = type;
		unite_jeu->x_unite=0;
		unite_jeu->y_unite=0;

		unite_jeu->portee = PT_PORTEE_UNITE_2;
		unite_jeu->pt_vie= PT_VIE_UNITE_2;
		unite_jeu->pt_vie_total = PT_VIE_UNITE_2;

		unite_jeu->pt_attaque= PT_ATTAQUE_UNITE_1;
		unite_jeu->pt_attaque_total = PT_ATTAQUE_UNITE_2;
		unite_jeu->pt_action= PT_ACTION_UNITE_2;
		unite_jeu->pt_action_total= PT_ACTION_UNITE_2;

		unite_jeu->pt_deplacement= PT_DEPLACEMENT_UNITE_2;
		unite_jeu->pt_deplacement_total= PT_DEPLACEMENT_UNITE_2;
		unite_jeu->pt_mouvement_unite= PT_MOUVEMENT_UNITE_2;
	}
	if(type == Destructeur)
	{
		unite_jeu->type = type;
		unite_jeu->x_unite=0;
		unite_jeu->y_unite=0;

		unite_jeu->portee = PT_PORTEE_UNITE_3;
		unite_jeu->pt_vie= PT_VIE_UNITE_3;
		unite_jeu->pt_vie_total = PT_VIE_UNITE_3;

		unite_jeu->pt_attaque= PT_ATTAQUE_UNITE_3;
		unite_jeu->pt_attaque_total = PT_ATTAQUE_UNITE_3;
		unite_jeu->pt_action= PT_ACTION_UNITE_3;
		unite_jeu->pt_action_total= PT_ACTION_UNITE_3;

		unite_jeu->pt_deplacement= PT_DEPLACEMENT_UNITE_3;
		unite_jeu->pt_deplacement_total= PT_DEPLACEMENT_UNITE_3;
		unite_jeu->pt_mouvement_unite= PT_MOUVEMENT_UNITE_3;
	}
}

Unite *creer_unite(TYPE_VAISSEAU type)
{
    Unite *nouvelle_unite = (Unite *)malloc(sizeof(Unite));
    initialiser_unite(nouvelle_unite, type);
    return nouvelle_unite;
}

void liberer_unite(Unite *unite_jeu)
{
	unite_jeu->x_unite = 0;
	unite_jeu->y_unite = 0;

	unite_jeu->portee = 0;
	unite_jeu->pt_vie= 0;
	unite_jeu->pt_vie_total = 0;

	unite_jeu->pt_attaque = 0;
	unite_jeu->pt_attaque_total = 0;
	unite_jeu->pt_action = 0;
	unite_jeu->pt_action_total = 0;

	unite_jeu->pt_deplacement = 0;
	unite_jeu->pt_deplacement_total = 0;
	unite_jeu->pt_mouvement_unite = 0;
}

void detruire_unite(Unite **unite_jeu)
{
    liberer_unite(*unite_jeu);
    free(*unite_jeu);
    *unite_jeu = NULL;
}


/************************************************************************/
/* Fonctions set et get                                                 */
/************************************************************************/

TYPE_VAISSEAU get_type_vaisseau(Unite* une_unite)
{
	return une_unite->type;
}
void set_indice_unite_dans_flotte(Unite *unite,const int i)
{
    unite->indice_dans_flotte = i;
}
int get_indice_unite_dans_flotte(const Unite *unite)
{
    return unite->indice_dans_flotte;
}
void set_pt_attaque(Unite *unite_jeu, const int x)
{
	unite_jeu->pt_attaque = x;
}
void set_pt_attaque_total(Unite *unite_jeu, const int x)
{
	unite_jeu->pt_attaque_total = x;
}
int get_pt_attaque_total(const Unite *unite_jeu)
{
	return unite_jeu->pt_attaque_total;
}
void set_pt_action_total(Unite *unite_jeu, const int x)
{
	unite_jeu->pt_action_total = x;
}
int get_pt_action_total(const Unite *unite_jeu)
{
	return unite_jeu->pt_action_total;
}
void set_pt_vie(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_vie = x;
}
void set_indice_joueur_unite(Unite *unite,const int i)
{
    unite->indice_joueur = i;
}
int get_indice_joueur_unite(const Unite *unite)
{
    return unite->indice_joueur;
}
void set_portee(Unite *unite_jeu, const int x)
{
	unite_jeu->portee = x;
}
int get_portee(const Unite *unite_jeu)
{
	return unite_jeu->portee;
}
int get_pt_vie(const Unite *unite_jeu)
{
    return unite_jeu->pt_vie;
}
void set_x_unite(Unite *unite_jeu, const int x)
{
	unite_jeu->x_unite=x;
}
int get_x_unite(const Unite *unite_jeu)
{
	return unite_jeu->x_unite;
}
void set_y_unite(Unite *unite_jeu, const int y)
{
	unite_jeu->y_unite=y;
}
int get_y_unite(const Unite *unite_jeu)
{
	return unite_jeu->y_unite;
}
int get_pt_attaque(const Unite *unite_jeu)
{
    return unite_jeu->pt_attaque;
}
void set_pt_action(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_action = x;
}
int get_pt_action(const Unite *unite_jeu)
{
    return unite_jeu->pt_action;
}
void set_pt_deplacement(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_deplacement = x;
}
int get_pt_deplacement(const Unite *unite_jeu)
{
    return unite_jeu->pt_deplacement;
}
void set_pt_mouvement_unite(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_mouvement_unite = x;
}
int get_pt_mouvement_unite(const Unite *unite_jeu)
{
    return unite_jeu->pt_mouvement_unite;
}


/************************************************************************/
/* Fonctions diverses                                                   */
/************************************************************************/

/**
 * \brief      Vérifie si une unité peut se déplacer
 * \details    Renvoie 1 si l'unité peut se déplacer, 0 sinon
 * \param      une_unite         Pointeur sur Unite 
 * \param      x	cordonnée en abscisse de l'unité
 * \param      y	cordonnée en ordonnée de l'unité
 */
bool unite_peut_se_deplacer(const Unite *une_unite, int x, int y)
{
    int x_min, y_min, x_max, y_max;

    x_min = une_unite->x_unite - une_unite->pt_deplacement;
    y_min = une_unite->y_unite - une_unite->pt_deplacement;
    x_max = une_unite->x_unite + une_unite->pt_deplacement;
    y_max = une_unite->y_unite + une_unite->pt_deplacement;
	printf("poss = (%d,%d);min (%d,%d) ; max (%d,%d) ; unite (%d,%d)\n",x,y,x_min,y_min,x_max, y_max,une_unite->x_unite,une_unite->y_unite);
    if((((y>=y_min) && (y<=y_max)&&(y!=une_unite->y_unite)&&(x==une_unite->x_unite))||((x>=x_min) && (x<=x_max)&&(x!=une_unite->x_unite)&&(y==une_unite->y_unite)))&& (une_unite->pt_mouvement_unite > 0))
    {
        return true;
    }
    else {return false;}
}


/**
 * \brief      Calcule la distance entre deux point
 * \details    Renvoie la distance entre une case de coordonnées (x_depart,y_depart) et une case de coordonnées (x_arrivee,y_arrivee)
 */
int calcul_distance_unite(const int x_depart, const int y_depart, const int x_arrivee, const int y_arrivee)
{
    return ceil(sqrt(pow(x_depart - x_arrivee, 2) + pow(y_depart - y_arrivee, 2)) - 0.1); /*on enleve 0.1 pour etre un peu plus précis: si on se deplace de 7.05 on veut que ce soit 7*/
}


/**
 * \brief      enlève des points de déplacements à l'unité
 * \details    enlève "distance" au points de déplacement de l'unité
 * \param      une_unite         Pointeur sur Unite 
 * \param      distance		le nombre de points de déplacement à retirer
 */
void enlever_pt_mouvement_combat_unite(Unite *une_unite, const int distance)
{
    int temp = get_pt_deplacement(une_unite);
    temp = temp - distance;
    set_pt_deplacement(une_unite, temp);
}


/**
 * \brief      enlève des points d'action à l'unité
 * \details    enlève "point" au points d'action de l'unité
 * \param      une_unite         Pointeur sur Unite 
 * \param      point		le nombre de points d'action à retirer
 */
void enlever_pt_action_unite(Unite *une_unite, const int point)
{
	int temp = get_pt_action(une_unite);
    temp = temp - point;
    set_pt_action(une_unite, temp);
}


/**
 * \brief      réinitialise les points de déplacement de l'unité
 * \details    
 * \param      une_unite         Pointeur sur Unite 
 */
void reinitialiser_mouvement_combat_unite(Unite *une_unite)
{
	une_unite->pt_deplacement = une_unite->pt_deplacement_total;
}

/**
 * \brief      réinitialise les points d'action de l'unité
 * \details    
 * \param      une_unite         Pointeur sur Unite 
 */
void reinitialiser_pt_action(Unite *une_unite)
{
	une_unite->pt_action = une_unite->pt_action_total;
}


/************************************************************************/
/* Fonctions sauvegarde et chargement                                   */
/************************************************************************/

void sauvegarde_unite(const Unite *une_unite, FILE* f)
{
    fprintf(f, "%d\n", (int)une_unite->type);
    fprintf(f, "%d\n", une_unite->indice_joueur);
    fprintf(f, "%d\n", une_unite->indice_dans_flotte);
    fprintf(f, "%d\n", une_unite->x_unite);
    fprintf(f, "%d\n", une_unite->y_unite);
    fprintf(f, "%d\n", une_unite->portee);
    fprintf(f, "%d\n", une_unite->pt_vie);
    fprintf(f, "%d\n", une_unite->pt_vie_total);
    fprintf(f, "%d\n", une_unite->pt_attaque);
    fprintf(f, "%d\n", une_unite->pt_attaque_total);
    fprintf(f, "%d\n", une_unite->pt_action);
    fprintf(f, "%d\n", une_unite->pt_action_total);
    fprintf(f, "%d\n", une_unite->pt_deplacement);
    fprintf(f, "%d\n", une_unite->pt_deplacement_total);
    fprintf(f, "%d\n", une_unite->pt_mouvement_unite);
}

Unite* ouverture_unite(FILE *f)
{
    char chaine[50];
    Unite *unite_ouverte;
    int b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte = creer_unite(b);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->indice_joueur);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->indice_dans_flotte);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->x_unite);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->y_unite);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->portee);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->pt_vie);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->pt_vie_total);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->pt_attaque);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->pt_attaque_total);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->pt_action);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->pt_action_total);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->pt_deplacement);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->pt_deplacement_total);
    sscanf(fgets(chaine, 50, f), "%d", &unite_ouverte->pt_mouvement_unite);
    return unite_ouverte;
}

void testRegression_Unite()
{
    Unite * chasseur;
	Unite * destroyer;
	Unite * destructeur;

	chasseur = creer_unite(Chasseur);
	destroyer = creer_unite(Destroyer);
	destructeur = creer_unite(Destructeur);
	
	assert(chasseur->x_unite == 0);
    assert(chasseur->y_unite == 0);
	assert(destroyer->x_unite == 0);
    assert(destroyer->y_unite == 0);
	assert(destructeur->x_unite == 0);
    assert(destructeur->y_unite == 0);
    detruire_unite(&chasseur);
    detruire_unite(&destroyer);
    detruire_unite(&destructeur);
}

