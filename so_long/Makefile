# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 11:38:23 by ekosnick          #+#    #+#              #
#    Updated: 2025/05/08 11:26:59 by ekosnick         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# NAME = so_long

# CC = gcc

# SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c

# CFLAGS = -Wall -Wextra -Werror

# SRC+= mlx_png.c mlx_mouse.m
# OBJ1=$(SRC:.c=.o)
# OBJ=$(OBJ1:.m=.o)
# CFLAGS+=-O2

# # Contains the X11 and MLX header files
# INCLUDES = -I/usr/include -Imlxx

# .c.o:
# 	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

# # Link X11 and MLX
# MLX_FLAGS = -Lmlxx -lmlxx -L/usr/lib/X11 -lXext -lX11

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)


# Target executable name
NAME = so_long

# Compiler and compilation flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g # Added -g for debugging symbols
# Assuming mlx files are in 'mlx' directory and libft headers in 'libft'
INCLUDES = -Ilibft -Imlx

# MLX library flags (adjust paths and library names if necessary)
# -Lmlx tells the linker to look in the 'mlx' directory for libraries
# -lmlx might need to be more specific, e.g., -lmlx_Linux if you're using libmlx_Linux.a
# Adding -lm for math functions and -lbsd if needed by mlx.
MLX_FLAGS = -Lmlx -lmlx -lXext -lX11 -lm -lbsd

# Source files for the main application
SRCS_MAIN = so_long.c # Add other .c files for so_long if you have them

# Object files for the main application
OBJ_DIR_MAIN = obj
OBJS_MAIN = $(addprefix $(OBJ_DIR_MAIN)/, $(SRCS_MAIN:.c=.o))

# Libft source files, object directory, and object files
LIBFT_DIR = libft
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/*.c) # Get all .c files from libft
LIBFT_OBJ_DIR = $(LIBFT_DIR)/obj
LIBFT_OBJS = $(patsubst $(LIBFT_DIR)/%.c, $(LIBFT_OBJ_DIR)/%.o, $(LIBFT_SRCS))

# All object files
ALL_OBJS = $(OBJS_MAIN) $(LIBFT_OBJS)

# Default rule
all: $(NAME)

# Rule to create the target executable
$(NAME): $(ALL_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(ALL_OBJS) $(MLX_FLAGS)

# Rule to compile main source files into the main object directory
$(OBJ_DIR_MAIN)/%.o: %.c | $(OBJ_DIR_MAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile libft source files into the libft object directory
$(LIBFT_OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c | $(LIBFT_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to create the object directories if they don't exist
$(OBJ_DIR_MAIN):
	mkdir -p $(OBJ_DIR_MAIN)

$(LIBFT_OBJ_DIR):
	mkdir -p $(LIBFT_OBJ_DIR)

# Clean rule: remove object files
clean:
	rm -rf $(OBJ_DIR_MAIN)
	rm -rf $(LIBFT_OBJ_DIR)

# Full clean rule: remove object files and the executable
fclean: clean
	rm -f $(NAME)

# Re-compile rule: full clean then build all
re: fclean all

# Phony targets (targets that are not actual files)
.PHONY: all clean fclean re