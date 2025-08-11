// main: точка входу
int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        error_exit("Usage: ./so_long map.ber");

    if (!has_extension(argv[1], ".ber"))
        error_exit("Error\nMap file must have .ber extension");

    char **map = parse_map(argv[1]);
    validate_map(map);
    game_init(&game, map);

    render_map(&game);

    // у main.c (після render_map)
    mlx_key_hook(game.win, handle_key, &game);
    mlx_hook(game.win, 17, 0, close_window, &game);

    mlx_key_hook(game.win, handle_key, &game);
    mlx_hook(game.win, 17, 0, game_exit, &game);

    mlx_loop(game.mlx);
    return (0);
}