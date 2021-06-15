# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sshin <sshin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/09 11:22:40 by sshin             #+#    #+#              #
#    Updated: 2021/06/13 16:08:15 by sshin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADER = ft_printf.h

SRCS		= ./ft_printf.c \
				./print_by_type.c \
				./print_nbr.c \
				./ft_printf_utils.c \

OBJS		= $(SRCS:.c=.o)

all : $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make all -C libft/
	cp ./libft/libft.a $@
	ar -rcs $@ $^

clean :
	rm -f $(OBJS)
	make clean -C ./libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C ./libft

re : fclean all

.PHONY: all clean fclean re
