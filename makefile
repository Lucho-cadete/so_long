# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucho <lucho@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/25 09:35:50 by luimarti          #+#    #+#              #
#    Updated: 2025/12/12 22:56:59 by lucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = $(HOME)/MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_INCLUDE = -I$(MLX_DIR)/include
LDFLAGS = -lglfw -ldl -pthread -lm
FILES = so_long.c \
		get_next_line.c \
		get_next_line_utils.c \
		map_validation.c \
		map_validation2.c \
		box_of_tools.c \
		validate_path.c \
		flood_fill.c \
		game.c
OBJ_DIR = o_files
OBJS = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
RM = rm -f

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LDFLAGS) -o $(NAME)
	@echo "✅ $(NAME) compiled with MLX42!"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "🧹 Object files removed!"
	@$(RM) $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "🗑️  Full clean done!"
	@$(RM) $(NAME)

re: fclean all
	@echo "🔁 Rebuilding project..."

.PHONY: all clean fclean re