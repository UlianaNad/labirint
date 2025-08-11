#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"

# define TILE_SIZE 64

// Key codes for Windows (MiniLibX)
# define KEY_W      87
# define KEY_A      65
# define KEY_S      83
# define KEY_D      68
# define KEY_UP     38
# define KEY_DOWN   40
# define KEY_LEFT   37
# define KEY_RIGHT  39
# define KEY_ESC    27

typedef struct s_game
{
    void    *mlx;
    void    *win;
    char    **map;
    int     width;
    int     height;
    int     player_x;
    int     player_y;
    int     collectibles;
    int     moves;

    void    *tex_wall;
    void    *tex_floor;
    void    *tex_player;
    void    *tex_collect;
    void    *tex_exit;
}   t_game;

// main
int     main(int argc, char **argv);

// Map parsing & validation
char    **parse_map(char *filename);
void    validate_map(char **map);
bool    check_path(char **map);
void    flood_fill(char **map, int x, int y);

// Utils
void    error_exit(char *msg);
bool    has_extension(char *filename, char *ext);
char    **append_line_to_map(char **map, char *line);
int     count_lines(char **map);
int     count_all_collectibles(char **map);
void    find_player_position(char **map, int *px, int *py);
void    free_map(char **map);
char    **duplicate_map(char **map);

// Game init / exit
void    game_init(t_game *game, char **map);
int     game_exit(t_game *game);
int     close_window(t_game *game);

// Rendering & input
void    render_map(t_game *game);
int     handle_key(int keycode, t_game *game);

#endif
