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
#include "batiment.h"
#include "constante.h"
#include "affichage.h"

int main(int argc, char *argv[])
{
    /*ecran_titre();*/
    Flotte *flotte;
    Unite *unite1;
    Unite *unite2;

	Flotte *flotte2;
    Unite *unite3;
    Unite *unite4;

	Flotte *flotte3;
	Unite *unite5;
	Unite *unite6;

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
	Joueur *joueur2;
	Jeu *jeu;
    Sauvegarde *une_sauvegarde;
    int x = 0;
	int y = 0;

    char nom_joueur[]="Pierre";
	char nom_joueur2[]="Boulet";
	char nom_terre[]="terre";
	char nom_jupiter[]="jupiter";
	char nom_venus[]="venus";

	un_terrain_espace = creer_terrain_espace(20, 15);
    modification_terrain_espace(un_terrain_espace, 'E');

    ajouter_planete_terrain_espace(un_terrain_espace, 2, 1, nom_terre);
    ajouter_planete_terrain_espace(un_terrain_espace, 4, 3, nom_jupiter);
	ajouter_planete_terrain_espace(un_terrain_espace, 0, 3, nom_venus);
    affiche_terrain_espace(un_terrain_espace);

    terre = get_planete_terrain_espace(un_terrain_espace, 2, 1);
    jupiter = get_planete_terrain_espace(un_terrain_espace, 4, 3);

	joueur = creer_joueur(nom_joueur);
	joueur2 = creer_joueur(nom_joueur2);
	jeu = creer_jeu();
    set_couleur(joueur2, 1);
	ajouter_joueur(jeu, joueur);
	ajouter_joueur(jeu, joueur2);

    flotte = creer_flotte();
    unite1 = creer_unite(1, 1, 1, 1, 1, 10);
    unite2 = creer_unite(2, 2, 2, 2, 2, 10);

	flotte2 = creer_flotte();
    unite3 = creer_unite(3, 3, 3, 3, 3, 10);
    unite4 = creer_unite(4, 4, 4, 4, 4, 10);

	flotte3 = creer_flotte();
	unite5 = creer_unite(5, 5, 5, 5, 5, 10);
	unite6 = creer_unite(6, 6, 6, 6, 6, 10);

	ajouter_planete_joueur(&jeu->tab_joueur[0], terre);
	afficher_planete(jeu->tab_joueur[0].tab_planete[0]);

	ajouter_planete_joueur(&jeu->tab_joueur[1], jupiter);
	afficher_planete(jeu->tab_joueur[1].tab_planete[0]);

    modification_production_planete(jeu->tab_joueur[0].tab_planete[0], 100, 50, 10, 100);
	modification_production_planete(jeu->tab_joueur[1].tab_planete[0], 200, 50, 75, 0);

    ajouter_unite_flotte(flotte, unite1);
    ajouter_unite_flotte(flotte, unite2);

	ajouter_unite_flotte(flotte2, unite3);
    ajouter_unite_flotte(flotte2, unite4);

	ajouter_unite_flotte(flotte3, unite5);
	ajouter_unite_flotte(flotte3, unite6);
/*
    ajouter_flotte_joueur(&jeu->tab_joueur[0], flotte);
	ajouter_flotte_joueur(&jeu->tab_joueur[0], flotte2);

    printf("Affiche flotte 1\n");
    afficher_flotte(&jeu->tab_joueur[0].tab_flotte[0]);
    printf("Affiche flotte 2\n");
    afficher_flotte(&jeu->tab_joueur[0].tab_flotte[1]);

    ajouter_flotte(get_case_terrain_espace(un_terrain_espace, 2, 3), &jeu->tab_joueur[0].tab_flotte[0]);
	ajouter_flotte(get_case_terrain_espace(un_terrain_espace, 5, 5), &jeu->tab_joueur[0].tab_flotte[1]);
*/
	ajouter_flotte_jeu(jeu, un_terrain_espace, flotte, 0, 2, 3);
	ajouter_flotte_jeu(jeu, un_terrain_espace, flotte2, 0, 5, 5);
	ajouter_flotte_jeu(jeu, un_terrain_espace, flotte3, 1, 0, 4);
    creer_fichier_sauvegarde("essai", un_terrain_espace, jeu);
    detruire_terrain_espace(&un_terrain_espace);
    detruire_jeu(&jeu);
    une_sauvegarde = selection_ouverture("essai");
    jeu = une_sauvegarde->jeu;
    un_terrain_espace = une_sauvegarde->terrain_espace;
	affichage_ecran(jeu, un_terrain_espace);

	while(1)
    {
		a = jeu->joueur_en_cours;
        printf("tapez planete, move, flotte, suivant, ressource ou exit\n");
        scanf("%s", menu);
        if(strcmp(menu, exit) == 0)
        {
            detruire_terrain_espace(&un_terrain_espace);
            detruire_jeu(&jeu);
            return 0;
        }
        if(strcmp(menu, move) == 0)
        {
			printf("Coordonnées où bouger la flotte:\n");
			scanf("%d", &x);
			scanf("%d", &y);
			if(deplacement_flotte(&jeu->tab_joueur[a], un_terrain_espace, &(jeu->tab_joueur[a].tab_flotte[0]), x, y) == false)
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
			afficher_flotte(&(jeu->tab_joueur[a].tab_flotte[1]));
        }
		if(strcmp(menu, ressource) == 0)
        {
            afficher_ressource_joueur(jeu);
        }
		if(strcmp(menu, passer_tour) == 0)
        {
			joueur_suivant(jeu, un_terrain_espace);
			affichage_ecran(jeu, un_terrain_espace);
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
    }
	detruire_terrain_espace(&un_terrain_espace);
	detruire_jeu(&jeu);

	return EXIT_SUCCESS;
}




