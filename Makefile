# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obibby <obibby@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 20:17:58 by libacchu          #+#    #+#              #
#    Updated: 2023/01/09 13:42:08 by obibby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
OBJ_DIR =	obj/
LIBFT	=	./libft/
SRC		=	src/main.c
INC		=
LIBS	=	-L/usr/X11/lib -lX11 -lXext $(LIBFT)libft.a
OBJ		=	$(SRC:%.c=$(OBJ_DIR)%.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
RESET	=	\33[0m

all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "\r$(GREY)Compiling $(BLUE)$<"
	@$(CC) $(CFLAGS) -c -g $< -o $@

$(NAME) : $(OBJ) $()
	make re -C $(LIBFT)
	#make -C $(LIBMLX)
	@printf "\33[2K\r$(GREY)Compiling $(BLUE)$(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean :
	@printf "$(GREY)Removing $(BLUE)$(OBJ)$(RESET)\n"
	@rm -fr $(OBJ_DIR)

fclean : clean
	@printf "$(GREY)Removing $(BLUE)$(NAME)$(RESET)\n"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re