/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyki <seungyki@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:12:29 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:12:31 by seungyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_info(const char *tmp, t_info *data)
{
	int	move;
	int	len;

	data->map_height = 0;
	data->map_width = 0;
	move = -1;
	len = 0;
	while (tmp[++move])
	{
		if (tmp[move] == '\n')
		{
			data->map_height++;
			if (data->map_width < len)
				data->map_width = len;
			len = 0;
			continue ;
		}
		len++;
	}
	if (data->map_width < len)
		data->map_width = len;
	if (len > 0)
		data->map_height++;
}

void	cpy_map(const char *tmp, t_info *data)
{
	int	y;
	int	x;
	int	move;

	y = -1;
	move = 0;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (tmp[move] && tmp[move] != '\n')
				data->map[y][x] = tmp[move++];
			else
				data->map[y][x] = ' ';
		}
		move++;
		data->map[y][x] = '\0';
	}
}

void	alloc_map(const char *tmp, t_info *data)
{
	int	y;

	data->map = (char **)malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		print_error("malloc error\n");
	y = -1;
	while (++y < data->map_height)
	{
		data->map[y] = (char *)malloc(sizeof(char) * (data->map_width + 1));
		if (!data->map[y])
			print_error("malloc error\n");
	}
	data->map[y] = 0;
	cpy_map(tmp, data);
}
