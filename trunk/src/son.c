/**
 * \file      son.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Lecture des sons
 * \details   Cette classe définit les sons et musiques de fond permet leur lecture dans le jeu
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#ifdef __APPLE__
#include "fmod.h"
#else
#include <FMOD/fmod.h>
#endif

void initialiser_systeme_son(FMOD_SYSTEM *system)
{
	FMOD_System_Create(&system);
	FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
}

void lire_musique(FMOD_SYSTEM *system, FMOD_SOUND *musique, char **tab_chanson)
{
	FMOD_RESULT resultat;
	FMOD_CHANNEL *channel;
	int choix;
	
	choix = rand()%5;
	resultat = FMOD_System_CreateSound(system, tab_chanson[choix], FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_OFF | FMOD_CREATESTREAM, 0, &musique);
	if (resultat != FMOD_OK)
	{
		fprintf(stderr, "Impossible de lire le fichier mp3\n");
		/*exit(EXIT_FAILURE);*/
	}

	FMOD_System_PlaySound(system, 1, musique, 0, NULL);
	FMOD_System_GetChannel(system, 1, &channel);
	FMOD_Channel_SetVolume(channel, 0.5);
}

void maj_musique(FMOD_SYSTEM *system, FMOD_SOUND *musique, char **tab_chanson)
{
	FMOD_CHANNEL *channel;
	bool fin_musique = false;
	FMOD_System_GetChannel(system, 1, &channel);
	FMOD_Channel_IsPlaying(channel, &fin_musique);
	

	if (fin_musique == false)
	{
		FMOD_Sound_Release(&musique);
		lire_musique(system, musique, tab_chanson);
	}
}

void lire_son(FMOD_SYSTEM *system, FMOD_SOUND *son)
{
	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, son, 0, NULL);
}

void fermer_systeme_son(FMOD_SYSTEM *system, FMOD_SOUND *musique)
{
	FMOD_Sound_Release(&musique);
	FMOD_System_Close(system);
	FMOD_System_Release(system);
}

void initialiser_tableau_chanson(char **tab_chanson)
{
	tab_chanson[0] = "../audio/musique/Battlestar.mp3";
	tab_chanson[1] = "../audio/musique/Halo.mp3";
	tab_chanson[2] = "../audio/musique/Mass effect 3.mp3";
	tab_chanson[3] = "../audio/musique/Prometheus.mp3";
	tab_chanson[4] = "../audio/musique/Star wars.mp3";
	tab_chanson[5] = "../audio/musique/Stargate.mp3";
}
