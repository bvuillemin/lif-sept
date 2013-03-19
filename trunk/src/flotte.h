#ifndef _FLOTTE_H_
#define _FLOTTE_H_

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
     int taille_maximum_flotte;
     int taille_flotte;
     Unite *tab_unite[taille_maximum_flotte];
 }Flotte;

void initialise_flotte(Flotte *flotte);
Flotte *creer_flotte();
