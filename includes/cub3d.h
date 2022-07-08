/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:23:46 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:44:57 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define K_A 0
# define K_D 2
# define K_S 1
# define K_W 13
# define K_AR_L 123
# define K_AR_R 124
# define K_ESC 53

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17

# define TEXT_HEIGTH 64
# define TEXT_WIDTH 64

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define WIN_WIDTH 1600
# define WIN_HEIGTH 900

typedef struct s_queue{
	int				x;
	int				y;
	struct s_queue	*next;
}				t_queue;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_key
{
	int		key_w;
	int		key_a;
	int		key_d;
	int		key_s;
	int		key_left;
	int		key_right;
}				t_key;

typedef struct s_info{
	int			**visited;
	double		p_xpos;
	double		p_ypos;
	int			map_width;
	int			map_height;
	char		*tile[4];
	char		**map;
	int			floor[4];
	int			celing[4];

	int			buf[WIN_HEIGTH][WIN_WIDTH];
	int			**texture;
	t_img		img;
	t_key		key;
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

	char		now_dir;
}				t_info;

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

int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
void	put_str(const char *str);
void	alloc_fc(char **tmp, t_info *data);
void	alloc_tile(char **tmp, t_info *data);
void	put_fc_data(char **tmp, int data[3]);
void	cpy_map(const char *tmp, t_info *data);
void	alloc_map(const char *tmp, t_info *data);
void	put_fc_data(char **tmp, int data[3]);
void	fc_init(t_info *data);
void	get_map_info(const char *tmp, t_info *data);
void	put_tile_data(char **tmp, t_info *data, int type);
void	we_just_do_same_things(char **tmp, char *dummy, \
	int space_len, int enter_len);
void	map_check(t_info *data);
void	remove_enter(char **tmp, int *cnt);
void	dequeue(t_queue **head);
void	enqueue(t_queue **head, int x, int y);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, int n);
char	*ft_strjoin(char const *s1, char const *s2);
t_info	*init_data(int fd);
t_queue	*get_last(t_queue *head);

void	set_north(t_info *data);
void	set_south(t_info *data);
void	set_east(t_info *data);
void	set_west(t_info *data);
void	set_dir_with_vec(t_info *data);

int		create_trgb(int t, int r, int g, int b);
void	print_error(const char *str);

int		key_press(int key, t_info *data);
int		key_release(int key, t_info *data);
int		key_update(t_info *data);
void	init_key_false(t_info *data);

void	update_w(t_info *data);
void	update_s(t_info *data);
void	update_a(t_info *data);
void	update_d(t_info *data);

void	ft_key_arrow_left(t_info *data);
void	ft_key_arrow_right(t_info *data);

void	ft_texture_init(t_info *data);

void	set_side_and_sidedist(t_ray *ray, t_info *data);
void	set_vector_and_dist(t_ray *ray, t_info *data, int x);
void	dda_algorithm(t_ray *ray, t_info *data);
void	set_texture_number(t_ray *ray);
void	set_buf_value(t_info *data, t_ray *ray, int x);

int		exit_mlx(t_info *data);
void	start_mlx(t_info *data);
void	raycast(t_info *data);
void	draw(t_info *data);
int		main_loop(t_info *data);

#endif
