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
	char nom[255]; /*adresse et nom de l'image à charger*/

	int tps_debut_anim;
	int frame_en_cours;

}Animation;


void initialiser_animation(Animation *une_animation, int nb_frame, int taille_frame_x, int taille_frame_y, int nb_ms, char nom);
Animation *creer_animation(int nb_frame, int taille_frame_x, int taille_frame_y, int nb_ms, char nom);

#endif // ANIMATION_H_
