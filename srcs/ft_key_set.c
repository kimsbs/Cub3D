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
	if (data->key.key_w)
		update_w(data);
	if (data->key.key_s)
		update_s(data);
	if (data->key.key_d)
		update_d(data);
	if (data->key.key_a)
		update_a(data);
	if (data->key.key_left)
		ft_key_arrow_left(data);
	if (data->key.key_right)
		ft_key_arrow_right(data);
	return (0);
}

void	init_key_false(t_info *data)
{
	data->key.key_w = 0;
	data->key.key_s = 0;
	data->key.key_a = 0;
	data->key.key_d = 0;
	data->key.key_left = 0;
	data->key.key_right = 0;
}
