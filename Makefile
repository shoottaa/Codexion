# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/12 15:19:47 by egaudich          #+#    #+#              #
#    Updated: 2026/03/12 15:19:47 by egaudich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCDIR = coders
SRC = $(SRCDIR)/main.c \
      $(SRCDIR)/args.c \
      $(SRCDIR)/dongle.c \
      $(SRCDIR)/pqueue.c \
      $(SRCDIR)/sim.c
OBJ = $(SRC:.c=.o)
INCLUDES = -I$(SRCDIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
