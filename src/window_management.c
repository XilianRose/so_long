/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_management.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 15:41:22 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/09 14:50:22 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	this is just a little wrapper for returns if anything fails with the MLX
	library. it prints the error message given by MLX and returns.

	arguments	: the pointer to the window instance struct
	returns		: EXIT_FAILURE
*/
int32_t	error(mlx_t	*mlx)
{
	if (mlx)
		mlx_close_window(mlx);
	ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
	return (EXIT_FAILURE);
}

/*	this function is where the keydata input gets connected to the right
	actions. it handles exiting with escape, resizing of the window and
	player movement.

	arguments	: the mlx keydata struct and the map data struct
	returns		: nothing
*/
static void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_map_info	*map;

	map = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_RELEASE)
		mlx_set_window_size(map->mlx, map->mlx->width + 32,
			map->mlx->height + 32);
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_RELEASE)
		mlx_set_window_size(map->mlx, map->mlx->width - 32,
			map->mlx->height - 32);
	if (((keydata.key == MLX_KEY_UP) || (keydata.key == MLX_KEY_W))
		&& (keydata.action == MLX_RELEASE))
		move_up(map);
	if (((keydata.key == MLX_KEY_DOWN) || (keydata.key == MLX_KEY_S))
		&& (keydata.action == MLX_RELEASE))
		move_down(map);
	if (((keydata.key == MLX_KEY_LEFT) || (keydata.key == MLX_KEY_A))
		&& (keydata.action == MLX_RELEASE))
		move_left(map);
	if (((keydata.key == MLX_KEY_RIGHT) || (keydata.key == MLX_KEY_D))
		&& (keydata.action == MLX_RELEASE))
		move_right(map);
}

/*	this is the big window & graphic management function where everything
	gets weaved together.

	a window instance gets initialized according to mapsize. a pointer to it
	get stored in the map data struct and then the asset loading and rendering
	happens. after this we set a keyhook and then the loop starts.

	arguments	: the map data struct
	returns		: EXIT_FAILURE if anything fails, else EXIT_SUCCES
*/
int32_t	window_management(t_map_info *map)
{
	mlx_t	*mlx;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(map->cols * 32, map->rows * 32, "Lucky Cat", true);
	if (!mlx)
		return (error(NULL));
	map->mlx = mlx;
	if (load_all(map, mlx) == EXIT_FAILURE
		|| render_all(map, mlx) == EXIT_FAILURE)
		return (mlx_terminate(map->mlx), EXIT_FAILURE);
	mlx_key_hook(mlx, &keyhook, map);
	mlx_loop(map->mlx);
	mlx_close_window(map->mlx);
	return (mlx_terminate(map->mlx), EXIT_SUCCESS);
}
