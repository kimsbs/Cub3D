#include "cub3d.h"

void	put_tile_data(char **tmp, t_info *data, int type)
{
	int		space_len;
	int		enter_len;
	char	*dummy;

	dummy = *tmp;
	space_len = 2;
	while (dummy[space_len] && dummy[space_len] == ' ')
		space_len++;
	enter_len = 0;
	while (dummy[space_len + enter_len] && dummy[space_len + enter_len] != '\n')
		enter_len++;
	//space 이후 STRING -> 복사 후 tile에 저장
	data->tile[type] = ft_strndup(dummy + space_len, enter_len);
	if (!data->tile[type])
		print_error("tile alloc\n");
	//'\n'이후 의 거시기 복사.
	dummy = ft_strdup(*tmp + space_len + enter_len + 1);
	free(*tmp);
	*tmp = dummy;
}

void	remove_enter(char **tmp)
{
	char	*dummy;

	dummy = ft_strdup(*tmp + 1);
	free(*tmp);
	*tmp = dummy;
}

void	alloc_tile(char **tmp, t_info *data)
{
	int	cnt;

	cnt = -1;
	while (++cnt < 4)
		data->tile[cnt] = 0;
	cnt = -1;
	while (++cnt < 4)
	{
		if (*tmp[0] == '\n')
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
