#include <stdlib.h>
#include <stdio.h>

#include "planete.h"
#include "case_terrain_espace.h"
#include "niveau.h"
#include "unite.h"
#include "terrain_espace.h"
#include "flotte.h"

int main()
{
    /*test_module_planete();
    test_module_flotte();
	test_module_unite();
	test_module_case_terrain();
	test_module_terrain();*/


    Flotte *flotte;
    Unite *unite1;
    Unite *unite2;

	char tab[30];
	scanf("%29s", tab);

	char tab2[30];
	scanf("%29s", tab2);

	Terrain_espace *un_terrain_espace;
    un_terrain_espace = creer_terrain_espace(5, 5);
    modification_terrain_espace(un_terrain_espace, 'E');

    ajouter_planete_terrain_espace(un_terrain_espace, 2, 1);
    ajouter_planete_terrain_espace(un_terrain_espace, 4, 4);

    set_nom_planete(un_terrain_espace->tab_terrain_espace[2*(un_terrain_espace->taille_espace_x)+1].planete, tab);
    set_nom_planete(un_terrain_espace->tab_terrain_espace[4*(un_terrain_espace->taille_espace_x)+4].planete, tab2);
    affiche_terrain_espace(un_terrain_espace);

    affiche_planete(un_terrain_espace->tab_terrain_espace[2*(un_terrain_espace->taille_espace_x)+1].planete);
    affiche_planete(un_terrain_espace->tab_terrain_espace[4*(un_terrain_espace->taille_espace_x)+4].planete);

    unite1 = creer_unite();
    unite2 = creer_unite();
    flotte = creer_flotte();

    ajouter_unite_flotte(flotte, unite1);
    ajouter_unite_flotte(flotte, unite2);

    set_pt_vie(&(flotte->tab_unite[0]), 10);
    set_pt_vie(&(flotte->tab_unite[1]), 15);

    ajouter_flotte(&(un_terrain_espace->tab_terrain_espace[3*(un_terrain_espace->taille_espace_x)+2]), flotte);
    affiche_terrain_espace(un_terrain_espace);

    sauvegarde_terrain(un_terrain_espace, "test");

    detruit_terrain_espace(&un_terrain_espace);

    return 0;
}

