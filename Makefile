NAME = cub3D

SRCS = srcs/get_map.c srcs/main.c srcs/ft_func1.c srcs/ft_func2.c	\
		srcs/map_data.c	srcs/map_input.c srcs/map_check.c\
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

bonus: $(NAME_BONUS)

$(NAME) : $(OBJS)
	@make -C $(MLX)
	gcc $(CFLAGS) -o $@ $(MLX_lib) $(OBJS)


clean:
	rm -f $(OBJS)
#	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
#	rm -f $(NAME_BONUS)
#	@make clean -C $(MLX)
	
re: fclean all