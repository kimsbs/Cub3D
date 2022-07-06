#include "../mlx/mlx.h"
#include "../includes/cub3d.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



int	worldMap[24][24] = {
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
						};

void	verLine(info *data, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, color);
		y++;
	}
}

void	calc(info *data)
{
	int	x;

	x = 0;
	while (x < data->win_width)
	{
		double cameraX = 2 * x / (double)data->win_width - 1;
		double rayDirX = data->dirX + data->planeX * cameraX;
		double rayDirY = data->dirY + data->planeY * cameraX;
		
		int mapX = (int)data->p_xpos;
		int mapY = (int)data->p_ypos;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
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
			if (worldMap[mapX][mapY] > 0) hit = 1;
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

		int	color;
		if (worldMap[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (worldMap[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (worldMap[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (worldMap[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		
		if (side == 1)
			color = color / 2;

		verLine(data, x, drawStart, drawEnd, color);
		
		x++;
	}
}

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}
int	main_loop(info *data)
{
	int color1 = 0; // ceil val
	int color2 = 0; // floor val
	// 
	color1 = create_trgb(0, 255, 255, 255);
	color2 = create_trgb(0, 0, 0, 0);

	// ceil
	for (int i = 0 ; i < data->win_height / 2 ; ++i)
		for (int j = 0 ; j < data->win_width ; ++j)
			mlx_pixel_put(data->mlx, data->win, j, i, color1);

	// floor
	for (int i = data->win_height / 2 ; i < data->win_height ; ++i)
		for (int j = 0 ; j < data->win_width ; ++j)
			mlx_pixel_put(data->mlx, data->win, j, i, color2);
	
	calc(data);
	// draw(data);
	// key_update(data);

	return (0);
}

int	key_press(int key, info* data)
{
	// front
	if (key == K_W)
	{
		if (!worldMap[(int)(data->p_xpos + data->dirX * data->moveSpeed)][(int)(data->p_ypos)])
			data->p_xpos += data->dirX * data->moveSpeed;
		if (!worldMap[(int)(data->p_xpos)][(int)(data->p_ypos + data->dirY * data->moveSpeed)])
			data->p_ypos += data->dirY * data->moveSpeed;
	}
	
	// back
	if (key == K_S)
	{
		if (!worldMap[(int)(data->p_xpos - data->dirX * data->moveSpeed)][(int)(data->p_ypos)])
			data->p_xpos -= data->dirX * data->moveSpeed;
		if (!worldMap[(int)(data->p_xpos)][(int)(data->p_ypos - data->dirY * data->moveSpeed)])
			data->p_ypos -= data->dirY * data->moveSpeed;
	}

	if (key == K_D)
	{
		if (!worldMap[(int)(data->p_xpos + data->planeX * data->moveSpeed)][(int)(data->p_ypos)])
			data->p_xpos += data->planeX * data->moveSpeed;
		if (!worldMap[(int)(data->p_xpos)][(int)(data->p_ypos + data->planeY * data->moveSpeed)])
			data->p_ypos += data->planeY * data->moveSpeed;
		
	}
	if (key == K_A)
	{
		if (!worldMap[(int)(data->p_xpos - data->planeX * data->moveSpeed)][(int)(data->p_ypos)])
			data->p_xpos -= data->planeX * data->moveSpeed;
		if (!worldMap[(int)(data->p_xpos)][(int)(data->p_ypos - data->planeY * data->moveSpeed)])
			data->p_ypos -= data->planeY * data->moveSpeed;
	}

	if (key == K_AR_R)
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
	if (key == K_AR_L)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(data->rotSpeed) - data->dirY * sin(data->rotSpeed);
		data->dirY = oldDirX * sin(data->rotSpeed) + data->dirY * cos(data->rotSpeed);

		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(data->rotSpeed) - data->planeY * sin(data->rotSpeed);
		data->planeY = oldPlaneX * sin(data->rotSpeed) + data->planeY * cos(data->rotSpeed);
	}
	printf("keyboard:%d\n", key);
	if (key == K_ESC)
		exit(0);
	printf("%lf %lf\n", data->p_xpos, data->p_ypos);
	return (0);
}

void	init_vec_data(info* data)
{
	data->mlx = mlx_init();
    if (!data->mlx)
        print_error("mlx NULL Error\n");

    // 초기화 (나중에 삭제)
    data->p_xpos = 12;
    data->p_ypos = 5;
	data->now_dir = 'N';
	// TODO: delete

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

	// 초기화 (나중에 삭제)
	data->moveSpeed = 0.5;
	data->rotSpeed = 0.05;
	data->win_width = 640;
	data->win_height = 480;
	// TODO: delete
	printf("dirx:%lf diry:%lf planex%lf planey%lf\n", data->dirX, data->dirY, data->planeX, data->planeY);
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "cub3D");
	printf("%p", data->win);
	mlx_loop_hook(data->mlx, &main_loop, data);
	printf("dirx:%lf diry:%lf planex%lf planey%lf\n", data->dirX, data->dirY, data->planeX, data->planeY);
	mlx_hook(data->win, X_EVENT_KEY_PRESS, 0, &key_press, data);

	mlx_loop(data->mlx);
}
