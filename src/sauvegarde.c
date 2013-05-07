#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "terrain_espace.h"
#include "planete.h"
#include "flotte.h"
#include "unite.h"
#include "niveau.h"
#include "sauvegarde.h"

void initialise_sauvegarde(Sauvegarde *une_sauvegarde)
{
    une_sauvegarde->terrain_espace =(Terrain_espace *)malloc(sizeof(Terrain_espace));
    une_sauvegarde->nb_planete = 0;
    une_sauvegarde->tab_planete =(Planete *)malloc(sizeof(Planete) * 10);
    une_sauvegarde->nb_flotte =0;
    une_sauvegarde->tab_flotte =(Flotte *)malloc(sizeof(Flotte) * 10);
}
Sauvegarde *creer_sauvegarde()
{
    Sauvegarde *une_sauvegarde=(Sauvegarde *)malloc(sizeof(Sauvegarde));
    initialise_sauvegarde(une_sauvegarde);
    return une_sauvegarde;
}
void ajouter_terrain_espace_sauvegarde(Sauvegarde *une_sauvegarde, Terrain_espace *un_terrain_espace)
{
    une_sauvegarde->terrain_espace = un_terrain_espace;
}
void ajouter_planete_sauvegarde(Sauvegarde *une_sauvegarde, Planete *une_planete)
{
    int i;
	i = une_sauvegarde->nb_planete;
	if(une_sauvegarde->nb_planete < 10)
	{
		une_sauvegarde->tab_planete[i] = *une_planete;
		une_sauvegarde->nb_planete ++;
	}
}
void ajouter_flotte_sauvegarde(Sauvegarde *une_sauvegarde, Flotte *une_flotte)
{
    int i;
	i = une_sauvegarde->nb_flotte;
	if((une_sauvegarde->nb_flotte) < 10)
	{
		une_sauvegarde->tab_flotte[i] = *une_flotte;
		une_sauvegarde->nb_flotte++;
	}
}
void creer_fichier_sauvegarde(const char nom[30], Terrain_espace *un_terrain_espace)
{
    FILE *f;
    f = fopen(nom, "w");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    sauvegarde_terrain_espace(un_terrain_espace, f);
    fclose(f);
}
void detruire_sauvegarde(const char nom[30])
{
    FILE *f;
    f = fopen(nom, "w");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    fclose(f);
}

Terrain_espace* selection_ouverture(const char nom[30])
{
    FILE *f;
	char chaine[50];
    Terrain_espace *une_sauvegarde = (Terrain_espace *)malloc(sizeof(Terrain_espace));
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
    printf("%s", chaine);
    if (strcmp(chaine, "Terrain_Espace\n")==0)
    {
        //Terrain_espace* un_terrain_espace;
        une_sauvegarde = ouverture_terrain(f);
        //fgets(chaine, 50, f);
        
        //ajouter_terrain_espace_sauvegarde(une_sauvegarde, un_terrain_espace);
    }
    }
    fclose(f);
    return une_sauvegarde;
}
