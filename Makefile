# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yham <yham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 20:23:57 by isunwoo           #+#    #+#              #
#    Updated: 2023/06/27 17:02:02 by yham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= 	cc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	cub3D

GNL_SRC	=	gnl/get_next_line.c\
			gnl/get_next_line_utils.c\

SRCS	=	main.c\
			raycasting.c\
			raycasting_utils.c\
			init_app.c\
			parsing.c\
			parsing_map.c\
			parsing_read.c\
			parsing_check.c\
			parsing_utils.c\
			player_movement.c\
			utils.c\
			free.c\
			$(GNL_SRC)\

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
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

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
