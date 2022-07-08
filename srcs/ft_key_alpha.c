/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyki <seungyki@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:10:19 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:10:20 by seungyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_w(t_info *data)
{
	if (data->map[(int)(data->p_ypos)]
		[(int)(data->p_xpos + data->dir_x * MOVE_SPEED)] == '0')
		data->p_xpos += data->dir_x * MOVE_SPEED;
	if (data->map[(int)(data->p_ypos + data->dir_y * MOVE_SPEED)]
		[(int)(data->p_xpos)] == '0')
		data->p_ypos += data->dir_y * MOVE_SPEED;
}

void	update_s(t_info *data)
{
	if (data->map[(int)(data->p_ypos)]
		[(int)(data->p_xpos - data->dir_x * MOVE_SPEED)] == '0')
		data->p_xpos -= data->dir_x * MOVE_SPEED;
	if (data->map[(int)(data->p_ypos - data->dir_y * MOVE_SPEED)]
		[(int)(data->p_xpos)] == '0')
		data->p_ypos -= data->dir_y * MOVE_SPEED;
}

void	update_a(t_info *data)
{
	if (data->map[(int)(data->p_ypos)]
		[(int)(data->p_xpos - data->plane_x * MOVE_SPEED)] == '0')
		data->p_xpos -= data->plane_x * MOVE_SPEED;
	if (data->map[(int)(data->p_ypos - data->plane_y * MOVE_SPEED)]
		[(int)(data->p_xpos)] == '0')
		data->p_ypos -= data->plane_y * MOVE_SPEED;
}

void	update_d(t_info *data)
{
	if (data->map[(int)(data->p_ypos)]
		[(int)(data->p_xpos + data->plane_x * MOVE_SPEED)] == '0')
		data->p_xpos += data->plane_x * MOVE_SPEED;
	if (data->map[(int)(data->p_ypos + data->plane_y * MOVE_SPEED)]
		[(int)(data->p_xpos)] == '0')
		data->p_ypos += data->plane_y * MOVE_SPEED;
}
