#include "../incl/so_long.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* ------------------- Helpers ------------------- */

static char *strip_newline(char *s)
{
    size_t len;

    if (!s)
        return NULL;
    len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
    return s;
}

void error_exit(char *msg)
{
    if (msg)
        write(STDERR_FILENO, msg, strlen(msg));
    write(STDERR_FILENO, "\n", 1);
    exit(EXIT_FAILURE);
}

bool has_extension(char *filename, char *ext)
{
    size_t fn;
    size_t ex;

    if (!filename || !ext)
        return false;
    fn = strlen(filename);
    ex = strlen(ext);
    if (fn < ex)
        return false;
    return (strcmp(filename + fn - ex, ext) == 0);
}

/* ------------------- Map manipulation ------------------- */

char **append_line_to_map(char **map, char *line)
{
    int     old_count;
    char    **new_map;
    char    *dup_line;
    int     i;

    old_count = 0;
    if (line == NULL)
        return map;
    dup_line = strdup(strip_newline(line));
    if (!dup_line)
        error_exit("Error\nMemory allocation failed");
    if (map)
    {
        while (map[old_count])
            old_count++;
    }
    new_map = malloc(sizeof(char *) * (old_count + 2));
    if (!new_map)
        error_exit("Error\nMemory allocation failed");
    i = 0;
    while (i < old_count)
    {
        new_map[i] = map[i];
        i++;
    }
    new_map[old_count] = dup_line;
    new_map[old_count + 1] = NULL;
    if (map)
        free(map);
    return new_map;
}

int count_lines(char **map)
{
    int n;

    n = 0;
    if (!map)
        return 0;
    while (map[n])
        n++;
    return n;
}

int count_all_collectibles(char **map)
{
    int y;
    int x;
    int cnt;

    y = 0;
    cnt = 0;
    while (map && map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'C')
                cnt++;
            x++;
        }
        y++;
    }
    return cnt;
}

void find_player_position(char **map, int *px, int *py)
{
    int y;
    int x;

    if (!map || !px || !py)
        return;
    y = 0;
    while (map[y])
    {
        x = 0;
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
    *px = -1;
    *py = -1;
}

void free_map(char **map)
{
    int i;

    if (!map)
        return;
    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

char **duplicate_map(char **map)
{
    int     lines;
    char    **dup;
    int     i;

    if (!map)
        return NULL;
    lines = count_lines(map);
    dup = malloc(sizeof(char *) * (lines + 1));
    if (!dup)
        error_exit("Error\nMemory allocation failed");
    i = 0;
    while (i < lines)
    {
        dup[i] = strdup(map[i]);
        if (!dup[i])
        {
            while (--i >= 0)
                free(dup[i]);
            free(dup);
            error_exit("Error\nMemory allocation failed");
        }
        i++;
    }
    dup[lines] = NULL;
    return dup;
}

/* ------------------- Flood fill ------------------- */

void flood_fill(char **map, int sx, int sy)
{
    int h;
    int w;
    int stack_size;
    int top;
    int *sx_stack;
    int *sy_stack;

    if (!map)
        return;
    h = count_lines(map);
    w = strlen(map[0]);
    if (sy < 0 || sy >= h || sx < 0 || sx >= w)
        return;
    stack_size = 1024;
    top = 0;
    sx_stack = malloc(sizeof(int) * stack_size);
    sy_stack = malloc(sizeof(int) * stack_size);
    if (!sx_stack || !sy_stack)
        error_exit("Error\nMemory allocation failed");
    sx_stack[top] = sx;
    sy_stack[top] = sy;
    top++;
    while (top > 0)
    {
        int x;
        int y;
        char c;

        top--;
        x = sx_stack[top];
        y = sy_stack[top];
        if (y < 0 || y >= h || x < 0 || x >= (int)strlen(map[y]))
            continue;
        c = map[y][x];
        if (c == '1' || c == 'V')
            continue;
        map[y][x] = 'V';
        if (top + 4 > stack_size)
        {
            stack_size *= 2;
            sx_stack = realloc(sx_stack, sizeof(int) * stack_size);
            sy_stack = realloc(sy_stack, sizeof(int) * stack_size);
            if (!sx_stack || !sy_stack)
                error_exit("Error\nMemory allocation failed");
        }
        sx_stack[top] = x;     sy_stack[top] = y - 1; top++;
        sx_stack[top] = x;     sy_stack[top] = y + 1; top++;
        sx_stack[top] = x - 1; sy_stack[top] = y;     top++;
        sx_stack[top] = x + 1; sy_stack[top] = y;     top++;
    }
    free(sx_stack);
    free(sy_stack);
}

bool check_path(char **map)
{
    char **copy;
    int px;
    int py;
    int y;
    int x;

    if (!map)
        return false;
    copy = duplicate_map(map);
    if (!copy)
        return false;
    find_player_position(copy, &px, &py);
    if (px == -1 || py == -1)
    {
        free_map(copy);
        return false;
    }
    flood_fill(copy, px, py);
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'C' && copy[y][x] != 'V')
            {
                free_map(copy);
                return false;
            }
            if (map[y][x] == 'E' && copy[y][x] != 'V')
            {
                free_map(copy);
                return false;
            }
            x++;
        }
        y++;
    }
    free_map(copy);
    return true;
}

/* ------------------- Parse & validate ------------------- */

char **parse_map(char *filename)
{
    int     fd;
    char    **map;
    char   *line;

    if (!filename)
        error_exit("Error\nNo map filename provided");
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("Error\nCan't open map file");
    map = NULL;
    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        error_exit("Error\nEmpty map file");
    }
    while (line)
    {
        map = append_line_to_map(map, line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return map;
}

void validate_map(char **map)
{
    int height;
    int width;
    int y;
    int x;
    int count_p;
    int count_e;
    int count_c;

    if (!map)
        error_exit("Error\nInvalid map");
    height = count_lines(map);
    if (height < 3)
        error_exit("Error\nMap too small");
    width = strlen(map[0]);
    if (width < 3)
        error_exit("Error\nMap too small");
    count_p = 0;
    count_e = 0;
    count_c = 0;
    y = 0;
    while (y < height)
    {
        if ((int)strlen(map[y]) != width)
            error_exit("Error\nMap is not rectangular");
        x = 0;
        while (x < width)
        {
            char tile;

            tile = map[y][x];
            if (tile != '0' && tile != '1' && tile != 'C' && tile != 'E' && tile != 'P')
                error_exit("Error\nInvalid character in map");
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
            {
                if (tile != '1')
                    error_exit("Error\nMap is not surrounded by walls");
            }
            if (tile == 'P') count_p++;
            if (tile == 'E') count_e++;
            if (tile == 'C') count_c++;
            x++;
        }
        y++;
    }
    if (count_p != 1 || count_e != 1 || count_c < 1)
        error_exit("Error\nInvalid number of P, E, or C");
    if (!check_path(map))
        error_exit("Error\nNo valid path to collect all items and exit");
}
