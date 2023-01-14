# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 20:17:58 by libacchu          #+#    #+#              #
#    Updated: 2023/01/14 15:35:20 by obibby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
OBJ_DIR =	obj/
LIBFT	=	./libft/
LIBMLX	=	./minilibx_linux/
SRC_DIR =	src/
SRC		=	main.c \
			free.c \
			error_check.c \
			err_utils.c \
			err_tex_check.c \
			err_rgb_check.c \
			err_map_check.c \
			err_map_check2.c \
			err_file_check.c \
			key_hooks.c \
			movement.c \
			exit.c
INC		=	includes/cub3D.h
SYS		=	$(shell uname -s)
ifeq ($(SYS), Linux)
    LIBS    =    -Lminilibx_linux -lm -lmlx -lXext -lX11 -Iminilibx_linux $(LIBFT)libft.a
endif
ifeq ($(SYS), Darwin)
    LIBS    =    -L/usr/X11/lib -lX11 -lXext $(LIBFT)libft.a ./minilibx_linux/libmlx.a
endif
SRCS	=	$(addprefix $(SRC_DIR), $(SRC))
OBJ		=	$(SRCS:%.c=$(OBJ_DIR)%.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
RESET	=	\33[0m

all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "\r$(GREY)Compiling $(BLUE)$<"
	@$(CC) $(CFLAGS) -c -g $< -o $@

$(NAME) : $(OBJ) $(INC)
	make re -C $(LIBFT)
	make -C $(LIBMLX)
	@printf "\33[2K\r$(GREY)Compiling $(BLUE)$(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean :
	@printf "$(GREY)Removing $(BLUE)$(OBJ)$(RESET)\n"
	@rm -fr $(OBJ_DIR)

fclean : clean
	@printf "$(GREY)Removing $(BLUE)$(NAME)$(RESET)\n"
	make fclean -C $(LIBFT)
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re