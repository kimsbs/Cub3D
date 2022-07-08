/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyki <seungyki@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:12:20 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:19:25 by seungyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_fc_data2(char now, int data[3], int *rgb)
{
	if (now == ',')
	{
		(*rgb)++;
		if (*rgb > 2)
			print_error("rgb data\n");
		return ;
	}
	if (now >= '0' && now <= '9')
	{
		if (data[*rgb] == -1)
			data[*rgb] = 0;
		data[*rgb] *= 10;
		data[*rgb] += now - '0';
		if (data[*rgb] > 255)
			print_error("rgb data\n");
	}
	else
		print_error("rgb data\n");
}

void	put_fc_data(char **tmp, int data[3])
{
	int		space_len;
	int		enter_len;
	int		rgb;
	char	*dummy;

	dummy = *tmp;
	space_len = 1;
	while (dummy[space_len] && dummy[space_len] == ' ')
		space_len++;
	enter_len = -1;
	rgb = 0;
	while (dummy[space_len + ++enter_len] \
		&& dummy[space_len + enter_len] != '\n')
		put_fc_data2(dummy[space_len + enter_len], data, &rgb);
	if (rgb != 2 || data[rgb] == -1)
		print_error("rgb data\n");
	if (enter_len == 0)
		print_error("floor and ceiling data empty\n");
	dummy = ft_strdup(*tmp + space_len + enter_len + 1);
	free(*tmp);
	*tmp = dummy;
	data[3] = 1;
}

void	fc_init(t_info *data)
{
	int	cnt;

	cnt = -1;
	while (++cnt < 4)
	{
		data->floor[cnt] = -1;
		data->celing[cnt] = -1;
		data->tile[cnt] = 0;
	}
}
