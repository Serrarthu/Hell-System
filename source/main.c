#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Turtle.h"

int main ( int argc, char** argv )
{
    /* Pour l'utilisation de printf dans un projet SDL sous Windows */
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);


    /* Affichage de la fenetre */
    SDL_Surface *ecran = NULL;
    if (SDL_Init(SDL_INIT_VIDEO)  == -1 ) { exit(EXIT_FAILURE); }
    ecran = SDL_SetVideoMode(1600, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    if (ecran == NULL) { exit(EXIT_FAILURE); }

printf("test");
    //if(TTF_Init() == -1) { exit(EXIT_FAILURE); }
    //srand(time(NULL));

    /* Chargement des fichiers L-System .fract du dossier Files */
    newLsystem(1600,900,ecran);

    runLsystem(lsystem);

    //TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
