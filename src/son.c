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
#include "son.h"

/**
 * \brief      Initialise la variable FMOD_SYSTEM
 * \details    Va créer le système son, réutilisé tout le long du programme
 * \param      system         Pointeur sur FMOD_SYSTEM
 */
void initialiser_systeme_son(FMOD_SYSTEM *system)
{
	FMOD_System_Create(&system);
	FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, NULL);
}


/**
 * \brief      Permet la lecture de musiques en boucle
 * \details    On va prendre dans un tableau de chansons, un titre au hazard puis on va le jouer
 * \param      system          Pointeur sur FMOD_SYSTEM
 * \param      musique		   Pointeur sur FMOD_SOUND qui va servir à lira la musique
 * \param      tab_chanson     Tableau de chaînes de caractères indiquant le nom des fichiers à lire
 */
void lire_musique(FMOD_SYSTEM *system, FMOD_SOUND *musique, char **tab_chanson)
{
	FMOD_RESULT resultat;
	FMOD_CHANNEL *channel;
	int choix;

	FMOD_System_GetChannel(system, 0, &channel);
	FMOD_Channel_Stop(channel);
	FMOD_Sound_Release(musique);
	choix = rand()%5;
	resultat = FMOD_System_CreateSound(system, tab_chanson[choix], FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_OFF | FMOD_CREATESTREAM, 0, &musique);
	if (resultat != FMOD_OK)
	{
		fprintf(stderr, "Impossible de lire une chanson\n");
	}

	FMOD_System_PlaySound(system, 0, musique, 0, NULL);
	FMOD_System_GetChannel(system, 0, &channel);
	FMOD_Channel_SetVolume(channel, 0.4);
}


/**
 * \brief      Met à jour la lecture de musiques
 * \details    Si la musique en cours n'est plus lue, on rapelle lire_chanson
 * \param      system          Pointeur sur FMOD_SYSTEM
 * \param      musique		   Pointeur sur FMOD_SOUND qui va servir à lira la musique
 * \param      tab_chanson     Tableau de chaînes de caractères indiquant le nom des fichiers à lire
 */
void maj_musique(FMOD_SYSTEM *system, FMOD_SOUND *musique, char **tab_chanson)
{
	FMOD_CHANNEL *channel;
	FMOD_BOOL fin_musique = false;
	FMOD_System_GetChannel(system, 0, &channel);
	FMOD_Channel_IsPlaying(channel, &fin_musique);


	if (fin_musique == false)
	{
		FMOD_Sound_Release(musique);
		lire_musique(system, musique, tab_chanson);
	}
}

/**
 * \brief      Permet de lire un son court
 * \details    On lit le son passé en paramètre
 * \param      system          Pointeur sur FMOD_SYSTEM
 * \param      son			   Pointeur sur FMOD_SOUND qui sera le son à lire
 */
void lire_son(FMOD_SYSTEM *system, FMOD_SOUND *son)
{
	FMOD_CHANNEL* channel;
	int i;

	for(i=1;i<10;i++)
	{
		FMOD_System_GetChannel(system, i, &channel);
		FMOD_Channel_Stop(channel);
	}
	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, son, 0, NULL);
}


/**
 * \brief      Va libérer le système son
 * \details    Appelé à la fin du programme pour libérer le système son
 * \param      system          Pointeur sur FMOD_SYSTEM
 * \param      musique		   Pointeur sur FMOD_SOUND qui va servir à lira la musique
 */
void fermer_systeme_son(FMOD_SYSTEM *system, FMOD_SOUND *musique)
{
	FMOD_Sound_Release(musique);
	FMOD_System_Close(system);
	FMOD_System_Release(system);
}


/**
 * \brief      Insère les chaînes de caractères qui correspondent aux musiques
 * \details    Ce tableau regroupe les musiques utilisées
 * \param      tab_chanson        Tableau de chaînes de caractères indiquant le nom des fichiers à lire
 */
void initialiser_tableau_chanson(char **tab_chanson)
{
	tab_chanson[0] = "../data/audio/musique/Battlestar.mp3";
	tab_chanson[1] = "../data/audio/musique/Halo.mp3";
	tab_chanson[2] = "../data/audio/musique/Mass effect 3.mp3";
	tab_chanson[3] = "../data/audio/musique/Prometheus.mp3";
	tab_chanson[4] = "../data/audio/musique/Star wars.mp3";
	tab_chanson[5] = "../data/audio/musique/Stargate.mp3";
}

/**
 * \brief      Insère les chaînes de caractères qui correspondent aux musiques
 * \details    Ce tableau regroupe les musiques utilisées
 * \param      tab_chanson        Tableau de chaînes de caractères indiquant le nom des fichiers à lire
 */
void initialiser_tableau_chanson_combat(char **tab_chanson)
{
	tab_chanson[0] = "../data/audio/musique/Combat1.mp3";
	tab_chanson[1] = "../data/audio/musique/Combat2.mp3";
	tab_chanson[2] = "../data/audio/musique/Combat3.mp3";
	tab_chanson[3] = "../data/audio/musique/Combat4.mp3";
	tab_chanson[4] = "../data/audio/musique/Combat5.mp3";
	tab_chanson[5] = "../data/audio/musique/Combat6.mp3";
}

/**
 * \brief      Insère les chaînes de caractères qui correspondent aux musiques
 * \details    Ce tableau regroupe les musiques utilisées
 * \param      tab_chanson        Tableau de chaînes de caractères indiquant le nom des fichiers à lire
 */
void initialiser_tableau_chanson_menu(char **tab_chanson)
{
	tab_chanson[0] = "../data/audio/musique/Menu.mp3";
	tab_chanson[1] = "../data/audio/musique/Menu.mp3";
	tab_chanson[2] = "../data/audio/musique/Menu.mp3";
	tab_chanson[3] = "../data/audio/musique/Menu.mp3";
	tab_chanson[4] = "../data/audio/musique/Menu.mp3";
	tab_chanson[5] = "../data/audio/musique/Menu.mp3";
}

/**
 * \brief      Insère les chaînes de caractères qui correspondent aux musiques
 * \details    Ce tableau regroupe les musiques utilisées
 * \param      tab_chanson        Tableau de chaînes de caractères indiquant le nom des fichiers à lire
 */
void initialiser_tableau_chanson_game_over(char **tab_chanson)
{
	tab_chanson[0] = "../data/audio/musique/GameOver.mp3";
	tab_chanson[1] = "../data/audio/musique/GameOver.mp3";
	tab_chanson[2] = "../data/audio/musique/GameOver.mp3";
	tab_chanson[3] = "../data/audio/musique/GameOver.mp3";
	tab_chanson[4] = "../data/audio/musique/GameOver.mp3";
	tab_chanson[5] = "../data/audio/musique/GameOver.mp3";
}