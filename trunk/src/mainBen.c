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
    Terrain_espace *terrain_ouvert;
    un_terrain_espace = creer_terrain_espace(10,10);
    modification_terrain_espace(un_terrain_espace, 'E');
    affiche_terrain_espace(un_terrain_espace);
    terrain_ouvert = selection_ouverture("test", 0);
    affiche_terrain_espace(terrain_ouvert);
	return 0;
}
