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
#include "affichage.h"

int main()
{	
	Jeu * jeu;
	Joueur * joueur1;
	Joueur * joueur2;
/*
	Terrain_combat * un_match;*/
	  Flotte *flotte1;
    Unite *unite1;
    Unite *unite2;
    Unite *unite3;

	Flotte *flotte2;
    Unite *unite4;
    Unite *unite5;
    Unite *unite6;
	/*int i;
	char c;
	bool p;*/
	ecran_titre();
	jeu = creer_jeu();
	afficher_info(jeu);
	joueur1=creer_joueur("allie",1,0);
	joueur2=creer_joueur("ennemi",2,0);
	ajouter_joueur(jeu, joueur1);
	ajouter_joueur(jeu, joueur2);
	afficher_info(jeu);
	joueur1=get_ieme_joueur_jeu(jeu,0);
	joueur2=get_ieme_joueur_jeu(jeu,1);
	printf("nb flotte j1 %d ; nb flotte j2 %d \n",get_nb_flotte_joueur(joueur1),get_nb_flotte_joueur(joueur2));

	flotte1 = creer_flotte();
	flotte2 = creer_flotte();
	ajouter_flotte_joueur(joueur1, flotte1);
	ajouter_flotte_joueur(joueur2, flotte2);
	flotte1 = get_ieme_flotte_joueur(joueur1,0);
	flotte2 = get_ieme_flotte_joueur(joueur2,0);
	unite1 = creer_unite(Chasseur);
    unite2 = creer_unite(Chasseur);
    unite3 = creer_unite(Chasseur);

    printf("Verif de la création de flottes\n");
	 printf("flotte1 %d\n",flotte1->indice_joueur);
   printf("flotte2 %d\n",flotte2->indice_joueur);
afficher_flotte(flotte1);
    ajouter_unite_flotte(flotte1, unite1);
	printf("flotte1 unite1 %d\n",get_indice_joueur_unite(get_unite_i_flotte(flotte1,0)));
    ajouter_unite_flotte(flotte1, unite2);
	printf("flotte1 unite2 %d\n",get_indice_joueur_unite(get_unite_i_flotte(flotte1,1)));
    ajouter_unite_flotte(flotte1, unite3);
	afficher_flotte(flotte1);
	
    unite4 = creer_unite(Chasseur);
    unite5 = creer_unite(Destroyer);
    unite6 = creer_unite(Destructeur);
 printf("Verif de la création de flottes\n");
    
afficher_flotte(flotte2);
    ajouter_unite_flotte(flotte2, unite4);
	printf("flotte2 unite1 %d\n",get_indice_joueur_unite(get_unite_i_flotte(flotte2,0)));
    ajouter_unite_flotte(flotte2, unite5);
    printf("flotte2 unite2 %d\n",get_indice_joueur_unite(get_unite_i_flotte(flotte2,0)));
	ajouter_unite_flotte(flotte2, unite6);
	afficher_flotte(flotte2);


	/*i=0;
	
	while(c!='q')
	{	
		printf("tour %d \n", i);
		un_tour_combat(un_match,flotte1);
		un_tour_combat(un_match,flotte2);
		reinitialiser_deplacement_unite_flotte(flotte1);
		reinitialiser_deplacement_unite_flotte(flotte2);printf("\n");
		reinitialiser_pt_action_unite_flotte(flotte1);
		reinitialiser_pt_action_unite_flotte(flotte2);
		afficher_flotte(flotte1);printf("\n");
		afficher_flotte(flotte2);
		printf("continuer?\n");
		do{
		scanf("%c",&c);
		}while((c!='q') &&(c!='o'));
		printf("ok!\n");
	}*/
	
	//lancer_combat_ecran(jeu,flotte1,flotte2);
	//detruire_jeu(&jeu);
	return 0;

}
