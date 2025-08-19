NAME        := so_long
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft -IMLX42/include

SRC_DIR     := src
SRC_FILES   := main.c game.c render.c events.c \
               map.c flood_fill.c input.c utils.c validate_map.c cleanup.c
SRC         := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR     := obj
OBJ         := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

MLX_DIR     := MLX42
MLX_BUILD   := $(MLX_DIR)/build
MLX_LIB     := $(MLX_BUILD)/libmlx42.a

LIBS := -L$(MLX_BUILD) -lmlx42 -lglfw3 -lopengl32 -lgdi32
# Якщо glfw не знаходиться → спробуй замінити -lglfw3 на -lglfw

# -------------------- Rules --------------------

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# -------------------- Libft --------------------
$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Error: libft not found!"; exit 1; \
	fi
	$(MAKE) -C $(LIBFT_DIR)

# -------------------- MLX42 --------------------
$(MLX_LIB):
	@if [ ! -d "$(MLX_BUILD)" ]; then \
		echo "Building MLX42..."; \
		cmake -S $(MLX_DIR) -B $(MLX_BUILD) -G "MinGW Makefiles"; \
		cmake --build $(MLX_BUILD) --config Release; \
	fi
	@if [ ! -f "$(MLX_LIB)" ]; then \
		echo "Error: MLX42 build failed!"; exit 1; \
	fi

# -------------------- Clean --------------------
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
