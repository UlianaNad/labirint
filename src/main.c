#include "../incl/so_long.h"

int main(int argc, char **argv)
{
    t_game game;
    char **map;

    if (argc != 2)
        error_exit("Usage: ./so_long <map.ber>");

    if (!has_extension(argv[1], ".ber"))
        error_exit("Error\nMap file must have .ber extension");

    map = parse_map(argv[1]);
    validate_map(map);

    game_init(&game, map);

    // initial render
    render_map(&game);

    // setup events
    mlx_key_hook(game.mlx, handle_key, &game);
    mlx_close_hook(game.mlx, close_window, &game); // if available; otherwise handle ESC in key

    mlx_loop(game.mlx);

    // cleanup (normally unreachable because mlx_loop is blocking; game_exit calls mlx_terminate)
    game_exit(&game);
    return (0);
}
