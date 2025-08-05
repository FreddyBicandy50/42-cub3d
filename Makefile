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
	\
	gnl/get_next_line.c \
	\
	src/render/window.c \
	src/render/handle_keys.c \
	src/render/handle_movements.c \
	src/render/handle_rotations.c \
	src/render/player.c \
	src/render/textures.c \
	src/render/calculations.c \
	src/render/rendering.c \
	\
	src/libft/ft_atoi.c \
	src/libft/ft_isdigit.c \
	src/libft/ft_putendl_fd.c \
	src/libft/ft_strcmp.c \
	src/libft/ft_strdup.c \
	src/libft/ft_strjoin.c \
	src/libft/ft_strlen.c \
	src/libft/ft_calloc.c \
	src/libft/ft_memset.c \
	src/libft/ft_strncmp.c \
	src/libft/ft_split.c \
	src/libft/ft_strtrim.c \
	src/libft/ft_putstr_fd.c \
	\
	src/parsing/free_game.c \
	src/parsing/parse_file.c \
	src/parsing/parse_file1.c \
	src/parsing/parse_file2.c \
	src/parsing/parse_file3.c \
	src/parsing/parse_file4.c \
	src/parsing/utils.c \
	src/parsing/validate_map.c \
	src/parsing/validate_map1.c \
	src/parsing/validate_map2.c \

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

