# include "cub3d.h"

void check_info(info data)
{
    printf("%s\n", data.tile[0]);
    printf("%s\n", data.tile[1]);
    printf("%s\n", data.tile[2]);
    printf("%s\n", data.tile[3]);
    printf("floor : %d,%d,%d\n", data.floor[0], data.floor[1], data.floor[2]);
    printf("celing : %d,%d,%d\n", data.celing[0], data.celing[1], data.celing[1]);
    printf("height : %d width : %d\n", data.height, data.width);
    for(int i = 0 ; i < data.height ; i++)
        printf("%s\n", data.map[i]);
}

void Leak_check(void)
{
    system("leaks cub3D");
}

int main(int argc, char **argv)
{
    info data;
    int fd;

    if(argc != 2)
        exit_with_str("Arguments!! ./cub3d [map.cub]\n", -1);
    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
        exit_with_str("File Open Error!!\n", -1);
    data = init_data(fd);
    close(fd);    
    check_info(data);

    //Leak_check();
    return (0);
}