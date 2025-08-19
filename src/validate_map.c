#include "../incl/so_long.h"

void validate_map(char **map)
{
    int y = 0;
    int player_count = 0;
    int exit_count = 0;
    int collectibles = 0;

    while (map[y])
    {
        int x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'P')
                player_count++;
            else if (map[y][x] == 'E')
                exit_count++;
            else if (map[y][x] == 'C')
                collectibles++;
            else if (map[y][x] != '1' && map[y][x] != '0')
                error_exit("Error\nInvalid map character");
            x++;
        }
        y++;
    }

    if (player_count != 1)
        error_exit("Error\nMap must have exactly 1 player");
    if (exit_count < 1)
        error_exit("Error\nMap must have at least 1 exit");
    if (collectibles < 1)
        error_exit("Error\nMap must have at least 1 collectible");
}
