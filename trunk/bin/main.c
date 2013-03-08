#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO); // Démarrage de la SDL (ici : chargement du système vidéo)

    /*
    La SDL est chargée.
    Vous pouvez mettre ici le contenu de votre programme
    */

    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

    return 0;
}
