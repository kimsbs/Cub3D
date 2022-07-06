#include "../mlx/mlx.h"
#include "../includes/cub3d.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	verLine(t_info *data, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, color);
		y++;
	}
}

void	calc(t_info *data)
{
	int	x;

	x = 0;
	while (x < data->win_width)
	{
		double cameraX = 2 * x / (double)data->win_width - 1;

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
			if (data->map[mapY][mapX] == '1') hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - data->p_xpos + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - data->p_ypos + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(data->win_height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + data->win_height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + data->win_height / 2;
		if(drawEnd >= data->win_height)
			drawEnd = data->win_height - 1;

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

		#define texWidth 64
		#define texHeight 64
		// x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - data->win_height / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = data->texture[texNum][texHeight * texY + texX];
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			data->buf[y][x] = color;
		}
		x++;
	}
}

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void	draw(t_info *data)
{
	for (int y = 0; y < data->win_height; y++)
	{
		for (int x = 0; x < data->win_width; x++)
		{
			data->img.data[y * data->win_width + x] = data->buf[y][x];
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
int	key_update(t_info* data);
int	main_loop(t_info *data)
{
	int color1 = 0; // ceil val
	int color2 = 0; // floor val
	// 
	color1 = create_trgb(0, data->celing[0], data->celing[1], data->celing[2]);
	color2 = create_trgb(0, data->floor[0], data->floor[1], data->floor[2]);

	
	// ceil 보류
	for (int i = 0 ; i < data->win_height / 2 ; ++i)
		for (int j = 0 ; j < data->win_width ; ++j)
			data->buf[i][j] = color1;

	// floor
	for (int i = data->win_height / 2 ; i < data->win_height ; ++i)
		for (int j = 0 ; j < data->win_width ; ++j)
			data->buf[i][j] = color2;
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
		if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos + data->dirX * data->moveSpeed)] == '0')
			data->p_xpos += data->dirX * data->moveSpeed;
			
			
		if (data->map[(int)(data->p_ypos + data->dirY * data->moveSpeed)][(int)(data->p_xpos)] == '0')
			data->p_ypos += data->dirY * data->moveSpeed;
	}
	
	// back
	if (data->key.key_s)
	{
		if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos - data->dirX * data->moveSpeed)] == '0')
			data->p_xpos -= data->dirX * data->moveSpeed;
			
		if (data->map[(int)(data->p_ypos - data->dirY * data->moveSpeed)][(int)(data->p_xpos)] == '0')
			data->p_ypos -= data->dirY * data->moveSpeed;
	}

	if (data->key.key_d)
	{
		if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos + data->planeX * data->moveSpeed)] == '0')
			
			data->p_xpos += data->planeX * data->moveSpeed;
		if (data->map[(int)(data->p_ypos + data->planeY * data->moveSpeed)][(int)(data->p_xpos)] == '0')
			data->p_ypos += data->planeY * data->moveSpeed;
		
	}
	if (data->key.key_a)
	{
		if (data->map[(int)(data->p_ypos)][(int)(data->p_xpos - data->planeX * data->moveSpeed)] == '0')
			data->p_xpos -= data->planeX * data->moveSpeed;
			
		if (data->map[(int)(data->p_ypos - data->planeY * data->moveSpeed)][(int)(data->p_xpos)] == '0')
			data->p_ypos -= data->planeY * data->moveSpeed;
	}

	if (data->key.key_left)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(-data->rotSpeed) - data->dirY * sin(-data->rotSpeed);
		data->dirY = oldDirX * sin(-data->rotSpeed) + data->dirY * cos(-data->rotSpeed);

		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(-data->rotSpeed) - data->planeY * sin(-data->rotSpeed);
		data->planeY = oldPlaneX * sin(-data->rotSpeed) + data->planeY * cos(-data->rotSpeed);
	}
	// left
	if (data->key.key_right)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(data->rotSpeed) - data->dirY * sin(data->rotSpeed);
		data->dirY = oldDirX * sin(data->rotSpeed) + data->dirY * cos(data->rotSpeed);

		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(data->rotSpeed) - data->planeY * sin(data->rotSpeed);
		data->planeY = oldPlaneX * sin(data->rotSpeed) + data->planeY * cos(data->rotSpeed);
	}
	// if (data->key.K_ESC)
		// exit(0);
	printf("%lf %lf\n", data->p_xpos, data->p_ypos);
	return (0);
}
// int	key_update(t_info* data)
// {
// 	// front
// 	if (data->key.key_w)
// 	{
// 		if (data->map[(int)(data->p_xpos + data->dirX * data->moveSpeed)][(int)(data->p_ypos)] != '1')
// 			data->p_xpos += data->dirX * data->moveSpeed;
// 		if (data->map[(int)(data->p_xpos)][(int)(data->p_ypos + data->dirY * data->moveSpeed)] != '1')
// 			data->p_ypos += data->dirY * data->moveSpeed;
// 	}
	
// 	// back
// 	if (data->key.key_s)
// 	{
// 		if (data->map[(int)(data->p_xpos - data->dirX * data->moveSpeed)][(int)(data->p_ypos)] != '1')
// 			data->p_xpos -= data->dirX * data->moveSpeed;
// 		if (data->map[(int)(data->p_xpos)][(int)(data->p_ypos - data->dirY * data->moveSpeed)] != '1')
// 			data->p_ypos -= data->dirY * data->moveSpeed;
// 	}

// 	if (data->key.key_d)
// 	{
// 		if (data->map[(int)(data->p_xpos + data->planeX * data->moveSpeed)][(int)(data->p_ypos)] != '1')
// 			data->p_xpos += data->planeX * data->moveSpeed;
// 		if (data->map[(int)(data->p_xpos)][(int)(data->p_ypos + data->planeY * data->moveSpeed)] != '1')
// 			data->p_ypos += data->planeY * data->moveSpeed;
		
// 	}
// 	if (data->key.key_a)
// 	{
// 		if (data->map[(int)(data->p_xpos - data->planeX * data->moveSpeed)][(int)(data->p_ypos)] != '1')
// 			data->p_xpos -= data->planeX * data->moveSpeed;
// 		if (data->map[(int)(data->p_xpos)][(int)(data->p_ypos - data->planeY * data->moveSpeed)] != '1')
// 			data->p_ypos -= data->planeY * data->moveSpeed;
// 	}

// 	if (data->key.key_right)
// 	{
// 		//both camera direction and camera plane must be rotated
// 		double oldDirX = data->dirX;
// 		data->dirX = data->dirX * cos(-data->rotSpeed) - data->dirY * sin(-data->rotSpeed);
// 		data->dirY = oldDirX * sin(-data->rotSpeed) + data->dirY * cos(-data->rotSpeed);

// 		double oldPlaneX = data->planeX;
// 		data->planeX = data->planeX * cos(-data->rotSpeed) - data->planeY * sin(-data->rotSpeed);
// 		data->planeY = oldPlaneX * sin(-data->rotSpeed) + data->planeY * cos(-data->rotSpeed);
// 	}
// 	// left
// 	if (data->key.key_left)
// 	{
// 		//both camera direction and camera plane must be rotated
// 		double oldDirX = data->dirX;
// 		data->dirX = data->dirX * cos(data->rotSpeed) - data->dirY * sin(data->rotSpeed);
// 		data->dirY = oldDirX * sin(data->rotSpeed) + data->dirY * cos(data->rotSpeed);

// 		double oldPlaneX = data->planeX;
// 		data->planeX = data->planeX * cos(data->rotSpeed) - data->planeY * sin(data->rotSpeed);
// 		data->planeY = oldPlaneX * sin(data->rotSpeed) + data->planeY * cos(data->rotSpeed);
// 	}
// 	// if (data->key.K_ESC)
// 		// exit(0);
// 	printf("%lf %lf\n", data->p_xpos, data->p_ypos);
// 	return (0);
// }

void	load_image(t_info* data, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
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
	while (++y < data->height)
	{
		free(data->map[y]);
	}
	free(data->map);
	exit (0);
}

void	init_vec_data(t_info* data)
{
	data->mlx = mlx_init();
    if (!data->mlx)
        print_error("mlx NULL Error\n");

    // 초기화 (나중에 삭제)
    // data->p_xpos = 12;
    // data->p_ypos = 5;
	// data->now_dir = 'N';
	// TODO: delete

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
	#define texHeight 64
	#define texWidth 64
	// 초기화 (나중에 삭제)
	data->moveSpeed = 0.2;
	data->rotSpeed = 0.05;
	data->win_width = 640;
	data->win_height = 480;
	// TODO: delete
	//printf("dirx:%lf diry:%lf planex%lf planey%lf\n", data->dirX, data->dirY, data->planeX, data->planeY);
	// window


	if (!(data->texture = (int **)malloc(sizeof(int *) * 4)))
		exit(1);
	for (int i = 0; i < 4; i++)
	{
		if (!(data->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			exit(1);
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			data->texture[i][j] = 0;
		}
	}

	load_texture(data);


	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "cub3D");
	// exception

	data->img.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->img.data = (int *)mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.size_l, &data->img.endian);
	// exception

	mlx_loop_hook(data->mlx, &main_loop, data);
	
	//ㅇㅖ쁘게 바바꿔  주주세세요요
	mlx_hook(data->win, 17, 0, exit_mlx, data);
	mlx_hook(data->win, X_EVENT_KEY_PRESS, 0, &key_press, data);
	mlx_hook(data->win, X_EVENT_KEY_RELEASE, 0, &key_release, data);

	mlx_loop(data->mlx);
}
