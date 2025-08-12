NAME        := so_long
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft -IMLX42/include
LIBS        := -LMLX42/build -lmlx42 -lglfw3 -lopengl32 -lgdi32 -lwinmm

SRC_DIR     := src
SRC_FILES   := main.c game.c map.c render.c events.c
SRC         := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR     := obj
OBJ         := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

MLX_DIR     := MLX42
MLX_LIB     := $(MLX_DIR)/build/libmlx42.a

all: $(MLX_LIB) $(NAME)

# Головна збірка
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)

# Компіляція .c у .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MLX_LIB) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Збірка libft
$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Error: libft not found!"; \
		exit 1; \
	fi
	$(MAKE) -C $(LIBFT_DIR)

# Клонування та збірка MLX42
$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		echo "Configuring MLX42 with CMake..."; \
		cmake -S $(MLX_DIR) -B $(MLX_DIR)/build; \
	fi
	cmake --build $(MLX_DIR)/build --config Release

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(MLX_DIR)/build

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
