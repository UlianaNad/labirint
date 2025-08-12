#include "../incl/so_long.h"

// helper to load PNG texture -> image
static mlx_image_t *load_image_from_file(mlx_t *mlx, const char *path, mlx_texture_t **out_tex)
{
    mlx_texture_t *tex = mlx_load_png(path);
    if (!tex)
        return NULL;
    mlx_image_t *img = mlx_texture_to_image(mlx, tex);
    if (!img)
    {
        mlx_delete_texture(tex);
        return NULL;
    }
    *out_tex = tex;
    return img;
}

void game_init(t_game *game, char **map)
{
    game->map = map;
    game->height = count_lines(map);
    game->width = ft_strlen(map[0]);
    game->moves = 0;
    game->collectibles = count_all_collectibles(map);
    find_player_position(map, &game->player_x, &game->player_y);

    game->mlx = mlx_init(game->width * TILE_SIZE, game->height * TILE_SIZE, "so_long", true);
    if (!game->mlx)
        error_exit("Error\nFailed to initialize MLX42");

    // load textures (use PNGs; convert your xpm to png)
    game->img_wall = load_image_from_file(game->mlx, "assets/wall.png", &game->tex_wall);
    game->img_floor = load_image_from_file(game->mlx, "assets/floor.png", &game->tex_floor);
    game->img_player = load_image_from_file(game->mlx, "assets/player.png", &game->tex_player);
    game->img_collect = load_image_from_file(game->mlx, "assets/collectible.png", &game->tex_collect);
    game->img_exit = load_image_from_file(game->mlx, "assets/exit.png", &game->tex_exit);

    if (!game->img_wall || !game->img_floor || !game->img_player || !game->img_collect || !game->img_exit)
        error_exit("Error\nFailed to load textures");
}

void game_exit(t_game *game)
{
    if (!game || !game->mlx)
        exit(0);

    // delete images and textures
    if (game->img_wall) mlx_delete_image(game->mlx, game->img_wall);
    if (game->img_floor) mlx_delete_image(game->mlx, game->img_floor);
    if (game->img_player) mlx_delete_image(game->mlx, game->img_player);
    if (game->img_collect) mlx_delete_image(game->mlx, game->img_collect);
    if (game->img_exit) mlx_delete_image(game->mlx, game->img_exit);

    if (game->tex_wall) mlx_delete_texture(game->tex_wall);
    if (game->tex_floor) mlx_delete_texture(game->tex_floor);
    if (game->tex_player) mlx_delete_texture(game->tex_player);
    if (game->tex_collect) mlx_delete_texture(game->tex_collect);
    if (game->tex_exit) mlx_delete_texture(game->tex_exit);

    // terminate MLX (this closes window)
    mlx_terminate(game->mlx);

    free_map(game->map);
    exit(0);
}
