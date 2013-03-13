#ifndef _CASE_H_
#define _CASE_H_

#include <stdlib.h>
#include <stdio.h>


/**
 * \file      Module case
 * \author    Les queux de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Case et ses particularités
 *
 * \details
 */

typedef struct
{
    int x,y;
    int type_terrain; // Quel type mettre?
    int presence_unite;
}case;

void set_x(case case_terrain, int x);
int get_x(case case_terrain);

void set_y(case case_terrain, int y);
int get_y(case case_terrain);



#endif
