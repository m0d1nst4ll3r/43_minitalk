# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 10:29:07 by rapohlen          #+#    #+#              #
#    Updated: 2025/11/27 13:27:34 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinc

SRCDIR		= src/

SRC_S		= $(addprefix $(SRCDIR), server.c server_error.c server_receive.c)
SRC_C		= $(addprefix $(SRCDIR), client.c client_error.c client_send.c)
SRC			= $(addprefix $(SRCDIR), util.c util_sig.c util_list.c)

OBJ_S		= $(SRC_S:.c=.o)
OBJ_C		= $(SRC_C:.c=.o)
OBJ			= $(SRC:.c=.o)

NAME_S		= server
NAME_C		= client
NAME		= $(NAME_S) $(NAME_C)

all:		$(NAME)

$(NAME_S):	$(OBJ_S) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $^

$(NAME_C):	$(OBJ_C) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $^

clean:
			rm -f $(OBJ_S) $(OBJ_C) $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY: clean fclean all
