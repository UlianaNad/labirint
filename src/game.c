// game_init: створює вікно та завантажує ресурси
void game_init(t_game *game, char **map)
{
    game->map = map;
    game->height = count_lines(map);
    game->width = ft_strlen(map[0]);
    game->moves = 0;
    game->collectibles = count_all_collectibles(map);

    find_player_position(map, &game->player_x, &game->player_y);

    game->mlx = mlx_init();
    if (!game->mlx)
        error_exit("Error\nFailed to initialize MLX");

    game->win = mlx_new_window(game->mlx,
                               game->width * TILE_SIZE,
                               game->height * TILE_SIZE,
                               "so_long");

    // завантаження текстур
    game->tex_wall = mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm", &w, &h);
    game->tex_floor = mlx_xpm_file_to_image(game->mlx, "assets/floor.xpm", &w, &h);
    game->tex_player = mlx_xpm_file_to_image(game->mlx, "assets/player.xpm", &w, &h);
    game->tex_collect = mlx_xpm_file_to_image(game->mlx, "assets/collectible.xpm", &w, &h);
    game->tex_exit = mlx_xpm_file_to_image(game->mlx, "assets/exit.xpm", &w, &h);
}

// game_exit: закриває гру та звільняє пам'ять
int game_exit(t_game *game)
{
    mlx_destroy_image(game->mlx, game->tex_wall);
    mlx_destroy_image(game->mlx, game->tex_floor);
    mlx_destroy_image(game->mlx, game->tex_player);
    mlx_destroy_image(game->mlx, game->tex_collect);
    mlx_destroy_image(game->mlx, game->tex_exit);

    mlx_destroy_window(game->mlx, game->win);

    free_map(game->map);
    exit(0);
}


