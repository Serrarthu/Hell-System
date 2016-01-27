#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <sys/types.h>
#include <dirent.h>

/* Exemples de L-System */
/*
static char dragon[] =      "Dragon\n90\nXY\n+-F\nFX\nX+YF+\n-FX-Y\n";
static char hexagosp[] =    "Hexagonal Gosper\n60\nXY\n+-F\nXF\nX+YF++YF-FX--FXFX-YF+\n-FX+YFYF++YF+FX--FX-Y\n";
static char triangle[] =    "Triangle\n120\nF\n+-\nF+F+F\nF-F+F\n";
static char peano[] =       "Peano\n90\nXY\n+-F\nX\nXFYFX+F+YFXFY-F-XFYFX\nYFXFY-F-XFYFX+F+YFXFY\n";
static char crystal[] =     "Crystal\n90\nF\n+-\nF+F+F+F\nFF+F++F+F\n";
static char squaresierp[] = "Square Sierpinski\n90\nF\n+-X\nF+XF+F+XF\nXF-F+F-XF+F+XF-F+F-X\n";
static char quadragosp[] =  "Quadratic Gosper\n90\nXY\n+-F\n-YF\nXFX-YF-YF+FX+FX-YF-YFFX+YF+FXFXYF-FX+YF+FXFX+YF-FXYF-YF-FX+FX+YFYF-\n+FXFX-YF-YF+FX+FXYF+FX-YFYF-FX-YF+FXYFYF-FX-YFFX+FX+YF-YF-FX+FX+YFY\n";
static char hilbert[] =     "Hilbert\n90\nXY\n+-F\nX\n-YF+XFX+FY-\n+XF-YFY-FX+\n";
static char board[] =       "Board\n90\nF\n+-\nF+F+F+F\nFF+F+F+F+FF\n";
static char koch[] =        "Koch\n90\nF\n+-\nF+F+F+F\nF+F-F-FF+F+F-F\n";
static char quadrakoch[] =  "Quadratic Koch island 1\n90\nF\n+-\nF+F+F+F\nF-FF+FF+F+F-F-FF+F+F-F-FF-FF+F\n";
static char quadrasnow[] =  "Quadratic snowflake\n90\nF\n+-\nF\nF-F+F+F-F\n";
static char arrowsierp[] =  "Sierpinski arrowhead\n60\nXY\n+-F\nYF\nYF+XF+Y\nXF-YF-X\n";
static char kochsnow[] =    "Koch snowflake\n60\nF\n+-\nF++F++F\nF-F++F-F\n";
static char cross1[] =      "Cross 1\n90\nF\n+-\nF+F+F+F\nF+FF++F+F\n";
static char cross2[] =      "Cross 2\n90\nF\n+-\nF+F+F+F\nF+F-F+F+F\n";
static char tiles[] =       "Tiles\n90\nF\n+-\nF+F+F+F\nFF+F-F+F+FF\n";
static char quadrakoch2[] = "Quadratic Koch island 2\n90\nF\n+-\nF+F+F+F\nF+F-F-FFF+F+F-F\n";
static char rings[] =       "Rings\n90\nF\n+-\nF+F+F+F\nFF+F+F+F+F+F-F\n";
static char bush[] =        "Bush\n26\nXY\n+-[]F\nY\nX[-FFF][+FFF]FX\nYFX[+Y][-Y]\n";
static char brocco[] =      "Broccoli\n35\nF\n+-[]\nF\nF[+FF][-FF]F[-F][+F]F\n";
static char sticks[] =      "Sticks\n20\nFX\n+-[]\nX\nFF\nF[+X]F[-X]+X\n";
static char pine[] =        "Pine\n20\nVWXYZ\n+-[]\nVZFFF\n[+++W][---W]YV\n+X[-W]Z\n-W[+X]Z\nYZ\n[-FFF][+FFF]F\n";
static char plant1[] =      "Plant 1\n45\nAF\n[]+-\nA\nF[+A]F[-A]A\nFF\n";
static char plant4[] =      "Plant 4\n12\nA\n[]+-F\nA\nF[+A][F-A]\n";
static char plant5[] =      "Plant 5\n45\nF\n[]+-\nF\nF[+F]F[-F]F\n";
static char plant6[] =      "Plant 6\n22\nA\n[]+-F\nA\nF[+A][-A]FA\n";
static char plant7[] =      "Plant 7\n45\nF\n[]+-\nF\nF[-FF]F[+FF]F\n";
static char plant8[] =      "Plant 8\n22\nF\n[]+-\nF\nFF+[+F-F-F]-[-F+F+F]\n";
static char campos[] =      "Campos\n45\nAF\n+-\n+A++A\nAFA++AFA\nFF\n";
static char spiral[] =      "Spiral\n15\nABC\n[]+-F\nAAAA\nB+B+B+B+B+B+\n[F+F+F+F[---B-C]+++++F++++++++F-F-F-F]\n[F+F+F+F[---C]+++++F++++++++F-F-F-F]\n";
static char penrose[] =     "Penrose tiling\n36\nABCDF\n[]+-\n[B]++[B]++[B]++[B]++[B]\nCF++DF----BF[-CF----AF]++\n+CF--DF[---AF--BF]+\n-AF++BF[+++CF++DF]-\n--CF++++AF[+DF++++BF]--BF\n \n";
static char cross[] =       "Cross curve\n90\nA\n+-F\nF+AF+F+AF\nAF-F+F-AF+F+AF-F+F-A\n";
static char snake[] =       "Snake curve\n45\nA\n+-F\n+A++A\nAFA++AFA\n";

static char plant2[] = "Plant 2\n25\nAF\n+-\nA\nF-[[A]+A]+F[+FA]-A\nFF\n"; // Sticks
static char plant3[] = "Plant 3\n22\nAF\n[]+-\nA\nF[+A]F[-A]+A\nFF\n";

static char cristal[] = "Cristal\n60\nF\n[]+-\nF\nFFF[F][+[F]+F][-[F]-F]\n";
static char dragon1[] = "Dragon curve 1\n90\nAB\nF+-\nFA\nA+BF\nFA-B";
static char dragon2[] = "Dragon curve 2\n90\nF\n+-\nF++F++F\nF+FF++F+F\n";
static char koch1[] = "Koch curve 1\n90\nF\n+-\nF\nF+F-F-F+F\n";
static char koch2[] = "Koch curve 2\n60\nF\n+-\nF++F++F\nF-F++F-F\n";
static char koch3[] = "Koch curve 3\n90\nF\n+-\nF++F++F\nFF+F+F+F+FF\n";
static char koch4[] = "Koch curve 4\n90\nF\n+-\nF++F++F\nFF+F++F+F\n";
static char koch5[] = "Koch curve 5\n90\nF\n+-\nF++F++F\nFF+F+F+F+F+F-F\n";
static char island1[] = "Island curve 1\n90\nF\n+-\nF++F++F\nF-FF+FF+F+F-F-FF+F+F-F-FF-FF+F\n";
static char island2[] = "Island curve 2\n90\nF\n+-\nF++F++F\nF+F-F-FF+F+F-F\n";
static char stair[] = "Stair curve 1\n90\nF\n+-\nF++F++F\nF+F-F-F+F\n";
static char sierpinski[] = "Sierpinski triangle (Newfags can't triforce)\n60\nFG\n+-\nF\nG-F-G\nF+G+F\n";
*/

typedef char* String;

/* Liste de regles d'un L-System */
typedef struct Rules {
	String rule;
	struct Rules* next;
} Rules;

/* Liste de generations d'un L-System */
typedef struct Generations {
	String generation;
	struct Generations* next;
} Generations;

/* Pile des dernieres positions sauvegardees pour le tracage du L-System ou sont stockes l'abcisse et l'ordonnee du point ainsi que l'angle */
typedef struct Position {
	double x;
	double y;
	int angle;
	struct Position* next;
} Position;

/* L-System et ses aprametres */
typedef struct Lsystem
{
    String name;
    String variables;
    String constants;
    String start;
    Rules* rules;
    int angle;
    Generations* generations;
    Position* position;
} Lsystem;

typedef struct ListLsystem
{
    Lsystem lsystem;
    struct ListLsystem* next;
} ListLsystem;

/* Liste des L-System */
ListLsystem* listlsystem;
/* L-System par defaut */
Lsystem lsystem;
/* Informations console activees (console=1) ou non (console=0)*/
int console;
/* Taille de la fenetre */
int width;
int height;
/* Fenetre a afficher */
SDL_Surface *screen;
/* Affichage statique (insta=1) ou dynamique (insta=-1) du L-System */
int insta;
/* Couleur RGB du L-System, {-1,-1,-1} pour un degrade */
int color[3];
/* Couleur du fond */
int background[3];
double zoom;
/* n-ieme generation a afficher */
int nbgen;
/* n-ieme L-System a afficher */
int nblsystem;
/* Decalage sur les axes des abcisses et ordonnees */
double xGap;
double yGap;
/* Compteur du nombre de captures d'ecran */
int nbImg;

void newLsystem(int dimX,int dimY,SDL_Surface *ecran);
ListLsystem* newListLsystem(ListLsystem* listlsystem);
ListLsystem* addLsystem(ListLsystem* teteliste, Lsystem lsystem);
Lsystem pickLsystem(ListLsystem* teteliste, int n);
double lenghtListLsystem(ListLsystem* teteliste);
Rules* addRule(Rules* teteliste, String rule);
Generations* addGeneration(Generations* teteliste, String generation);
String dispRules(Rules* teteliste, String variables);
String dispVariables(String variables);
String dispConstants(String constants);
String dispLsystem(Lsystem lsystem);
String dispGen(Generations* teteliste);
String dispGen2(Generations* teteliste, Lsystem lsystem, int n);
String ctos(char c);
int isNull(Lsystem lsystem);
Lsystem initLsystem(String strLsystem);
int isVariable(char var, Lsystem lsystem);
int isConstant(char constant, Lsystem lsystem);
String nextGen(String generation, Lsystem lsystem);
double lenghtGen(Generations* teteliste);
Generations* newGeneration(Generations* generation,Lsystem lsystem);
void createGen(Generations* generations, Lsystem lsystem, int n);
int isDrawable(String generation);

#endif // GENERATOR_H
