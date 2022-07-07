#include "cub3d.h"

void	position_alloc(t_info *data, int y, int x, int *cnt)
{
	data->now_dir = data->map[y][x];
	data->map[y][x] = '0';
	data->p_ypos = y - 0.1;
	data->p_xpos = x - 0.1;
	(*cnt)++;
}

void	check_map(t_info *data, int cnt)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			c = data->map[y][x];
			if (c == ' ' || c == '0' || c == '1' || c == 'W'\
				|| c == 'E' || c == 'S' || c == 'N')
			{
				if (c == 'W' || c == 'E' || c == 'S' || c == 'N')
					position_alloc(data, y, x, &cnt);
				continue ;
			}
			else
				print_error("map contain odd data\n");
		}
	}
	if (cnt != 1)
		print_error("map contain odd data\n");
}

void	mapdata_to_info(char *tmp, t_info *data)
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
	check_map(data, 0);
	map_check(data);
}

t_info	init_data(int fd)
{
	t_info	data;
	char	buf[129];
	char	*tmp;
	int		rd_len;

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
