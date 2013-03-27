#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "planete.h"
#include "case_terrain_espace.h"
#include "niveau.h"
#include "unite.h"
#include "terrain_espace.h"
#include "flotte.h"
#include "sauvegarde.h"
#include "terrain_combat.h"
#include "case_terrain_combat.h"

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

	char menu[50];
	char exit[] = "exit";
	char move[] = "move";
	char info[] = "info";
	char nomterre[] = "terre";

	Planete *terre;

	int x = 1;
	int y = 1;

	Terrain_espace *un_terrain_espace;
/*	Terrain_combat * un_terrain_combat;*/

	un_terrain_espace = creer_terrain_espace(10, 10);
    modification_terrain_espace(un_terrain_espace, 'E');

    ajouter_planete_terrain_espace(un_terrain_espace, 2, 1);
    affiche_terrain_espace(un_terrain_espace);

    set_nom_planete(un_terrain_espace->tab_terrain_espace[1*(un_terrain_espace->taille_espace_x)+2].planete, nomterre);
    affiche_terrain_espace(un_terrain_espace);

    affiche_planete(un_terrain_espace->tab_terrain_espace[1*(un_terrain_espace->taille_espace_x)+2].planete);

    terre = get_planete_terrain_espace(un_terrain_espace, 2, 1);
    affiche_planete(terre);

    unite1 = creer_unite();
    unite2 = creer_unite();
    flotte = creer_flotte();

    ajouter_unite_flotte(flotte, unite1);
    ajouter_unite_flotte(flotte, unite2);

    set_pt_vie(&(flotte->tab_unite[0]), 10);
    set_pt_vie(&(flotte->tab_unite[1]), 15);

    ajouter_flotte(&(un_terrain_espace->tab_terrain_espace[2*(un_terrain_espace->taille_espace_x)+3]), flotte);
    affiche_terrain_espace(un_terrain_espace);

    set_pt_mouvement_espace_flotte(flotte, 10);

    system("clear");

    while(1)
    {
        printf("tapez info, move ou exit\n");
        scanf("%s", menu);
        if(strcmp(menu, exit) == 0)
        {
            return 0;
        }
        if(strcmp(menu, move) == 0)
        {
            printf("Coordonnées où bouger la flotte:\n");
            scanf("%d", &x);
            scanf("%d", &y);
            system("clear");
            if(deplacement_flotte(un_terrain_espace, flotte, x, y) == false)
            {
                printf("Déplacement impossible\n");
            }
            affiche_terrain_espace(un_terrain_espace);
        }
        if(strcmp(menu, info) == 0)
        {
            affiche_planete(terre);
        }

    }

    /*sauvegarde_terrain(un_terrain_espace, "test");

	printf("\n \n");
	un_terrain_combat = creer_terrain_combat(7,7);
	modification_terrain_combat(un_terrain_combat, 'E');
	affiche_terrain_combat(un_terrain_combat);
	*/

    detruit_terrain_espace(&un_terrain_espace);

}


