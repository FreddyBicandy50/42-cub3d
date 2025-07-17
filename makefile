# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes -Iminilibx-linux

# Executable name
NAME    = cub3d

# MiniLibX
MLX_DIR = .minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Source files (manually listed)
SRC = main.c \
	libft/libft.c \
	libft/libft.utils.c \
	libft/split.c \
	parsing/parsing.c \
	parsing/map_parsing.c \
	parsing/color_parsing.c \
	parsing/parsing_utils.c \
	parsing/map_checker.c \
	parsing/read_and_extract.c \
	utils/directions.c \
	utils/copy_2darray.c \
	utils/colors.c \
	utils/flood_fill.c \
	utils/utils.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

