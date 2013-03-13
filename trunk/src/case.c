#include <stdlib.h>
#include <stdio.h>
#include "case.h"

void set_x(case case_terrain, int x)
{
    case_terrain.x = x;
}

int get_x(case case_terrain)
{
    return case_terrain.x;
}

void set_y(case case_terrain, int y)
{
    case_terrain.y = y;
}

int get_y(case case_terrain)
{
    return case_terrain.y;
}
