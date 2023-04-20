# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 10:11:24 by fkrug             #+#    #+#              #
#    Updated: 2023/04/20 09:28:26 by fkrug            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libget_next_line.a

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = get_next_line.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(OBJ)
	ar rcs $(NAME) $(OBJ)


test:
	@$(CC) -o a.out test.c -L. -lget_next_line
#	@echo "Test file:"
#	@cat test1.txt
#	@echo "|-->end"
	@./a.out

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all