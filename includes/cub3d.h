#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> // 나중에 삭제할것

# define K_A 0
# define K_D 2
# define K_S 1
# define K_W 13
# define K_AR_L 123
# define K_AR_R 124
# define K_ESC 53

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define mapWidth 24
#define mapHeight 24

typedef struct info{
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
}           info;

int     ft_strlen(const char *str);
int     ft_strncmp(const char *s1, const char *s2, int n);
int     ft_strlcpy(char *dst, const char *src, int  dstsize);
void    put_str(const char *str);
void    alloc_fc(char **tmp, info *data);
void    alloc_tile(char **tmp, info *data);
void    put_fc_data(char **tmp, int data[3]);
void    cpy_map(const char *tmp, info *data);
void    alloc_map(const char *tmp, info *data);
void    get_map_info(const char *tmp, info *data);
void    exit_with_str(const char *str, int exit_code);
void    put_tile_data(char **tmp, info *data, int type);
void    we_just_do_same_things(char **tmp, char *dummy, int space_len, int enter_len);
char    *ft_strdup(const char *str);
char    *ft_strndup(const char *str, int n);
char	*ft_strjoin(char const *s1, char const *s2);
info    init_data(int fd);

void	init_vec_data(info *data);
void set_north(info* data);
void set_south(info* data);
void set_east(info* data);
void set_west(info* data);
void print_error(const char * str);
#endif