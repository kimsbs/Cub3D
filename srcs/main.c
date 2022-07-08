/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyki <seungyki@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:12:05 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:21:04 by seungyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../mlx/mlx.h"

void	free_all_data(t_info *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(data->tile[i]);
	i = -1;
	while (++i < 4)
		free(data->texture[i]);
	free(data->texture);
	i = -1;
	while (++i < data->map_height)
		free(data->map[i]);
	free(data->map);
	free(data);
}

int	main(int argc, char **argv)
{
	t_info	*data;
	int		fd;

	if (argc != 2)
		print_error("Arguments!! ./cub3d [map.cub]\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_error("File Open Failed!!\n");
	data = init_data(fd);
	close(fd);
	start_mlx(data);
	free_all_data(data);
	return (0);
}
