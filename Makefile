# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 11:27:05 by nmeintje          #+#    #+#              #
#    Updated: 2025/05/06 13:55:39 by mdahlstr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

#directories
MLX_DIR = ./libraries/MLX42
LIBFT_DIR = ./libraries/libft
SRC_DIR = ./sources
OBJ_DIR = $(SRC_DIR)/objects


#source and object files
SOURCES = main.c \
	parse_file.c \
	p_get_config.c \
	p_get_map.c \
	p_get_spawn_pos.c \
	p_spaces_to_zeroes.c \
	p_validate_and_count_lines.c \
	p_validate_map.c \
	p_validate_input.c \
	p_pad_map_lines.c \
	parsing_utils.c \
	parsing_utils2.c \
	parsing_colours.c \
	parse_config.c \
	parsing_map_grid.c \
	parsing_error.c \
	cube_errors.c \
	cube_hooks.c \
	cube_draw.c \
	cube_player.c \
	cube_movement.c \
	cube_rotation.c \
	cube_init.c \
	cube_exit.c \
	cube_exit2.c \
	cube_raycasting.c \
	raycasting_utils.c \
	cube_textures.c

SRCS = $(addprefix $(SRC_DIR)/,$(SOURCES))

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

HEADERS = -I ./include -I $(MLX_DIR)/include -I $(LIBFT_DIR)

MLXLIB = $(MLX_DIR)/build/libmlx42.a
LIBFT = $(LIBFT_DIR)/libft.a

# MLX42 dependencies - dl dynamically loaded lib, glfw graphics library framework m math library
MLXLIB_FLAGS = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -lm
# MLXLIB_FLAGS = $(MLX_DIR)/build/libmlx42.a -lglfw -framework Cocoa -framework OpenGL -framework IOKit
LIBFT_FLAGS = -L $(LIBFT_DIR) -lft

CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

RM = rm -rf

all: $(LIBFT) $(MLXLIB) $(NAME)

$(MLXLIB):
	@cd libraries && git clone https://github.com/codam-coding-college/MLX42.git
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBFT_FLAGS) $(MLXLIB) $(MLXLIB_FLAGS) $(HEADERS) -o $@
	@echo "$(NAME) compiled successfully"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(MLX_DIR)/build
	@make -C $(LIBFT_DIR) clean
		
fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(MLX_DIR)
	@make -C $(LIBFT_DIR) fclean
				
re:	fclean all

.PHONY: all clean fclean re

