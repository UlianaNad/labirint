#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"

# define TILE_SIZE 64

// keycodes from MLX42 are passed via mlx_key_data; keep symbolic names for clarity
# define KEY_W      MLX_KEY_W
# define KEY_A      MLX_KEY_A
# define KEY_S      MLX_KEY_S
# define KEY_D      MLX_KEY_D
# define KEY_UP     MLX_KEY_UP
# define KEY_DOWN   MLX_KEY_DOWN
# define KEY_LEFT   MLX_KEY_LEFT
# define KEY_RIGHT  MLX_KEY_RIGHT
# define KEY_ESC    MLX_KEY_ESCAPE

typedef struct s_game
{
    mlx_t           *mlx;
    // no separate win in MLX42; mlx_t contains window
    char            **map;
    int             width;
    int             height;
    int             player_x;
    int             player_y;
    int             collectibles;
    int             moves;

    mlx_image_t     *img_wall;
    mlx_image_t     *img_floor;
    mlx_image_t     *img_player;
    mlx_image_t     *img_collect;
    mlx_image_t     *img_exit;

    mlx_texture_t   *tex_wall;
    mlx_texture_t   *tex_floor;
    mlx_texture_t   *tex_player;
    mlx_texture_t   *tex_collect;
    mlx_texture_t   *tex_exit;
}   t_game;

/* map / utils */
char    **parse_map(char *filename);
void    validate_map(char **map);
bool    check_path(char **map);
void    flood_fill(char **map, int x, int y);

void    error_exit(char *msg);
bool    has_extension(char *filename, char *ext);
char    **append_line_to_map(char **map, char *line);
int     count_lines(char **map);
int     count_all_collectibles(char **map);
void    find_player_position(char **map, int *px, int *py);
void    free_map(char **map);
char    **duplicate_map(char **map);

/* game */
void    game_init(t_game *game, char **map);
void    game_exit(t_game *game);
void    render_map(t_game *game);

/* events */
void    handle_key(struct mlx_key_data keydata, void *param);
void    close_window(void *param);

#endif
