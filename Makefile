# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/27 20:03:27 by atamas            #+#    #+#              #
#    Updated: 2024/11/05 13:22:19 by atamas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Werror -Wextra
SRC = main.c mlx.c draw.c move.c
OBJ = $(SRC:.c=.o)
MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -lX11 -lXext -lm -o $(NAME)

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re