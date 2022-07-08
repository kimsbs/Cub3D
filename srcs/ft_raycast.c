/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:11:44 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:46:04 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../mlx/mlx.h"

void	set_side_and_sidedist(t_ray *ray, t_info *data)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->p_xpos - ray->map_x) \
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->p_xpos) \
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->p_ypos - ray->map_y) \
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->p_ypos) \
			* ray->delta_dist_y;
	}
}

void	set_vector_and_dist(t_ray *ray, t_info *data, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_y = data->dir_y + data->plane_y * ray->camera_x;
	ray->ray_dir_x = data->dir_x + data->plane_x * ray->camera_x;
	ray->map_y = (int)data->p_ypos;
	ray->map_x = (int)data->p_xpos;
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
}

void	dda_algorithm(t_ray *ray, t_info *data)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - data->p_xpos + \
			(1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->wall_dist = (ray->map_y - data->p_ypos + \
			(1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	set_texture_number(t_ray *ray)
{
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_number = 0;
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_number = 1;
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_number = 2;
	else if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_number = 3;
}

void	set_buf_value(t_info *data, t_ray *ray, int x)
{
	int		y;
	double	wall_x;

	if (ray->side == 0)
		wall_x = data->p_ypos + ray->wall_dist * ray->ray_dir_y;
	else
		wall_x = data->p_xpos + ray->wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)TEXT_WIDTH);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = TEXT_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = TEXT_WIDTH - ray->tex_x - 1;
	ray->step = 1.0 * TEXT_HEIGTH / ray->line_height;
	ray->tex_pos = (ray->draw_start_pos - WIN_HEIGTH / 2 \
		+ ray->line_height / 2) * ray->step;
	y = ray->draw_start_pos;
	while (y < ray->draw_end_pos)
	{
		ray->tex_y = (int)ray->tex_pos & (TEXT_HEIGTH - 1);
		ray->tex_pos += ray->step;
		data->buf[y][x] = data->texture[ray->tex_number] \
			[TEXT_HEIGTH * ray->tex_y + ray->tex_x];
		y++;
	}
}
