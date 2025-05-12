# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 16:02:32 by sgadinga          #+#    #+#              #
#    Updated: 2025/05/12 18:33:40 by sgadinga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
MLX_FLAGS = -lXext -lX11 -lm -lz
CFLAGS = -Wall -Werror -Wextra -g -Ilibft/includes -Iincludes -Iminilibx-linux -O3
SANITIZE_FLAGS = -fsanitize=address

SRC_DIR = src
UTILS_DIR = utils
OBJ_DIR = obj

UTILS = $(addprefix $(UTILS_DIR)/, draw_utils.c map_utils.c hooks_utils.c render_utils.c)
SRCS = $(addprefix $(SRC_DIR)/, fdf.c colors.c draw.c \
		 map.c render.c hooks.c rotations.c $(UTILS))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: libft mlx $(NAME)

libft:
	@make -C libft

mlx:
	@make -C minilibx-linux

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Lminilibx-linux -Llibft -lft -lmlx $(MLX_FLAGS) $(SANITIZE_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/utils
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft fclean
	@make -C minilibx-linux clean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft mlx
