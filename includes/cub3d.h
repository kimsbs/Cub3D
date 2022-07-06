#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> // 나중에 삭제할것

//ㅈㅓㅇ리
# define K_A 0
# define K_D 2
# define K_S 1
# define K_W 13
# define K_AR_L 123
# define K_AR_R 124
# define K_ESC 53

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17

//TODO : remove
#define mapWidth 24
#define mapHeight 24

typedef struct s_queue{
    int x;
    int y;
    struct s_queue *next;
}				t_queue;

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_key
{
	int		key_w;
	int		key_a;
	int		key_d;
	int		key_s;
	int		key_left;
	int		key_right;
}				t_key;


typedef struct s_info{
	//need free
	int		**visited;
	
	double     p_xpos;
	double     p_ypos;
	
	// bool
	int     surround;
	// map size
	int     width;
	int     height;

	char    *tile[4];

	// real map
	char    **map;
	//
	int     floor[4];
	int     celing[4];

	// 내껏 헤
	int		buf[480][640];
	int		**texture;
	t_img		img;
	t_key		key;
	void*		mlx;
	void*		win;
	int			win_width;
	int			win_height;
	double     dirX;
	double     dirY;
	double     planeX;
	double     planeY;

	char        now_dir;

	double		moveSpeed;
	double		rotSpeed;
}           	t_info;

int     ft_strlen(const char *str);
int     ft_strncmp(const char *s1, const char *s2, int n);
int     ft_strlcpy(char *dst, const char *src, int  dstsize);
void    put_str(const char *str);
void    alloc_fc(char **tmp, t_info *data);
void    alloc_tile(char **tmp, t_info *data);
void    put_fc_data(char **tmp, int data[3]);
void    cpy_map(const char *tmp, t_info *data);
void    alloc_map(const char *tmp, t_info *data);
void 	alloc_fc(char **tmp, t_info *data);
void    get_map_info(const char *tmp, t_info *data);
void    put_tile_data(char **tmp, t_info *data, int type);
void    we_just_do_same_things(char **tmp, char *dummy, int space_len, int enter_len);
void	map_check(t_info *data);
void	remove_enter(char **tmp);
void	dequeue(t_queue **head);
void	enqueue(t_queue **head, int x, int y);
char    *ft_strdup(const char *str);
char    *ft_strndup(const char *str, int n);
char	*ft_strjoin(char const *s1, char const *s2);
t_info	init_data(int fd);
t_queue	*get_last(t_queue *head);

void	init_vec_data(t_info *data);
void set_north(t_info* data);
void set_south(t_info* data);
void set_east(t_info* data);
void set_west(t_info* data);
void print_error(const char * str);
#endif