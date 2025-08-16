# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/03 12:28:58 by mjeremy           #+#    #+#              #
#    Updated: 2025/08/16 15:15:59 by mjeremy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

LIBFT_DIR	=	includes/libft
LIBFT		=	$(LIBFT_DIR)/libft.a

MLX_DIR		=	includes/minilibx
MLX			=	$(MLX_DIR)/libmlx.a

INCLUDES	=	-I includes -I $(LIBFT_DIR)/include -I $(MLX_DIR)

SRCS		=	src/color.c \
				src/hooks.c \
				src/image.c \
				src/init.c \
				src/main.c \
				src/mouse_hooks.c\
				src/parse.c \
				src/render.c \
				src/utils.c

OBJS		=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX) -lXext -lX11 -lm -o $(NAME)

$(LIBFT)	:
	make -C $(LIBFT_DIR)

$(MLX)		:
	make -C $(MLX_DIR)

%.o	:	%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean	:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean	:	clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re	:	fclean all

.PHONY	:	all clean fclean re
