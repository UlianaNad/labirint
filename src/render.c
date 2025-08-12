#include "../incl/so_long.h"

void render_map(t_game *game)
{
    int y = 0;

    // MLX42 draws images to the window via mlx_image_to_window
    // We'll place copies of the preloaded images at tile positions.
    // Note: depending on MLX42, images can be moved by setting img->instances[0].x/y or using mlx_image_to_window.

    while (y < game->height)
    {
        int x = 0;
        while (x < game->width)
        {
            char tile = game->map[y][x];
            int px = x * TILE_SIZE;
            int py = y * TILE_SIZE;

            // draw floor first
            mlx_image_to_window(game->mlx, game->img_floor, px, py);

            if (tile == '1')
                mlx_image_to_window(game->mlx, game->img_wall, px, py);
            else if (tile == 'C')
                mlx_image_to_window(game->mlx, game->img_collect, px, py);
            else if (tile == 'E')
                mlx_image_to_window(game->mlx, game->img_exit, px, py);

            // draw player on top if coordinates match
            if (x == game->player_x && y == game->player_y)
                mlx_image_to_window(game->mlx, game->img_player, px, py);

            x++;
        }
        y++;
    }
}
