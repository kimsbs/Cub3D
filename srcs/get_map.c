/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyki <seungyki@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:11:56 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:36:58 by seungyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	position_alloc(t_info *data, int y, int x, int *cnt)
{
	data->now_dir = data->map[y][x];
	data->map[y][x] = '0';
	data->p_ypos = y + 0.12345678901234567;
	data->p_xpos = x + 0.12345678901234567;
	(*cnt)++;
}

void	check_map(t_info *data, int cnt)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			c = data->map[y][x];
			if (c == ' ' || c == '0' || c == '1' || c == 'W'\
				|| c == 'E' || c == 'S' || c == 'N')
			{
				if (c == 'W' || c == 'E' || c == 'S' || c == 'N')
					position_alloc(data, y, x, &cnt);
				continue ;
			}
			else
				print_error("map contain odd data\n");
		}
	}
	if (cnt != 1)
		print_error("map contain odd data\n");
}

void	mapdata_to_info(char *tmp, t_info *data)
{
	alloc_tile(&tmp, data);
	get_map_info(tmp, data);
	alloc_map(tmp, data);
	free(tmp);
	check_map(data, 0);
	map_check(data);
}

t_info	*init_data(int fd)
{
	t_info	*data;
	char	buf[129];
	char	*tmp;
	int		rd_len;

	data = (t_info *)malloc(sizeof(t_info));
	if (!data)
		print_error("malloc error\n");
	tmp = NULL;
	rd_len = read(fd, buf, 128);
	while (rd_len > 0)
	{
		buf[rd_len] = '\0';
		tmp = ft_strjoin(tmp, buf);
		rd_len = read(fd, buf, 128);
	}
	mapdata_to_info(tmp, data);
	return (data);
}
