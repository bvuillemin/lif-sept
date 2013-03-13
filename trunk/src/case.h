#ifndef _CASE_H_
#define _CASE_H_

#include <stdlib.h>
#include <stdio.h>


/**
 * \file      Module case
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Case et ses particularités
 *
 * \details
 */

typedef struct
{
    int x,y;
    int type_case; // Quel type mettre?
    int presence_unite;
}Case_terrain;

void initialise_case(Case_terrain *case_terrain);
Case_terrain *creer_case();

void set_x(Case_terrain *case_terrain, int x);
int get_x(const Case_terrain *case_terrain);

void set_y(Case_terrain *case_terrain, int y);
int get_y(const Case_terrain *case_terrain);


#endif
