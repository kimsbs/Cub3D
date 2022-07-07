NAME = cub3D
SRCS = srcs/get_map.c srcs/main.c srcs/ft_func1.c srcs/ft_func2.c	\
		srcs/map_tile.c	srcs/map_input.c srcs/map_check.c srcs/map_fc.c\
		srcs/ft_queue.c		\
		srcs/set_data.c		\
		srcs/set_dir.c		\
		srcs/util.c			\

MLX = mlx

MLX_lib = -Lmlx -lmlx -framework OpenGL -framework AppKit

INCLUDES = -I includes -I $(MLX)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

OBJS = $(SRCS:.c=.o)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(NAME)

$(NAME) : $(OBJS)
	@make -C $(MLX)
	gcc $(CFLAGS) -o $@ $(MLX_lib) $(OBJS)

clean:
	rm -f $(OBJS)
	@make clean -C $(MLX)

fclean: clean
	rm -f $(NAME)
	
re: fclean all