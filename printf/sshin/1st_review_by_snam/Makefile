# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swshin <swshin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/09 11:22:40 by sshin             #+#    #+#              #
#    Updated: 2021/06/15 23:00:08 by swshin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f

INCS		= ./incs

SRCS_DIR	= ./srcs/
SRCS_LST	= ft_printf.c \
				print_by_type.c \
				print_nbr.c \
				ft_printf_utils.c
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_LST))

OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= ./libft
LIBFT_LIB	= libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCS) -c $< -o $@

$(NAME): $(OBJS)
	make all -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT_LIB) $@
	$(AR) $@ $^

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
