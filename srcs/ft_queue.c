/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyki <seungyki@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:10:52 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:14:14 by seungyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_queue	*get_last(t_queue *head)
{
	t_queue	*node;

	node = head;
	while (node->next)
		node = node->next;
	return (node);
}

void	enqueue(t_queue **head, int x, int y)
{
	t_queue	*last;
	t_queue	*new_node;

	new_node = (t_queue *)malloc(sizeof(t_queue));
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

void	dequeue(t_queue **head)
{
	t_queue	*remove;

	remove = *head;
	*head = remove->next;
	free(remove);
}
