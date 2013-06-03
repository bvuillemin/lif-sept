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
    testRegression_sauvegarde();
    testRegression_Terrain_espace();
    testRegression_terrain_combat();
    testRegression_Unite();
    testRegression_Vision_terrain();
    testRegression_Vision_case();
    testRegression_Planete();
    testRegression_Joueur();
    testRegression_Jeu();
    testRegression_flotte();
    testRegression_case_terrain_combat();
    testRegression_case_terrain_espace();
    testRegression_Animation();
    printf("Tests réussis");
	return EXIT_SUCCESS;
}
