# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/26 17:11:06 by kilkim            #+#    #+#              #
#    Updated: 2020/04/26 17:11:07 by kilkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
C_FLAGS = -Wall -Wextra -Werror

LIB_D = libft
PTF_D = .
SRC_D = sources
INC_D = includes
OBJ_D = objects

all : obj $(NAME)

obj :
	@mkdir -p $(OBJ_D)
	@$(CC) $(C_FLAGS) -I $(LIB_D)/$(INC_D) -c $(LIB_D)/$(SRC_D)/*.c
	@$(CC) $(C_FLAGS) -I $(PTF_D)/$(INC_D) -c $(PTF_D)/$(SRC_D)/*.c
	@mv *.o $(OBJ_D)

$(NAME) :
	@ar rc $(NAME) $(OBJ_D)/*.o
	@ranlib $(NAME)

clean :
	@rm -rf $(OBJ_D)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
