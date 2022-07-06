#include "../includes/cub3d.h"

void set_north(t_info* data)
{
    data->dirX = 0.0;
    data->dirY = -1.0;
    
    data->planeX = 0.66;
    data->planeY = 0.0;
}

void set_south(t_info* data)
{
    data->dirX = 0.0;
    data->dirY = 1.0;
    data->planeX = -0.66;
    data->planeY = 0.0;
}

void set_west(t_info* data)
{
    data->dirX = -1.0;
    data->dirY = 0.0;
    data->planeX = 0.0;
    data->planeY = -0.66;
}

void set_east(t_info* data)
{
    data->dirX = 1.0;
    data->dirY = 0.0;
    data->planeX = 0.0;
    data->planeY = 0.66;
}
