NAME        = so_long
CC          = cc
SRC_DIR     = src
OBJ_DIR     = obj
INCL_DIR    = include

SRC_FILES   = main.c game.c render.c events.c \
              map.c flood_fill.c input.c utils.c validate_map.c cleanup.c
SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX42_DIR   = MLX42
MLX_BUILD   = $(MLX42_DIR)/build
MLX_LIB     = $(MLX_BUILD)/libmlx42.a

CFLAGS      = -Wall -Wextra -Werror -I$(INCL_DIR) -I$(LIBFT_DIR) -I$(MLX42_DIR)/include
LIBS        = -L$(MLX_BUILD) -lmlx42 -lglfw -ldl -lm -lpthread

all: $(MLX_LIB) $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(MLX_LIB)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Error: libft not found!"; exit 1; \
	fi
	$(MAKE) -C $(LIBFT_DIR)

$(MLX42_DIR):
	@if [ ! -d "$@" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $@; \
	fi

$(MLX_LIB): $(MLX42_DIR)
	cmake $(MLX42_DIR) -B $(MLX_BUILD)
	make -C $(MLX_BUILD) -j4

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)
	rm -rf $(MLX_BUILD)

re: fclean all

.PHONY: all clean fclean re
