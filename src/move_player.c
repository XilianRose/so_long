/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 13:08:18 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/03 15:50:46 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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
		mlx_close_window(map->mlx);
}

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
		if (ft_strchr("CE", map->grid[y][x + 1]) != NULL)
			encounter(map, x + 1, y);
	}
}
