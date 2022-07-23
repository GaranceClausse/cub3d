MANDA_NAMES = 	background_rect.c cub3d.c free_error.c hooks.c \
				mouvements.c print_map.c read_map.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c \

MANDA_OBJS =	 $(MANDA_NAMES:.c=.o)

NAME = cub3d

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
MLX = mlx/libmlx_Linux.a -lX11 -lXext

AR = ar rc

RM = rm -f

RL = ranlib

$(NAME):	$(MANDA_OBJS)
			make -C mlx
			$(CC) $(CFLAGS) -lm $(MANDA_OBJS) $(MLX) -o $(NAME)

all:		$(NAME)

clean:	
			$(RM) $(MANDA_OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

malloc_test: $(MANDA_OBJS)
	make -C mlx
	$(CC) $(CFLAGS)  -o $@ ${MANDA_OBJS} $(MLX) -L. -lmallocator

.PHONY:		all bonus clean fclean re