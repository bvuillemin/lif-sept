/**
 * \file      constante.h
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les constantes du jeu
 * \details   Cette classe définit les constantes du jeu, comme la résolution d'écran, les caractéristiques des unités...
 */

#ifndef _CONSTANTE_H_
#define _CONSTANTE_H_

/*CrÈation des unitÈs*/
#define PT_VIE_UNITE_1 30
#define PT_ATTAQUE_UNITE_1 10
#define PT_ACTION_UNITE_1 10
#define PT_DEPLACEMENT_UNITE_1 10
#define PT_MOUVEMENT_UNITE_1 10
#define PT_PORTEE_UNITE_1 1
#define NB_TOUR_UNITE_1 1
#define NB_METAL_UNITE_1 20
#define NB_ARGENT_UNITE_1 20
#define NB_CARBURANT_UNITE_1 20
#define NB_POPULATION_UNITE_1 20

#define PT_VIE_UNITE_2 200
#define PT_ATTAQUE_UNITE_2 50
#define PT_ACTION_UNITE_2 10
#define PT_DEPLACEMENT_UNITE_2 10
#define PT_MOUVEMENT_UNITE_2 10
#define PT_PORTEE_UNITE_2 2
#define NB_TOUR_UNITE_2 3
#define NB_METAL_UNITE_2 1000
#define NB_ARGENT_UNITE_2 1000
#define NB_CARBURANT_UNITE_2 1000
#define NB_POPULATION_UNITE_2 1000

#define PT_VIE_UNITE_3 500
#define PT_ATTAQUE_UNITE_3 200
#define PT_ACTION_UNITE_3 10
#define PT_DEPLACEMENT_UNITE_3 10
#define PT_MOUVEMENT_UNITE_3 10
#define PT_PORTEE_UNITE_3 2
#define NB_TOUR_UNITE_3 10
#define NB_METAL_UNITE_3 5000
#define NB_ARGENT_UNITE_3 5000
#define NB_CARBURANT_UNITE_3 5000
#define NB_POPULATION_UNITE_3 5000

/*Constantes pour l'Ècran*/
#define TAILLE_FENETRE_X 1280
#define TAILLE_FENETRE_Y 768
#define NOMBRE_BITS_COULEUR 32
#define TAILLE_TERRAIN_ESPACE_X 1280
#define TAILLE_TERRAIN_ESPACE_Y 600

#define TAILLE_MINIMAP_X 200
#define TAILLE_MINIMAP_Y 140

#define TAILLE_BARRE_RESSOURCE 30

#define TEMPS_INFOBULLE 1000
#define DEPLACEMENT_AFFICHAGE 5

/*l'ecran du combat (ou/et du l'espace)*/
#define X_CASE_COMBAT 13
#define Y_CASE_COMBAT 6
#define TAILLE_ECRAN_COMBAT_X 1280
#define TAILLE_ECRAN_COMBAT_Y 768
#define X_CARTE 0
#define Y_CARTE 0
#define X_INTERFACE 0
#define Y_INTERFACE (TAILLE_ECRAN_COMBAT_Y -158 +30)
#define X_BOUTON_PASSER (TAILLE_ECRAN_COMBAT_X -300)
#define Y_BOUTON_PASSER 10
#define X_BOUTON_ATTAQUER (TAILLE_ECRAN_COMBAT_X -150)
#define Y_BOUTON_ATTAQUER 10
#define X_TEXTE 100
#define Y_TEXTE (TAILLE_ECRAN_COMBAT_Y - 20)
#define TAILLE_X_BOUTON_ATTAQUER 100
#define TAILLE_Y_BOUTON_ATTAQUER 100
#define NOIR SDL_MapRGB(ecran->format,0,0,0);
#endif

