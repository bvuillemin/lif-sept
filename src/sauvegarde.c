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
    fprintf(f, "Terrain\n");
    fprintf(f, "%d\n", terrain_jeu_espace->taille_espace_x);
    fprintf(f, "%d\n", terrain_jeu_espace->taille_espace_y);
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
    fprintf(f, "Planete\n");
    fprintf(f, "%s\n", une_planete->nom_planete);
    fprintf(f, "%d\n", une_planete->x);
    fprintf(f, "%d\n", une_planete->y);
    fprintf(f, "%d\n", une_planete->taille_utilisee);
    fprintf(f, "%d\n", une_planete->taille_planete);
    fprintf(f, "%d\n", une_planete->habitabilite);
    fprintf(f, "%d\n", une_planete->planete_principale);
    fprintf(f, "%d\n", une_planete->planete_colonisee);
    fprintf(f, "%d\n", une_planete->metal);
    fprintf(f, "%d\n", une_planete->argent);
    fprintf(f, "%d\n", une_planete->carburant);
    fprintf(f, "%d\n", une_planete->population);
    fprintf(f, "FinPlanete\n");
    fclose(f);
}
void sauvegarde_flotte(const Flotte *une_flotte, const char nom[30])
{
    FILE *f;
    int i;
    f = fopen(nom, "a");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    fprintf(f, "Flotte\n");
    fprintf(f, "%d\n", une_flotte->x_flotte);
    fprintf(f, "%d\n", une_flotte->y_flotte);
    fprintf(f, "%d\n", une_flotte->taille_maximum_flotte);
    fprintf(f, "%d\n", une_flotte->taille_flotte);
    fprintf(f, "%d\n", une_flotte->pt_mouvement_espace_flotte);
    for(i=0; i<une_flotte->taille_flotte; i++)
    {
        sauvegarde_unite(&une_flotte->tab_unite[i], f);
    }
    fprintf(f, "FinFlotte\n");
    fclose(f);
}
void sauvegarde_unite(const Unite *une_unite, FILE* f)
{
    fprintf(f, "%d\n", une_unite->pt_vie);
    fprintf(f, "%d\n", une_unite->pt_attaque);
    fprintf(f, "%d\n", une_unite->pt_action);
    fprintf(f, "%d\n", une_unite->pt_deplacement);
    fprintf(f, "%d\n", une_unite->pt_mouvement_unite);
}
Terrain_espace* ouverture_terrain(FILE *f)
{
    Terrain_espace* terrain_ouvert;
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
    return terrain_ouvert;
}

Planete* ouverture_planete(FILE *f)
{
    Planete* planete_ouverte;
    char chaine[50];
    int b, c;
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
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_planete_principale(planete_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_planete_colonisee(planete_ouverte, b);
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

Flotte* ouverture_flotte(FILE *f)
{
    Flotte* flotte_ouverte;
    char chaine[50];
    int b, i;
    flotte_ouverte = creer_flotte();
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_x_flotte(flotte_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_y_flotte(flotte_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_taille_maximum_flotte(flotte_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_taille_flotte(flotte_ouverte, b);
    sscanf(fgets(chaine, 50, f), "%d", &b);
    set_pt_mouvement_espace_flotte(flotte_ouverte, b);
    for(i=0; i<flotte_ouverte->taille_flotte; i++)
    {
        flotte_ouverte->tab_unite[i] = *ouverture_unite(f);
    }
    return flotte_ouverte;
}

Unite* ouverture_unite(FILE *f)
{
    Unite* unite_ouverte;
    char chaine[50];
    int b, c, d, e, g;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    sscanf(fgets(chaine, 50, f), "%d", &c);
    sscanf(fgets(chaine, 50, f), "%d", &d);
    sscanf(fgets(chaine, 50, f), "%d", &e);
    sscanf(fgets(chaine, 50, f), "%d", &g);
    unite_ouverte = creer_unite(b, c, d, e, g);
    return unite_ouverte;
}

Sauvegarde* selection_ouverture(const char nom[30], long a)
{
    Sauvegarde* une_sauvegarde;
    une_sauvegarde = creer_sauvegarde();
    FILE *f;
    char chaine[50];
    f = fopen(nom, "r");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }
    fseek (f, a, SEEK_SET);
    if(fgetc(f)!=EOF)
    {
    fseek(f, -1, SEEK_CUR);
    fgets(chaine, 50, f);
    a = ftell(f);
    printf("%ld\n", a);
    printf("%s", chaine);
    if (strcmp(chaine, "Terrain\n")==0)
    {
        printf("%s\n","GENIAL Terrain");
        Terrain_espace* un_terrain_espace;
        un_terrain_espace = ouverture_terrain(f);
        fgets(chaine, 50, f);
        a = ftell(f);
        printf("%ld\n", a);
        une_sauvegarde = selection_ouverture(nom, a);
        ajouter_terrain_espace_sauvegarde(une_sauvegarde, un_terrain_espace);
    }
    else if (strcmp(chaine, "Planete\n")==0)
    {
        printf("%s\n","GENIAL Planete");
        Planete* une_planete;
        une_planete = ouverture_planete(f);
        fgets(chaine, 50, f);
        a = ftell(f);
        printf("%ld\n", a);
        une_sauvegarde = selection_ouverture(nom, a);
        ajouter_planete_sauvegarde(une_sauvegarde, une_planete);
    }
    else if (strcmp(chaine, "Flotte\n")==0)
    {
        printf("%s\n","GENIAL Flotte");
        Flotte* une_flotte;
        une_flotte = ouverture_flotte(f);
        fgets(chaine, 50, f);
        a = ftell(f);
        printf("%ld\n", a);
        une_sauvegarde = selection_ouverture(nom, a);
        ajouter_flotte_sauvegarde(une_sauvegarde, une_flotte);
    }
    }
    fclose(f);
    return une_sauvegarde;
}