#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "terrain_espace.h"

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
void sauvegarde_terrain(const Terrain_espace *terrain_jeu_espace, const char nom[30])
{
    FILE *f;
    int i,j;
    f = fopen(nom, "a");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    fprintf(f, "Terrain \n");
    for(i=0;i<terrain_jeu_espace->taille_espace_x;i++)
    {
        fprintf(f, "#");
        for(j=0;j<terrain_jeu_espace->taille_espace_y;j++)
        {
           fprintf(f,"%c", terrain_jeu_espace->tab_terrain_espace[i*(terrain_jeu_espace->taille_espace_y)+j].type_case_terrain_espace);
        }
        fprintf(f, "#\n");
    }
    fprintf(f, "FinTerrain\n");
    fclose(f);
}
void sauvegarde_planete(const Planete *une_planete, const char nom[30])
{
    FILE *f;
    f = fopen(nom, "a");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    fprintf(f, "Planete \n");
    fprintf(f, "%s \n", une_planete->nom_planete);
    fprintf(f, "%d \n", une_planete->x);
    fprintf(f, "%d \n", une_planete->y);
    fprintf(f, "%d \n", une_planete->taille_utilisee);
    fprintf(f, "%d \n", une_planete->taille_planete);
    fprintf(f, "%d \n", une_planete->planete_colonisee);
    fprintf(f, "%d \n", une_planete->planete_principale);
    fprintf(f, "FinPlanete\n");
    fclose(f);
}
void sauvegarde_flotte(const Flotte *une_flotte, const char nom[30])
{
    FILE *f;
    f = fopen(nom, "a");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    fprintf(f, "Flotte \n");
    fprintf(f, "%d \n", une_flotte->x_flotte);
    fprintf(f, "%d \n", une_flotte->y_flotte);
    fprintf(f, "%d \n", une_flotte->taille_maximum_flotte);
    fprintf(f, "%d \n", une_flotte->taille_flotte);
    fprintf(f, "%d \n", une_flotte->pt_mouvement_espace_flotte);
    fprintf(f, "FinFlotte\n");
    fclose(f);
}
void sauvegarde_unite(const Unite *une_unite, const char nom[30])
{
    FILE *f;
    f = fopen(nom, "a");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    fprintf(f, "Unite \n");
    fprintf(f, "%d \n", une_unite->x_unite);
    fprintf(f, "%d \n", une_unite->y_unite);
    fprintf(f, "%d \n", une_unite->pt_vie);
    fprintf(f, "%d \n", une_unite->pt_attaque);
    fprintf(f, "%d \n", une_unite->pt_action);
    fprintf(f, "%d \n", une_unite->pt_deplacement);
    fprintf(f, "%d \n", une_unite->pt_mouvement_espace);
    fprintf(f, "FinUnite\n");
    fclose(f);
}
void ouverture_terrain(const char nom[30])
{
    FILE *f;
    char chaine[256];
    f = fopen(nom, "r");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    rewind(f);
    fgets(chaine, 256, f);
    if (strcmp(chaine, "Terrain")==1) {
        printf("%s","GENIAL");
    }
    else {printf("%s","BOUH");} 
    fclose(f);
}