# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/27 20:03:27 by atamas            #+#    #+#              #
#    Updated: 2024/11/06 14:34:47 by hzakharc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Werror -Wextra
SRC = main.c init.c mlx.c draw.c move.c
OBJ = $(SRC:.c=.o)
MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a
GNL_DIR = ./inc/gnl
GNL = $(GNL_DIR)/gnl.a

all: $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

$(NAME): $(GNL) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(GNL) $(MLX) -lX11 -lXext -lm -o $(NAME)

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) -C $(GNL_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re