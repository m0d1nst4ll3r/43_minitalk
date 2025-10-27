# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 10:29:07 by rapohlen          #+#    #+#              #
#    Updated: 2025/10/22 16:25:23 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I includes/

SRCDIR		= srcs/
SRCDIR_S	= srcs/server/
SRCDIR_C	= srcs/client/

SRC_S		= $(addprefix $(SRCDIR_S), server.c server_error.c server_receive.c)
SRC_C		= $(addprefix $(SRCDIR_C), client.c client_error.c client_send.c)
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
			rm -f $(NAME_S) $(NAME_C)

re:			fclean all

.PHONY: clean fclean all
