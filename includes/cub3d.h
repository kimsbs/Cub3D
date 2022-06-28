#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct info{
    int     surround;
    int     width;
    int     height;
    char    *tile[4];
    char    **map;
    int     floor[4];
    int     celing[4];
}info;

int     ft_strlen(const char *str);
int     ft_strncmp(const char *s1, const char *s2, int n);
int     ft_strlcpy(char *dst, const char *src, int  dstsize);
void    exit_with_str(const char *str, int exit_code);
void    put_str(const char *str);
void    we_just_do_same_things(char **tmp, char *dummy, int space_len, int enter_len);
void    put_tile_data(char **tmp, info *data, int type);
void    alloc_tile(char **tmp, info *data);
void    put_fc_data(char **tmp, int data[3]);
void    alloc_fc(char **tmp, info *data);
void    get_map_info(const char *tmp, info *data);
void    cpy_map(const char *tmp, info *data);
void    alloc_map(const char *tmp, info *data);
char    *ft_strdup(const char *str);
char    *ft_strndup(const char *str, int n);
char	*ft_strjoin(char const *s1, char const *s2);
info    init_data(int fd);
#endif