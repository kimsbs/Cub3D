/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyki <seungyki@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:13:01 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:13:02 by seungyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_north(t_info *data)
{
	data->dir_x = 0.0;
	data->dir_y = -1.0;
	data->plane_x = 0.66;
	data->plane_y = 0.0;
}

void	set_south(t_info *data)
{
	data->dir_x = 0.0;
	data->dir_y = 1.0;
	data->plane_x = -0.66;
	data->plane_y = 0.0;
}

void	set_west(t_info *data)
{
	data->dir_x = -1.0;
	data->dir_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = -0.66;
}

void	set_east(t_info *data)
{
	data->dir_x = 1.0;
	data->dir_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = 0.66;
}

void	set_dir_with_vec(t_info *data)
{
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
}
