#include "so_long.h"

// handle_key: обробка натискання клавіш
int handle_key(int keycode, t_game *game)
{
    new_x = game->player_x;
    new_y = game->player_y;

    // W / UP
    if (keycode == KEY_W || keycode == KEY_UP)
        new_y -= 1;

    // S / DOWN
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        new_y += 1;

    // A / LEFT
    else if (keycode == KEY_A || keycode == KEY_LEFT)
        new_x -= 1;

    // D / RIGHT
    else if (keycode == KEY_D || keycode == KEY_RIGHT)
        new_x += 1;

    // ESC — вихід
    else if (keycode == KEY_ESC)
        game_exit(game);

    // Якщо нова позиція — стіна, рух скасовується
    if (game->map[new_y][new_x] == '1')
        return (0);

    // Якщо на новій позиції collectible
    if (game->map[new_y][new_x] == 'C')
    {
        game->collectibles--;
        game->map[new_y][new_x] = '0'; // прибираємо з карти
    }

    // Якщо на новій позиції вихід
    if (game->map[new_y][new_x] == 'E')
    {
        if (game->collectibles == 0) // виграли
            game_exit(game);
        else
            return (0); // якщо не всі зібрані — не заходимо
    }

    // Оновлюємо координати гравця
    game->player_x = new_x;
    game->player_y = new_y;

    // Лічильник кроків
    game->moves++;
    ft_printf("Moves: %d\n", game->moves);

    // Перемальовуємо карту
    render_map(game);

    return (0);
}
// close_window: викликається при натисканні на хрестик
int close_window(t_game *game)
{
    game_exit(game);
    return (0);
}
