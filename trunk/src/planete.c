#include <stdlib.h>
#include <stdio.h>

#include "planete.h"




void initialise_planete(Planete *planete, int id)
{
    planete->id_planete = id;
    planete->nom_planete = (char*)malloc(sizeof(char) * 30);
    planete->planete_colonise = 0;
    planete->planete_principale = 0;
    planete->taille_planete = 0; /* a modifier*/
    planete->taille_utilisee = 0;
}

Planete *creer_planete(int id)
{
    Planete *planete=(Planete *)malloc(sizeof(Planete));
    initialise_planete(planete, id);
    return planete;
}


void set_nom_planete(Planete *planete, char nom[30])
{
    int i;
    for(i=0;i<30;i++)
    {
        planete->nom_planete[i]=nom[i];
    }
}

void test_module_planete()
{
    Planete *terre;
    printf("Verif de la création de planètes\n");
    terre = creer_planete(1);
    if((terre->id_planete == 1) && (terre->taille_planete == 0))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}

}
