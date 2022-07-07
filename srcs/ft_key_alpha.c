#include "../includes/cub3d.h"

void	update_w(t_info *data)
{
	if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos + data->dirX * MOVE_SPEED)] == '0')
		data->p_xpos += data->dirX * MOVE_SPEED;
	if (data->map[(int)(data->p_ypos + data->dirY * MOVE_SPEED)][(int)(data->p_xpos)] == '0')
		data->p_ypos += data->dirY * MOVE_SPEED;
}

void	update_s(t_info *data)
{
	if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos - data->dirX * MOVE_SPEED)] == '0')
		data->p_xpos -= data->dirX * MOVE_SPEED;
	if (data->map[(int)(data->p_ypos - data->dirY * MOVE_SPEED)][(int)(data->p_xpos)] == '0')
		data->p_ypos -= data->dirY * MOVE_SPEED;
}

void	update_a(t_info *data)
{
	if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos - data->planeX * MOVE_SPEED)] == '0')
		data->p_xpos -= data->planeX * MOVE_SPEED;
	if (data->map[(int)(data->p_ypos - data->planeY * MOVE_SPEED)][(int)(data->p_xpos)] == '0')
		data->p_ypos -= data->planeY * MOVE_SPEED;
}

void	update_d(t_info *data)
{
	if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos + data->planeX * MOVE_SPEED)] == '0')
		data->p_xpos += data->planeX * MOVE_SPEED;
	if (data->map[(int)(data->p_ypos + data->planeY * MOVE_SPEED)][(int)(data->p_xpos)] == '0')
		data->p_ypos += data->planeY * MOVE_SPEED;
}
