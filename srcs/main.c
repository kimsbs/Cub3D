# include "cub3d.h"
# include "../mlx/mlx.h"

void	check_info(t_info *data)
{
	printf("%s\n", data->tile[0]);
	printf("%s\n", data->tile[1]);
	printf("%s\n", data->tile[2]);
	printf("%s\n", data->tile[3]);
	printf("floor : %d,%d,%d\n", data->floor[0], data->floor[1], data->floor[2]);
	printf("celing : %d,%d,%d\n", data->celing[0], data->celing[1], data->celing[1]);
	printf("height : %d width : %d\n", data->map_height, data->map_width);
	for (int i = 0 ; i < data->map_height ; i++)
		printf("%s\n", data->map[i]);
}

void	free_all_data(t_info *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(data->tile[i]);
	i = -1;
	while (++i < data->map_height)
		free(data->map[i]);
	free(data->map);
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
	check_info(data);
	start_mlx(data);
	free_all_data(data);
	return (0);
}
