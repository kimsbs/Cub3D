NAME = cub3D
NAME_BONUS = cub3D_bonus
SRCS = srcs/get_map.c srcs/main.c srcs/ft_func1.c srcs/ft_func2.c\
		srcs/map_data.c	srcs/map_input.c
#SRCS_BONUS = 
MLX = mlx
MLX_lib = -Lmlx -lmlx -framework OpenGL -framework AppKit
INCLUDES = -I includes -I $(MLX)
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
#OBJS_BONUS = $(SRCS_BONUS:.c=.o)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME):$(OBJS)
#	@make -C $(MLX)
#	gcc $(CFLAGS) -o $@ $(MLX_lib) $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

$(NAME_BONUS):$(OBJS_BONUS)
	@make clean -C $(MLX)
	@make -C $(MLX)
	gcc $(CFLAGS) -o $@ $(MLX_lib) $(OBJS_BONUS)

clean:
	rm -f $(OBJS)
#	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
#	rm -f $(NAME_BONUS)
#	@make clean -C $(MLX)
	
re: fclean all