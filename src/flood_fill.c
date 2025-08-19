# include "../incl/so_long.h"
#include "libft.h"

// Внутрішня рекурсивна функція flood fill
static void flood_fill_util(char **map, int x, int y)
{
	if (!map[y] || x < 0 || y < 0 || map[y][x] == '\0')
		return;
	if (map[y][x] == '1' || map[y][x] == 'F') // '1' = стіна, 'F' = вже відвідано
		return;

	map[y][x] = 'F'; // позначаємо як відвідано

	flood_fill_util(map, x + 1, y); // вправо
	flood_fill_util(map, x - 1, y); // вліво
	flood_fill_util(map, x, y + 1); // вниз
	flood_fill_util(map, x, y - 1); // вгору
}

// Основна функція для перевірки досяжності
int flood_fill_check(char **original_map, int px, int py)
{
	int y = 0;
	int x;
	char **map_copy;
	int success = 1;

	// копіюємо карту, щоб не змінювати оригінал
	int height = 0;
	while (original_map[height])
		height++;

	map_copy = malloc(sizeof(char *) * (height + 1));
	if (!map_copy)
		return (0);

	while (original_map[y])
	{
		map_copy[y] = ft_strdup(original_map[y]);
		if (!map_copy[y])
			success = 0;
		y++;
	}
	map_copy[y] = NULL;

	if (!success)
	{
		y = 0;
		while (map_copy[y])
		{
			free(map_copy[y]);
			y++;
		}
		free(map_copy);
		return (0);
	}

	flood_fill_util(map_copy, px, py);

	// Перевіряємо, чи залишились колектібли або вихід недоступними
	y = 0;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
				success = 0; // недосяжні
			x++;
		}
		y++;
	}

	// звільняємо копію
	y = 0;
	while (map_copy[y])
		free(map_copy[y++]);
	free(map_copy);

	return (success);
}
