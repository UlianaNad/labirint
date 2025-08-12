#include "../incl/so_long.h"
#include "mlx42.h"


#define WIN_W 800
#define WIN_H 600

int	close_window(void *param)
{
	(void)param;
	exit(0);
}

int	handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307) // ESC для Linux (для Windows може бути інший код)
		exit(0);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, WIN_W, WIN_H, "so_long test");
	if (!win)
		return (1);

	mlx_key_hook(win, handle_key, NULL);
	mlx_hook(win, 17, 0, close_window, NULL); // закриття по хрестику

	mlx_loop(mlx);
	return (0);
}
