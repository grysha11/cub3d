# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 16:00:05 by hzakharc          #+#    #+#              #
#    Updated: 2024/12/08 11:43:20 by hzakharc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXECDIR		=	src/execution
PARSEDIR	=	src/parse
SRCSDIR		=	src

EXEC		=	$(EXECDIR)/checkers.c $(EXECDIR)/draw.c $(EXECDIR)/init.c \
				$(EXECDIR)/mlx.c $(EXECDIR)/move.c $(EXECDIR)/raycast_helper.c \
				$(EXECDIR)/raycast.c \

PARSE		=	$(PARSEDIR)/color.c $(PARSEDIR)/fill_helper.c $(PARSEDIR)/fill.c \
				$(PARSEDIR)/parse_util.c $(PARSEDIR)/parse.c $(PARSEDIR)/textures.c \
				$(PARSEDIR)/color_util.c \

SRCS		=	$(SRCSDIR)/main.c $(EXEC) $(PARSE) \

LIBFTDIR	=	inc/libft
GNLDIR		=	inc/gnl
MLXDIR		=	inc/minilibx

LIBS		=	$(GNLDIR)/gnl.a $(LIBFTDIR)/libft.a $(MLXDIR)/libmlx.a

OBJS		=	$(SRCS:.c=.o)

CC			=	@cc
RM			=	@rm -f
CCFLAGS		=	-Wall -Werror -Wextra -Iinclude/mlx -g
MLXFLAGS	=	-L/usr/X11/lib -lX11 -lXext -Llibs/mlx_linux -lm

BLUE		=	\033[0;94m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW		=	\e[0;33m
CYAN		=	\033[0;96m
COLOR		=	\033[0m

CLEAR		=	\033c

SUCCESS		=	@echo "$(YELLOW)cub3d is compileleleleleled$(COLOR)"
S_OBJS		=	@echo "$(BLUE)<(￣︶￣)>$(COLOR)"
S_NAME		=	@echo "$(CYAN)ヽ(・∀・)ﾉ$(COLOR)"

NAME		=	cub3d

%.o:		%.c
			$(CC) $(CCFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -sC $(LIBFTDIR)
			@make -sC $(GNLDIR)
			@make --no-print-directory -sC $(MLXDIR)
			@$(CC) $(CCFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) -o $(NAME)
			$(SUCCESS)

clean:
			$(RM) $(OBJS)
			@make --no-print-directory -sC $(LIBFTDIR) clean
			@make --no-print-directory -sC $(GNLDIR) clean
			@make --no-print-directory -sC $(MLXDIR) clean
			$(S_OBJS)

fclean:		clean
			$(RM) $(NAME)
			@make --no-print-directory -sC $(LIBFTDIR) fclean
			@make --no-print-directory -sC $(GNLDIR) fclean
			$(RM) $(MLXDIR)/libmlx.a
			$(S_NAME)

re:			fclean all

.PHONY:		all clean fclean re