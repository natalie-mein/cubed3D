# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 11:27:05 by nmeintje          #+#    #+#              #
#    Updated: 2025/04/02 13:30:38 by mdahlstr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

#directories
MLX_DIR = ./libraries/MLX42
LIBFT_DIR = ./libraries/libft
SRC_DIR = ./sources
###BONUS_DIR = ./bonus
OBJ_DIR = $(SRC_DIR)/objects
###BONUS_OBJ_DIR = $(BONUS_DIR)/bonus_objects

#source and object files
SOURCES = main.c \
	  cube_errors.c \
	  cube_hooks.c \
	  cube_validation.c

###BONUS = ./_bonus.c \

SRCS = $(addprefix $(SRC_DIR)/,$(SOURCES))
###BONUS_SRC = $(addprefix $(BONUS_DIR)/,$(BONUS))

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))
###BONUS_OBJS = $(patsubst %.c,$(BONUS_OBJ_DIR)/%.o,$(notdir $(BONUS)))

HEADERS = -I ./include -I $(MLX_DIR)/include -I $(LIBFT_DIR)
###BONUS_HEADERS = -I ./include_bonus -I $(MLX_DIR)

MLXLIB = $(MLX_DIR)/build/libmlx42.a
LIBFT = $(LIBFT_DIR)/libft.a

# MLX42 dependencies - dl dynamically loaded lib, glfw graphics library framework m math library

MLXLIB_FLAGS = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -lm
LIBFT_FLAGS = -L $(LIBFT_DIR) -lft

CC = cc
CFLAGS = -Wall -Wextra -Werror

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

###bonus: $(MLXLIB) $(BONUS_OBJS)
###	$(CC) $(BONUS_OBJS) $(MLXLIB) $(MLXLIB_FLAGS) $(BONUS_HEADERS) -o $(NAME)_bonus
###	@echo "$(NAME) bonus compiled successfully"

###(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(BONUS_OBJ_DIR)
###        @$(CC) $(CFLAGS) $(BONUS_HEADERS) -c $< -o $@

###$(BONUS_OBJ_DIR):
###	@mkdir -p $(BONUS_OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR)
###	@$(RM) $(BONUS_OBJ_DIR)
	@$(RM) $(MLX_DIR)/build
	@make -C $(LIBFT_DIR) clean
        
fclean: clean
	@$(RM) $(NAME)
###     @$(RM) $(NAME)_bonus
	@$(RM) $(MLX_DIR)
	@make -C $(LIBFT_DIR) fclean
                
re:	fclean all

.PHONY: all clean fclean re

