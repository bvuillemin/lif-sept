#ifndef _PLANETE_H_
#define _PLANETE_H_

#include <stdlib.h>
#include <stdio.h>

/**
 * \file      Module terrain
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Planète et ses particularités
 *
 * \details
 */

 typedef struct
 {
     int id_planete;
     char *nom_planete;
     /*lien sur proprietaire
     tab de batiments
     ressources produites*/
     int taille_utilisee;
     int taille_planete;
     int planete_principale; /*1 si oui, 0 sinon (booléen?)*/
     int planete_colonise; /*1 si oui, 0 sinon  (booléen?)*/

 }Planete;

void initialise_planete(Planete *planete, int id);
Planete *creer_planete(int id);


void set_nom_planete(Planete *planete, char nom[30]);

void test_module_planete();



#endif
