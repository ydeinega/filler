# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/05 15:41:14 by ydeineha          #+#    #+#              #
#    Updated: 2018/06/05 15:41:16 by ydeineha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ydeineha.filler

LIB = ./libft/libft.a

VISU = visu

FLAGS = -Wall -Wextra -Werror -I. -c

SRCS = filler.c put_piece.c check_piece.c board.c

SRCS_VISU = visu.c print_board.c board.c initialize.c

OBJS = $(SRCS:.c=.o)

OBJS_VISU = $(SRCS_VISU:.c=.o)

all: $(NAME)

$(LIB): 
	@make -C libft

$(NAME): $(LIB)
	@gcc $(SRCS) $(FLAGS)
	@gcc $(OBJS) $(LIB) -o $(NAME)
	@echo "\x1b[35mYour PLAYER has been successfully created!\x1b[0m"

$(VISU): $(LIB)
	@gcc $(SRCS_VISU) $(FLAGS)
	@gcc $(OBJS_VISU) $(LIB) -lncurses -o $(VISU)
	@echo "\x1b[35mVisualizer has been successfully created!\x1b[0m"

clean:
	@make -C libft clean
	@rm -rf $(OBJS)
	@rm -rf $(OBJS_VISU)

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)
	@rm -rf $(VISU)

re: fclean all

.PHONY: all clean fclean re