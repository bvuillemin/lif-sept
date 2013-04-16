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
	Terrain_espace *un_terrain_espace;
/*
	Planete *terre;
	Planete *jupiter;*/
	char nom_terre[]="terre";
	char nom_jupiter[]="jupiter";

	un_terrain_espace = creer_terrain_espace(12, 12);
	modification_terrain_espace(un_terrain_espace, 'E');

	ajouter_planete_terrain_espace(un_terrain_espace, 2, 1, nom_terre);
	ajouter_planete_terrain_espace(un_terrain_espace, 8, 8, nom_jupiter);
	
	affichage_ecran(un_terrain_espace);
	return EXIT_SUCCESS;
}
  



