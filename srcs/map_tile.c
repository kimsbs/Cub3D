/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyki <seungyki@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:12:45 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:19:36 by seungyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_tile_data(char **tmp, t_info *data, int type)
{
	int		space_len;
	int		enter_len;
	char	*dummy;

	dummy = *tmp;
	space_len = 2;
	while (dummy[space_len] && dummy[space_len] == ' ')
		space_len++;
	enter_len = 0;
	while (dummy[space_len + enter_len] && dummy[space_len + enter_len] != '\n')
		enter_len++;
	data->tile[type] = ft_strndup(dummy + space_len, enter_len);
	if (!data->tile[type])
		print_error("tile alloc\n");
	dummy = ft_strdup(*tmp + space_len + enter_len + 1);
	free(*tmp);
	*tmp = dummy;
}

void	remove_enter(char **tmp, int *cnt)
{
	char	*dummy;

	dummy = ft_strdup(*tmp + 1);
	free(*tmp);
	*tmp = dummy;
	*cnt -= 1;
}

void	alloc_tile(char **tmp, t_info *data)
{
	int	cnt;

	fc_init(data);
	cnt = 0;
	while (cnt < 6 && *tmp[0])
	{
		if (*tmp[0] == '\n')
			remove_enter(tmp, &cnt);
		else if (ft_strncmp(*tmp, "NO", 2) && !data->tile[0])
			put_tile_data(tmp, data, 0);
		else if (ft_strncmp(*tmp, "SO", 2) && !data->tile[1])
			put_tile_data(tmp, data, 1);
		else if (ft_strncmp(*tmp, "WE", 2) && !data->tile[2])
			put_tile_data(tmp, data, 2);
		else if (ft_strncmp(*tmp, "EA", 2) && !data->tile[3])
			put_tile_data(tmp, data, 3);
		else if (ft_strncmp(*tmp, "F", 1) && data->floor[3] == -1)
			put_fc_data(tmp, data->floor);
		else if (ft_strncmp(*tmp, "C", 1) && data->celing[3] == -1)
			put_fc_data(tmp, data->celing);
		else
			print_error(".cub data\n");
		cnt++;
	}
}
