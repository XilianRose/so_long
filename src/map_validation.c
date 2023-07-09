/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:39:27 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/09 13:54:38 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	this function checks to see if the check_path function has visited all the
	destinations, i.e. all the collectibles. It first checks if the exit has
	been visited and then it checks the collectibles

	arguments	: the map data struct and a 2D boolean array with visited positions
	returns		: true when all the destinations have been visited, else false
*/
static bool	check_destinations(t_map_info *map, bool **visited)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = map->exit.position[i].x;
	y = map->exit.position[i].y;
	if (visited[y][x] != true)
		return (false);
	while (i < map->collect.count)
	{
		x = map->collect.position[i].x;
		y = map->collect.position[i].y;
		if (visited[y][x] != true)
			return (false);
		i++;
	}
	return (true);
}

/*	this function checks to see if there's a path between player starting point,
	all the collectibles and the exit. I made it recursively for ease so I had
	to isolate the destinations check to it's own function

	So it first checks to see if all the target destinations have been visited. If
	not, it checks if the position itself is valid and sets it to true if it is. It
	goes through all the connecting tiles/nodes/positions until it no longer can or
	until it no longer has to.

	arguments	: the map data struct, the player starting coordinates (x, y) and
				a 2D boolean array
	returns		: false if it has gone through the entire array and destination
				check was false. true if destination check returns true at any point
*/
bool	check_path(t_map_info *map, int x, int y, bool **visited)
{
	if (check_destinations(map, visited) == true)
		return (true);
	if (x < 0 || x > map->cols || y < 0 || y > map->rows
		|| ft_strchr("0CEP", map->grid[y][x]) == NULL)
		return (false);
	if (visited[y][x] == true)
		return (false);
	visited[y][x] = true;
	if ((check_path(map, x - 1, y - 1, visited) == true)
		|| (check_path(map, x - 1, y, visited) == true)
		|| (check_path(map, x, y - 1, visited) == true)
		|| (check_path(map, x + 1, y + 1, visited) == true)
		|| (check_path(map, x + 1, y, visited) == true)
		|| (check_path(map, x, y + 1, visited) == true)
		|| (check_path(map, x + 1, y - 1, visited) == true)
		|| (check_path(map, x - 1, y + 1, visited) == true))
		return (true);
	return (false);
}

/*	this functions checks if the map is surrounded by walls or not.
	it first compares the chars in the first and last row at the same time, then
	it compares the chars in the first and last column at the same time.

	arguments	: the map data struct and the error message struct
	returns		: exit_wrapper if the char is not '1', else MAP_OK
*/
int	check_mapwalls(t_map_info *map, t_error *errme)
{
	int	i;

	i = 0;
	while (i < map->cols)
	{
		if (map->grid[0][i] == '1' && map->grid[map->rows - 1][i] == '1')
			i++;
		else
			exit_wrapper(errme->map6);
	}
	i = 0;
	while (i < map->rows)
	{
		if (map->grid[i][0] == '1' && map->grid[i][map->cols - 1] == '1')
			i++;
		else
			exit_wrapper(errme->map6);
	}
	return (MAP_OK);
}

/*	this functions checks if the given row contains only valid map components.

	it also keeps count of the player, exit and collectible count. Then it calls
	on the mapcomponents_save function, since we're already at a position of
	a component that needs to be saved

	arguments	: the current row (string), the map data struct and the error
				message struct
	returns		: if the map consists of only the correct components and not
				more than 1 exit or starting position it's return MAP_OK, else
				exit_wrapper
*/
static int	check_mapcomponents(char *row, t_map_info *map, t_error *errme)
{
	int	i;

	i = 0;
	while (i < map->cols)
	{
		if (ft_strchr("01CEP", row[i]) != NULL)
		{
			if (row[i] == 'C')
				map->collect.count++;
			else if (row[i] == 'E')
				map->exit.count++;
			else if (row[i] == 'P')
				map->player.count++;
			else if (row[i] == '1')
				map->wall.count++;
			if (map->exit.count > 1 || map->player.count > 1)
				exit_wrapper(errme->map4);
			if (ft_strchr("1CEP", row[i]) != NULL)
				save_mapcomponents(map, i, map->rows, row[i]);
			i++;
		}
		else
			exit_wrapper(errme->map5);
	}
	return (MAP_OK);
}

/*	this function checks if the map has a valid shape. It first checks if it's
	empty, then it checks if there's at least 3 columns. After that it compares
	the length of every row to check if it's rectangular and then it checks if
	there's at least 3 rows. The row is then put into a function that checks
	the map components. After this it frees the strings allocated by GNL

	arguments	: the file desicriptor, the map data struct, the error message struct
	returns		: MAP_OK when all is ok, else exit_wrapper
 */
int	check_mapshape(int fd, t_map_info *map, t_error *errme)
{
	char	*row;

	map->rows = 0;
	map->cols = 0;
	row = get_next_line(fd);
	if (row == NULL)
		exit_wrapper(errme->map0);
	map->cols = ft_strlen(row) - 1;
	if (map->cols < 3)
		exit_wrapper(errme->map1);
	while (row != NULL)
	{
		if ((int)ft_strlen(row) - 1 != map->cols)
			exit_wrapper(errme->map2);
		check_mapcomponents(row, map, errme);
		my_freestr(row);
		map->rows++;
		row = get_next_line(fd);
	}
	if (map->rows < 3)
		exit_wrapper(errme->map3);
	return (MAP_OK);
}
