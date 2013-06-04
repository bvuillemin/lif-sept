#ifndef _SON_H_
#define _SON_H_


#ifdef __APPLE__
#include "fmod.h"
#else
#include <FMOD/fmod.h>
//#include "../lib/inc/fmod.h"
#endif

void initialiser_systeme_son(FMOD_SYSTEM *system);
void fermer_systeme_son(FMOD_SYSTEM *system, FMOD_SOUND *musique);
void lire_musique(FMOD_SYSTEM *system, FMOD_SOUND *musique, char **tab_chanson);
void lire_son(FMOD_SYSTEM *system, FMOD_SOUND *son);
void maj_musique(FMOD_SYSTEM *system, FMOD_SOUND *musique, char **tab_chanson);

void initialiser_tableau_chanson(char **tab_chanson);
void initialiser_tableau_chanson_combat(char **tab_chanson);
void initialiser_tableau_chanson_menu(char **tab_chanson);
void initialiser_tableau_chanson_game_over(char **tab_chanson);
#endif
