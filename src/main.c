#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "planete.h"
#include "case_terrain_espace.h"
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
//    ecran_titre();
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
	char afficher_carte[] = "carte";
	char creer[] = "creer";

	Planete *terre;
	Planete *jupiter;
	Joueur *joueur;
	Joueur *joueur2;
	Jeu *jeu;
    Sauvegarde *une_sauvegarde;
    int x = 0;
	int y = 0;
	int i;

    char nom_joueur[]="Pierre";
	char nom_joueur2[]="Boulet";
	char nom_terre[]="terre";
	char nom_jupiter[]="jupiter";
	char nom_venus[]="venus";

	srand(time(NULL));
	un_terrain_espace = creer_terrain_espace(20, 15);
    modification_terrain_espace(un_terrain_espace, 'E');

    ajouter_planete_terrain_espace(un_terrain_espace, 2, 1, nom_terre);
    ajouter_planete_terrain_espace(un_terrain_espace, 4, 3, nom_jupiter);
	ajouter_planete_terrain_espace(un_terrain_espace, 0, 3, nom_venus);
    affiche_terrain_espace(un_terrain_espace);

    terre = get_planete_terrain_espace(un_terrain_espace, 2, 1);
    jupiter = get_planete_terrain_espace(un_terrain_espace, 4, 3);

	joueur = creer_joueur(nom_joueur, 0, false);
	joueur2 = creer_joueur(nom_joueur2, 1, true);
	jeu = creer_jeu();
    ajouter_joueur(jeu, joueur);
	ajouter_joueur(jeu, joueur2);

    flotte = creer_flotte();
    unite1 = creer_unite(Chasseur);
    unite2 = creer_unite(Destroyer);

	flotte2 = creer_flotte();
    unite3 = creer_unite(Destructeur);
    unite4 = creer_unite(Chasseur);


	flotte3 = creer_flotte();
	unite5 = creer_unite(Chasseur);
	unite6 = creer_unite(Destructeur);

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

	ajouter_flotte_jeu(jeu, un_terrain_espace, flotte, 0, 2, 2);
	ajouter_flotte_jeu(jeu, un_terrain_espace, flotte2, 0, 5, 5);
	ajouter_flotte_jeu(jeu, un_terrain_espace, flotte3, 1, 0, 4);

	creer_vision_jeu(jeu, un_terrain_espace);
	//creer_vision_joueur(jeu, un_terrain_espace, 0);
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
			if(deplacement_flotte(&jeu->tab_joueur[a], un_terrain_espace, get_ieme_flotte_joueur(&jeu->tab_joueur[a], 0), x, y) == false)
			{
				printf("Déplacement impossible\n");
			}
			affiche_terrain_espace(un_terrain_espace);
        }
        if(strcmp(menu, info_planete) == 0)
        {
            afficher_planete(terre);
            /*afficher_planete(jupiter);*/
        }
		if(strcmp(menu, info_flotte) == 0)
        {
			printf("Affiche flotte du joueur %d\n", a);
			afficher_flotte(get_ieme_flotte_joueur(&jeu->tab_joueur[a], 0));
			afficher_flotte(get_ieme_flotte_joueur(&jeu->tab_joueur[a], 1));
        }
		if(strcmp(menu, ressource) == 0)
        {
            afficher_ressource_joueur(jeu);
        }
		if(strcmp(menu, passer_tour) == 0)
        {
			for(i=0;i<1;i++)
			{
				joueur_suivant(jeu, un_terrain_espace);
			}
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
		if(strcmp(menu, afficher_carte) == 0)
		{
			affiche_terrain_espace(un_terrain_espace);
			affichage_vision_jeu(jeu, un_terrain_espace);
		}
		if(strcmp(menu, creer) == 0)
		{
			if(condition_creation_unite(get_joueur_en_cours(jeu), (jeu->tab_joueur[a]).tab_planete[0], i + 1))
			{
				creation_unite_planete(&jeu->tab_joueur[a], (jeu->tab_joueur[a]).tab_planete[0], 1);
				printf("Création\n");
			}
			else
			{
				printf("Pas de création\n");
			}
		}
    }
	detruire_terrain_espace(&un_terrain_espace);
	detruire_jeu(&jeu);

	return EXIT_SUCCESS;
}




