# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 16:02:32 by sgadinga          #+#    #+#              #
#    Updated: 2025/04/30 16:40:15 by sgadinga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
MLX_FLAGS = -lXext -lX11 -lm -lz
CFLAGS = -Wall -Werror -Wextra -g -Ilibft/includes -Iincludes -Iminilibx-linux -O3
SANITIZE_FLAGS = -fsanitize=address

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(addprefix $(SRC_DIR)/, fdf.c colors.c)

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
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean
	@make -C minilibx-linux clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft clean

re: fclean all

.PHONY: all clean fclean re libft mlx
