#ifndef _SON_H_
#define _SON_H_


#include <FMOD/fmod.h>
#include "son.h"


void initialiser_systeme_son(FMOD_SYSTEM *system);
void fermer_systeme_son(FMOD_SYSTEM *system, FMOD_SOUND *musique);
void lire_musique(FMOD_SYSTEM *system, FMOD_SOUND *musique, char **tab_chanson);
void lire_son(FMOD_SYSTEM *system, FMOD_SOUND *son);
void maj_musique(FMOD_SYSTEM *system, FMOD_SOUND *musique, char **tab_chanson);

void initialiser_tableau_chanson(char **tab_chanson);

#endif
