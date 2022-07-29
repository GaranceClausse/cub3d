NAME    =	cub3D

SRC_PATH=./srcs/

SRCS    =	check_map_utils.c \
			check_texture.c \
			check_files.c \
			get_valid_map.c \
			manage_errors.c\
			create_parsing.c \
			main.c\


SRC=$(addprefix $(SRC_PATH), $(SRCS))

OBJS=$(SRC:.c=.o)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

CC        =    gcc
#CC        =    clang-9
RM        =    rm -f
CFLAGS    =  -Wall -Werror -Wextra -g3
#-fsanitize=address -fsanitize=leak -g3

MLX        = ./mlx_linux

MLX_LIB = ./mlx_linux/libmlx_Linux.a

LIBFT= ./libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(SRC) $(CFLAGS) -I . -g3 -Lmlx_Linux -lmlx_Linux -L ./mlx_linux -Imlx_Linux -L ./libft -lft -lXext -lX11 -lm -lz -o $(NAME)	

$(MLX_LIB):
	cd ./mlx_linux && ./configure

$(LIBFT):
	make -C libft
	

clean:
	${RM} ${OBJS}
	make clean -C ${MLX}
	make clean -C libft

fclean:        clean
	${RM} ${NAME}
	make fclean -C libft
	${RM} ${NAME} ${MLX_LIB}

re:            fclean
	$(MAKE) all -j

.PHONY:        all clean fclean re


#-framework OpenGL -framework AppKit
