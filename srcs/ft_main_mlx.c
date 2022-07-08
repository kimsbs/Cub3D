/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:10:44 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:46:03 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../mlx/mlx.h"

int	exit_mlx(t_info *data)
{
	int	y;

	y = -1;
	while (++y < data->map_height)
	{
		free(data->map[y]);
	}
	free(data->map);
	exit (0);
}

void	start_mlx(t_info *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		print_error("mlx NULL Error\n");
	init_key_false(data);
	set_dir_with_vec(data);
	ft_texture_init(data);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGTH, "cub3D");
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGTH);
	data->img.data = (int *)mlx_get_data_addr(data->img.img, &data->img.bpp, \
		&data->img.size_l, &data->img.endian);
	mlx_loop_hook(data->mlx, &main_loop, data);
	mlx_hook(data->win, X_EVENT_KEY_EXIT, 0, exit_mlx, data);
	mlx_hook(data->win, X_EVENT_KEY_PRESS, 0, &key_press, data);
	mlx_hook(data->win, X_EVENT_KEY_RELEASE, 0, &key_release, data);
	mlx_loop(data->mlx);
}

void	raycast(t_info *data)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		set_vector_and_dist(&ray, data, x);
		ray.hit = 0;
		set_side_and_sidedist(&ray, data);
		dda_algorithm(&ray, data);
		ray.line_height = (int)(WIN_HEIGTH / ray.wall_dist);
		ray.draw_start_pos = -ray.line_height / 2 + WIN_HEIGTH / 2;
		if (ray.draw_start_pos < 0)
			ray.draw_start_pos = 0;
		ray.draw_end_pos = ray.line_height / 2 + WIN_HEIGTH / 2;
		if (ray.draw_end_pos >= WIN_HEIGTH)
			ray.draw_end_pos = WIN_HEIGTH - 1;
		set_texture_number(&ray);
		set_buf_value(data, &ray, x);
	}
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
	int	ceil_color;
	int	floor_color;
	int	y;
	int	x;

	ceil_color = create_trgb(0, data->celing[0], \
		data->celing[1], data->celing[2]);
	floor_color = create_trgb(0, data->floor[0], \
		data->floor[1], data->floor[2]);
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
	raycast(data);
	draw(data);
	key_update(data);
	return (0);
}
