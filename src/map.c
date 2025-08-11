#include "so_long.h"

char **parse_map(char *filename)
{
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("Error\nCan't open map file");

    map = NULL;
    while (line = get_next_line(fd))
    {
        // видалити \n в кінці, якщо є
        map = append_line_to_map(map, line);
        free(line);
    }
    close(fd);

    if (!map)
        error_exit("Error\nEmpty map file");

    return map;
}


// validate_map: перевіряє всі правила з сабджекту
void validate_map(char **map)
{
    width = ft_strlen(map[0]);
    height = count_lines(map);

    count_p = 0;
    count_e = 0;
    count_c = 0;

    for (y = 0; y < height; y++)
    {
        if (ft_strlen(map[y]) != width)
            error_exit("Error\nMap is not rectangular");

        for (x = 0; x < width; x++)
        {
            char tile = map[y][x];
            if (tile not in ['0','1','C','E','P'])
                error_exit("Error\nInvalid character in map");

            if (y == 0 || y == height-1 || x == 0 || x == width-1)
            {
                if (tile != '1')
                    error_exit("Error\nMap is not surrounded by walls");
            }

            if (tile == 'P') count_p++;
            if (tile == 'E') count_e++;
            if (tile == 'C') count_c++;
        }
    }

    if (count_p != 1 || count_e != 1 || count_c < 1)
        error_exit("Error\nInvalid number of P, E, or C");

    if (!check_path(map))
        error_exit("Error\nNo valid path to collect all items and exit");
}

// check_path: перевіряє, чи можна дістатися до всіх C та E
bool check_path(char **map)
{
    copy_map = duplicate_map(map);

    // знайти координати гравця
    find_player_position(copy_map, &px, &py);

    // BFS або DFS для обходу карти
    flood_fill(copy_map, px, py);

    // перевірити, що всі C та E були відвідані
    for (y = 0; copy_map[y]; y++)
        for (x = 0; copy_map[y][x]; x++)
            if (map[y][x] == 'C' && copy_map[y][x] != 'V')
                return false;
            if (map[y][x] == 'E' && copy_map[y][x] != 'V')
                return false;

    free_map(copy_map);
    return true;
}
