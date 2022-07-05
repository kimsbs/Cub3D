#include <stdlib.h>

void print_error(const char * str)
{
    printf("%s ", str);
    printf("Error\n");
    exit(1);
}