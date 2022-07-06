# include "../includes/cub3d.h"

s_queue *get_last(s_queue *head)
{
    s_queue *node;

    node = head;
    while (node->next)
        node = node->next;
    return (node);
}

void enqueue(s_queue **head, int x, int y)
{
    s_queue *last;
    s_queue *new_node;

    new_node = (s_queue *)malloc(sizeof(s_queue));
    if (!new_node)
        print_error("enqueue_error\n");
    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;
    if (!*head)
        *head = new_node;
    else
    {
        last = get_last(*head);
        last->next = new_node; 
    }
}

void dequeue(s_queue **head)
{
    s_queue *remove;

    remove = *head;
    *head = remove->next;
    free(remove);
}

void bst(info *data, s_queue *head, int x, int y)
{
    if (y < 0 || y >= data->height || x < 0 || x >= data->width)
        return ;
    if (data->visited[y][x] == 1)
        return ;
    if (data->map[y][x] == '1')
        return ;
    if (data->map[y][x] == '0')
    {
        if (y == 0 || y == data->height - 1 || x == 0 || x == data->width - 1)
            print_error("map isn't surrounded by 1\n");
        data->visited[y][x] = 1;
        enqueue(&head, x, y);
    }
    else
        print_error("map has space area or not surrounded by 1\n");
}

void visitied_init(info *data)
{
    int y;
    int x;

    data->visited = (int **)malloc(sizeof(int *) * data->height);
    y = -1;
    while(++y < data->height)
    {
        data->visited[y] = (int *)malloc(sizeof(int) * data->width);
    }
    y = -1;
    while (++y < data->height)
    {
        x = -1;
        while(++x < data->width)
            data->visited[y][x] = 0; 
    }
}

void map_check(info *data)
{
    s_queue *head;

    visitied_init(data);
    head = NULL;
    data->visited[(int)data->p_ypos][(int)data->p_xpos] = 1;
    enqueue(&head, data->p_xpos, data->p_ypos);
    while (head)
    {
        bst(data, head, head->x - 1, head->y);
        bst(data, head, head->x, head->y - 1);
        bst(data, head, head->x + 1, head->y);
        bst(data, head, head->x, head->y + 1);
        dequeue(&head);
    }
    data->surround = 1;
}