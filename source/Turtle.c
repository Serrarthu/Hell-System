#include "Turtle.h"

void runLsystem(Lsystem lsystem)
{
    String strImg = (String)malloc(20*sizeof(char));
    double xClic = 0;
    double yClic = 0;
    int continuer = 1;
    int fullscreen = -1;

    /* Creation de la fenetre */
    SDL_WM_SetCaption("Hell-System", NULL);
    if (console==1) printf("Creation de la fenetre\n");
    screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, background[0], background[1], background[2]));
    SDL_Flip(screen);
    SDL_Event event;
    SDL_EnableKeyRepeat(100, 50);

    /* Initialisation des variables */
    if (console==1) printf("Initialisation des variables\n");
    insta = 1;
    zoom = 1;
    nbgen = 0;
    nblsystem = 0;
    xGap = 0;
    yGap = 0;
    nbImg = 1;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    background[0] = 0;
    background[1] = 0;
    background[2] = 0;
    lsystem = pickLsystem(listlsystem, nblsystem);
    while (isDrawable(dispGen2(lsystem.generations,lsystem,nbgen))!=1) nbgen = nbgen+1;
    if (console==1) printf("Affichage de la %dieme generation\n",nbgen);
    /* Affichage du premier L-System charge par defaut */
    dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);

    SDL_Flip(screen);

/* Configuration de la souris des touches du clavier:
Echap: Quitter
Touches directionelles et clic molette: Deplacement
Touches +- du pave numerique et molette: Zoom
Espace et touche 0 du pave numerique: Activation/desactivation de l'affichage dynamique
Entree et Entree du pave numerique: Reinitialisation de la position du L-System
Clic droit/gauche, Ctrl gauche/droit et touches 2/8 du pave numerique: generation precedente/suivante
Maj gauche/droit et touches 3/9 du pave numerique: Affichage du L-System precedent/suivant
Imprime ecran: sauvegarde du L-System sous forme d'image dans le dossier "screenshots" a la racine du projet
*/
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_TAB:
                        fullscreen = -fullscreen;
                        if (fullscreen==1){
                            if (console==1) printf("Plein ecran active\n");
                            screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                        }
                        else {
                            if (console==1) printf("Plein ecran desactive\n");
                            screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        }
                        if (console==1) printf("Affichage de la %dieme generation\n",nbgen);
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        if (console==1) printf("\n");
                        break;
                    case SDLK_UP:
                        if (console==1) printf("Deplacement haut\n");
                        yGap = yGap+20;
                        if (insta==-1){
                        insta = 1;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        insta = -1;
                        }
                        else dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_DOWN:
                        if (console==1) printf("Deplacement bas\n");
                        yGap = yGap-20;
                        if (insta==-1){
                        insta = 1;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        insta = -1;
                        }
                        else dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_RIGHT:
                        if (console==1) printf("Deplacement droite\n");
                        xGap = xGap-20;
                        if (insta==-1){
                        insta = 1;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        insta = -1;
                        }
                        else dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_LEFT:
                        if (console==1) printf("Deplacement gauche\n");
                        xGap = xGap+20;
                        if (insta==-1){
                        insta = 1;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        insta = -1;
                        }
                        else dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_KP_PLUS:
                        if (zoom<200){
                        zoom = zoom*1.25;
                        if (console==1) printf("Zoom a %d%%\n",(int)(zoom*100));
                        if (insta==-1){
                        insta = 1;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        insta = -1;
                        }
                        else dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        }
                        break;
                    case SDLK_KP_MINUS:
                        if (zoom>0.02){
                        zoom = zoom*0.8;
                        if (console==1) printf("Zoom a %d%%\n",(int)(zoom*100));
                        if (insta==-1){
                        insta = 1;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        insta = -1;
                        }
                        else dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        }
                        break;
                    case SDLK_KP2:
                        if (nbgen>0 && isDrawable(dispGen2(lsystem.generations,lsystem,nbgen-1))==1) {
                        nbgen = nbgen-1;
                        if (console==1) printf("Affichage de la %dieme generation\n",nbgen);
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        }
                        break;
                    case SDLK_KP8:
                        nbgen = nbgen+1;
                        if (console==1) printf("Affichage de la %dieme generation\n",nbgen);
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_KP3:
                        nblsystem = nblsystem-1;
                        if (nblsystem<0) nblsystem = lenghtListLsystem(listlsystem)-1;
                        nbgen = 0;
                        lsystem = pickLsystem(listlsystem, nblsystem);
                        while (isDrawable(dispGen2(lsystem.generations,lsystem,nbgen))!=1) nbgen = nbgen+1;
                        zoom = 1;
                        xGap = 0;
                        yGap = 0;
                        if (console==1) printf("Choix du L-System %s\n",dispLsystem(lsystem));
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_KP9:
                        nblsystem = nblsystem+1;
                        if (nblsystem>=lenghtListLsystem(listlsystem)) nblsystem = 0;
                        nbgen = 0;
                        lsystem = pickLsystem(listlsystem, nblsystem);
                        while (isDrawable(dispGen2(lsystem.generations,lsystem,nbgen))!=1) nbgen = nbgen+1;
                        zoom = 1;
                        xGap = 0;
                        yGap = 0;
                        if (console==1) printf("Choix du L-System %s\n",dispLsystem(lsystem));
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_KP0:
                        insta = -insta;
                        if (console==1){
                        if (insta==-1) printf("Affichage dynamique\n");
                        else printf("Affichage statique\n");
                        }
                        if (insta==-1) dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_SPACE:
                        insta = -insta;
                        if (console==1){
                        if (insta==-1) printf("Affichage dynamique\n");
                        else printf("Affichage statique\n");
                        }
                        if (insta==-1) dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_KP_ENTER:
                        if (zoom!=1 || xGap!=0 || yGap!=0){
                        if (console==1) printf("Reinitialisation de l'affichage\n");
                        zoom = 1;
                        xGap = 0;
                        yGap = 0;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        }
                        break;
                    case SDLK_RETURN:
                        if (zoom!=1 || xGap!=0 || yGap!=0){
                        if (console==1) printf("Reinitialisation de l'affichage\n");
                        zoom = 1;
                        xGap = 0;
                        yGap = 0;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        }
                        break;
                    case SDLK_LCTRL:
                        if (nbgen>0 && isDrawable(dispGen2(lsystem.generations,lsystem,nbgen-1))==1) {
                        nbgen = nbgen-1;
                        if (console==1) printf("Affichage de la %dieme generation\n",nbgen);
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        }
                        break;
                    case SDLK_RCTRL:
                        nbgen = nbgen+1;
                        if (console==1) printf("Affichage de la %dieme generation\n",nbgen);
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_LSHIFT:
                        nblsystem = nblsystem-1;
                        if (nblsystem<0) nblsystem = lenghtListLsystem(listlsystem)-1;
                        nbgen = 0;
                        lsystem = pickLsystem(listlsystem, nblsystem);
                        while (isDrawable(dispGen2(lsystem.generations,lsystem,nbgen))!=1) nbgen = nbgen+1;
                        zoom = 1;
                        xGap = 0;
                        yGap = 0;
                        if (console==1) printf("Choix du L-System %s\n",dispLsystem(lsystem));
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_RSHIFT:
                        nblsystem = nblsystem+1;
                        if (nblsystem>=lenghtListLsystem(listlsystem)) nblsystem = 0;
                        nbgen = 0;
                        lsystem = pickLsystem(listlsystem, nblsystem);
                        while (isDrawable(dispGen2(lsystem.generations,lsystem,nbgen))!=1) nbgen = nbgen+1;
                        zoom = 1;
                        xGap = 0;
                        yGap = 0;
                        if (console==1) printf("Choix du L-System %s\n",dispLsystem(lsystem));
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_q: // Degrade multicolore
                        if (console==1) printf("Couleur L-System degrade Multicolore\n");
                        color[0] = -1;
                        color[1] = -1;
                        color[2] = -1;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_w: // Degrade nature
                        if (console==1) printf("Couleur L-System degrade Nature\n");
                        color[0] = -3;
                        color[1] = -3;
                        color[2] = -3;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_e: // Degrade noir et blanc
                        if (console==1) printf("Couleur L-System degrade Noir et Blanc\n");
                        color[0] = -2;
                        color[1] = -2;
                        color[2] = -2;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_r: // Blanc
                        if (console==1) printf("Couleur L-System blanc\n");
                        color[0] = 255;
                        color[1] = 255;
                        color[2] = 255;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_t: // Noir
                        if (console==1) printf("Couleur L-System noir\n");
                        color[0] = 0;
                        color[1] = 0;
                        color[2] = 0;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_y: // Rouge
                        if (console==1) printf("Couleur L-System rouge\n");
                        color[0] = 128;
                        color[1] = 0;
                        color[2] = 0;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_u: // Vert
                        if (console==1) printf("Couleur L-System vert\n");
                        color[0] = 0;
                        color[1] = 128;
                        color[2] = 0;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_i: // Bleu
                        if (console==1) printf("Couleur L-System bleu\n");
                        color[0] = 0;
                        color[1] = 0;
                        color[2] = 128;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_a: // Noir
                        if (console==1) printf("Couleur fond noir\n");
                        background[0] = 0;
                        background[1] = 0;
                        background[2] = 0;
                        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, background[0], background[1], background[2]));
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_s: // Blanc
                        if (console==1) printf("Couleur fond blanc\n");
                        background[0] = 255;
                        background[1] = 255;
                        background[2] = 255;
                        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, background[0], background[1], background[2]));
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_d: // Rouge
                        if (console==1) printf("Couleur fond rouge\n");
                        background[0] = 128;
                        background[1] = 0;
                        background[2] = 0;
                        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, background[0], background[1], background[2]));
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_f: // Vert
                        if (console==1) printf("Couleur fond vert\n");
                        background[0] = 0;
                        background[1] = 128;
                        background[2] = 0;
                        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, background[0], background[1], background[2]));
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_g: // Bleu
                        if (console==1) printf("Couleur fond bleu\n");
                        background[0] = 0;
                        background[1] = 0;
                        background[2] = 128;
                        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, background[0], background[1], background[2]));
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDLK_PRINT:
                    if (console==1) printf("Capture d'ecran\n");
                    strcpy (strImg,"");
                    strcat(strImg,"screenshots/image ");
                    char buff[5];
                    sprintf(buff,"%d",nbImg);
                    strcat(strImg,buff);
                    strcat(strImg,".bmp");
                    SDL_SaveBMP(screen, strImg);
                    nbImg = nbImg+1;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                    case SDL_BUTTON_MIDDLE:
                        xClic = event.button.x;
                        yClic = event.button.y;
                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                    case SDL_BUTTON_MIDDLE:
                        if (event.motion.x!=xClic || event.motion.y!=yClic){
                        if (console==1) printf("Deplacement\n");
                        xGap = xGap+(event.motion.x-xClic);
                        yGap = yGap+(event.motion.y-yClic);
                        if (insta==-1){
                        insta = 1;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        insta = -1;
                        }
                        else dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        }
                        break;
                    case SDL_BUTTON_RIGHT:
                        if (nbgen>0 && isDrawable(dispGen2(lsystem.generations,lsystem,nbgen-1))==1) {
                        nbgen = nbgen-1;
                        if (console==1) printf("Affichage de la %dieme generation\n",nbgen);
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        }
                        break;
                    case SDL_BUTTON_LEFT:
                        nbgen = nbgen+1;
                        if (console==1) printf("Affichage de la %dieme generation\n",nbgen);
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        break;
                    case SDL_BUTTON_WHEELUP:
                        if (zoom<200){
                        zoom = zoom*1.25;
                        if (console==1) printf("Zoom a %d%%\n",(int)(zoom*100));
                        if (insta==-1){
                        insta = 1;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        insta = -1;
                        }
                        else dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        }
                        break;
                    case SDL_BUTTON_WHEELDOWN:
                    if (zoom>0.02){
                        zoom = zoom*0.8;
                        if (console==1) printf("Zoom a %d%%\n",(int)(zoom*100));
                        if (insta==-1){
                        insta = 1;
                        dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        insta = -1;
                        }
                        else dispTurtle(screen,dispGen2(lsystem.generations,lsystem,nbgen),lsystem,lsystem.position);
                        }
                        break;
                }
                break;
            case SDL_MOUSEMOTION:

                break;
        }
    }
    if (console==1) printf("Fin du programme\n");
}

/* Initialisation de la pile des positions sauvegardees */
Position* newPosition(Position* position)
{
    position = NULL;
    return position;
}

/* Affichage de la pile */
String dispPos (Position* teteliste)
{
    String str = (String)malloc(70*sizeof(char));
    strcpy (str,"");
    str = strcat(str,"Pile des positions sauvegardees :\n\n");
    double lenghtTot = 70;
    Position* l = teteliste;
    double i = lenghtPos(teteliste);
    char buff[5];
    while (l != NULL)
     {
         str = strcat(str,"n=");
         sprintf(buff,"%d",(int)i);
         str = strcat(str,buff);
         str = strcat(str," : x=");
         sprintf(buff,"%f",l->x);
         str = strcat(str,buff);
         str = strcat(str," ; y=");
         sprintf(buff,"%f",l->y);
         str = strcat(str,buff);
         str = strcat(str," ; angle=");
         sprintf(buff,"%d",l->angle);
         str = strcat(str,buff);
         str = strcat(str,"\n");
         i = i-1;
         l = l->next;
         if (l!=NULL) {
             lenghtTot=lenghtTot+40;
             str=(String)realloc(str,lenghtTot*sizeof(char));
         }
     }
     str = strcat(str,"\n");
     return str;
}

/* Renvoi du nombre de positions sauvegardees */
double lenghtPos (Position* teteliste)
{
    double i=0;
    Position* l = teteliste;
     while (l!=NULL)
     {
           i=i+1;
           l = l->next;
     }
     return i;
}

/* Sauvegarde la position actuelle */
Position* pushPos(Position* teteliste, double x, double y, int angle)
{
       Position* noeud = (Position*)malloc(sizeof(Position));
       noeud->x = x;
       noeud->y = y;
       noeud->angle = angle;
       noeud->next = teteliste;
       return noeud;
}

/* Renvoi de la derniere position sauvegardee et retrait de celle-ci dans la pile */
Position* popPos(Position* teteliste)
{
       if (teteliste == NULL) return NULL;
       Position* noeud = teteliste->next;
       free(teteliste);
       return noeud;
}

double min(double a, double b){
    if (a<b) return a;
    else return b;
}

double max(double a, double b){
    if (a<b) return b;
    else return a;
}

double abso(double a){
    if (a<0) return -a;
    else return a;
}

void dispTurtle(SDL_Surface * screen, String generation, Lsystem lsystem, Position* position)
{

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, background[0], background[1], background[2]));

    double xMin = 0;
    double yMin = 0;
    double xMax = 0;
    double yMax = 0;
    double i = 0;
    double x = 0;
    double y = 0;
    int angle = 0;
    double nbLines = 0; // Nombre de lignes total a tracer pour le L-System a une generation donnee
    double nbPos = 0; // Nombre de sauvegardes de position total
    double lenght = 10; // Taille avant reajustement automatique
    /* Calcul de la taille du L-System avant reajustement */
    while (i<(double)strlen(generation)){
        switch (generation[(int)i]) {

            case 'F' :
                x = x+lenght*sin(angle*M_PI/180);
                y = y-lenght*cos(angle*M_PI/180);
                if (x<xMin) xMin = x;
                else if (x>xMax) xMax = x;
                if (y<yMin) yMin = y;
                else if (y>yMax) yMax = y;
                nbLines = nbLines+1;
                break; // 'F'

            case 'G' :
                x = x+lenght*sin(angle*M_PI/180);
                y = y-lenght*cos(angle*M_PI/180);
                if (x<xMin) xMin = x;
                else if (x>xMax) xMax = x;
                if (y<yMin) yMin = y;
                else if (y>yMax) yMax = y;
                nbLines = nbLines+1;
                break; // 'G'

            case '+' :
                angle = angle+lsystem.angle;
                if (angle>360) angle=angle-360;
                break; // '+'

            case '-' :
                angle = angle-lsystem.angle;
                if (angle<-360) angle=angle+360;
                break; // '-'

            case '[' :
                position = pushPos(position,x,y,angle);
                nbPos = max(nbPos, lenghtPos(position));
                break; // '['

            case ']' :
                x = position->x;
                y = position->y;
                angle = position->angle;
                position=popPos(position);
                break; // ']'

        } // switch
    i = i+1;
    } // while

    double xSize = max(xMax-xMin,xMin-xMax);
    double ySize = max(yMax-yMin,yMin-yMax);
    double xCoef = width/xSize;
    double yCoef = height/ySize;
    double coef = min(xCoef,yCoef);
    x=0;
    y=0;

    /* Reajustement de la taille et centrage du L-System sur la surface */
    if (xMin<0) {
        xMax = xMax+abso(xMin);
        x = x+abso(xMin);
        xMin = xMin+abso(xMin);
    }
    if (yMin<0) {
        yMax = yMax+abso(yMin);
        y = y+abso(yMin);
        yMin = yMin+abso(yMin);
    }

    lenght = lenght*coef;
    xMin = xMin*coef;
    yMin = yMin*coef;
    xMax = xMax*coef;
    yMax = yMax*coef;
    xSize = xSize*coef;
    ySize = ySize*coef;
    x = x*coef;
    y = y*coef;

    lenght = lenght*zoom;
    xSize = xSize*zoom;
    ySize = ySize*zoom;
    x = x*zoom;
    y = y*zoom;

    x = x+(width-xSize)/2;
    y = y+(height-ySize)/2;

    angle = 0;

    int delay = (int)(1000/nbLines); // Delai entre l'affichage de deux traits
    if (delay>20) delay = 20;

    double posColor1 = 1/nbLines;
    int gradColor[3];
    double cptColor1 = posColor1;
    double posColor2;
    double cptColor2;
    double posColor3;
    double cptColor3;
    if (nbPos==0) {
        posColor2 = 255/nbLines;
        cptColor2 = posColor2;
        posColor3 = 100;
        cptColor3 = 100/nbLines;
    }
    else {
        posColor2 = 255/nbPos;
        cptColor2 = posColor2;
        posColor3 = 100;
        cptColor3 = 100/nbPos;
    }

    /* Tracage du L-System */
    i = 0;
    while (i<(double)strlen(generation)){
        switch (generation[(int)i]) {

            case 'F' :
                if (color[0]==-1 && color[1]==-1 && color[2]==-1){
                gradient(posColor1,gradColor);
                posColor1 = posColor1+cptColor1;
                aalineRGBA(screen,(int)x+xGap,(int)y+yGap,(int)(x+xGap+lenght*sin(angle*M_PI/180)),(int)(y+yGap-lenght*cos(angle*M_PI/180)),gradColor[0],gradColor[1],gradColor[2],255);
                }
                else if (color[0]==-2 && color[1]==-2 && color[2]==-2){
                aalineRGBA(screen,(int)x+xGap,(int)y+yGap,(int)(x+xGap+lenght*sin(angle*M_PI/180)),(int)(y+yGap-lenght*cos(angle*M_PI/180)),(int)posColor2,(int)posColor2,(int)posColor2,255);
                if (nbPos==0) posColor2 = posColor2+cptColor2;
                }
                else if (color[0]==-3 && color[1]==-3 && color[2]==-3){
                aalineRGBA(screen,(int)x+xGap,(int)y+yGap,(int)(x+xGap+lenght*sin(angle*M_PI/180)),(int)(y+yGap-lenght*cos(angle*M_PI/180)),(int)posColor3,(int)(150-posColor3),0,255);
                if (nbPos==0) posColor3 = posColor3-cptColor3;
                }
                else aalineRGBA(screen,(int)x+xGap,(int)y+yGap,(int)(x+xGap+lenght*sin(angle*M_PI/180)),(int)(y+yGap-lenght*cos(angle*M_PI/180)),color[0],color[1],color[2],255);
                x = x+lenght*sin(angle*M_PI/180);
                y = y-lenght*cos(angle*M_PI/180);
                if (insta==-1 && i-1!=(int)strlen(generation)){
                    SDL_Delay((Uint32)delay);
                    SDL_Flip(screen);
                }
                break; // 'F'

            case 'G' :
                if (color[0]==-1 && color[1]==-1 && color[2]==-1){
                gradient(posColor1,gradColor);
                posColor1 = posColor1+cptColor1;
                aalineRGBA(screen,(int)x+xGap,(int)y+yGap,(int)(x+xGap+lenght*sin(angle*M_PI/180)),(int)(y+yGap-lenght*cos(angle*M_PI/180)),gradColor[0],gradColor[1],gradColor[2],255);
                }
                else if (color[0]==-2 && color[1]==-2 && color[2]==-2){
                aalineRGBA(screen,(int)x+xGap,(int)y+yGap,(int)(x+xGap+lenght*sin(angle*M_PI/180)),(int)(y+yGap-lenght*cos(angle*M_PI/180)),(int)posColor2,(int)posColor2,(int)posColor2,255);
                if (nbPos==0) posColor2 = posColor2+cptColor2;
                }
                else if (color[0]==-3 && color[1]==-3 && color[2]==-3){
                aalineRGBA(screen,(int)x+xGap,(int)y+yGap,(int)(x+xGap+lenght*sin(angle*M_PI/180)),(int)(y+yGap-lenght*cos(angle*M_PI/180)),(int)posColor3,(int)(150-posColor3),0,255);
                if (nbPos==0) posColor3 = posColor3-cptColor3;
                }
                else aalineRGBA(screen,(int)x+xGap,(int)y+yGap,(int)(x+xGap-lenght*sin(angle*M_PI/180)),(int)(y+yGap-lenght*cos(angle*M_PI/180)),color[0],color[1],color[2],255);
                x = x+lenght*sin(angle*M_PI/180);
                y = y-lenght*cos(angle*M_PI/180);
                if (insta==-1 && i-1!=(int)strlen(generation)){
                    SDL_Delay((Uint32)delay);
                    SDL_Flip(screen);
                }
                break; // 'G'

            case '+' :
                angle = angle+lsystem.angle;
                if (angle>360) angle=angle-360;
                break; // '+'

            case '-' :
                angle = angle-lsystem.angle;
                if (angle<-360) angle=angle+360;
                break; // '-'

            case '[' :
                position = pushPos(position,x,y,angle);
                if (color[0]==-2 && color[1]==-2 && color[2]==-2 && nbPos>0) posColor2 = posColor2+cptColor2;
                if (color[0]==-3 && color[1]==-3 && color[2]==-3 && nbPos>0) posColor3 = posColor3-cptColor3;
                break; // '['

            case ']' :
                x = position->x;
                y = position->y;
                angle = position->angle;
                position=popPos(position);
                if (color[0]==-2 && color[1]==-2 && color[2]==-2 && nbPos>0) posColor2 = posColor2-cptColor2;
                if (color[0]==-3 && color[1]==-3 && color[2]==-3 && nbPos>0) posColor3 = posColor3+cptColor3;
                break; // ']'

        } // switch
    i = i+1;
    } // while
    SDL_Flip(screen);
}

void gradient(double position,int c[])
{

  if (position>1.0){if (position-(int)position==0.0)position=1.0; else position=position-(int)position;}

  unsigned char nmax=6;
  double m=nmax* position;

  int n=(int)m;

  double f=m-n;
  unsigned char t=(int)(f*255);

switch( n){
   case 0: {
      c[0] = 255;
      c[1] = t;
      c[2] = 0;
       break;
    };
   case 1: {
      c[0] = 255 - t;
      c[1] = 255;
      c[2] = 0;
       break;
    };
   case 2: {
      c[0] = 0;
      c[1] = 255;
      c[2] = t;
       break;
    };
   case 3: {
      c[0] = 0;
      c[1] = 255 - t;
      c[2] = 255;
       break;
    };
   case 4: {
      c[0] = t;
      c[1] = 0;
      c[2] = 255;
       break;
    };
   case 5: {
      c[0] = 255;
      c[1] = 0;
      c[2] = 255 - t;
       break;
    };
    default: {
      c[0] = 255;
      c[1] = 0;
      c[2] = 0;
       break;
    };

};
}
