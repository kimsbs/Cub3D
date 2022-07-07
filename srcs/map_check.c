# include "../includes/cub3d.h"

void	bst(t_info *data, t_queue *head, int x, int y)
{
	if (y < 0 || y >= data->map_height || x < 0 || x >= data->map_width)
		return ;
	if (data->visited[y][x] == 1)
		return ;
	if (data->map[y][x] == '1')
		return ;
	if (data->map[y][x] == '0')
	{
		if (y == 0 || y == data->map_height - 1 || x == 0 || x == data->map_width - 1)
			print_error("map isn't surrounded by 1\n");
		data->visited[y][x] = 1;
		enqueue(&head, x, y);
	}
	else
		print_error("map has space area or not surrounded by 1\n");
}

void	visitied_init(t_info *data)
{
	int	y;
	int	x;

	data->visited = (int **)malloc(sizeof(int *) * data->map_height);
	if (!data->visited)
		print_error("malloc error\n");
	y = -1;
	while (++y < data->map_height)
	{
		data->visited[y] = (int *)malloc(sizeof(int) * data->map_width);
		if (!data->visited[y])
			print_error("malloc error\n");
	}
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
			data->visited[y][x] = 0;
	}
}

void	free_visited(t_info *data)
{
	int	y;

	y = -1;
	while (++y < data->map_height)
	{
		free(data->visited[y]);
	}
	free(data->visited);
}

void	map_check(t_info *data)
{
	t_queue	*head;

	visitied_init(data);
	head = NULL;
	data->visited[(int)(data->p_ypos + 0.1)][(int)(data->p_xpos + 0.1)] = 1;
	enqueue(&head, data->p_xpos, data->p_ypos);
	while (head)
	{
		bst(data, head, head->x - 1, head->y);
		bst(data, head, head->x, head->y - 1);
		bst(data, head, head->x + 1, head->y);
		bst(data, head, head->x, head->y + 1);
		dequeue(&head);
	}
	free_visited(data);
}
