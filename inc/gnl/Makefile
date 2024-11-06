# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 09:41:11 by hzakharc          #+#    #+#              #
#    Updated: 2024/11/06 15:32:34 by hzakharc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	gnl.c
LIBFTDIR	= 	../libft/

LIBFT		= 	$(LIBFTDIR)libft.a
OBJS		= 	$(SRCS:.c=.o)

CC			= 	cc
RM			= 	@rm -rf
CCFLAGS		= 	-Wall -Werror -Wextra -I.

NAME		= 	gnl.a

%.o:			%.c
				@$(CC) $(CCFLAGS) -c $< -o $@

all:			$(NAME)
				
$(NAME):		$(OBJS)
				@make -sC ${LIBFTDIR}
				@ar rcs $(NAME) $(LIBFT) $(OBJS)

clean:
				@make --no-print-directory -C $(LIBFTDIR) clean
				$(RM) $(OBJS)

fclean:			clean
				@make --no-print-directory -C $(LIBFTDIR) fclean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re