/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/09 12:23:59 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/09 15:00:09 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	these are all the functions that get called by the keyhook function to make
	the player move.

	if the player presses an arrow or WASD button the player image gets changed
	to the corresponding movement image by enabling the correct image instance and
	disabling the rest.

	if the tile the player wants to move to is not a wall it will then move the
	image by 1 tilesize. only then the move counter in the map data stuct goes up
	and the number of moves get printed to shell.

	if the tile the player moves to has a collectible or an exit, the encounter
	function is called.

	arguments	: the map data struct
	returns		: nothing
*/

void	move_up(t_map_info *map)
{
	int	x;
	int	y;

	x = map->player.image[0]->instances[0].x / 32;
	y = map->player.image[0]->instances[0].y / 32;
	map->player.image[0]->instances[0].enabled = false;
	map->player.image[1]->instances[0].enabled = true;
	map->player.image[2]->instances[0].enabled = false;
	map->player.image[3]->instances[0].enabled = false;
	map->player.image[4]->instances[0].enabled = false;
	if (ft_strchr("0CEP", map->grid[y - 1][x]) != NULL)
	{
		map->player.image[0]->instances[0].y -= 32;
		map->player.image[1]->instances[0].y -= 32;
		map->player.image[2]->instances[0].y -= 32;
		map->player.image[3]->instances[0].y -= 32;
		map->player.image[4]->instances[0].y -= 32;
		map->moves++;
		ft_printf("Moves: %i\n", map->moves);
		if (ft_strchr("CE", map->grid[y - 1][x]) != NULL)
			encounter(map, x, y - 1);
	}
}

void	move_down(t_map_info *map)
{
	int	x;
	int	y;

	x = map->player.image[0]->instances[0].x / 32;
	y = map->player.image[0]->instances[0].y / 32;
	map->player.image[0]->instances[0].enabled = false;
	map->player.image[1]->instances[0].enabled = false;
	map->player.image[2]->instances[0].enabled = true;
	map->player.image[3]->instances[0].enabled = false;
	map->player.image[4]->instances[0].enabled = false;
	if (ft_strchr("0CEP", map->grid[y + 1][x]) != NULL)
	{
		map->player.image[0]->instances[0].y += 32;
		map->player.image[1]->instances[0].y += 32;
		map->player.image[2]->instances[0].y += 32;
		map->player.image[3]->instances[0].y += 32;
		map->player.image[4]->instances[0].y += 32;
		map->moves++;
		ft_printf("Moves: %i\n", map->moves);
		if (ft_strchr("CE", map->grid[y + 1][x]) != NULL)
			encounter(map, x, y + 1);
	}
}

void	move_left(t_map_info *map)
{
	int	x;
	int	y;

	x = map->player.image[0]->instances[0].x / 32;
	y = map->player.image[0]->instances[0].y / 32;
	map->player.image[0]->instances[0].enabled = false;
	map->player.image[1]->instances[0].enabled = false;
	map->player.image[2]->instances[0].enabled = false;
	map->player.image[3]->instances[0].enabled = true;
	map->player.image[4]->instances[0].enabled = false;
	if (ft_strchr("0CEP", map->grid[y][x - 1]) != NULL)
	{
		map->player.image[0]->instances[0].x -= 32;
		map->player.image[1]->instances[0].x -= 32;
		map->player.image[2]->instances[0].x -= 32;
		map->player.image[3]->instances[0].x -= 32;
		map->player.image[4]->instances[0].x -= 32;
		map->moves++;
		ft_printf("Moves: %i\n", map->moves);
		if (ft_strchr("CE", map->grid[y][x - 1]) != NULL)
			encounter(map, x - 1, y);
	}
}

void	move_right(t_map_info *map)
{
	int	x;
	int	y;

	x = map->player.image[0]->instances[0].x / 32;
	y = map->player.image[0]->instances[0].y / 32;
	map->player.image[0]->instances[0].enabled = false;
	map->player.image[1]->instances[0].enabled = false;
	map->player.image[2]->instances[0].enabled = false;
	map->player.image[3]->instances[0].enabled = false;
	map->player.image[4]->instances[0].enabled = true;
	if (ft_strchr("0CEP", map->grid[y][x + 1]) != NULL)
	{
		map->player.image[0]->instances[0].x += 32;
		map->player.image[1]->instances[0].x += 32;
		map->player.image[2]->instances[0].x += 32;
		map->player.image[3]->instances[0].x += 32;
		map->player.image[4]->instances[0].x += 32;
		map->moves++;
		ft_printf("Moves: %i\n", map->moves);
		if (ft_strchr("CE", map->grid[y][x + 1]) != NULL)
			encounter(map, x + 1, y);
	}
}
