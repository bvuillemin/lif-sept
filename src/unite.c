#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "unite.h"

void initialise_unite(Unite *unite_jeu,int x_unite,int y_unite,int pt_vie, int pt_attaque, int pt_action, int pt_deplacement,int pt_mouvement)
{
    unite_jeu->pt_vie=pt_vie;
    unite_jeu->pt_attaque=pt_attaque;
    unite_jeu->pt_action=pt_action;
    unite_jeu->pt_deplacement=pt_deplacement;
    unite_jeu->pt_mouvement_unite=pt_mouvement;
	unite_jeu->x_unite=x_unite;
	unite_jeu->y_unite=y_unite;
    /*initialise_niveau(unite_jeu->niveau_unite, 0, 0);*/
}

Unite *creer_unite(int x_unite,int y_unite,int pt_vie, int pt_attaque, int pt_action, int pt_deplacement,int pt_mouvement)
{
    Unite *nouvelle_unite = (Unite *)malloc(sizeof(Unite));
    initialise_unite(nouvelle_unite,x_unite,y_unite,pt_vie, pt_attaque, pt_action, pt_deplacement, pt_mouvement);
    return nouvelle_unite;
}

void libere_unite(Unite *unite_jeu)
{
    unite_jeu->pt_vie=0;
    unite_jeu->pt_attaque=0;
    unite_jeu->pt_action=0;
    unite_jeu->pt_deplacement=0;
    unite_jeu->pt_mouvement_unite=0;
    /*libere_niveau(unite_jeu->niveau_unite);*/
}

void detruit(Unite **unite_jeu)
{
    libere_unite(*unite_jeu);
    free(*unite_jeu);
    *unite_jeu = NULL;
}

void set_pt_vie(Unite *unite_jeu, const int x)
{
    unite_jeu->pt_vie = x;
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

void enlever_pt_mouvement_combat_unite(Unite *une_unite, int distance)
{
    int temp = get_pt_mouvement_unite(une_unite);
    temp = temp - distance;
    set_pt_mouvement_unite(une_unite, temp);
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
