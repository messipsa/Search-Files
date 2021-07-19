#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>


/* global variable definitions */
int entete=0; //affichage de l'entete
int nb_resultats=0; //nombre de resultats apres Search

int s_option=0; //à 1 si -a ou -d mentionne
int t_option=0;//à 1 si -a ou -d mentionne
int d_option=0;//à 1 si -a ou -d mentionne
int m_option=0;//à 1 si -a ou -d mentionne
int p_option=0;//à 1 si -a ou -d mentionne

int profondeur=-1;//INDIQUE la profondeur de la recherche , sinon on cherche dans l'intégralité de l'hiérarchie

typedef enum booleen{
    Faux,
    Vrai
    }
booleen;//enumeration de booleen pour l'utilisation au lieu des entiers

booleen astr_debut;//INDIQUE si l'expression commence avec un (*)
booleen astr_fin;//INDIQUE si l'expression se termine avec un (*)

char regex[512]="";// chaine qui contient l’expression reguliere
char *exp_decoup[512];//decoupage de l’expression reguliere en petites expressions separees par (*) 
int taille_decoup=0;// taille des petites expressions


/* end of global variable definitions */





void affichage_binome()
{
printf (" %s",//L'affichage
	  "                                               @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
  
  printf (" %s",
	  "                                               @           ____________________________________________________________________           @\n");
  
  printf (" %s",
	  "                                               @@         |                                                                    |         @@\n");
  
  printf (" %s",
	  "                                               @@@        |         Ecole Nationale Superieure d'Informatique -ESI-            |        @@@\n");
   
  printf (" %s",
	  "                                               @@@@       |                                                                    |       @@@@\n");
  
  printf (" %s",
	  "                                               @@@@@      |                     Tp Système centralisé II                       |      @@@@@\n");
 
  printf (" %s",
	  "                                               @@@@@@     |                                                                    |     @@@@@@\n");
 
  printf (" %s",
	  "                                               @@@@@@     |                                                                    |     @@@@@@\n");
 
  printf (" %s",
	  "                                               @@@@@@     |          Commande Search---Recherche de fichiers Sous Linux        |     @@@@@@\n");
  
  printf (" %s",
	  "                                               @@@@@@     |                                                                    |     @@@@@@\n");
  
  printf (" %s",
	  "                                               @@@@@@     |                                                                    |     @@@@@@\n");
  
  printf (" %s",
	  "                                               @@@@@@     |                --- Realise par Tamazouzt Messipsa ---              |     @@@@@@\n");
    
  printf (" %s",
	  "                                               @@@@@@     |                                                                    |     @@@@@@\n");
  
  printf (" %s",
	  "                                               @@@@@@     |                      --- Ahmed Ali Nassim ---                      |     @@@@@@\n");
  
  printf (" %s",
	  "                                               @@@@@      |                                                                    |      @@@@@\n");
   
  printf (" %s",
	  "                                               @@@@       |                   Encadre par : Mme Bouzar Lydia                   |       @@@@\n");
    
   printf (" %s",
	  "                                               @@@        |                                                                    |        @@@\n");
 
  printf (" %s",
	  "                                               @@         |____________________________________________________________________|         @@\n");
  
  printf (" %s",
	  "                                               @           ____________________________________________________________________           @\n");
  
  printf (" %s",
	  "                                               @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
 
  printf (" %s",
	  "                                                                                            \n");
 
  printf (" %s",
	  "                                                                                            \n");
  printf (" %s",
	  "                                                                                            \n");
}


void afficher_entete() //affiche l'entete
{
if (p_option) printf("\n%10s", "Permission  ");
if (t_option)  printf("%4s","Type  ");
if (s_option) printf("%s","     Taille ");
if (d_option) printf ("%22s","Derniere Utilisation  ");
if (m_option) printf("%17s","Derniere modification   ");
 printf("Chemin du fichier\n");
}


void Documentation()//affichage de documentation en cas d'erreur
{
        
	
	printf (" %s",//L'affichage
	  "                                               \n");
  
  printf (" %s",
	  "                                                           ____________________________________________________________________           \n");
	    printf (" %s",
	  "                                                          |                                                                    |       \n");
   
  printf (" %s",
	  "                                                          |        Aide réalisé par TAMAZOUZT MESSIPSA---AHMED ALI NASSIM      |        \n");
	    printf (" %s",
	  "                                                          |                                                                    |       \n");
  
  printf (" %s",
	  "                                                          |         search - Chercher un fichier dans l'hierarchie             |        \n");
   
  printf (" %s",
	  "                                                          |                                                                    |       \n");
  
  printf (" %s",
	  "                                                          |         Scenario    :  search [Chemins] [-Options] [Nom_fich]      |      \n");
 
  printf (" %s",
	  "                                                          |                                                                    |     \n");
  printf (" %s",
	  "                                                          |                             OPTIONS                                |     \n");
  printf (" %s",
	  "                                                          |                                                                    |     \n");
 
  printf (" %s",
	  "                                                          |      -N : N un entier positif indiquant la profondeur du fichier   |     \n");
 
  printf (" %s",
	  "                                                          |         Si N non mentionne on cherche dans toute l'hierarchie      |     \n");
  
  printf (" %s",
	  "                                                          |                                                                    |     \n");
  
  printf (" %s",
	  "                                                          |           -d :  Afficher la derniere utilisation du fichier        |     \n");
  
  printf (" %s",
	  "                                                          |           -m :  Afficher la derniere modification du fichier       |     \n");
    
  printf (" %s",
	  "                                                          |           -s :  Afficher la taille du fichier                      |     \n");
  
  printf (" %s",
	  "                                                          |           -t :  Afficher le type du fichier                        |     \n");
  
  printf (" %s",
	  "                                                          |           -p : Afficher la protection du fichier                   |      \n");
   
  printf (" %s",
	  "                                                          |           -a : Afficher toutes les informations                    |       \n");
    
   printf (" %s",
	  "                                                          |                                                                    |        \n");
	    printf (" %s",
	  "                                                          |                           Remarque :                               |        \n");
	    printf (" %s",
	  "                                                          |                                                                    |        \n");
	    printf (" %s",
	  "                                                          |     Les Types sont : REGU: Fichier regulier , DIREC: Repertoire    |        \n");
	     printf (" %s",
	  "                                                          |                 LINK: Lien symbolique , SOCK: socket               |        \n");
	     printf (" %s",
	  "                                                          |     FIFO: named pipe, MCAR: character device, BLOCK: block device  |        \n");
 
  printf (" %s",
	  "                                                          |____________________________________________________________________|         \n");
  
  printf (" %s",
	  "                                                                    \n");
   
  printf (" %s",
	  "                                               \n");
 
  printf (" %s",
	  "                                                                                            \n");
 
	
} 


void afficher_resultats(int argc,char *argv[])//affichage des resultats
{
	if (nb_resultats==0)
	{
	 printf("Aucun fichier correspendant '%s'\n",argv[argc-1]);
	}
	else 
	{
	printf("%d Les fichiers correspondants '%s'\n",nb_resultats,argv[argc-1]);
	}
}




void afficher_temps(time_t fulltime) //affiche le temps exacte
{
        const char *forme;
	forme = "%3b %e %Y %R   ";
	char temps[80];
	strftime(temps, sizeof(temps), forme, localtime(&fulltime));
	fputs(temps, stdout);
}


void Erreur(int err,char *argv[])//affichage message d'erreur
{
	printf("%s: Option invalide -- '%s'\n",argv[0],argv[-(err+1)]+1);
}



booleen egalite_partielle(char* argument,char* nom_fich_part)//teste l'egalite partielle de nom (cas de ?)
{
	int i=0;
	if (strlen(argument) == strlen(nom_fich_part)){
		while (i<strlen(argument))
		{
			if (argument[i]=='?' || argument[i]==nom_fich_part[i]) 
			{
            			i=i+1;
			}
			else return Faux;
        	}
		return Vrai;		
	}	
	return Faux;	

}


int pointeur_debut(char *partie,char *nom_fich) //pointe la premiere occurence de l'argument dans le nom de fichier
{	
	int i=0,j=0;
	char s[512]="";
	while (i+strlen(partie)<=strlen(nom_fich))
	{		
		strncpy(s,nom_fich+i,strlen(partie));
		if (egalite_partielle(partie,s))
		{
		 return i;
		}
		i=i+1;
	}
	return -1;
}

void recuperer_derniers_caracteres(char *s,int n,char *ret) //recupere n derniers caracteres d'une expression
{
	int i=0;
	int j = strlen(s)-n;
	while (j<0) j++;
	for (i=j;i<strlen(s);i++) 
	{
	sprintf(ret,"%s%c",ret,s[i]);
	}
}



void decouper_expression() //decoupage de l'expression reguliere en petites expressions
{
	
	char* s;
	int i=0;
	
	if (regex[strlen(regex)-1]=='*') 
	{
	astr_fin=Vrai;
	} 
	else 
	{
	astr_fin=Faux;
	}
	if (regex[0]=='*') 
	{
	astr_debut=Vrai;
	} 
	else 
	{
	astr_debut=Faux;
	}	
	s = strtok(regex,"*");
	if (s!=NULL){
		exp_decoup[i++]=s; 
		while ((s = strtok(NULL,"*"))!=NULL)
		{
			exp_decoup[i++]=s;
		}	
	}
	taille_decoup=i;
}








booleen egalite(char* nom_fich) //teste l'egalité de noms
{
	char *result[512];
	int n=0,ind=0;
	char part_nom_fich[512];
	sprintf(part_nom_fich,"%s",nom_fich);
	int i=1;
	if(taille_decoup>0)
	{	
		ind = pointeur_debut(exp_decoup[0],part_nom_fich);
		
		if (ind<0) 
		{
		return Faux;
		}	
		if (!astr_debut && ind>0) 
		{
		return Faux;
		} 						
		sprintf(part_nom_fich,"%s",part_nom_fich+ind);
		while (i<n-1)
		{
			ind = pointeur_debut(exp_decoup[i],part_nom_fich);
			if (ind<0) 
			{
			return Faux;
			}
			sprintf(part_nom_fich,"%s",part_nom_fich+ind);
			i=i+1;
		}
		ind = pointeur_debut(exp_decoup[taille_decoup-1],part_nom_fich);
		if (ind<0) 
		{
		return Faux;
		}
		if (!astr_fin) 
		{
			sprintf(part_nom_fich,"%s",part_nom_fich+ind);		
			char ret[512]="";
			recuperer_derniers_caracteres(part_nom_fich,strlen(exp_decoup[taille_decoup-1]),ret);
			if (!egalite_partielle(exp_decoup[taille_decoup-1],ret)) 
			{
			return Faux;
			}
		}
		return Vrai; 
	}
	else
	{
		if (astr_debut && astr_fin)
		{
		 return Vrai;
		}
		return Faux;
	}
}






void permission(char *chemin_fich,char* perm)//affiche les permissions du fichier
{	
	int i=0;
	strcpy(perm,"----------");
	struct stat info_fich;
	stat(chemin_fich, &info_fich);
	mode_t mode = info_fich.st_mode;
	if (S_ISDIR(mode)) perm[0]='d';
	if ((mode & S_IRUSR) == S_IRUSR) perm[1]='r';
	if ((mode & S_IWUSR) == S_IWUSR) perm[2]='w';
	if ((mode & S_IXUSR) == S_IXUSR) perm[3]='x';
	if ((mode & S_IRGRP) == S_IRGRP) perm[4]='r';
	if ((mode & S_IWGRP) == S_IWGRP) perm[5]='w';
	if ((mode & S_IXGRP) == S_IXGRP) perm[6]='x';
	if ((mode & S_IROTH) == S_IROTH) perm[7]='r';
	if ((mode & S_IWOTH) == S_IWOTH) perm[8]='w';
	if ((mode & S_IXOTH) == S_IXOTH) perm[9]='x';    	
	
}




void afficher_sans_stats(char *chemin_fich) //affichage sans détails
 {

if (p_option) printf("%10s", "----------  ");
if (t_option)  printf("%4s  ","!!!!");
if (s_option) printf("%9s   ","!!!!");
if (d_option) printf ("%6s ---%10s"," ","  ");
if (m_option) printf("%6s ---%10s"," ","  ");
printf("%s --- On a pas pu avoir les informations du fichier : %s \n",chemin_fich,strerror(errno));
}



char fichier_type(char *chemin_fich)//affiche le type du fichier
{
	char ret='-';
	struct stat info_fich;
	stat(chemin_fich, &info_fich);
	if (S_ISREG(info_fich.st_mode)) ret='-';
	else if (S_ISFIFO(info_fich.st_mode)) ret='p';
	else if (S_ISCHR(info_fich.st_mode)) ret='c';
	else if (S_ISBLK(info_fich.st_mode)) ret='b';
	else if (S_ISDIR(info_fich.st_mode)) ret='d';
	else if (S_ISLNK(info_fich.st_mode)) ret='l';
	else if (S_ISSOCK(info_fich.st_mode)) ret='s';
	return ret;
}



void afficher_details(char *chemin_fich)//affichage avec détails
{
	char chemin_absolu[512];
	char fich_string[512];
	struct stat info_fich;
	stat(chemin_fich, &info_fich);


if (p_option) 
       {
		int i=0;
		char permission_fich[11]="";
		mode_t mode = info_fich.st_mode;
		permission(chemin_fich,permission_fich);
		printf("%10s  ",permission_fich);
	}	

if (t_option) 
       {
		char t = fichier_type(chemin_fich);
		if (t=='-') strcpy(fich_string,"REGU");
		else if (t=='p') strcpy(fich_string,"FIFO");
		else if (t=='c') strcpy(fich_string,"MCAR");
		else if (t=='b') strcpy(fich_string,"BLOCK");
		else if (t=='d') strcpy(fich_string,"REPR");
		else if (t=='l') strcpy(fich_string,"LIEN");
		else if (t=='s') strcpy(fich_string,"SOCK");
		printf("%4s  ",fich_string);
	}

if (s_option) 
       {
		long taille=info_fich.st_size;
		if ( (taille/1024) <1 ) printf("%6ld oc   ",taille);
		else if (( (taille/1024)/1024) <1 ) printf("%6.2f Ko   ", (float)taille/(float)1024);
		else printf("%6.2f Mo   ",(float)taille/(float)1024/(float)1024);
	}	

if (d_option) 
        {
		afficher_temps(info_fich.st_atime);
	}
if (m_option) 
        {
		afficher_temps(info_fich.st_mtime);
	}
    printf("%s",chemin_fich);
    printf("\n");
	
}  



int analyse_arguments(int argc, char * argv[], char* chemin)//analyse des arguments
{

	char c;
	char chaine[256];
	int ind=1;
	if (argc >2 && argv[1][0]!='-' ) 	
	{		
		strcpy(chemin,argv[1]); 
		ind =2;	
	}
	else 
	{
	strcpy(chemin,".");
	}
	strcpy(regex,argv[argc-1]);	
	while (ind<argc-1) 
	{
		if (argv[ind][0]=='-') 
		{
			sprintf(chaine,"%s",argv[ind]+1);
			if (strlen(chaine)==1) 
			{
				c=chaine[0];	
				switch(c) 
				{
					case 'd':
						d_option=1;
					break;
					case 'm':
						m_option=1;
					break;
					case 's':
						s_option=1;
					break;
					case 't':
						t_option=1;
					break;
					case 'p':
						p_option=1;
					break;
					case 'a':
						d_option=1; m_option=1; s_option=1; t_option=1; p_option=1;
					break;
					default:
					if (atoi(chaine)!=0 ) 
					{
					profondeur=atoi(chaine);
					}
					else
					{
						if (chaine[0]=='0') 
						{
						profondeur=0;
						}
						else 
						{
						return -ind-1;
						}
					}
					break;		
				}
				}
				else 
				{
					int i=0;	
					if (atoi(chaine)!=0 )
					{
					 profondeur=atoi(chaine);
					}				
					else for (i=0;i<strlen(chaine);i++)
					{
						if (chaine[i]!='0') return -ind-1;					
					}					
				}
			}
		ind++;	
		}	
	return 0;
}




int parcourir(char * chemin,int niveau) //parcours de l'hiérarchie
{
       char chemin_fich[512];
       struct dirent * entry = NULL;
       struct stat info_fich ;
	DIR *dir = NULL;
        
     

        if ( (dir = opendir(chemin)) == NULL) 
        {
		perror(chemin);
                return 0;
        }

         while (entry = readdir(dir)) 
         {
             if (chemin[strlen(chemin)-1]!='/')
            {
              strcat(chemin,"/");
            }
            sprintf(chemin_fich,"%s%s", chemin, entry -> d_name);
        

            if (stat(chemin_fich, &info_fich) == -1) 
              {      
			if (egalite(entry->d_name)) 
			{                        
			      if (!entete) 
			       { 
					afficher_entete();
					entete=1;
				}			
			afficher_sans_stats(chemin_fich);
			}                        
			continue;
                }
           if (S_ISDIR(info_fich.st_mode)) 
           {
                   
                    if (strcmp(entry -> d_name, ".") == 0 ||strcmp(entry -> d_name, "..") == 0) continue; 

					   
					    if (niveau==-1)
					    {					
	 				      parcourir(chemin_fich,niveau);
			    	            }
					    else if (niveau>0)
					    {
						parcourir(chemin_fich,niveau-1);	
					    }
            }
        
			if (egalite(entry->d_name)) 
			{
				if (!entete) 
				{ 
					afficher_entete();
					entete=1;
				}
				afficher_details(chemin_fich); 
				nb_resultats++; 
			}
        }
        closedir(dir);
        return 1;
}







int main (int argc, char * argv[])//programme principale
{
               char chemin[512];
               //affichage_binome(); 		
		if (argc == 1) 
		{
			
			//Documentation();		
		}
		else 
		{
			int err = analyse_arguments(argc, argv,chemin);					
			if (err<0) 
			{
				Erreur(err,argv);	
			}
			else 
			{	
				decouper_expression();								
				int fsd = parcourir(chemin,profondeur);
				if (fsd) 
				{
				afficher_resultats(argc,argv);
				}
			}
		}		
	return 0;
}
