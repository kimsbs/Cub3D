#include "../mlx/mlx.h"
#include "../includes/cub3d.h"

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_y;
	double	ray_dir_x;
	int		map_y;
	int		map_x;
	double	side_dist_y;
	double	side_dist_x;
	double	delta_dist_y;
	double	delta_dist_x;
	double	wall_dist;
	int		step_y;
	int		step_x;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start_pos;
	int		draw_end_pos;
	int		tex_number;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}				t_ray;

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

void	test(t_ray *ray, t_info *data)
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

void	test1(t_ray *ray)
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

void	calc(t_info *data)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		set_vector_and_dist(&ray, data, x);
		ray.hit = 0;
		set_side_and_sidedist(&ray, data);
		test(&ray, data);
		ray.line_height = (int)(WIN_HEIGTH / ray.wall_dist);
		ray.draw_start_pos = -ray.line_height / 2 + WIN_HEIGTH / 2;
		if (ray.draw_start_pos < 0)
			ray.draw_start_pos = 0;
		ray.draw_end_pos = ray.line_height / 2 + WIN_HEIGTH / 2;
		if (ray.draw_end_pos >= WIN_HEIGTH)
			ray.draw_end_pos = WIN_HEIGTH - 1;
		test1(&ray);
		set_buf_value(data, &ray, x);
	}
}

void	draw(t_info *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < WIN_HEIGTH)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			data->img.data[y * WIN_WIDTH + x] = data->buf[y][x];
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	main_loop(t_info *data)
{
	int	ceil_color;
	int	floor_color;
	int	y;
	int	x;

	ceil_color = create_trgb(0, data->celing[0], \
		data->celing[1], data->celing[2]);
	floor_color = create_trgb(0, data->floor[0], \
		data->floor[1], data->floor[2]);
	y = -1;
	while (++y < WIN_HEIGTH)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < WIN_HEIGTH / 2)
				data->buf[y][x] = ceil_color;
			else
				data->buf[y][x] = floor_color;
		}
	}
	calc(data);
	draw(data);
	key_update(data);
	return (0);
}

int	exit_mlx(t_info *data)
{
	int	y;

	y = -1;
	while (++y < data->map_height)
	{
		free(data->map[y]);
	}
	free(data->map);
	exit (0);
}

void	start_mlx(t_info *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		print_error("mlx NULL Error\n");
	init_key_false(data);
	set_dir_with_vec(data);
	ft_texture_init(data);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGTH, "cub3D");
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGTH);
	data->img.data = (int *)mlx_get_data_addr(data->img.img, &data->img.bpp, \
		&data->img.size_l, &data->img.endian);
	mlx_loop_hook(data->mlx, &main_loop, data);
	mlx_hook(data->win, X_EVENT_KEY_EXIT, 0, exit_mlx, data);
	mlx_hook(data->win, X_EVENT_KEY_PRESS, 0, &key_press, data);
	mlx_hook(data->win, X_EVENT_KEY_RELEASE, 0, &key_release, data);
	mlx_loop(data->mlx);
}
