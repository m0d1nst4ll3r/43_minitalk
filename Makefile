# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 10:29:07 by rapohlen          #+#    #+#              #
#    Updated: 2025/12/01 20:30:00 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinc -Ilibft/inc -D VERBOSE=1 -D VERBOSE_ERR=1

SRCDIR		= src/

SRC_S		= $(addprefix $(SRCDIR), server.c server_loop.c server_print.c server_receive.c)
SRC_C		= $(addprefix $(SRCDIR), client.c client_send.c)
SRC			= $(addprefix $(SRCDIR), util_sig.c)

OBJ_S		= $(SRC_S:.c=.o)
OBJ_C		= $(SRC_C:.c=.o)
OBJ			= $(SRC:.c=.o)

NAME_S		= server
NAME_C		= client
NAME		= $(NAME_C) $(NAME_S)

LIB			= libft/libft.a

all:		$(NAME)

bonus:		all

$(NAME_S):	$(OBJ_S) $(OBJ) $(LIB) 
			$(CC) $(CFLAGS) -o $@ $^

$(NAME_C):	$(OBJ_C) $(OBJ) $(LIB) 
			$(CC) $(CFLAGS) -o $@ $^

$(LIB):
			$(MAKE) -C libft

clean:
			$(MAKE) clean -C libft
			rm -f $(OBJ_S) $(OBJ_C) $(OBJ)

fclean:		clean
			$(MAKE) fclean -C libft
			rm -f $(NAME)

re:			fclean all

.PHONY: clean fclean all
