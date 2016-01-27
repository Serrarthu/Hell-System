#ifndef TURTLE_H
#define TURTLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Generator.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void runLsystem(Lsystem lsystem);
Position* pushPos(Position* teteliste, double x, double y, int angle);
Position* popPos(Position* teteliste);
String dispPos (Position* teteliste);
double lenghtPos (Position* teteliste);
Position* newPosition(Position* position);
void dispTurtle(SDL_Surface * screen, String generation, Lsystem lsystem, Position* position);
double min(double a, double b);
double max(double a, double b);
double abso(double a);
void gradient(double position,int c[]);

/* Fonction de trace de ligne de la librairie SDL_gfxPrimitives.h
int aalineRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
*/

/*
Turtle Interpretation :
F, G : Se deplacer d’un pas unitaire
Autre lettre : Rien
+ : Tourner a gauche d’angle donne
- : Tourner a droite d’un angle donne
[ : Sauvegarder la position courante
] : Restaurer la derniere position sauvee
*/

#endif // TURTLE_H
