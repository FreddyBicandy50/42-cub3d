# Compiler and flags
GREEN=\033[0;32m
RED=\033[0;31m
RESET=\033[0m

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes -Iminilibx-linux

# Executable name
NAME    = cub3d

# MiniLibX
MLX_DIR = .minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Source files (manually listed)
SRCS = main.c \
	game/window.c \
	game/render.c \
	\
	libft/libft.c \
	libft/split.c \
	libft/libft.utils.c \
	\
	parsing/parsing.c \
	parsing/map_checker.c \
	parsing/map_parsing.c \
	parsing/parsing_utils.c \
	parsing/color_parsing.c \
	parsing/read_and_extract.c \
	\
	utils/init.c \
	utils/utils.c \
	utils/colors.c \
	utils/flood_fill.c \
	utils/directions.c \
	utils/copy_2darray.c \

OBJ = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean
	@clear
	@echo "${GREEN}Objects Complied Successfully${RESET}"

fclean: clean
	rm -f $(NAME)
	@clear
	@echo "$(RED)Objects Cleaned Successfully$(RESET)"

re: fclean all

.PHONY: all clean fclean re

