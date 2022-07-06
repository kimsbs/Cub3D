#include "cub3d.h"

void put_tile_data(char **tmp, info *data, int type)
{
    int space_len;
    int enter_len;
    char *dummy;

    dummy = *tmp;
    space_len = 2;
    while (dummy[space_len] && dummy[space_len] == ' ')
        space_len++;
    enter_len = 0;
    while (dummy[space_len + enter_len] && dummy[space_len + enter_len] != '\n')
        enter_len++;
    //space 이후 STRING -> 복사 후 tile에 저장
    data->tile[type] = ft_strndup(dummy + space_len, enter_len);
    if(!data->tile[type])
        print_error("tile alloc\n");
    //'\n'이후 의 거시기 복사.
    dummy = ft_strdup(*tmp + space_len + enter_len + 1);
    free(*tmp);
    *tmp = dummy;
}
void remove_enter(char **tmp)
{
    char *dummy;

    dummy = ft_strdup(*tmp + 1);
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
        if(*tmp[0] == '\n')
        {
            --cnt;
            remove_enter(tmp);
        }
        else if (ft_strncmp(*tmp, "NO", 2) && !data->tile[0])
            put_tile_data(tmp, data, 0);
        else if (ft_strncmp(*tmp, "SO", 2) && !data->tile[1])
            put_tile_data(tmp, data, 1);
        else if (ft_strncmp(*tmp, "WE", 2) && !data->tile[2])
            put_tile_data(tmp, data, 2);
        else if (ft_strncmp(*tmp, "EA", 2) && !data->tile[3])
            put_tile_data(tmp, data, 3);
        else
            print_error("tile data\n");
    }
}

int put_fc_data2(char now, int data[3], int *rgb)
{
    if (now == ',')
    {
        (*rgb)++;
        if (*rgb > 2)
            print_error("rgb data\n");
        return (0);
    }
    if (now >= '0' && now <= '9')
    {
        data[*rgb] *= 10;
        data[*rgb] += now - '0';
        if (data[*rgb] > 255)
            print_error("rgb data\n");
    }
    else
        print_error("rgb data\n");
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
    //remove space
    while (dummy[space_len] && dummy[space_len] == ' ')
        space_len++;
    enter_len = -1;
    rgb = 0;
    //255,0,0 -> to array data[]
    while (dummy[space_len + ++enter_len] && dummy[space_len + enter_len] != '\n')
        put_fc_data2(dummy[space_len + enter_len], data, &rgb);
    if (enter_len == 0)
        print_error("floor and ceiling data empty\n");
    //'\n'다음 라인으로 tmp 복사 후 기존 tmp free
    dummy = ft_strdup(*tmp + space_len + enter_len + 1);
    free(*tmp);
    *tmp = dummy;
}

void fc_init(info *data)
{
    int cnt;

    cnt = -1;
    while (++cnt < 4)
    {
        data->floor[cnt] = 0;
        data->celing[cnt] = 0;
    }
}

void alloc_fc(char **tmp, info *data)
{
    int cnt;

    fc_init(data);
    cnt = -1;
    while (++cnt < 2 && *tmp[0])
    {
        if(*tmp[0] == '\n')
        {
            --cnt;
            remove_enter(tmp);
        }
        else if (*tmp[0] == 'F' && !data->floor[3])
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
            print_error("color\n");
    }
}