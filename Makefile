NAME    =	cub3D

SRC_PATH=./srcs/
MYRI_PATH = ./myri/

SRCS    =	check_map_utils.c \
			check_texture.c \
			check_files.c \
			get_valid_map.c \
			manage_errors.c\
			create_parsing.c \
			main_parsing.c\
			
SRC2 =			cub.c mouvements.c hooks.c  draw.c init.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c \
				floor_ceiling.c calc.c calc_text.c load_texture.c \
				pst.c

SRC2_B =		cub.c mouvements.c hooks.c  draw.c init.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c \
				floor_ceiling_bonus.c calc.c calc_text.c load_texture.c \
				pst.c

SRC=$(addprefix $(SRC_PATH), $(SRCS))  $(addprefix $(MYRI_PATH), $(SRC2))

SRC_B=$(addprefix $(SRC_PATH), $(SRCS))  $(addprefix $(MYRI_PATH), $(SRC2_B))

OBJS=$(SRC:.c=.o)

OBJS_B=$(SRC_B:.c=.o)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

CC        =    gcc
#CC        =    clang-9
RM        =    rm -f
CFLAGS    =  -Wall -Werror -Wextra -g3
#-fsanitize=address -fsanitize=leak -g3

MLX        = ./mlx

MLX_LIB = ./mlx/libmlx_Linux.a

LIBFT= ./libft/libft.a

bonus: $(LIBFT) $(MLX_LIB) $(OBJS_B)
	 $(CC) $(SRC_B) $(CFLAGS) -I . -g3 -Lmlx_Linux -lmlx_Linux -L ./mlx -Imlx_Linux -L ./libft -lft -lXext -lX11 -lm -lz -o  $(NAME)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(SRC) $(CFLAGS) -I . -g3 -Lmlx_Linux -lmlx_Linux -L ./mlx -Imlx_Linux -L ./libft -lft -lXext -lX11 -lm -lz -o $(NAME)	


$(MLX_LIB):
	cd ./mlx && ./configure

$(LIBFT):
	make -C libft
	

clean:
	${RM} ${OBJS} ${OBJS_B}
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
