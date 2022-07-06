#include <unistd.h>
#include <stdlib.h>
#include "../includes/cub3d.h"

void print_error(const char * str)
{
    const char *error_message = "Error\n";
    write(1, str, ft_strlen(str));
    write(1, error_message, ft_strlen(error_message));
    exit(1);
}