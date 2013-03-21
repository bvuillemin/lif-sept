#include <stdlib.h>
#include <stdio.h>

#include "planete.h"
#include "case.h"
#include "niveau.h"
#include "unite.h"
#include "terrain.h"
#include "flotte.h"

int main()
{
    /*test_module_planete();
    test_module_flotte();
	test_module_unite();
	test_module_case_terrain();
	test_module_terrain();*/

	Terrain *un_terrain;
    un_terrain = creer_terrain(20, 20);
    modification_terrain(un_terrain, 'E');
    affiche_terrain(un_terrain);

    ajouter_planete_terrain(un_terrain, 2, 1);
    affiche_terrain(un_terrain);

    affiche_planete(un_terrain->tab_terrain[2*(un_terrain->taille_x)+1].planete);

    detruit_terrain(&un_terrain);

    return 0;
}
