#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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
    fprintf(f, "%d \n", terrain_jeu_espace->taille_espace_x);
    fprintf(f, "%d \n", terrain_jeu_espace->taille_espace_y);
    for(i=0;i<terrain_jeu_espace->taille_espace_x;i++)
    {
        for(j=0;j<terrain_jeu_espace->taille_espace_y;j++)
        {
           fprintf(f, "%c", terrain_jeu_espace->tab_terrain_espace[i*(terrain_jeu_espace->taille_espace_y)+j].type_case_terrain_espace);
        }
        fprintf(f, "\n");
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
    fprintf(f, "%d \n", une_unite->pt_mouvement_unite);
    fprintf(f, "FinUnite\n");
    fclose(f);
}
void ouverture_terrain(FILE *f, long a)
{
    fseek (f, a, SEEK_SET);
    Terrain_espace *terrain_ouvert;
    char chaine[50], carre[1];
    int b, c;
    int i = 0;
    int j = 0;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    sscanf(fgets(chaine, 50, f), "%d", &c);
    terrain_ouvert = creer_terrain_espace(b, c);
    while (j != c) {
        fgets(carre, 2, f);
        if(strcmp(carre, "\n") == 0)
        {
            j++;
            i = 0;
        }
        else
        {
            modifie_type_case_terrain_espace(terrain_ouvert, i, j, carre[0]);
            i++;
        }
    }
}
void selection_ouverture(const char nom[30], long a)
{
    FILE *f;
    char chaine[50];
    f = fopen(nom, "r");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    fseek (f, a, SEEK_SET);
    fgets(chaine, 50, f);
    a = ftell(f);
    printf("%ld \n", a);
    printf(chaine);
    if (strcmp(chaine, "Terrain \n")==0)
    {
        printf("%s \n","GENIAL Terrain");
        ouverture_terrain(f, a);
    }
    if (strcmp(chaine, "Planete \n")==0)
    {
        printf("%s \n","GENIAL Planete");
    }
    if (strcmp(chaine, "Flotte \n")==0)
    {
        printf("%s \n","GENIAL Flotte");
    }
    if (strcmp(chaine, "Unite \n")==0)
    {
        printf("%s \n","GENIAL Unite");
    }
    fclose(f);
}
