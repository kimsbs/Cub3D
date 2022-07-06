#include "cub3d.h"

void position_alloc(info *data, int y, int x, int *cnt)
{
    data->now_dir = data->map[y][x];
    data->p_ypos = y;
    data->p_xpos = x;
    (*cnt)++;
}

void check_map(info *data, int cnt)
{
    int y;
    int x;
    char c;

    y = -1;
    while (++y < data->height)
    {
        x = -1;
        while (++x < data->width)
        {
            c = data->map[y][x];
            if (c == ' ' || c == '0' || c == '1' || c == 'W' || c == 'E' || c == 'S' || c == 'N')
            {
                if (c == 'W' || c == 'E' || c == 'S' || c == 'N')
                    position_alloc(data, y, x, &cnt);
                continue;
            }
            else
                print_error("map contain odd data\n");
        }
    }
    if (cnt != 1)
        print_error("map contain odd data\n");
}

void mapdata_to_info(char *tmp, info *data)
{
    //타일 종류별 할당
    alloc_tile(&tmp, data);
    //천장 바닥 색상할당
    alloc_fc(&tmp, data);
    // map의 width height 계산
    get_map_info(tmp, data);
    // map 할당
    alloc_map(tmp, data);
    free(tmp);
    data->surround = -1;
    check_map(data, 0);
    map_check(data);
}

info init_data(int fd)
{
    info data;
    char buf[129];
    char *tmp;
    int rd_len;

    tmp = NULL;
    rd_len = read(fd, buf, 128);
    while (rd_len > 0)
    {
        buf[rd_len] = '\0';
        // add buf to tmp
        tmp = ft_strjoin(tmp, buf);
        rd_len = read(fd, buf, 128);
    }
    mapdata_to_info(tmp, &data);
    return (data);
}