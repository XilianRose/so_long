/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_management.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 15:41:22 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/03 14:16:13 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int32_t	error(mlx_t	*mlx)
{
	if (mlx)
		mlx_close_window(mlx);
	ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
	return (EXIT_FAILURE);
}

static void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_map_info	*map;

	map = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
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

// static void	keyhook(mlx_key_data_t keydata, void *param)
// {
// 	t_map_info	*map;

// 	map = param;
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
// 		mlx_close_window(map->mlx);
// 	if (((keydata.key == MLX_KEY_UP) || (keydata.key == MLX_KEY_W))
// 		&& (keydata.action == MLX_RELEASE))
// 		map->player.image[0]->instances[0].y -= 32;
// 	if (((keydata.key == MLX_KEY_DOWN) || (keydata.key == MLX_KEY_S))
// 		&& (keydata.action == MLX_RELEASE))
// 		map->player.image[0]->instances[0].y += 32;
// 	if (((keydata.key == MLX_KEY_LEFT) || (keydata.key == MLX_KEY_A))
// 		&& (keydata.action == MLX_RELEASE))
// 		map->player.image[0]->instances[0].x -= 32;
// 	if (((keydata.key == MLX_KEY_RIGHT) || (keydata.key == MLX_KEY_D))
// 		&& (keydata.action == MLX_RELEASE))
// 		map->player.image[0]->instances[0].x += 32;
// }

int32_t	window_management(t_map_info *map)
{
	mlx_t			*mlx;

	mlx = mlx_init(map->cols * 32, map->rows * 32, "Lucky Cat", true);
	if (!mlx)
		return (error(NULL));
	map->mlx = mlx;
	load_all(map, mlx);
	render_all(map, mlx);
	mlx_key_hook(mlx, &keyhook, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
