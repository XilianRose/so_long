/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:39:27 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/09 16:16:22 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*	this function checks to see if the path_check function has visited all the
	destinations. It takes the map struct and 2D bool array with visited
	positions as arguments. It first checks if the exit has been visited and then
	it checks the collectibles */

static bool	destinations_check(t_map_info *map, bool **visited)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = map->exit.position[i].x;
	y = map->exit.position[i].y;
	if (visited[x][y] != true)
		return (false);
	while (i < map->collect.count)
	{
		x = map->collect.position[i].x;
		y = map->collect.position[i].y;
		if (visited[x][y] != true)
			return (false);
		i++;
	}
	return (true);
}

/*	this function checks to see if there's a path between player starting point,
	all the collectibles and the exit. It takes the map struct, the player
	starting coordinates and a 2D bool array as arguments. I made it recursively
	for ease so I had to isolate the destinations check to it's own function.

	So it first checks to see if all the target destinations have been visited. If
	not, it checks if the position itself is valid and sets it to true if it is. It
	goes through all the connecting tiles/nodes/positions until it no longer can,
	which is when it will return false, or until the destination check returns true,
	which is when it returns true. */
bool	path_check(t_map_info *map, int x, int y, bool **visited)
{
	int i = 0;
	int j = 0;
	if (destinations_check(map, visited) == true)
		return (true);
	if (x < 0 || x > map->cols || y < 0 || y > map->rows
		|| map->grid[x][y] != '0' || map->grid[x][y] != 'C'
		|| map->grid[x][y] != 'E' || map->grid[x][y] != 'P')
		return (false);
	if (visited[x][y] == true)
		return (false);
	visited[x][y] = true;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			printf("[%d] ", map->grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	if ((path_check(map, x - 1, y - 1, visited) == true)
		|| (path_check(map, x - 1, y, visited) == true)
		|| (path_check(map, x, y - 1, visited) == true)
		|| (path_check(map, x + 1, y + 1, visited) == true)g
		|| (path_check(map, x + 1, y, visited) == true)
		|| (path_check(map, x, y + 1, visited) == true)
		|| (path_check(map, x + 1, y - 1, visited) == true)
		|| (path_check(map, x - 1, y + 1, visited) == true))
		return (true);
	return (false);
}

int	main(void)
{
	t_map_info	test;
	bool		**visited;
	bool		res;
	int			i;
	int			j;
	// int			x;
	// int			y;

	test.cols = 5;
	test.rows = 5;
	test.exit.count = 1;
	test.exit.position[0].x = 3;
	test.exit.position[0].y = 3;
	test.collect.count = 2;
	test.collect.position[0].x = 3;
	test.collect.position[0].y = 1;
	test.collect.position[1].x = 1;
	test.collect.position[1].y = 3;
	visited = calloc(test.rows + 1, sizeof (bool *));
	if (!visited)
		return (perror("Error\n"), 0);
	i = 0;
	while (i <= test.rows)
	{
		visited[i] = calloc(test.cols + 1, sizeof(bool));
		if (!visited[i])
			return (free_map((char **) visited), perror("Error\n"), 0);
		i++;
	}
	res = false;
	allocate_map(&test);
	test.grid[0] = "11111";
	test.grid[1] = "1P0C1";
	test.grid[2] = "10101";
	test.grid[3] = "1C0E1";
	test.grid[4] = "11111";
	i = 0;
	while (i < test.rows)
	{
		j = 0;
		while (j < test.cols)
		{
			printf("[%c] ", test.grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	res = path_check(&test, 1, 1, visited);
	printf("res = %d\n", res);
	return (0);
}

// /*	this functions checks if the map is surrounded by walls or not.
// 	it first compares the chars in the first and last row at the same time, then
// 	it compares the chars in the first and last column at the same time. If, at
// 	any time, the char is not '1' it wil return an error message and false. */
// bool	mapwalled_check(t_map_info map, t_error map_err)
// {
// 	int		i;

// 	i = 0;
// 	while (i < map.cols)
// 	{
// 		if (map.grid[0][i] == '1' && map.grid[map.rows][i] == '1')
// 			i++;
// 		else
// 			return (ft_printf("%s", map_err.no08), false);
// 	}
// 	i = 0;
// 	while (i < map.rows)
// 	{
// 		if (map.grid[i][0] == '1' && map.grid[i][map.cols] == '1')
// 			i++;
// 		else
// 			return (ft_printf("%s", map_err.no08), false);
// 	}
// 	return (true);
// }

// /*	this functions checks if the given row contains only valid map components.
// 	It returns 'true' if it does and 'false' if it doesn't

// 	y = map.rows, x = i (als component gevonden is, opslaan in struct)
// 	array [count - 1]

// 	*/
// static bool	mapcomponents_check(char *row, t_map_info map, t_error map_err)
// {
// 	int	i;

// 	i = 0;
// 	while (i <= map.cols)
// 	{
// 		if (ft_strchr("01CEP", row[i]) != NULL)
// 		{
// 			if (row[i] == '0')
// 				map.empty.count++;
// 			else if (row[i] == '1')
// 				map.wall.count++;
// 			else if (row[i] == 'C')
// 				map.collect.count++;
// 			else if (row[i] == 'E')
// 				map.exit.count++;
// 			else if (row[i] == 'P')
// 				map.player.count++;
// 			if (map.exit.count > 1 || map.player.count > 1)
// 				return (ft_printf("%s", map_err.no05), false);
// 			i++;
// 		}
// 		else
// 			return (ft_printf("%s", map_err.no07), false);
// 	}
// 	return (true);
// }

// /*	this function checks if the map has a valid shape. It first checks if it's
// 	empty, then it checks if there's at least 3 columns. After that it compares
// 	the length of every row to check if it's rectangular and then it checks if
// 	there's at least 3 rows.

// 	Free the strings allocated by GNL

// 	The row is then put into a function that checks the map components */

// void	mapshape_check(int fd, t_map_info map, t_error map_err)
// {
// 	char	*row;

// 	map.rows = 0;
// 	map.cols = 0;
// 	row = get_next_line(fd);
// 	if (row == NULL)
// 		return (ft_printf("%s", map_err.no01));
// 	map.cols = ft_strlen(row);
// 	if (map.cols < 3)
// 		return (ft_printf("%s", map_err.no02), ft_freestr(row));
// 	while (row != NULL)
// 	{
// 		if (mapcomponents_check(row, map, map_err) == false)
// 			break ;
// 		if (ft_strlen(row) != map.cols)
// 			return (ft_printf("%s", map_err.no03), ft_freestr(row));
// 		ft_freestr(row);
// 		map.rows++;
// 		row = get_next_line(fd);
// 	}
// 	if (map.rows < 3)
// 		return (ft_printf("%s", map_err.no04), ft_freestr(row));
// 	return (ft_freestr(row));
// }
