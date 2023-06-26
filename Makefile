# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 20:23:57 by isunwoo           #+#    #+#              #
#    Updated: 2023/06/26 15:03:54 by isunwoo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= 	cc
CFLAGS	=	-g
#-Wall -Wextra -Werror
NAME	=	cub3D

GNL_SRC	=	gnl/get_next_line.c\
			gnl/get_next_line_utils.c\

SRCS	=	main.c\
			raycasting.c\
			init_app.c\

OBJS	=	$(SRCS:.c=.o)

INCS	=	cub3D.h\
			gnl/gnl.h\

ON_CLUSTER = 1

MLX_L	=	-lmlx -framework OpenGL -framework AppKit
MLX_I	=

ifeq ($(ON_CLUSTER) , 0)
MLX_L	+= -L./minilibx_opengl_20191021
MLX_I	+= -I./minilibx_opengl_20191021
endif

LDFLAGS = -L./libft -lft
LDFLAGS += $(MLX_L)

$(NAME) : $(OBJS)
	make -C ./libft
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.SUFFIXES : .c .o
.c.o : $(INCS) $(SRCS)
	$(CC) -c $(CFLAGS) $< -o $@ $(MLX_I)

all : $(NAME)

clean :
	make clean -C ./libft
	rm -f $(OBJS)

fclean : clean
	make fclean -C ./libft
	rm -f $(NAME) $(OBJS)

re :
	make fclean
	make all

.PHONY : all clean fclean re
