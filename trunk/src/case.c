#include <stdlib.h>
#include <stdio.h>
#include "case.h"

void set_x(Case_terrain case_terrain, int x)
{
    case_terrain.x = x;
}

int get_x(Case_terrain case_terrain)
{
    return case_terrain.x;
}

void set_y(Case_terrain case_terrain, int y)
{
    case_terrain.y = y;
}

int get_y(Case_terrain case_terrain)
{
    return case_terrain.y;
}
