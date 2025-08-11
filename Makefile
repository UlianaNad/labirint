# **************************************************************************** #
#                                  SETTINGS                                    #
# **************************************************************************** #

NAME        := so_long
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror
INCLUDES    := -Iinclude -Ilibft -Iminilibx-win
MLX_FLAGS   := -Lminilibx-win -lmlx -lopengl32 -lwinmm -lgdi32

# **************************************************************************** #
#                                  SOURCES                                     #
# **************************************************************************** #

SRC_DIR     := src
SRC_FILES   := main.c game.c map.c render.c events.c
SRC         := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR     := obj
OBJ         := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# **************************************************************************** #
#                                  LIBRARIES                                   #
# **************************************************************************** #

LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

MLX_DIR     := minilibx-win
MLX         := $(MLX_DIR)/libmlx.a

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
