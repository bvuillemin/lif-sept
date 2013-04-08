#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "terrain_espace.h"
#include "planete.h"
#include "flotte.h"
#include "unite.h"
#include "niveau.h"
#include "sauvegarde.h"

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
Terrain_espace* ouverture_terrain(FILE *f, long a)
{
    Terrain_espace* terrain_ouvert;
    char chaine[50], carre[1];
    int b, c;
    int i = 0;
    int j = 0;
    fseek (f, a, SEEK_SET);
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
    return terrain_ouvert;
}

Planete* ouverture_planete(FILE *f, long a)
{
    Planete* planete_ouverte;
    char chaine[50];
    int b, c;
    fseek (f, a, SEEK_SET);
    fgets(chaine, 50, f);
    planete_ouverte = creer_planete(chaine);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    sscanf(fgets(chaine, 50, f), "%d", &c);
    set_position_planete(planete_ouverte, b, c);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_taille_utilisee(planete_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_taille_planete(planete_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_habitabilite(planete_ouverte, b);
    if (sscanf(fgets(chaine, 50, f), "%d", &b) == 1)
    {
        set_planete_principale(planete_ouverte, 1);
    }
    else
    {
        set_planete_principale(planete_ouverte, 0);
    };
    if (sscanf(fgets(chaine, 50, f), "%d", &b) == 1)
    {
        set_planete_colonisee(planete_ouverte, 1);
    }
    else
    {
        set_planete_colonisee(planete_ouverte, 0);
    };
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_metal(planete_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_argent(planete_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_carburant(planete_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_population(planete_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    return planete_ouverte;
}

Flotte* ouverture_flotte(FILE *f, long a)
{
    Flotte* flotte_ouverte;
    char chaine[50];
    int b;
    fseek (f, a, SEEK_SET);
    flotte_ouverte = creer_flotte();
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_x_flotte(flotte_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_y_flotte(flotte_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_pt_mouvement_espace_flotte(flotte_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    return flotte_ouverte;
}

Unite* ouverture_unite(FILE *f, long a)
{
    Unite* unite_ouverte;
    char chaine[50];
    int b, c, d, e, g, h, k;
    fseek (f, a, SEEK_SET);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    sscanf(fgets(chaine, 50, f), "%d", &c);
    sscanf(fgets(chaine, 50, f), "%d", &d);
    sscanf(fgets(chaine, 50, f), "%d", &e);
    sscanf(fgets(chaine, 50, f), "%d", &g);
    sscanf(fgets(chaine, 50, f), "%d", &h);
    sscanf(fgets(chaine, 50, f), "%d", &k);
    unite_ouverte = creer_unite(b, c, d, e, g, h, k);
    return unite_ouverte;
}

/* Niveau* ouverture_niveau(FILE *f, long a)
{
    Niveau* niveau_ouvert;
    char chaine[50];
    int b, c;
    fseek (f, a, SEEK_SET);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    sscanf(fgets(chaine, 50, f), "%d", &c);
    niveau_ouvert = creer_niveau(b, c);
    return niveau_ouvert;
}*/

Terrain_espace* selection_ouverture(const char nom[30], long a)
{
    Terrain_espace* terrain_ouvert = NULL;
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
    printf("%s", chaine);
    if (strcmp(chaine, "Terrain \n")==0)
    {
        printf("%s \n","GENIAL Terrain");
        terrain_ouvert = ouverture_terrain(f, a);
        printf("%ld", a);
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
    return terrain_ouvert;
}

/*int selection_ouverture(const char nom[30], long a)
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
    printf("%s", chaine);
    if (strcmp(chaine, "Terrain \n")==0)
    {
        return 1;
    }
    if (strcmp(chaine, "Planete \n")==0)
    {
        return 2;
    }
    if (strcmp(chaine, "Flotte \n")==0)
    {
        return 3;
    }
    if (strcmp(chaine, "Unite \n")==0)
    {
        return 4;
    }
    fclose(f);
}*/