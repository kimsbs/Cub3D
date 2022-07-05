#include "cub3d.h"

void    get_map_info(const char *tmp, info *data)
{
    int move;
    int len;

    data->height = 0;
    data->width = 0;
    move = -1;
    len = 0;
    while (tmp[++move])
    {
        if(tmp[move] == '\n')
        {
            data->height++;
            if (data->width < len)
                data->width = len;
            len = 0;
            continue;
        }
        len++;
    }
    if (data->width < len)
        data->width = len;
    if (len > 0)
        data->height++;
}

void    cpy_map(const char *tmp, info *data)
{
    int y;
    int x;
    int move;

    y = -1;
    move = 0;
    while (++y < data->height)
    {
        x = -1;
        while (++x < data->width)
        {
            if(tmp[move] && tmp[move] != '\n')
                data->map[y][x] = tmp[move++];
            else
                data->map[y][x] = ' ';
        }
        move++;
        data->map[y][x] = '\0';
    }
}

void    alloc_map(const char *tmp, info *data)
{
    int y;

    data->map = (char **)malloc(sizeof(char *) * (data->height + 1));
    if(!data->map)
        exit_with_str("malloc error\n", -1);
    y = -1;
    while (++y < data->height)
    {
        data->map[y] = (char *)malloc(sizeof(char) * (data->width + 1));
        if(!data->map[y])
            exit_with_str("malloc error\n", -1);
    }
    data->map[y] = 0;
    cpy_map(tmp, data);
}