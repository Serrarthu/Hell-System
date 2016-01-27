#include "Generator.h"

/* Chargement des fichiers L-System .fract du dossier Files */
void newLsystem(int dimX,int dimY,SDL_Surface *ecran)
{
    console = 0;
    if (console==1) printf("Hell-System\n\n");
    width = dimX;
    height = dimY;
    screen = ecran;
    DIR *dp;
    FILE* fichier = NULL;
    struct dirent *ep;
    String strFileName = (String)malloc(100*sizeof(char));
    String strFileContent = (String)malloc(1000*sizeof(char));
    String strTmpFileContent = (String)malloc(500*sizeof(char));
    dp = opendir ("./files/");
    if (dp != NULL){
        if (console==1) printf("Chargement des fichiers L-System\n");
        String strFileName = (String)malloc(50*sizeof(char));
        strcpy(strFileName,"");
        while ((ep = readdir (dp))){
            if (strstr(ep->d_name,".fract")!=0){
                strFileName=(String)realloc(strFileName,((int)strlen(ep->d_name)+10)*sizeof(char));
                strcpy(strFileName,"");
                strcat(strFileName,"files/");
                strcat(strFileName,ep->d_name);
                fichier = fopen(strFileName, "r");
                if (fichier != NULL){
                    char buff[1000];
                    String strFileContent = (String)malloc(1000*sizeof(char));
                    strcpy(strFileContent,"");
                    while (fgets(buff, 1000, fichier) != NULL){
                    strcat(strFileContent,buff);
                    }
                    listlsystem = addLsystem(listlsystem,initLsystem(strFileContent));
                    if (console==1) printf("Fichier %s charge\n",ep->d_name);
                    fclose(fichier);
                }
            }
        }
        (void) closedir (dp);
    }
    else if (console==1) printf("Chargement des fichiers echoue\n",ep->d_name);
}

/* Initialisation de la liste des L-System */
ListLsystem* newListLsystem(ListLsystem* listlsystem)
{
    listlsystem = NULL;
    return listlsystem;
}

/* Renvoi de la taille de la liste des L-System */
double lenghtListLsystem(ListLsystem* teteliste)
{
    double i=0;
    ListLsystem* l = teteliste;
     while (l!=NULL)
     {
           i = i+1;
           l = l->next;
     }
     return i;
}

/* Renvoi le n-ieme L-System de la liste */
Lsystem pickLsystem(ListLsystem* teteliste, int n)
{
    double i = 0;
    ListLsystem* l = teteliste;
    for(i=0;i<n;i++) l = l->next;
     return l->lsystem;
}

/* Affichage des regles correspondantes a chacune des variables d'un L-System donne */
String dispRules (Rules* teteliste, String variables)
{
  String str = (String)malloc(200*sizeof(char));
  strcpy (str,"");
  Rules* l = teteliste;
  double i=0;
  while (l!=NULL)
     {
         str = strcat(str,"( ");
         str = strcat(str,ctos(variables[(int)i]));
         str = strcat(str," -> ");
         str = strcat(str,l->rule);
         str = strcat(str," ) ");
         i = i+1;
         l = l->next;
     }
  return str;
}

/* Affichage des generations presentemment crees d'un L-System donne */
String dispGen(Generations* teteliste)
{
    String str = (String)malloc(((double)strlen(teteliste->generation)+10)*sizeof(char));
    strcpy (str,"");
    double lenghtTot = (double)strlen(teteliste->generation)+10;
    Generations* l = teteliste;
    double i = 0;
    char buff[5];
    while (l!=NULL)
     {
         str = strcat(str,"n=");
         sprintf(buff,"%f",i);
         str = strcat(str,buff);
         str = strcat(str," : ");
         str = strcat(str,l->generation);
         str = strcat(str,"\n");
         i = i+1;
         l = l->next;
         if (l!=NULL) {
             lenghtTot = lenghtTot+(double)strlen(l->generation)+10;
             str = (String)realloc(str,lenghtTot*sizeof(char));
         }
     }
  return str;
}

/* Affichage des variables de l'alphabet d'un L-System donne */
String dispVariables(String variables)
{
    int i = 0;
    String strLsystem = (String)malloc(50*sizeof(char));
    strcpy (strLsystem,"");
    strcat(strLsystem,"Variables: {");
    for(i=0;i<(int)strlen(variables);i++){
        strcat(strLsystem,ctos(variables[i]));
        if (i!=(int)strlen(variables)-1) strcat(strLsystem,",");
    }
    strcat(strLsystem,"}\n");
    return strLsystem;
}

/* Affichage des constantes d'un L-System donne */
String dispConstants(String constants)
{
    int i=0;
    String strLsystem = (String)malloc(50*sizeof(char));
    strcpy (strLsystem,"");
    strcat(strLsystem,"Constants: {");
    for(i=0;i<(int)strlen(constants);i++){
        strcat(strLsystem,ctos(constants[i]));
        if (i!=(int)strlen(constants)-1) strcat(strLsystem,",");
    }
    strcat(strLsystem,"}\n");
    return strLsystem;
}

/* Affichage du L-System et de ses parametres */
String dispLsystem(Lsystem lsystem)
{
    String strLsystem = (String)malloc(200*sizeof(char));
    strcpy(strLsystem,"");
    strcat(strLsystem,lsystem.name);
    strcat(strLsystem,"\n");
    strcat(strLsystem,dispVariables(lsystem.variables));
    strcat(strLsystem,dispConstants(lsystem.constants));
    strcat(strLsystem,"Start: ");
    strcat(strLsystem,lsystem.start);
    strcat(strLsystem,"\nRules: ");
    strcat(strLsystem,dispRules(lsystem.rules,lsystem.variables));
    strcat(strLsystem,"\nAngle: ");
    char buff[3];
    sprintf(buff,"%d",lsystem.angle);
    strcat(strLsystem,buff);
    return strLsystem;
}

/* Initialisation de la premiere generation d'un L-System donne */
Generations* newGeneration(Generations* generation,Lsystem lsystem)
{
    generation->generation = lsystem.start;
    generation->next = NULL;
    return generation;
}

/* Test du vide d'un nouveau L-System */
int isNull(Lsystem lsystem)
{
    if ((lsystem.name==NULL) && (lsystem.variables==NULL) && (lsystem.constants==NULL) && (lsystem.start==NULL) & (lsystem.rules==NULL)) return 1;
    else return 0;
}

int isDrawable(String generation){
    int i = 0;
    for (i==0;i<(int)strlen(generation);i++){
        if (generation[i]=='F' || generation[i]=='G') return 1;
    }
    return 0;
}
/* Conversion d'un char en char* ou String */
String ctos(char c)
{
    char* tmp = (String)malloc(2*sizeof(char));
    tmp[0] = c;
    tmp[1] = '\0';
    return tmp;
}

/* Ajout d'une regle dans la liste de regles */
Rules* addRule(Rules* teteliste, String n)
{
     Rules* noeud = (Rules*)malloc(sizeof(Rules));
     noeud->rule = n;
     noeud->next = NULL;

     if (teteliste == NULL) return noeud;
     Rules* l = teteliste;
     while (l->next!=NULL)
     {
           l = l->next;
     }
     l->next = noeud;
     return teteliste;
}

ListLsystem* addLsystem(ListLsystem* teteliste, Lsystem lsystem)
{
     ListLsystem* noeud = (ListLsystem*)malloc(sizeof(ListLsystem));
     noeud->lsystem = lsystem;
     noeud->next = NULL;

     if (teteliste == NULL) return noeud;
     ListLsystem* l = teteliste;
     while (l->next!=NULL)
     {
           l = l->next;
     }
     l->next = noeud;
     return teteliste;
}

/* Ajout d'une generation dans la liste des generations */
Generations* addGeneration(Generations* teteliste, String n)
{
     Generations* noeud = (Generations*)malloc(sizeof(Generations));
     noeud->generation = n;
     noeud->next = NULL;

     if (teteliste == NULL) return noeud;
     Generations* l = teteliste;
     while (l->next!=NULL)
     {
           l = l->next;
     }
     l->next = noeud;
     return teteliste;
}

/* Renvoi du nombre de generations dans la liste de generations */
double lenghtGen(Generations* teteliste)
{
    double i=0;
    Generations* l = teteliste;
     while (l!=NULL)
     {
           i = i+1;
           l = l->next;
     }
     return i;
}

/* Initialisation d'un L-System a partir d'une chaine de caracteres ou sont stockes les parametres */
Lsystem initLsystem(String strLsystem)
{
    Lsystem lsystem;
    lsystem.name = NULL;
    lsystem.variables = NULL;
    lsystem.constants = NULL;
    lsystem.start = NULL;
    lsystem.rules = NULL;
    lsystem.generations = NULL;
    lsystem.position = NULL;

    char delims[] = "\n";

    lsystem.name = strtok( strLsystem, delims );
    lsystem.angle = atoi(strtok( NULL, delims ));
    lsystem.variables = strtok( NULL, delims );
    lsystem.constants = strtok( NULL, delims );
    lsystem.start = strtok( NULL, delims );
    String result = NULL;
    result = strtok( NULL, delims );
    while( result != NULL ) {
        lsystem.rules=addRule(lsystem.rules,result);
        result = strtok( NULL, delims );
    }
    lsystem.generations = (Generations*)malloc(sizeof(Generations));
    lsystem.generations = newGeneration(lsystem.generations,lsystem);
    lsystem.position = (Position*)malloc(sizeof(Position));
    lsystem.position = newPosition(lsystem.position);
    return lsystem;
}

/* Renvoi de la generation suivante d'une generation donnee pour un L-System donne */
String nextGen(String generation, Lsystem lsystem)
{
    String generation2=(String)malloc((double)strlen(generation)*sizeof(char));
    strcpy (generation2,"");
    double i = 0;
    double lenghtTot = (double)strlen(generation);
    while (i<(double)strlen(generation)){
        int nbVar = isVariable(generation[(int)i],lsystem);
        if (nbVar==-1) strcat(generation2,ctos(generation[(int)i]));
        else {
            int j;
            Rules* l = lsystem.rules;
            for (j=0;j<nbVar;j++){
                    l = l->next;
            }
            lenghtTot = lenghtTot+(double)strlen(l->rule);
            generation2 = (String)realloc(generation2,lenghtTot*sizeof(char));
            strcat(generation2,l->rule);
        }
    i = i+1;
    }
    return generation2;
}

/* Creation de n generations si ce n'est pas deja fait */
void createGen(Generations* generations, Lsystem lsystem, int n)
{
    if (n>lenghtGen(generations)-1){
        Generations* l=generations;
        while (l->next!=NULL)
        {
           l = l->next;
        }
        while (n!=lenghtGen(generations)-1){
        generations = addGeneration(generations,nextGen(l->generation,lsystem));
        l = l->next;
        }
    }
}

/* Affichage de la n-ieme generation d'un L-System donne */
String dispGen2(Generations* teteliste, Lsystem lsystem, int n)
{
    if (n>lenghtGen(teteliste)-1) createGen(teteliste, lsystem, n);
    int i=0;
    Generations* l =teteliste;
    while (i!=n)
        {
           l = l->next;
           i=i+1;
        }
    return l->generation;
}

/* Renvoi de la position de la variable en question dans la liste de variables, ou -1 sinon */
int isVariable(char var, Lsystem lsystem)
{
    int i=0;
    while (lsystem.variables[i]!=var && i!=(int)strlen(lsystem.variables)) i=i+1;
    if (lsystem.variables[i]==var) return i;
    else return -1;
}

/* Renvoi de la position de la constante en question dans la liste de constantes, ou -1 sinon */
int isConstant(char constant, Lsystem lsystem)
{
    int i=0;
    while (lsystem.constants[i]!=constant && i!=(int)strlen(lsystem.constants)) i=i+1;
    if (lsystem.constants[i]==constant) return i;
    else return -1;
}
