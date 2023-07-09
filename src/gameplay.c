/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameplay.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 13:08:18 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/09 22:54:15 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	this function prints a message corresponding to the game status and amount
	of mice collected.

	arguments	: the map data struct
	returns		: it exits with EXIT_SUCCES
*/
void	end_game(t_map_info *map)
{
	if (map->collect.count == map->collected)
	{
		if (map->status == WIN)
			ft_printf("Congratulations! You won the game in %i moves.\n",
				map->moves);
		else
			ft_printf("Oh no! You failed to offer the mice :(\n");
	}
	else
		ft_printf("You didn't catch all the mice. Better luck next time.\n");
	exit(EXIT_SUCCESS);
}

/*	this is the function that gets called on when the player encounters a
	collectible tile or the exit.

	if it's a collectible and the number of collected is lower than the count
	of collected, it goes through all the collectible image instances and
	compares their location to the current location. when found it checks to
	see if the image instance is enabled or not. If it's enabled it gets
	disabled and the collected count goes up. after that it checks if the
	amount of collected is the same as the amount of collectibles and if that's
	true the image instance of the exit gets enabled.

	if it's the exit and the image instance is enabled, it sets the map status
	to win and closes the window

	nothing happends when a player moves over a tile with an disabled image

	arguments	: the map data struct, current position coordinates
	returns		: nothing but does set map status to win and closes window when
				exit is enabled an reached
*/
void	encounter(t_map_info *map, int x, int y)
{
	int	i;

	i = 0;
	if (map->grid[y][x] == 'C' && map->collected < map->collect.count)
	{
		while (i < map->collect.count)
		{
			if (map->collect.image[0]->instances[i].x == x * 32
				&& map->collect.image[0]->instances[i].y == y * 32
				&& map->collect.image[0]->instances[i].enabled == true)
			{
				map->collect.image[0]->instances[i].enabled = false;
				map->collected++;
				if (map->collected == map->collect.count)
					map->exit.image[0]->instances[0].enabled = true;
				return ;
			}
			i++;
		}
	}
	if (map->grid[y][x] == 'E' &&
		map->exit.image[0]->instances[0].enabled == true)
		return ((map->status = WIN), mlx_close_window(map->mlx));
}
