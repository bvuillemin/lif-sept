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
    Terrain_espace *un_terrain_espace;
    Sauvegarde *une_sauvegarde;
    Flotte *une_flotte;
    Planete *une_planete;
    int a, b;
    detruire_sauvegarde("test");
    un_terrain_espace = creer_terrain_espace(10,10);
    modification_terrain_espace(un_terrain_espace, 'E');
    une_flotte = creer_flotte();
    set_taille_maximum_flotte(une_flotte, 5);
    set_taille_flotte(une_flotte, 4);
    affiche_terrain_espace(un_terrain_espace);
    une_planete = creer_planete("Terre");
    set_planete_colonisee(une_planete, 1);
    set_metal(une_planete, 35);
    set_population(une_planete, 56578);
    set_position_planete(une_planete, 3, 5);
    set_taille_planete(une_planete, 3);
    set_taille_utilisee(une_planete, 5);
    afficher_planete(une_planete);
    sauvegarde_terrain(un_terrain_espace, "test");
    sauvegarde_flotte(une_flotte, "test");
    sauvegarde_planete(une_planete, "test");
    une_sauvegarde = selection_ouverture("test", 0);
    affiche_terrain_espace(une_sauvegarde->terrain_espace);
    a = get_taille_espace_x(une_sauvegarde->terrain_espace);
    b = get_taille_espace_x(une_sauvegarde->terrain_espace);
    printf("%d, %d \n", a, b);
    afficher_flotte(&une_sauvegarde->tab_flotte[0]);
    printf("%d \n", une_sauvegarde->nb_flotte);
    afficher_planete(&une_sauvegarde->tab_planete[0]);
    printf("%d \n", une_sauvegarde->nb_planete);
	return 0;
}