#include <unistd.h>
#include <stdlib.h>
#include "../includes/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	int trgb;

	trgb = t << 24 | r << 16 | g << 8 | b;
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
