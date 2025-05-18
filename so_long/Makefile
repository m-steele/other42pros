# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 11:38:23 by ekosnick          #+#    #+#              #
#    Updated: 2025/05/18 07:42:00 by ekosnick         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Ilibft -Imlx

# MLX library flags -lm for math functions and -lbsd
MLX_FLAGS = -Lmlx -lmlx -lXext -lX11 -lm -lbsd

# Source files for the main application
SRCS_MAIN = so_long.c load_map.c get_map_utils.c map_valid.c \
			key_press.c

# Object files for the main application
OBJ_DIR_MAIN = obj
OBJS_MAIN = $(addprefix $(OBJ_DIR_MAIN)/, $(SRCS_MAIN:.c=.o))

# Libft source files, object directory, and object files
LIBFT_DIR = libft
LIBFT_SRCS = 	$(LIBFT_DIR)/ft_abs.c $(LIBFT_DIR)/ft_atoi.c \
				$(LIBFT_DIR)/ft_bzero.c $(LIBFT_DIR)/ft_calloc.c \
				$(LIBFT_DIR)/ft_isalnum.c $(LIBFT_DIR)/ft_isalpha.c \
				$(LIBFT_DIR)/ft_isascii.c $(LIBFT_DIR)/ft_isdigit.c \
				$(LIBFT_DIR)/ft_isprint.c $(LIBFT_DIR)/ft_itoa.c \
				$(LIBFT_DIR)/ft_lstadd_back.c $(LIBFT_DIR)/ft_lstadd_front.c \
				$(LIBFT_DIR)/ft_lstclear.c $(LIBFT_DIR)/ft_lstdelone.c \
				$(LIBFT_DIR)/ft_lstiter.c $(LIBFT_DIR)/ft_lstlast.c \
				$(LIBFT_DIR)/ft_lstmap.c $(LIBFT_DIR)/ft_lstnew.c \
				$(LIBFT_DIR)/ft_lstsize.c $(LIBFT_DIR)/ft_memchr.c \
				$(LIBFT_DIR)/ft_memcmp.c $(LIBFT_DIR)/ft_memcpy.c \
				$(LIBFT_DIR)/ft_memmove.c $(LIBFT_DIR)/ft_memset.c \
				$(LIBFT_DIR)/ft_printf.c $(LIBFT_DIR)/ft_putchar_fd.c \
				$(LIBFT_DIR)/ft_putendl_fd.c $(LIBFT_DIR)/ft_putnbr_fd.c \
				$(LIBFT_DIR)/ft_putstr_fd.c $(LIBFT_DIR)/ft_split.c \
				$(LIBFT_DIR)/ft_strchr.c $(LIBFT_DIR)/ft_strdup.c \
				$(LIBFT_DIR)/ft_striteri.c $(LIBFT_DIR)/ft_strjoin.c \
				$(LIBFT_DIR)/ft_strlcat.c $(LIBFT_DIR)/ft_strlcpy.c \
				$(LIBFT_DIR)/ft_strlen.c $(LIBFT_DIR)/ft_strmapi.c \
				$(LIBFT_DIR)/ft_strncmp.c $(LIBFT_DIR)/ft_strncpy.c \
				$(LIBFT_DIR)/ft_strnstr.c $(LIBFT_DIR)/ft_strrchr.c \
				$(LIBFT_DIR)/ft_strtrim.c $(LIBFT_DIR)/ft_substr.c \
				$(LIBFT_DIR)/ft_tolower.c $(LIBFT_DIR)/ft_toupper.c \
				$(LIBFT_DIR)/process_c.c $(LIBFT_DIR)/process_id.c \
				$(LIBFT_DIR)/process_p.c $(LIBFT_DIR)/process_s.c \
				$(LIBFT_DIR)/process_u.c $(LIBFT_DIR)/process_x.c \
				$(LIBFT_DIR)/process_xx.c $(LIBFT_DIR)/get_next_line.c

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