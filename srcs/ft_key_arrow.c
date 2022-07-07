#include "../includes/cub3d.h"

void	ft_key_arrow_left(t_info *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y * sin(-ROT_SPEED);
	data->dir_y = old_dir_x * sin(-ROT_SPEED) + data->dir_y * cos(-ROT_SPEED);
	data->plane_x = data->plane_x * cos(-ROT_SPEED)
		- data->plane_y * sin(-ROT_SPEED);
	data->plane_y = old_plane_x * sin(-ROT_SPEED)
		+ data->plane_y * cos(-ROT_SPEED);
}

void	ft_key_arrow_right(t_info *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y * sin(ROT_SPEED);
	data->dir_y = old_dir_x * sin(ROT_SPEED) + data->dir_y * cos(ROT_SPEED);
	data->plane_x = data->plane_x * cos(ROT_SPEED)
		- data->plane_y * sin(ROT_SPEED);
	data->plane_y = old_plane_x * sin(ROT_SPEED)
		+ data->plane_y * cos(ROT_SPEED);
}
