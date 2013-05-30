/**
 * \file      case_terrain_espace.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les cases d'un terrain d'espace
 * \details   Cette classe définit les cases d'un terrain d'espace et leurs caractéristiques
 */

#include "case_terrain_espace.h"


/************************************************************************/
/* Initialisation, création et destruction                              */
/************************************************************************/

void initialiser_case_espace(Case_terrain_espace *une_case_terrain_espace)
{
    une_case_terrain_espace->x_espace=0;
    une_case_terrain_espace->y_espace=0;
    une_case_terrain_espace->type_case_terrain_espace='N';
    une_case_terrain_espace->presence_flotte= false;
	une_case_terrain_espace->planete = NULL;
	une_case_terrain_espace->flotte = NULL;
}

Case_terrain_espace *creer_case_espace()
{
    Case_terrain_espace *une_case_terrain_espace=(Case_terrain_espace *)malloc(sizeof(Case_terrain_espace));
    initialiser_case_espace(une_case_terrain_espace);
    return une_case_terrain_espace;
}

void liberer_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace)
{
    /*if(une_case_terrain_espace->presence_flotte == true)
    {
        detruire_flotte(&(une_case_terrain_espace->flotte));
        une_case_terrain_espace->presence_flotte = false;
    }*/
    if(une_case_terrain_espace->type_case_terrain_espace == 'P')
    {
        detruire_planete(&(une_case_terrain_espace->planete));
    }
    une_case_terrain_espace->x_espace=0;
    une_case_terrain_espace->y_espace=0;
	une_case_terrain_espace->presence_flotte= false;
	/*une_case_terrain_espace->est_visible = false;*/
    une_case_terrain_espace->type_case_terrain_espace='N';
}

void detruire_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace)
{
    liberer_case_terrain_espace(une_case_terrain_espace);
    free(une_case_terrain_espace);
    une_case_terrain_espace = NULL;
}


/************************************************************************/
/* Fonctions set et get                                                 */
/************************************************************************/

void set_x_espace(Case_terrain_espace *une_case_terrain_espace, int x)
{
    une_case_terrain_espace->x_espace = x;
}
int get_x_espace(const Case_terrain_espace *une_case_terrain_espace)
{
    return une_case_terrain_espace->x_espace;
}
void set_y_espace(Case_terrain_espace *une_case_terrain_espace, int y)
{
    une_case_terrain_espace->y_espace = y;
}
int get_y_espace(const Case_terrain_espace *une_case_terrain_espace)
{
    return une_case_terrain_espace->y_espace;
}
void set_type_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace, char type)
{
	une_case_terrain_espace->type_case_terrain_espace = type;
}
char get_type_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace)
{
	return une_case_terrain_espace->type_case_terrain_espace;
}
Planete * get_planete(Case_terrain_espace *une_case_terrain_espace)
{
	return une_case_terrain_espace->planete;
}
Flotte * get_flotte(Case_terrain_espace *une_case_terrain_espace)
{
	return une_case_terrain_espace->flotte;
}
bool get_presence_flotte(Case_terrain_espace* une_case)
{
	return une_case->presence_flotte;
}


/************************************************************************/
/* Fonctions                                                            */
/************************************************************************/

void definir_case_terrain_espace(Case_terrain_espace *une_case_terrain_espace, char c)
{
    if((c == 'E')||(c == 'F')||(c == 'P'))
    {
        c = get_type_case_terrain_espace(une_case_terrain_espace);
    }
}

void affiche_case_terrain_espace(const Case_terrain_espace *une_case_terrain_espace)
{
    printf("|%c|", une_case_terrain_espace->type_case_terrain_espace);
}

void ajouter_planete(Case_terrain_espace *une_case_terrain_espace, Planete *une_planete)
{
    une_case_terrain_espace->type_case_terrain_espace = 'P';
    une_case_terrain_espace->planete = une_planete;
    une_case_terrain_espace->planete->x = une_case_terrain_espace->x_espace;
    une_case_terrain_espace->planete->y = une_case_terrain_espace->y_espace;
}

void ajouter_flotte(Case_terrain_espace *une_case_terrain_espace, Flotte *une_flotte)
{
    une_case_terrain_espace->flotte = une_flotte;
    une_case_terrain_espace->presence_flotte = true;
    une_case_terrain_espace->flotte->x_flotte = une_case_terrain_espace->x_espace;
    une_case_terrain_espace->flotte->y_flotte = une_case_terrain_espace->y_espace;
}

void retirer_flotte(Case_terrain_espace *une_case_terrain_espace)
{
    une_case_terrain_espace->flotte = NULL;
    une_case_terrain_espace->presence_flotte = false;
}

void test_module_case_terrain_espace()
{
    Case_terrain_espace *une_case_terrain_espace;
    printf("Verif de la création de cases\n");
    une_case_terrain_espace = creer_case_espace();
    definir_case_terrain_espace(une_case_terrain_espace, 'E');
    affiche_case_terrain_espace(une_case_terrain_espace);
    if((une_case_terrain_espace->x_espace == 0) && (une_case_terrain_espace->y_espace == 0))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}
}

/************************************************************************/
/* Fonctions sauvegarde et chargement                                   */
/************************************************************************/

void sauvegarde_case_terrain_espace(const Case_terrain_espace *une_case_terrain_espace, FILE*f)
{
    fprintf(f, "%d\n", une_case_terrain_espace->x_espace);
    fprintf(f, "%d\n", une_case_terrain_espace->y_espace);
    fprintf(f, "%s\n", &une_case_terrain_espace->type_case_terrain_espace);
    fprintf(f, "%d\n", une_case_terrain_espace->presence_flotte);
    if (une_case_terrain_espace->planete != NULL) {
        sauvegarde_planete(une_case_terrain_espace->planete, f);
    }
    if (une_case_terrain_espace->presence_flotte == true) {
        sauvegarde_flotte(une_case_terrain_espace->flotte, f);
    }
    fprintf(f, "FinCase\n");
}

Case_terrain_espace* ouverture_case_terrain_espace(FILE*f)
{
    Case_terrain_espace *case_terrain_espace_ouverte=creer_case_espace();
    char chaine[50];
    int b;
    sscanf(fgets(chaine, 50, f), "%d", &case_terrain_espace_ouverte->x_espace);
    sscanf(fgets(chaine, 50, f), "%d", &case_terrain_espace_ouverte->y_espace);
    fgets(chaine, 50, f);
    case_terrain_espace_ouverte->type_case_terrain_espace = chaine[0];
    sscanf(fgets(chaine, 50, f), "%d", &b);
    case_terrain_espace_ouverte->presence_flotte = b;
    fgets(chaine, 50, f);
    if (strcmp(chaine, "Planete\n")==0)
    {
        case_terrain_espace_ouverte->planete = ouverture_planete(f);
        fgets(chaine, 50, f);
    }
    if (strcmp(chaine, "Flotte\n")==0)
    {
        case_terrain_espace_ouverte->flotte = ouverture_flotte(f);
        fgets(chaine, 50, f);
    }
    return case_terrain_espace_ouverte;
}