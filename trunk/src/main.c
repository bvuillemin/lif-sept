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
	test_module_terrain();

    Flotte *flotte;
    Unite *unite1;
    Unite *unite2;

	Flotte *flotte2;
    Unite *unite3;
    Unite *unite4;*/

	Terrain_espace *un_terrain_espace;
	/*Terrain_combat * un_terrain_combat;*/

    int a = 1;
	char menu[50];
	char exit[] = "exit";
	char move[] = "move";
	char info_planete[] = "planete";
	char info_flotte[] = "flotte";
	char passer_tour[] = "suivant";
	char ressource[] = "ressource";
	char info[] = "info";
	char coloniser[] = "coloniser";

	Planete *terre;
	Planete *jupiter;
	Joueur *joueur;
	/*Joueur *joueur2;*/
	Jeu *jeu;

    int x = 0;
	int y = 0;

    char nom_joueur[]="Pierre";
	/*char nom_joueur2[]="Boulet";*/
	char nom_terre[]="terre";
	char nom_jupiter[]="jupiter";

	un_terrain_espace = creer_terrain_espace(15, 10);
    modification_terrain_espace(un_terrain_espace, 'E');

    ajouter_planete_terrain_espace(un_terrain_espace, 2, 1, nom_terre);
    ajouter_planete_terrain_espace(un_terrain_espace, 8, 9, nom_jupiter);
    affiche_terrain_espace(un_terrain_espace);

    terre = get_planete_terrain_espace(un_terrain_espace, 2, 1);
    jupiter = get_planete_terrain_espace(un_terrain_espace, 8, 9);

	joueur = creer_joueur(1, nom_joueur);
	/*joueur2 = creer_joueur(2, nom_joueur2);*/
	jeu = creer_jeu();

    /*flotte = creer_flotte();
    unite1 = creer_unite(1, 1, 1, 1, 10);
    unite2 = creer_unite(1, 1, 1, 1, 10);

	flotte2 = creer_flotte();
    unite3 = creer_unite(1, 1, 1, 1, 10);
    unite4 = creer_unite(1, 1, 1, 1, 10);*/

	ajouter_planete_joueur(joueur, terre);
	afficher_planete(joueur->tab_planete[0]);

	/*ajouter_planete_joueur(joueur2, jupiter);
	afficher_planete(joueur2->tab_planete[0]);*/

    modification_production_planete(joueur->tab_planete[0], 100, 50, 10, 100);
	/*modification_production_planete(joueur2->tab_planete[0], 200, 50, 75, 0);

    ajouter_unite_flotte(flotte, unite1);
    ajouter_unite_flotte(flotte, unite2);

	ajouter_unite_flotte(flotte2, unite3);
    ajouter_unite_flotte(flotte2, unite4);

    ajouter_flotte_joueur(joueur, *flotte);
	ajouter_flotte_joueur(joueur2, *flotte2);

    printf("Affiche flotte 1\n");
    afficher_flotte(&joueur->tab_flotte[0]);
    printf("Affiche flotte 2\n");
    afficher_flotte(&joueur2->tab_flotte[0]);

    ajouter_flotte(get_case_terrain_espace(un_terrain_espace, 2, 3), &joueur->tab_flotte[0]);
	ajouter_flotte(get_case_terrain_espace(un_terrain_espace, 9, 9), &joueur2->tab_flotte[0]);*/

	ajouter_joueur(jeu, joueur);
	/*ajouter_joueur(jeu, joueur2);*/


	affiche_terrain_espace(un_terrain_espace);


   /* while(1)
    {
		a = jeu->joueur_en_cours;

        printf("tapez planete, move, flotte, suivant, ressource ou exit\n");
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
			//system("clear");
			if(deplacement_flotte(un_terrain_espace, &(jeu->tab_joueur[a].tab_flotte[0]), x, y) == false)
			{
				printf("Déplacement impossible\n");
			}
			affiche_terrain_espace(un_terrain_espace);
        }
        if(strcmp(menu, info_planete) == 0)
        {
            afficher_planete(terre);
            afficher_planete(jupiter);
        }
		if(strcmp(menu, info_flotte) == 0)
        {
			printf("Affiche flotte du joueur %d\n", a);
			afficher_flotte(&(jeu->tab_joueur[a].tab_flotte[0]));
        }
		if(strcmp(menu, ressource) == 0)
        {
            afficher_ressource_joueur(jeu);
        }
		if(strcmp(menu, passer_tour) == 0)
        {
			joueur_suivant(jeu);
        }
		if(strcmp(menu, info) == 0)
        {
			afficher_info(jeu);
        }
        if(strcmp(menu, coloniser) == 0)
        {
			colonisation_planete(&(jeu->tab_joueur[a]), terre);
			colonisation_planete(&(jeu->tab_joueur[a]), jupiter);
        }
    }*/
    afficher_planete(terre);
    afficher_batiment(terre);
    creation_batiment(terre, 0);
    joueur_suivant(jeu);
    validation_batiment(terre);
    afficher_batiment(terre);
    creation_batiment(terre, 1);
    joueur_suivant(jeu);
    validation_batiment(terre);
    afficher_batiment(terre);
    joueur_suivant(jeu);
    joueur_suivant(jeu);




    //detruit_terrain_espace(&un_terrain_espace);
/*	un_terrain_combat = creer_terrain_combat(7,7);
	modification_terrain_combat(un_terrain_combat, 'E');
	affiche_terrain_combat(un_terrain_combat);
*/
	return 0;

}


