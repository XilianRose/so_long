/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_management.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 15:41:22 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/26 15:33:56 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t	*img;

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
		img->instances[0].y -= 3;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
		img->instances[0].y += 3;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_A))
		img->instances[0].x -= 3;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_D))
		img->instances[0].x += 3;
}

int32_t	main(int32_t argc, const char *argv[])
{
	mlx_t		*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "Lucky Cat", true);
	if (!mlx)
	{
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
		return (EXIT_FAILURE);
	}
	img = mlx_new_image(mlx, 32, 32);
	if (!img)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
		return (EXIT_FAILURE);
	}
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int));
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
