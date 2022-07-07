#include "../includes/cub3d.h"

void	ft_key_arrow_left(t_info *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dirX;
	old_plane_x = data->planeX;
	data->dirX = data->dirX * cos(-ROT_SPEED) - data->dirY * sin(-ROT_SPEED);
	data->dirY = old_dir_x * sin(-ROT_SPEED) + data->dirY * cos(-ROT_SPEED);
	data->planeX = data->planeX * cos(-ROT_SPEED)
		- data->planeY * sin(-ROT_SPEED);
	data->planeY = old_plane_x * sin(-ROT_SPEED)
		+ data->planeY * cos(-ROT_SPEED);
}

void	ft_key_arrow_right(t_info *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dirX;
	old_plane_x = data->planeX;
	data->dirX = data->dirX * cos(ROT_SPEED) - data->dirY * sin(ROT_SPEED);
	data->dirY = old_dir_x * sin(ROT_SPEED) + data->dirY * cos(ROT_SPEED);
	data->planeX = data->planeX * cos(ROT_SPEED)
		- data->planeY * sin(ROT_SPEED);
	data->planeY = old_plane_x * sin(ROT_SPEED)
		+ data->planeY * cos(ROT_SPEED);
}
