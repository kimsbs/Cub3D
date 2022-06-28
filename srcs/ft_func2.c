# include "cub3d.h"

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        i++;
    }
    return (i);
}

void    put_str(const char *str)
{
    int len;

    len = ft_strlen(str);
    write(1, str, len);
}

void    exit_with_str(const char *str, int exit_code)
{
    int len;

    len = ft_strlen(str);
    write(1, str, len);
    exit(exit_code);
}