# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 11:38:23 by ekosnick          #+#    #+#              #
#    Updated: 2025/05/05 13:49:23 by ekosnick         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# Contains the X11 and MLX header files
INCLUDES = -I/usr/include -Imlxx

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

# Link X11 and MLX
MLX_FLAGS = -Lmlxx -lmlxx -L/usr/lib/X11 -lXext -lX11

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)