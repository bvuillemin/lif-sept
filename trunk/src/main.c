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

	char tab[30];
	scanf("%29s", tab);

	char tab2[30];
	scanf("%29s", tab2);

	Terrain_espace *un_terrain_espace;
    un_terrain_espace = creer_terrain_espace(20, 20);
    modification_terrain_espace(un_terrain_espace, 'E');
    affiche_terrain_espace(un_terrain_espace);

    ajouter_planete_terrain_espace(un_terrain_espace, 2, 1);
    ajouter_planete_terrain_espace(un_terrain_espace, 18, 15);

    set_nom_planete(un_terrain_espace->tab_terrain_espace[2*(un_terrain_espace->taille_espace_x)+1].planete, tab);
    set_nom_planete(un_terrain_espace->tab_terrain_espace[18*(un_terrain_espace->taille_espace_x)+15].planete, tab2);
    affiche_terrain_espace(un_terrain_espace);

    affiche_planete(un_terrain_espace->tab_terrain_espace[2*(un_terrain_espace->taille_espace_x)+1].planete);
    affiche_planete(un_terrain_espace->tab_terrain_espace[18*(un_terrain_espace->taille_espace_x)+15].planete);

    sauvegarde_terrain(un_terrain_espace, "test");

    detruit_terrain_espace(&un_terrain_espace);

    return 0;
}

