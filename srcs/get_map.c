#include "cub3d.h"

void    check_map(info *data, int cnt)
{
    int y;
    int x;
    char    c;

    y = -1;
    while (++y < data->height)
    {
        x = -1;
        while (++x < data->width)
        {
            c = data->map[y][x];
            if(c == ' ' || c == '0' || c == '1' || c == 'W'\
                || c == 'E' || c == 'S' || c == 'N')
            {
                if(c == 'W' || c == 'E' || c == 'S' || c == 'N')
                    cnt++;
                continue;
            }
            else
                exit_with_str("MAP CONTAIN ODD DATA", -1);
        }
    }
    if (cnt != 1)
        exit_with_str("MAP CONTAIN ODD DATA", -1);
}

void    mapdata_to_info(char *tmp, info *data)
{
    alloc_tile(&tmp, data);
    alloc_fc(&tmp, data);
    get_map_info(tmp, data);
    alloc_map(tmp, data);
    free(tmp);
    data->surround = -1;
    check_map(data, 0);
}

info init_data(int fd)
{
    info    data;
    char    buf[129];
    char    *tmp;
    int rd_len;

    tmp = NULL;
    rd_len = read(fd, buf, 128);
    while (rd_len > 0)
    {
        buf[rd_len] = '\0';
        tmp = ft_strjoin(tmp, buf);
        rd_len = read(fd, buf, 128);
    }
    mapdata_to_info(tmp, &data);
    return (data);
}