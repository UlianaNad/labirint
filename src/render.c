// render_map: малює всю карту у вікні
void render_map(t_game *game)
{
    for (y = 0; y < game->height; y++)
    {
        for (x = 0; x < game->width; x++)
        {
            char tile = game->map[y][x];

            // 1. Спочатку малюємо підлогу (щоб фон завжди був)
            mlx_put_image_to_window(game->mlx, game->win, game->tex_floor,
                                    x * TILE_SIZE, y * TILE_SIZE);

            // 2. Малюємо стіну
            if (tile == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->tex_wall,
                                        x * TILE_SIZE, y * TILE_SIZE);

            // 3. Малюємо collectible
            else if (tile == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->tex_collect,
                                        x * TILE_SIZE, y * TILE_SIZE);

            // 4. Малюємо вихід
            else if (tile == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->tex_exit,
                                        x * TILE_SIZE, y * TILE_SIZE);

            // 5. Малюємо гравця
            if (x == game->player_x && y == game->player_y)
                mlx_put_image_to_window(game->mlx, game->win, game->tex_player,
                                        x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}
