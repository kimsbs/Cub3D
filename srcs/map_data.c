#include "cub3d.h"

void put_tile_data(char **tmp, info *data, int type)
{
    int space_len;
    int enter_len;
    char *dummy;

    dummy = *tmp;
    space_len = 2;
    while (dummy[space_len] == ' ')
        space_len++;
    enter_len = 0;
    while (dummy[space_len + enter_len] && dummy[space_len + enter_len] != '\n')
        enter_len++;
    data->tile[type] = ft_strndup(dummy + space_len, enter_len);
    dummy = ft_strdup(*tmp + space_len + enter_len + 1);
    free(*tmp);
    *tmp = dummy;
}

void alloc_tile(char **tmp, info *data)
{
    int cnt;
    cnt = -1;
    while (++cnt < 4)
        data->tile[cnt] = 0;
    cnt = -1;
    while (++cnt < 4)
    {
        if (ft_strncmp(*tmp, "NO", 2) && !data->tile[0])
            put_tile_data(tmp, data, 0);
        else if (ft_strncmp(*tmp, "SO", 2) && !data->tile[1])
            put_tile_data(tmp, data, 1);
        else if (ft_strncmp(*tmp, "WE", 2) && !data->tile[2])
            put_tile_data(tmp, data, 2);
        else if (ft_strncmp(*tmp, "EA", 2) && !data->tile[3])
            put_tile_data(tmp, data, 3);
        else
            exit_with_str("TILE_DATA_ERROR\n", -1);
    }
}

int put_fc_data2(char now, int data[3], int *rgb)
{
    if (now == ',')
    {
        (*rgb)++;
        if (*rgb > 2)
            exit_with_str("RGB DATA ERROR\n", -1);
        return (0);
    }
    if (now >= '0' && now <= '9')
    {
        data[*rgb] *= 10;
        data[*rgb] += now - '0';
        if (data[*rgb] > 255)
            exit_with_str("RGB DATA ERROR\n", -1);
    }
    else
        exit_with_str("RGB DATA ERROR\n", -1);
    return (0);
}

void put_fc_data(char **tmp, int data[3])
{
    int space_len;
    int enter_len;
    int rgb;
    char *dummy;

    dummy = *tmp;
    space_len = 1;
    while (dummy[space_len] == ' ')
        space_len++;
    enter_len = -1;
    rgb = 0;
    while (dummy[space_len + ++enter_len] && dummy[space_len + enter_len] != '\n')
        put_fc_data2(dummy[space_len + enter_len], data, &rgb);
    dummy = ft_strdup(*tmp + space_len + enter_len + 1);
    free(*tmp);
    *tmp = dummy;
}

void alloc_fc(char **tmp, info *data)
{
    int cnt;

    cnt = -1;
    while (++cnt < 4)
    {
        data->floor[cnt] = 0;
        data->celing[cnt] = 0;
    }
    cnt = -1;
    while (++cnt < 2)
    {
        if (*tmp[0] == 'F' && !data->floor[3])
        {
            put_fc_data(tmp, data->floor);
            data->floor[3] = 1;
        }
        else if (*tmp[0] == 'C' && !data->celing[3])
        {
            put_fc_data(tmp, data->celing);
            data->celing[3] = 1;
        }
        else
            exit_with_str("Floor_Celing_ERROR\n", -1);
    }
}