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

LIB = libft.a

FLAGS = -Wall -Wextra -Werror -I. -c

SRCS_LIB = ./libft/ft_memset.c ./libft/ft_bzero.c ./libft/ft_memcpy.c ./libft/ft_memccpy.c ./libft/ft_memmove.c \
./libft/ft_memchr.c ./libft/ft_memcmp.c ./libft/ft_strlen.c ./libft/ft_strdup.c ./libft/ft_strcpy.c ./libft/ft_strncpy.c \
./libft/ft_strcat.c ./libft/ft_strncat.c ./libft/ft_strlcat.c ./libft/ft_strchr.c ./libft/ft_strrchr.c ./libft/ft_strstr.c \
./libft/ft_strnstr.c ./libft/ft_strcmp.c ./libft/ft_strncmp.c ./libft/ft_atoi.c ./libft/ft_isalpha.c ./libft/ft_isdigit.c \
./libft/ft_isalnum.c ./libft/ft_isascii.c ./libft/ft_isprint.c ./libft/ft_toupper.c ./libft/ft_tolower.c ./libft/ft_memalloc.c \
./libft/ft_memdel.c ./libft/ft_strnew.c ./libft/ft_strdel.c ./libft/ft_strclr.c ./libft/ft_striter.c ./libft/ft_striteri.c \
./libft/ft_strmap.c ./libft/ft_strmapi.c ./libft/ft_strequ.c ./libft/ft_strnequ.c ./libft/ft_strsub.c ./libft/ft_strjoin.c \
./libft/ft_strtrim.c ./libft/ft_strsplit.c ./libft/ft_itoa.c ./libft/ft_putchar.c ./libft/ft_putstr.c ./libft/ft_putendl.c \
./libft/ft_putnbr.c ./libft/ft_putchar_fd.c ./libft/ft_putstr_fd.c ./libft/ft_putendl_fd.c ./libft/ft_putnbr_fd.c \
./libft/ft_lstnew.c ./libft/ft_lstdelone.c ./libft/ft_lstdel.c ./libft/ft_lstadd.c ./libft/ft_lstiter.c ./libft/ft_lstmap.c \
./libft/ft_realloc.c ./libft/ft_isspace.c ./libft/ft_lstprint.c ./libft/ft_lstaddb.c ./libft/ft_memdel_md.c \
./libft/get_next_line.c ./libft/apostrophe.c ./libft/arg_char.c ./libft/arg_num.c ./libft/arg_ptr.c ./libft/conv_char.c \
./libft/conv_num.c ./libft/dollar_flag.c ./libft/flags.c ./libft/zero_width_prc.c ./libft/ft_printf.c ./libft/itoa_base.c ./libft/sign_num.c \
./libft/star_flag.c ./libft/str_num.c ./libft/width_num.c ./libft/nonvalid.c ./libft/str_wchar.c

SRCS = filler.c put_piece.c check_piece.c

OBJS_LIB = ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o \
ft_memchr.o ft_memcmp.o ft_strlen.o ft_strdup.o ft_strcpy.o ft_strncpy.o \
ft_strcat.o ft_strncat.o ft_strlcat.o ft_strchr.o ft_strrchr.o ft_strstr.o \
ft_strnstr.o ft_strcmp.o ft_strncmp.o ft_atoi.o ft_isalpha.o ft_isdigit.o \
ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o ft_memalloc.o \
ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o \
ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o \
ft_strtrim.o ft_strsplit.o ft_itoa.o ft_putchar.o ft_putstr.o ft_putendl.o \
ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o \
ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o \
ft_realloc.o ft_isspace.o ft_lstprint.o ft_lstaddb.o ft_memdel_md.o get_next_line.o \
apostrophe.o arg_char.o arg_num.o arg_ptr.o conv_char.o conv_num.o dollar_flag.o \
flags.o zero_width_prc.o ft_printf.o itoa_base.o sign_num.o star_flag.o str_num.o \
width_num.o nonvalid.o str_wchar.o

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIB): 
	gcc $(SRCS_LIB) $(FLAGS)
	ar rc $(LIB) $(OBJS_LIB)
	ranlib $(LIB)

$(NAME): $(LIB)
	gcc $(SRCS) $(FLAGS)
	gcc $(OBJS) -L. -lft -o $(NAME)

clean: 
	rm -rf $(OBJS)
	rm -rf $(OBJS_LIB)

fclean: clean
	rm -rf $(LIB)
	rm -rf $(NAME)

re: fclean all
