#include "../incl/so_long.h"

void close_window(void *param)
{
    t_game *game = (t_game *)param;
    (void)game;
    // викликаємо game_exit для чистки
    if (game)
        game_exit(game);
    else
        exit(0);
}

void handle_key(struct mlx_key_data keydata, void *param)
{
    t_game *game = (t_game *)param;
    int new_x = game->player_x;
    int new_y = game->player_y;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == KEY_W || keydata.key == KEY_UP)
            new_y -= 1;
        else if (keydata.key == KEY_S || keydata.key == KEY_DOWN)
            new_y += 1;
        else if (keydata.key == KEY_A || keydata.key == KEY_LEFT)
            new_x -= 1;
        else if (keydata.key == KEY_D || keydata.key == KEY_RIGHT)
            new_x += 1;
        else if (keydata.key == KEY_ESC)
            game_exit(game);
        else
            return;

        // bounds check
        if (new_x < 0 || new_y < 0 || new_x >= game->width || new_y >= game->height)
            return;

        char dest = game->map[new_y][new_x];
        if (dest == '1')
            return;

        if (dest == 'C')
        {
            game->collectibles--;
            game->map[new_y][new_x] = '0';
        }

        if (dest == 'E')
        {
            if (game->collectibles == 0)
                game_exit(game);
            else
                return;
        }

        game->player_x = new_x;
        game->player_y = new_y;
        game->moves++;
        ft_printf("Moves: %d\n", game->moves);

        render_map(game);
    }
}
