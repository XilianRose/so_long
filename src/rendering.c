/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 10:35:09 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/02 12:58:18 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

mlx_image_t	*render_img(char *str, mlx_t *mlx, int x, int y)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(str);
	if (!texture)
		return (error(mlx), NULL);
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		return (error(mlx), NULL);
	if (mlx_image_to_window(mlx, img, x * 32, y * 32) == -1)
		return (error(mlx), NULL);
	mlx_delete_texture(texture);
	return (img);
}

int32_t	render_grass(t_map_info *map, mlx_t *mlx)
{
	int			i;
	int			j;
	char		*str[2];
	int			random;

	i = 1;
	j = 1;
	str[0] = "assets/grass.png";
	str[1] = "assets/grass2.png";
	while (i < map->rows - 1)
	{
		random = rand() % 2;
		j = 1;
		if (render_img(str[random], mlx, i, j) == NULL)
			return (EXIT_FAILURE);
		while (j < map->cols - 1)
		{
			random = rand() % 2;
			if (render_img(str[random], mlx, i, j) == NULL)
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int32_t	render_walls(t_map_info *map, mlx_t *mlx)
{
	int	i;

	i = 1;
	if ((render_img("assets/top_left.png", mlx, 0, 0) == NULL)
		|| (render_img("assets/top_right.png", mlx, map->cols - 1, 0) == NULL)
		|| (render_img("assets/bottom_left.png", mlx, 0, map->rows - 1) == NULL)
		|| (render_img("assets/bottom_right.png", mlx, map->cols - 1,
				map->rows - 1) == NULL))
		return (EXIT_FAILURE);
	while (i < map->cols - 1)
	{
		if ((render_img("assets/top.png", mlx, i, 0) == NULL)
			|| (render_img("assets/bottom.png", mlx, i, map->rows - 1) == NULL))
			return (EXIT_FAILURE);
		i++;
	}
	i = 1;
	while (i < map->rows - 1)
	{
		if ((render_img("assets/left.png", mlx, 0, i) == NULL)
			|| (render_img("assets/right.png", mlx, map->cols - 1, i) == NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

// static int32_t	render_collectibles(t_map_info *map, mlx_t *mlx)
// {
// 	mlx_image_t	*img;
// 	int			i;

// 	i = 0;
// 	while (i < map->collect.count)
// 	{
// 		img = render_img("assets/mouse.png", mlx, map->collect.position[i].x,
// 				map->collect.position[i].y);
// 		if (!img)
// 			return (EXIT_FAILURE);
// 		map->collect.instance[i] = img;
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

int32_t	render_sprites(t_map_info *map, mlx_t *mlx)
{
	int	i;

	if (render_img("assets/manekineko.png", mlx, map->exit.position[0].x,
			map->exit.position[0].y) == NULL)
		return (EXIT_FAILURE);
	// if (render_collectibles(map, mlx) == EXIT_FAILURE)
	// 	(EXIT_FAILURE);
	// i = 0;
	// while (i < map->collect.count)
	// {
	// 	if (render_img("assets/mouse.png", mlx, map->collect.position[i].x,
	// 			map->collect.position[i].y) == NULL)
	// 		return (EXIT_FAILURE);
	// 	i++;
	// }
	i = 0;
	while (i < map->wall.count)
	{
		if (map->wall.position[i].x != 0 && map->wall.position[i].y != 0
			&& map->wall.position[i].x != map->cols - 1
			&& map->wall.position[i].x != map->rows - 1)
			if (render_img("assets/bush.png", mlx, map->wall.position[i].x,
					map->wall.position[i].y) == NULL)
				return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
