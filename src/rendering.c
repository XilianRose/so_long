/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 10:35:09 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/03 12:50:35 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int32_t	render_img(mlx_t *mlx, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(mlx, img, x * 32, y * 32) == -1)
		return (error(mlx), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int32_t	render_grass(t_map_info *map, mlx_t *mlx)
{
	int			i;
	int			j;
	int			random;

	i = 1;
	j = 1;
	while (i < map->rows - 1)
	{
		j = 1;
		while (j < map->cols - 1)
		{
			random = rand() % 2;
			if (render_img(mlx, map->empty.image[random], i, j) == 1)
				return (error(mlx), EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/*	[0][1][2]
	[3]   [4]
	[5][6][7]	*/

static int32_t	render_walls(t_map_info *map, mlx_t *mlx)
{
	int	i;

	i = 1;
	if ((render_img(mlx, map->wall.image[0], 0, 0) == 1)
		|| (render_img(mlx, map->wall.image[2], map->cols - 1, 0) == 1)
		|| (render_img(mlx, map->wall.image[5], 0, map->rows - 1) == 1)
		|| (render_img(mlx, map->wall.image[7], map->cols - 1,
				map->rows - 1) == 1))
		return (EXIT_FAILURE);
	while (i < map->cols - 1)
	{
		if ((render_img(mlx, map->wall.image[1], i, 0) == 1)
			|| (render_img(mlx, map->wall.image[6], i, map->rows - 1) == 1))
			return (EXIT_FAILURE);
		i++;
	}
	i = 1;
	while (i < map->rows - 1)
	{
		if ((render_img(mlx, map->wall.image[3], 0, i) == 1)
			|| (render_img(mlx, map->wall.image[4], map->cols - 1, i) == 1))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int32_t	render_sprites(t_map_info *map, mlx_t *mlx)
{
	if (render_img(mlx, map->exit.image[0], map->exit.position[0].x,
			map->exit.position[0].y) == 1)
		return (EXIT_FAILURE);
	map->exit.image[0]->instances[0].enabled = false;
	if (render_img(mlx, map->player.image[0], map->player.position[0].x,
			map->player.position[0].y) == 1
		|| render_img(mlx, map->player.image[1], map->player.position[0].x,
			map->player.position[0].y) == 1
		|| render_img(mlx, map->player.image[2], map->player.position[0].x,
			map->player.position[0].y) == 1
		|| render_img(mlx, map->player.image[3], map->player.position[0].x,
			map->player.position[0].y) == 1
		|| render_img(mlx, map->player.image[4], map->player.position[0].x,
			map->player.position[0].y) == 1)
		return (EXIT_FAILURE);
	map->player.image[1]->instances[0].enabled = false;
	map->player.image[2]->instances[0].enabled = false;
	map->player.image[3]->instances[0].enabled = false;
	map->player.image[4]->instances[0].enabled = false;
	return (EXIT_SUCCESS);
}

int32_t	render_all(t_map_info *map, mlx_t *mlx)
{
	int	i;

	if (render_walls(map, mlx) == 1 || render_grass(map, mlx) == 1
		|| render_sprites(map, mlx) == 1)
		return (EXIT_FAILURE);
	i = 0;
	while (i < map->wall.count)
	{
		if (map->wall.position[i].x != 0 && map->wall.position[i].y != 0
			&& map->wall.position[i].x != map->cols - 1
			&& map->wall.position[i].y != map->rows - 1)
			if (render_img(mlx, map->wall.image[8], map->wall.position[i].x,
					map->wall.position[i].y) == 1)
				return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < map->collect.count)
	{
		if (render_img(mlx, map->collect.image[0], map->collect.position[i].x,
				map->collect.position[i].y) == 1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
