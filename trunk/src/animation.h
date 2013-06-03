#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>

typedef struct
{
	int nb_frame; /*nombre de frames qui va constituer l'animation*/
	int taille_frame_x;
	int taille_frame_y;
	int nb_ms; /*nombre de millisecondes pendant laquelle chaque frame s'affichera*/
	char nom[255]; /*adresse et nom de l'image ‡ charger*/

	int tps_debut_anim;
	int frame_en_cours;
	int x; /*coordonées où blitter la frame*/
	int y;

}Animation;


void initialiser_animation(Animation *une_animation, int nb_frame, int taille_frame_x, int taille_frame_y, int nb_ms, char nom[255]);
Animation *creer_animation(int nb_frame, int taille_frame_x, int taille_frame_y, int nb_ms, char nom[255]);
void liberer_animation(Animation *une_animation);
void detruire_animation(Animation **une_animation);
void testRegression_Animation();
#endif /* ANIMATION_H_*/
