#include "../mlx/mlx.h"
#include "../includes/cub3d.h"

int	key_update(t_info* data);

void	calc(t_info *data)
{
	int	x;
	int y;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		double cameraX = 2 * x / (double)WIN_WIDTH - 1;

		double rayDirY = data->dirY + data->planeY * cameraX;
		double rayDirX = data->dirX + data->planeX * cameraX;
		
		int mapY = (int)data->p_ypos;
		int mapX = (int)data->p_xpos;
		
		//length of ray from current position to next x or y-side
		double sideDistY;
		double sideDistX;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistY = fabs(1 / rayDirY);
		double deltaDistX = fabs(1 / rayDirX);
		
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepY;
		int stepX;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->p_xpos - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->p_xpos) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->p_ypos - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->p_ypos) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (data->map[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - data->p_xpos + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - data->p_ypos + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(WIN_HEIGTH / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + WIN_HEIGTH / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGTH / 2;
		if (drawEnd >= WIN_HEIGTH)
			drawEnd = WIN_HEIGTH - 1;

		int texNum;
		if (side == 1 && rayDirY < 0)
			texNum = 0;
			// N
		else if (side == 1 && rayDirY > 0)
			texNum = 1;
			// S
		else if (side == 0 && rayDirX < 0)
			texNum = 2;
			// W
		else if (side == 0 && rayDirX > 0)
			texNum = 3;
			// E
		double wallX;
		if (side == 0)
			wallX = data->p_ypos + perpWallDist * rayDirY;
		else
			wallX = data->p_xpos + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)TEXT_WIDTH);
		if (side == 0 && rayDirX > 0)
			texX = TEXT_WIDTH - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = TEXT_WIDTH - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * TEXT_HEIGTH / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - WIN_HEIGTH / 2 + lineHeight / 2) * step;
		y = drawStart;
		while (y < drawEnd)
		{
			// Cast the texture coordinate to integer, and mask with (TEXT_HEIGTH - 1) in case of overflow
			int texY = (int)texPos & (TEXT_HEIGTH - 1);
			texPos += step;
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			data->buf[y][x] = data->texture[texNum][TEXT_HEIGTH * texY + texX];
			y++;
		}
	}
}

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void	draw(t_info *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < WIN_HEIGTH)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			data->img.data[y * WIN_WIDTH + x] = data->buf[y][x];
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	main_loop(t_info *data)
{
	int	ceil_color = 0; // ceil val
	int	floor_color = 0; // floor val
	int	y;
	int	x;

	ceil_color = create_trgb(0, data->celing[0], data->celing[1], data->celing[2]);
	floor_color = create_trgb(0, data->floor[0], data->floor[1], data->floor[2]);

	y = -1;
	while (++y < WIN_HEIGTH)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < WIN_HEIGTH / 2)
				data->buf[y][x] = ceil_color;
			else
				data->buf[y][x] = floor_color;
		}
	}
	calc(data);
	draw(data);
	key_update(data);
	return (0);
}

int	key_update(t_info* data)
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

void	load_image(t_info* data, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->img_width, &img->img_height);
	if (!img->img)
		print_error("Img load fail\n");
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);

	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}	
	mlx_destroy_image(data->mlx, img->img);
}

void	load_texture(t_info *data)
{
	t_img	img;

	load_image(data, data->texture[0], data->tile[0], &img);
	load_image(data, data->texture[1], data->tile[1], &img);
	load_image(data, data->texture[2], data->tile[2], &img);
	load_image(data, data->texture[3], data->tile[3], &img);
}

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

int	exit_mlx(t_info *data)
{
	int y;

	y = -1;
	while (++y < data->map_height)
	{
		free(data->map[y]);
	}
	free(data->map);
	exit (0);
}

void	init_vec_data(t_info* data)
{
	int i;
	int j;

	data->mlx = mlx_init();
    if (!data->mlx)
        print_error("mlx NULL Error\n");

	data->key.key_w = 0;
	data->key.key_s = 0;
	data->key.key_a = 0;
	data->key.key_d = 0;
	data->key.key_left = 0;
	data->key.key_right = 0;


    if (data->now_dir == 'N')
		set_north(data);
	else if (data->now_dir == 'S')
		set_south(data);
	else if (data->now_dir == 'W')
		set_west(data);
	else if (data->now_dir == 'E')
		set_east(data);
    else
		print_error("No search dir");

	// window

	data->texture = (int **)malloc(sizeof(int *) * 4);
	if (!data->texture)
		exit(1);
	i = -1;
	while (++i < 4)
	{
		data->texture[i] = (int *)malloc(sizeof(int) * (TEXT_HEIGTH * TEXT_WIDTH));
		if (!data->texture[i])
			exit(1);
	}
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < TEXT_HEIGTH * TEXT_WIDTH)
		{
			data->texture[i][j] = 0;
		}
	}
	load_texture(data);

	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGTH, "cub3D");
	// exception

	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGTH);
	data->img.data = (int *)mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.size_l, &data->img.endian);
	// exception

	mlx_loop_hook(data->mlx, &main_loop, data);
	mlx_hook(data->win, X_EVENT_KEY_EXIT, 0, exit_mlx, data);
	mlx_hook(data->win, X_EVENT_KEY_PRESS, 0, &key_press, data);
	mlx_hook(data->win, X_EVENT_KEY_RELEASE, 0, &key_release, data);

	mlx_loop(data->mlx);
}
