/**
 * \file      animation.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les animations du jeu
 * \details   Cette classe permet l'affichage des animations du jeu
 */
#include <assert.h>
#include <string.h>

#ifdef __APPLE__
#include "SDL_image.h"
#else
#include <SDL/SDL_image.h>
#endif

#include "animation.h"

void initialiser_animation(Animation* une_animation, int nb_frame, int taille_x, int taille_y, int nb_ms, char nom[255])
{
	une_animation->nb_frame = nb_frame;
	une_animation->taille_frame_x = taille_x;
	une_animation->taille_frame_y = taille_y;
	une_animation->nb_ms = nb_ms;
	strcpy(une_animation->nom, nom);
	une_animation->frame_en_cours = 0;
	une_animation->tps_debut_anim = 0;
	une_animation->x = 0;
	une_animation->y = 0;
}

Animation* creer_animation(int nb_frame, int taille_frame_x, int taille_frame_y, int nb_ms, char nom[255])
{
	Animation* une_animation = (Animation*)malloc(sizeof(Animation));
	initialiser_animation(une_animation, nb_frame, taille_frame_x, taille_frame_y, nb_ms, nom);
	return une_animation;
}

void liberer_animation(Animation *une_animation)
{
	une_animation->nb_frame = 0;
	une_animation->taille_frame_x = 0;
	une_animation->taille_frame_y = 0;
	une_animation->nb_ms = 0;
	strcpy(une_animation->nom, "");
	une_animation->frame_en_cours = 0;
	une_animation->tps_debut_anim = 0;
	une_animation->x = 0;
	une_animation->y = 0;
}

void detruire_animation(Animation **une_animation)
{
	liberer_animation(*une_animation);
	free(*une_animation);
	*une_animation = NULL;
}

void testRegression_Animation()
{
    Animation *une_animation;
    une_animation = creer_animation(0, 0, 0, 0, "TEST");
    assert(une_animation->frame_en_cours == 0);
    assert(une_animation->nb_frame == 0);
    assert(une_animation->nb_ms == 0);
    assert(une_animation->x == 0);
    assert(une_animation->y == 0);
    assert(une_animation->tps_debut_anim == 0);
    assert(strcmp(une_animation->nom, "TEST") == 0);
	detruire_animation(&une_animation);
}
