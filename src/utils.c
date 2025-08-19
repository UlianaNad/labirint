#include "../incl/so_long.h"

char **parse_map(char *filename)
{
    int     fd;
    char    *line;
    char    **map = NULL;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("Error\nCannot open map file");

    while ((line = get_next_line(fd)))
    {
        map = append_line_to_map(map, line);
        free(line);
    }
    close(fd);
    if (!map)
        error_exit("Error\nEmpty map file");
    return map;
}

int count_lines(char **map)
{
    int i = 0;
    while (map[i])
        i++;
    return i;
}

int count_all_collectibles(char **map)
{
    int y = 0;
    int count = 0;

    while (map[y])
    {
        int x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'C')
                count++;
            x++;
        }
        y++;
    }
    return count;
}

void find_player_position(char **map, int *px, int *py)
{
    int y = 0;

    while (map[y])
    {
        int x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'P')
            {
                *px = x;
                *py = y;
                return;
            }
            x++;
        }
        y++;
    }
}

void free_map(char **map)
{
    int i = 0;

    if (!map)
        return;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}
