# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 10:29:07 by rapohlen          #+#    #+#              #
#    Updated: 2025/11/27 17:22:27 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinc -Ilibft/inc

SRCDIR		= src/

SRC_S		= $(addprefix $(SRCDIR), server.c server_error.c server_receive.c)
SRC_C		= $(addprefix $(SRCDIR), client.c client_error.c client_send.c)
SRC			= $(addprefix $(SRCDIR), util.c util_sig.c util_list.c)

OBJ_S		= $(SRC_S:.c=.o)
OBJ_C		= $(SRC_C:.c=.o)
OBJ			= $(SRC:.c=.o)

NAME_S		= server
NAME_C		= client
NAME		= $(NAME_C) $(NAME_S)

LIB			= libft/libft.a

all:		$(NAME)

bonus:		all

$(NAME_S):	$(OBJ_S) $(OBJ)
			make -C libft
			$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(NAME_C):	$(OBJ_C) $(OBJ)
			make -C libft
			$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
			make clean -C libft
			rm -f $(OBJ_S) $(OBJ_C) $(OBJ)

fclean:		clean
			make fclean -C libft
			rm -f $(NAME)

re:			fclean all

.PHONY: clean fclean all
