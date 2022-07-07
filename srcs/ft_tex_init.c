#include "../mlx/mlx.h"
#include "../includes/cub3d.h"

static void	load_image(t_info *data, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	img->img = mlx_xpm_file_to_image(data->mlx, path, \
		&img->img_width, &img->img_height);
	if (!img->img)
		print_error("Img load fail\n");
	img->data = (int *)mlx_get_data_addr(img->img, \
		&img->bpp, &img->size_l, &img->endian);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}	
	mlx_destroy_image(data->mlx, img->img);
}

static void	load_texture(t_info *data)
{
	t_img	img;

	load_image(data, data->texture[0], data->tile[0], &img);
	load_image(data, data->texture[1], data->tile[1], &img);
	load_image(data, data->texture[2], data->tile[2], &img);
	load_image(data, data->texture[3], data->tile[3], &img);
}

void	ft_texture_init(t_info *data)
{
	int	i;
	int	j;

	data->texture = (int **)malloc(sizeof(int *) * 4);
	if (!data->texture)
		exit(1);
	i = -1;
	while (++i < 4)
	{
		data->texture[i] = (int *)malloc(sizeof(int) * \
			(TEXT_HEIGTH * TEXT_WIDTH));
		if (!data->texture[i])
			print_error("malloc");
	}
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < TEXT_HEIGTH * TEXT_WIDTH)
		{
			data->texture[i][j] = 0;
		}
	}
	load_texture(data);
}
