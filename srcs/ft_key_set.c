#include "../includes/cub3d.h"

int	key_press(int key, t_info *data)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		data->key.key_w = 1;
	else if (key == K_A)
		data->key.key_a = 1;
	else if (key == K_S)
		data->key.key_s = 1;
	else if (key == K_D)
		data->key.key_d = 1;
	else if (key == K_AR_L)
		data->key.key_left = 1;
	else if (key == K_AR_R)
		data->key.key_right = 1;
	return (0);
}

int	key_release(int key, t_info *data)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		data->key.key_w = 0;
	else if (key == K_A)
		data->key.key_a = 0;
	else if (key == K_S)
		data->key.key_s = 0;
	else if (key == K_D)
		data->key.key_d = 0;
	else if (key == K_AR_L)
		data->key.key_left = 0;
	else if (key == K_AR_R)
		data->key.key_right = 0;
	return (0);
}

int	key_update(t_info *data)
{
	// front
	if (data->key.key_w)
	{
		if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos + data->dirX * MOVE_SPEED)] == '0')
			data->p_xpos += data->dirX * MOVE_SPEED;
		if (data->map[(int)(data->p_ypos + data->dirY * MOVE_SPEED)][(int)(data->p_xpos)] == '0')
			data->p_ypos += data->dirY * MOVE_SPEED;
	}
	
	// back
	if (data->key.key_s)
	{
		if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos - data->dirX * MOVE_SPEED)] == '0')
			data->p_xpos -= data->dirX * MOVE_SPEED;
		if (data->map[(int)(data->p_ypos - data->dirY * MOVE_SPEED)][(int)(data->p_xpos)] == '0')
			data->p_ypos -= data->dirY * MOVE_SPEED;
	}

	if (data->key.key_d)
	{
		if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos + data->planeX * MOVE_SPEED)] == '0')
			data->p_xpos += data->planeX * MOVE_SPEED;
		if (data->map[(int)(data->p_ypos + data->planeY * MOVE_SPEED)][(int)(data->p_xpos)] == '0')
			data->p_ypos += data->planeY * MOVE_SPEED;
	}

	if (data->key.key_a)
	{
		if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos - data->planeX * MOVE_SPEED)] == '0')
			data->p_xpos -= data->planeX * MOVE_SPEED;
		if (data->map[(int)(data->p_ypos - data->planeY * MOVE_SPEED)][(int)(data->p_xpos)] == '0')
			data->p_ypos -= data->planeY * MOVE_SPEED;
	}

	if (data->key.key_left)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(-ROT_SPEED) - data->dirY * sin(-ROT_SPEED);
		data->dirY = oldDirX * sin(-ROT_SPEED) + data->dirY * cos(-ROT_SPEED);

		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(-ROT_SPEED) - data->planeY * sin(-ROT_SPEED);
		data->planeY = oldPlaneX * sin(-ROT_SPEED) + data->planeY * cos(-ROT_SPEED);
	}
	
	if (data->key.key_right)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(ROT_SPEED) - data->dirY * sin(ROT_SPEED);
		data->dirY = oldDirX * sin(ROT_SPEED) + data->dirY * cos(ROT_SPEED);

		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(ROT_SPEED) - data->planeY * sin(ROT_SPEED);
		data->planeY = oldPlaneX * sin(ROT_SPEED) + data->planeY * cos(ROT_SPEED);
	}
	return (0);
}