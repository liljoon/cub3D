# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 20:23:57 by isunwoo           #+#    #+#              #
#    Updated: 2023/05/20 17:20:33 by isunwoo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= 	cc
CFLAGS	=	-g
#-Wall -Wextra -Werror
NAME	=	cub3D

SRCS	=	main.c\
			raycasting.c\
			init_app.c\

OBJS	=	$(SRCS:.c=.o)

INCS	=	cub3D.h\

ON_CLUSTER = 1

MLX_L	=	-lmlx -framework OpenGL -framework AppKit
MLX_I	=

ifeq ($(ON_CLUSTER) , 0)
MLX_L	+= -L./minilibx_opengl_20191021
MLX_I	+= -I./minilibx_opengl_20191021
endif

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(MLX_L)

.SUFFIXES : .c .o
.c.o : $(INCS)
	$(CC) -c $(CFLAGS) $< -o $@ $(MLX_I)

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME) $(OBJS)

re :
	make fclean
	make all

.PHONY : all clean fclean re
