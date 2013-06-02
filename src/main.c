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

	Terrain_espace *un_terrain_espace;

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

	/*Liste des planètes*/
	Planete* Terre;
	Planete* Caprica;

	Joueur *joueur;
	Joueur *joueur2;
	Jeu *jeu;
    Sauvegarde *une_sauvegarde;
    int x = 0;
	int y = 0;
	int i;

    char nom_joueur[]="Joueur 1";
	char nom_joueur2[]="Joueur 2";

	srand(time(NULL));
	un_terrain_espace = creer_terrain_espace(20, 15);
    modification_terrain_espace(un_terrain_espace, 'E');

    ajouter_planete_terrain_espace(un_terrain_espace, 1, 1, "Terre", 300, 300, 300, 300);
    ajouter_planete_terrain_espace(un_terrain_espace, 4, 4, "Jupiter", 50, 25, 300, 25);
	ajouter_planete_terrain_espace(un_terrain_espace, 0, 4, "Mars", 150, 100, 20, 150);
	ajouter_planete_terrain_espace(un_terrain_espace, 0, 6, "Venus", 200, 200, 10, 50);
	ajouter_planete_terrain_espace(un_terrain_espace, 1, 8, "Saturne", 20, 30, 200, 50);

	ajouter_planete_terrain_espace(un_terrain_espace, 10, 7, "Kobol", 200, 300, 150, 50);

	ajouter_planete_terrain_espace(un_terrain_espace, 18, 13, "Caprica", 300, 300, 300, 300);
	ajouter_planete_terrain_espace(un_terrain_espace, 15, 14, "Gemenon", 50, 25, 300, 25);
	ajouter_planete_terrain_espace(un_terrain_espace, 19, 9, "Picon", 150, 100, 20, 150);
	ajouter_planete_terrain_espace(un_terrain_espace, 14, 11, "Sagitarron", 200, 200, 10, 50);
	ajouter_planete_terrain_espace(un_terrain_espace, 10, 13, "Tauron", 20, 30, 200, 50);

    affiche_terrain_espace(un_terrain_espace);

    Terre = get_planete_terrain_espace(un_terrain_espace, 1, 1);
    Caprica = get_planete_terrain_espace(un_terrain_espace, 18, 13);

	joueur = creer_joueur(nom_joueur, 0, false);
	joueur2 = creer_joueur(nom_joueur2, 1, false);
	jeu = creer_jeu();
    ajouter_joueur(jeu, joueur);
	ajouter_joueur(jeu, joueur2);

    flotte = creer_flotte();
    unite1 = creer_unite(Chasseur);
    unite2 = creer_unite(Destroyer);

	flotte2 = creer_flotte();
	unite3 = creer_unite(Chasseur);
	unite4 = creer_unite(Destroyer);

	ajouter_planete_joueur(get_ieme_joueur_jeu(jeu, 0), Terre);

	ajouter_planete_joueur(get_ieme_joueur_jeu(jeu, 1), Caprica);

    ajouter_unite_flotte(flotte, unite1);
    ajouter_unite_flotte(flotte, unite2);

	ajouter_unite_flotte(flotte2, unite3);
    ajouter_unite_flotte(flotte2, unite4);
	
	ajouter_flotte_jeu(jeu, un_terrain_espace, flotte, 0, 2, 2);
	ajouter_flotte_jeu(jeu, un_terrain_espace, flotte2, 1, 5, 5);

	creer_vision_jeu(jeu, un_terrain_espace);
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
            afficher_planete(Terre);
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
			colonisation_planete(&(jeu->tab_joueur[a]), Terre);
			colonisation_planete(&(jeu->tab_joueur[a]), Caprica);
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




