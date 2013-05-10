#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <FMOD/fmod.h>

void initialiser_systeme_son(FMOD_SYSTEM *system, FMOD_SOUND *musique)
{
	FMOD_RESULT resultat;

	FMOD_System_Create(&system);
	FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

	/* On ouvre la musique */
	resultat = FMOD_System_CreateSound(system, "../audio/musique/Battlestar.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);

	/* On vérifie si elle a bien été ouverte */
	if (resultat != FMOD_OK)
	{
		fprintf(stderr, "Impossible de lire le fichier mp3\n");
		/*exit(EXIT_FAILURE);*/
	}

	/* On active la répétition de la musique à l'infini */
	FMOD_Sound_SetLoopCount(musique, -1);

	/* On joue la musique */
	 FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
}

void fermer_systeme_son(FMOD_SYSTEM *system, FMOD_SOUND *musique)
{
	FMOD_Sound_Release(musique);
	FMOD_System_Close(system);
	FMOD_System_Release(system);
}