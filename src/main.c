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
#include "joueur.h"
#include "jeu.h"

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

	Terrain_espace *un_terrain_espace;
	/*Terrain_combat * un_terrain_combat;*/

	char menu[50];
	char exit[] = "exit";
	char move[] = "move";
	char info[] = "info";

	Planete *terre;
	Planete *jupiter;
	Joueur *joueur;
	Jeu *jeu;

    int x = 1;
	int y = 1;

    char nom_joueur[]="Pierre";
	char nom_terre[]="terre";
	char nom_jupiter[]="jupiter";


	un_terrain_espace = creer_terrain_espace(10, 10);
    modification_terrain_espace(un_terrain_espace, 'E');

    ajouter_planete_terrain_espace(un_terrain_espace, 2, 1, nom_terre);
    ajouter_planete_terrain_espace(un_terrain_espace, 8, 9, nom_jupiter);
    affiche_terrain_espace(un_terrain_espace);

    /*affiche_planete(un_terrain_espace->tab_terrain_espace[1*(un_terrain_espace->taille_espace_x)+2].planete);*/

    terre = get_planete_terrain_espace(un_terrain_espace, 2, 1);
    jupiter = get_planete_terrain_espace(un_terrain_espace, 8, 9);

	joueur = creer_joueur(1, nom_joueur);
	jeu = creer_jeu();

	ajouter_planete_joueur(joueur, terre);
	afficher_planete(joueur->tab_planete[0]);

	ajouter_planete_joueur(joueur, jupiter);
	afficher_planete(joueur->tab_planete[1]);

    modification_production_planete(joueur->tab_planete[0], 100, 100, 100, 100);
	modification_production_planete(joueur->tab_planete[1], 200, 50, 75, 0);

	ajouter_joueur(jeu, joueur);
	tour_suivant(jeu);
	tour_suivant(jeu);

    unite1 = creer_unite(1, 1, 1, 1, 1, 1, 10);
    unite2 = creer_unite(1, 1, 1, 1, 1, 1, 10);
    flotte = creer_flotte();

    ajouter_unite_flotte(flotte, unite1);
    ajouter_unite_flotte(flotte, unite2);

    ajouter_flotte_joueur(joueur, *flotte);

    printf("Affiche flotte 1\n");
    afficher_flotte(&joueur->tab_flotte[0]);
    printf("Affiche flotte 2\n");
    afficher_flotte(flotte);



   /* ajouter_flotte(&(un_terrain_espace->tab_terrain_espace[2*(un_terrain_espace->taille_espace_x)+3]), flotte);
    affiche_terrain_espace(un_terrain_espace);

    set_pt_mouvement_espace_flotte(flotte, 10);
    detruire_sauvegarde("test");
    sauvegarde_terrain(un_terrain_espace, "test");
    sauvegarde_planete(un_terrain_espace->tab_terrain_espace[1*(un_terrain_espace->taille_espace_x)+2].planete, "test");
    sauvegarde_flotte(flotte, "test");
    sauvegarde_unite(unite1, "test");
    sauvegarde_unite(unite2, "test");
    ouverture_terrain("test");
    system("clear");*/


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
            afficher_planete(terre);
            afficher_planete(jupiter);
        }

    }

    printf("\n \n");
/*	un_terrain_combat = creer_terrain_combat(7,7);
	modification_terrain_combat(un_terrain_combat, 'E');
	affiche_terrain_combat(un_terrain_combat);
*/

	system("pause");
	return 0;

}


