/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_management.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 15:41:22 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/02 12:40:14 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static mlx_image_t	*g_player;

int32_t	error(mlx_t	*mlx)
{
	if (mlx)
		mlx_close_window(mlx);
	ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
	return (EXIT_FAILURE);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
	if (((keydata.key == MLX_KEY_UP) || (keydata.key == MLX_KEY_W))
		&& (keydata.action == MLX_RELEASE))
		g_player->instances[0].y -= 32;
	if (((keydata.key == MLX_KEY_DOWN) || (keydata.key == MLX_KEY_S))
		&& (keydata.action == MLX_RELEASE))
		g_player->instances[0].y += 32;
	if (((keydata.key == MLX_KEY_LEFT) || (keydata.key == MLX_KEY_A))
		&& (keydata.action == MLX_RELEASE))
		g_player->instances[0].x -= 32;
	if (((keydata.key == MLX_KEY_RIGHT) || (keydata.key == MLX_KEY_D))
		&& (keydata.action == MLX_RELEASE))
		g_player->instances[0].x += 32;
}

int32_t	rendering(t_map_info *map, mlx_t *mlx)
{
	if (render_grass(map, mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (render_sprites(map, mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (render_walls(map, mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int32_t	window_management(t_map_info *map)
{
	mlx_t			*mlx;

	mlx = mlx_init(map->cols * 32, map->rows * 32, "Lucky Cat", true);
	if (!mlx)
		return (error(NULL));
	rendering(map, mlx);
	g_player = render_img("assets/cat_down.png", mlx, map->player.position[0].x,
			map->player.position[0].y);
	mlx_key_hook(mlx, &keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
