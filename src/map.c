#include "../incl/so_long.h"
#include "../libft/libft.h"

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
        write(2, msg, ft_strlen(msg));  // 2 = stderr
    write(2, "\n", 1);
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

char **append_line_to_map(char **map, char *line)
{
    int     old_count;
    char    **new_map;
    char    *dup_line;
    int     i;

    old_count = 0;
    if (line == NULL)
        return map;
    dup_line = ft_strdup(strip_newline(line));
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