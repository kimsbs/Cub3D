/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyki <seungyki@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:13:09 by seungyki          #+#    #+#             */
/*   Updated: 2022/07/08 11:13:10 by seungyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../includes/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	int	trgb;

	trgb = (t << 24) | (r << 16) | (g << 8) | b;
	return (trgb);
}

void	print_error(const char *str)
{
	const char	*error_message = "Error\n";

	write(2, error_message, ft_strlen(error_message));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}
