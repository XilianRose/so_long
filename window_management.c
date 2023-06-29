/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_management.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 15:41:22 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/29 16:13:04 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static mlx_image_t	*img;




void	keyhook(mlx_key_data_t keydata, void *param)
{
	mlx_t *mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
	if (((keydata.key == MLX_KEY_UP) || (keydata.key == MLX_KEY_W))
		&& (keydata.action == MLX_RELEASE))
		img->instances[0].y -= 32;
	if (((keydata.key == MLX_KEY_DOWN) || (keydata.key == MLX_KEY_S))
		&& (keydata.action == MLX_RELEASE))
		img->instances[0].y += 32;
	if (((keydata.key == MLX_KEY_LEFT) || (keydata.key == MLX_KEY_A))
		&& (keydata.action == MLX_RELEASE))
		img->instances[0].x -= 32;
	if (((keydata.key == MLX_KEY_RIGHT) || (keydata.key == MLX_KEY_D))
		&& (keydata.action == MLX_RELEASE))
		img->instances[0].x += 32;
}

// void	ft_hook(void *param)
// {
// 	mlx_t	*mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
// 		img->instances[0].y -= 3;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
// 		img->instances[0].y += 3;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_A))
// 		img->instances[0].x -= 3;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_D))
// 		img->instances[0].x += 3;
// }

int	start(t_map_info *map)
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;

	mlx = mlx_init(map->cols * 32, map->rows * 32, "Lucky Cat", true);
	if (!mlx)
	{
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
		exit(EXIT_FAILURE);
	}
	texture = mlx_load_png("images/cat_up.png");
	if (!texture)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
		return (EXIT_FAILURE);
	}

	img = mlx_texture_to_image(mlx, texture);
	if (!img)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, img, map->player.position[0].x * 32,
			map->player.position[0].y * 32) == -1)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
		return (EXIT_FAILURE);
	}
	mlx_key_hook(mlx, &keyhook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
