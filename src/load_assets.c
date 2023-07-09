/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_assets.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 16:33:24 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/09 14:41:40 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	this is the main asset loading function. it calls on mlx_load_png to get a
	texture from a .png file. then it creates an image data struct with the the
	texture. the texture gets deleted at the end since it's no longer needed.

	arguments	: the png file path & mlx window instance struct
	returns		: pointer to the image struct that gets created or NULL with
				the corresponding MLX error message
*/
mlx_image_t	*load_asset(char *str, mlx_t *mlx)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(str);
	if (!texture)
		return (error(mlx), NULL);
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		return (error(mlx), NULL);
	mlx_delete_texture(texture);
	return (img);
}

static int32_t	load_walls(t_map_info *map, mlx_t *mlx)
{
	map->wall.image[0] = load_asset("assets/top_left.png", mlx);
	if (!map->wall.image[0])
		return (EXIT_FAILURE);
	map->wall.image[1] = load_asset("assets/top.png", mlx);
	if (!map->wall.image[1])
		return (EXIT_FAILURE);
	map->wall.image[2] = load_asset("assets/top_right.png", mlx);
	if (!map->wall.image[2])
		return (EXIT_FAILURE);
	map->wall.image[3] = load_asset("assets/left.png", mlx);
	if (!map->wall.image[3])
		return (EXIT_FAILURE);
	map->wall.image[4] = load_asset("assets/right.png", mlx);
	if (!map->wall.image[4])
		return (EXIT_FAILURE);
	map->wall.image[5] = load_asset("assets/bottom_left.png", mlx);
	if (!map->wall.image[5])
		return (EXIT_FAILURE);
	map->wall.image[6] = load_asset("assets/bottom.png", mlx);
	if (!map->wall.image[6])
		return (EXIT_FAILURE);
	map->wall.image[7] = load_asset("assets/bottom_right.png", mlx);
	if (!map->wall.image[7])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int32_t	load_player(t_map_info *map, mlx_t *mlx)
{
	map->player.image[0] = load_asset("assets/cat_idle.png", mlx);
	if (!map->player.image[0])
		return (EXIT_FAILURE);
	map->player.image[1] = load_asset("assets/cat_up.png", mlx);
	if (!map->player.image[1])
		return (EXIT_FAILURE);
	map->player.image[2] = load_asset("assets/cat_down.png", mlx);
	if (!map->player.image[2])
		return (EXIT_FAILURE);
	map->player.image[3] = load_asset("assets/cat_left.png", mlx);
	if (!map->player.image[3])
		return (EXIT_FAILURE);
	map->player.image[4] = load_asset("assets/cat_right.png", mlx);
	if (!map->player.image[4])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*	this is the function where all the asset loading functions get called.
	some loading is done free standing some are functions.

	arguments	: the map data struct & mlx window instance struct
	returns		: EXIT_FAILURE if anything fails, else EXIT SUCCES
*/
int32_t	load_all(t_map_info *map, mlx_t *mlx)
{
	map->collect.image[0] = load_asset("assets/mouse.png", mlx);
	if (!map->collect.image[0])
		return (EXIT_FAILURE);
	map->exit.image[0] = load_asset("assets/manekineko.png", mlx);
	if (!map->exit.image[0])
		return (EXIT_FAILURE);
	map->empty.image[0] = load_asset("assets/grass.png", mlx);
	if (!map->empty.image[0])
		return (EXIT_FAILURE);
	map->empty.image[1] = load_asset("assets/grass2.png", mlx);
	if (!map->empty.image[1])
		return (EXIT_FAILURE);
	map->wall.image[8] = load_asset("assets/bush.png", mlx);
	if (!map->wall.image[8])
		return (EXIT_FAILURE);
	if (load_player(map, mlx) == EXIT_FAILURE
		|| load_walls(map, mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
