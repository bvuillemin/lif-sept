/**
 * \file      sauvegarde.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit les sauvegardes du jeu
 * \details   Cette classe définit les sauvegardes du jeu et les chargements de sauvegardes
 */

#include <time.h>
#include "sauvegarde.h"

/************************************************************************/
/* Initialisation, création et destruction                              */
/************************************************************************/

void initialise_sauvegarde(Sauvegarde *une_sauvegarde)
{
    une_sauvegarde->terrain_espace = (Terrain_espace *)malloc(sizeof(Terrain_espace));
    une_sauvegarde->jeu = (Jeu *)malloc(sizeof(Jeu));
}
Sauvegarde *creer_sauvegarde()
{
    Sauvegarde *une_sauvegarde=(Sauvegarde *)malloc(sizeof(Sauvegarde));
    initialise_sauvegarde(une_sauvegarde);
    return une_sauvegarde;
}

void detruire_sauvegarde(const char nom[30])
{
    int i;
    i = remove(nom);
}

/************************************************************************/
/* Fonctions diverses                                                   */
/************************************************************************/

/**
 * \brief      Crée une sauvegarde
 * \details    Crée un fichier de sauvegarde à partir d'un nom et sauvegarde le jeu et le terrain_espace
 * \param      nom                 Nom de la sauvegarde
 * \param      un_terrain_espace   Terrain_espace à sauvegarder
 * \param      jeu                 Jeu à sauvegarder
 */
void creer_fichier_sauvegarde(const char nom[30], Terrain_espace *un_terrain_espace, Jeu *un_jeu)
{
    FILE *f;
    f = fopen(nom, "w");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    sauvegarde_terrain_espace(un_terrain_espace, f);
    sauvegarde_jeu(un_jeu, f);
    fclose(f);
}

/**
 * \brief      Charge une sauvegarde
 * \details    Charge une sauvegarde dans le jeu à partir d'un nom de fichier
 * \param      nom                 Nom de la sauvegarde
 */
Sauvegarde* selection_ouverture(const char nom[30])
{
    FILE *f;
	char chaine[50];
    Sauvegarde* une_sauvegarde;
    une_sauvegarde = creer_sauvegarde();
    f = fopen(nom, "r");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    fseek (f, 0, SEEK_SET);
    while(fgetc(f)!=EOF)
    {
        fseek(f, -1, SEEK_CUR);
        fgets(chaine, 50, f);
        if (strcmp(chaine, "Terrain_Espace\n")==0)
        {
            une_sauvegarde->terrain_espace = ouverture_terrain_espace(f);
        }
        fgets(chaine, 50, f);
        if (strcmp(chaine, "Jeu\n")==0)
        {
            une_sauvegarde->jeu = ouverture_jeu(f);
        }
        creer_vision_joueur(une_sauvegarde->jeu, une_sauvegarde->terrain_espace, 0);
    }
    fclose(f);
    return une_sauvegarde;
}
