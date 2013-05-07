#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "unite.h"

void initialise_unite(Unite *unite_jeu, const int pt_vie,const int pt_attaque,const int pt_action,const int pt_deplacement,const int portee,const int pt_mouvement)
{
	unite_jeu->x_unite=0;
	unite_jeu->y_unite=0;

	unite_jeu->portee = portee;
	unite_jeu->portee_total = portee;
    unite_jeu->pt_vie=pt_vie;
	unite_jeu->pt_vie_total = pt_vie;

    unite_jeu->pt_attaque=pt_attaque;
	unite_jeu->pt_attaque_total = pt_attaque;
    unite_jeu->pt_action=pt_action;
	unite_jeu->pt_action_total=pt_action;

    unite_jeu->pt_deplacement=pt_deplacement;
	unite_jeu->pt_deplacement_total=pt_deplacement;
    unite_jeu->pt_mouvement_unite=pt_mouvement;
	/*initialise_niveau(unite_jeu->niveau_unite, 0, 0);*/
}

Unite *creer_unite(const int pt_vie,const int pt_attaque,const int pt_action,const int pt_deplacement,const int portee,const int pt_mouvement)
{
    Unite *nouvelle_unite = (Unite *)malloc(sizeof(Unite));
    initialise_unite(nouvelle_unite, pt_vie, pt_attaque, pt_action, pt_deplacement,portee, pt_mouvement);
    return nouvelle_unite;
}

void liberer_unite(Unite *unite_jeu)
{
	unite_jeu->x_unite = 0;
	unite_jeu->y_unite = 0;

	unite_jeu->portee = 0;
	unite_jeu->portee_total = 0;
	unite_jeu->pt_vie= 0;
	unite_jeu->pt_vie_total = 0;

	unite_jeu->pt_attaque = 0;
	unite_jeu->pt_attaque_total = 0;
	unite_jeu->pt_action = 0;
	unite_jeu->pt_action_total = 0;

	unite_jeu->pt_deplacement = 0;
	unite_jeu->pt_deplacement_total = 0;
	unite_jeu->pt_mouvement_unite = 0;
    /*libere_niveau(unite_jeu->niveau_unite);*/
}

void detruire_unite(Unite **unite_jeu)
{
    liberer_unite(*unite_jeu);
    free(*unite_jeu);
    *unite_jeu = NULL;
}

void set_indice_joueur_unite(Unite *unite,const int i)
{
    unite->indice_joueur = i;
}

int get_indice_joueur_unite(const Unite *unite)
{
    return unite->indice_joueur;
}

void set_pt_vie(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_vie = x;
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

void set_pt_attaque(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_attaque = x;
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

int calcul_distance_unite(const int x_depart, const int y_depart, const int x_arrivee, const int y_arrivee)
{
    return ceil(sqrt(pow(x_depart - x_arrivee, 2) + pow(y_depart - y_arrivee, 2)) - 0.1); /*on enleve 0.1 pour etre un peu plus précis: si on se deplace de 7.05 on veut que ce soit 7*/
}

void enlever_pt_mouvement_combat_unite(Unite *une_unite, const int distance)
{
    int temp = get_pt_deplacement(une_unite);
    temp = temp - distance;
    set_pt_deplacement(une_unite, temp);
}

void enlever_pt_action_unite(Unite *une_unite, const int point)
{
	int temp = get_pt_action(une_unite);
    temp = temp - point;
    set_pt_action(une_unite, temp);
}

void reinitialiser_mouvement_combat_unite(Unite *une_unite)
{
	une_unite->pt_deplacement = une_unite->pt_deplacement_total;
}
void reinitialiser_pt_action(Unite *une_unite)
{
	une_unite->pt_action = une_unite->pt_action_total;
}

void sauvegarde_unite(const Unite *une_unite, FILE* f)
{
    fprintf(f, "%d\n", une_unite->indice_joueur);
    fprintf(f, "%d\n", une_unite->x_unite);
    fprintf(f, "%d\n", une_unite->y_unite);
    fprintf(f, "%d\n", une_unite->portee);
    fprintf(f, "%d\n", une_unite->portee_total);
    fprintf(f, "%d\n", une_unite->pt_vie);
    fprintf(f, "%d\n", une_unite->pt_vie_total);
    fprintf(f, "%d\n", une_unite->pt_attaque);
    fprintf(f, "%d\n", une_unite->pt_attaque_total);
    fprintf(f, "%d\n", une_unite->pt_action);
    fprintf(f, "%d\n", une_unite->pt_action_total);
    fprintf(f, "%d\n", une_unite->pt_deplacement);
    fprintf(f, "%d\n", une_unite->pt_deplacement_total);
    fprintf(f, "%d\n", une_unite->pt_mouvement_unite);
    sauvegarde_niveau(&une_unite->niveau_unite, f);
}

Unite* ouverture_unite(FILE *f)
{
    Unite *unite_ouverte = (Unite *)malloc(sizeof(Unite));
    char chaine[50];
    int b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->indice_joueur = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->x_unite = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->y_unite = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->portee = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->portee_total = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->pt_vie = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->pt_vie_total = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->pt_attaque = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->pt_attaque_total = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->pt_action= b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->pt_action_total = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->pt_deplacement = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->pt_deplacement_total = b;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    unite_ouverte->pt_mouvement_unite = b;
    unite_ouverte->niveau_unite = *ouverture_niveau(f);
    return unite_ouverte;
}
/*void test_module_unite()
{
    Unite *guerriers;
    printf("Verif de la création d'une unité\n");
    guerriers = creer_unite();
    if((guerriers->pt_vie == 0) && (guerriers->pt_attaque == 0) && (guerriers->pt_attaque == 0) && (guerriers->pt_deplacement == 0))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}

}
*/
