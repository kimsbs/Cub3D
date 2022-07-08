NAME = cub3D
SRCS = srcs/get_map.c srcs/main.c srcs/ft_func1.c srcs/ft_func2.c	\
		srcs/map_tile.c	srcs/map_input.c srcs/map_check.c srcs/map_fc.c\
		srcs/ft_queue.c		\
		srcs/set_dir.c		\
		srcs/util.c			\
		srcs/ft_key_set.c	\
		srcs/ft_key_alpha.c	\
		srcs/ft_key_arrow.c	\
		srcs/ft_tex_init.c	\
		srcs/ft_raycast.c	\
		srcs/ft_main_mlx.c	\

MLX = mlx

MLX_lib = -Lmlx -lmlx -framework OpenGL -framework AppKit

INCLUDES = -I includes -I $(MLX)

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(NAME)

$(NAME) : $(OBJS)
	@make -C $(MLX)
	cc $(CFLAGS) -o $@ $(MLX_lib) $(OBJS)

clean:
	rm -f $(OBJS)
	@make clean -C $(MLX)

fclean: clean
	rm -f $(NAME)
	
re: 
	make fclean
	make all

.PHONY: all clean fclean re