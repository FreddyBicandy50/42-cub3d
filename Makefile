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
	src/game/window.c \
	src/game/render.c \
	\
	libft/libft.c \
	libft/split.c \
	libft/libft.utils.c \
	\
	src/parsing/parsing.c \
	src/parsing/map_checker.c \
	src/parsing/map_parsing.c \
	src/parsing/parsing_utils.c \
	src/parsing/color_parsing.c \
	src/parsing/read_and_extract.c \
	\
	src/utils/init.c \
	src/utils/utils.c \
	src/utils/colors.c \
	src/utils/flood_fill.c \
	src/utils/directions.c \
	src/utils/copy_2darray.c \

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
	@make clean
	@clear
	@echo "${GREEN}Recompiled Successfully${RESET}"
.PHONY: all clean fclean re

