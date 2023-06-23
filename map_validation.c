/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:39:27 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/23 16:24:53 by mstegema      ########   odam.nl         */
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
	if (destinations_check(map, visited) == true)
		return (true);
	printf("char: %c\n", map->grid[x][y]);
	if (x < 0 || x > map->cols || y < 0 || y > map->rows
		|| ft_strchr("0CEP", map->grid[x][y]) == NULL)
		return (false);
	if (visited[x][y] == true)
		return (false);
	visited[x][y] = true;
	if ((path_check(map, x - 1, y - 1, visited) == true)
		|| (path_check(map, x - 1, y, visited) == true)
		|| (path_check(map, x, y - 1, visited) == true)
		|| (path_check(map, x + 1, y + 1, visited) == true)
		|| (path_check(map, x + 1, y, visited) == true)
		|| (path_check(map, x, y + 1, visited) == true)
		|| (path_check(map, x + 1, y - 1, visited) == true)
		|| (path_check(map, x - 1, y + 1, visited) == true))
		return (true);
	return (false);
}

/*	this functions checks if the map is surrounded by walls or not.
	it first compares the chars in the first and last row at the same time, then
	it compares the chars in the first and last column at the same time. If, at
	any time, the char is not '1' it wil return an error message and false.

wss rows - 1 if statement veranderen naar gewoon rows of cols - 1 naar cols - 2 */
bool	mapwalled_check(t_map_info *map, t_error *errme)
{
	int		i;

	i = 0;
	while (i < map->cols)
	{
		if (map->grid[0][i] == '1' && map->grid[map->rows - 1][i] == '1')
			i++;
		else
			return (ft_printf("%s", errme->map6), false);
	}
	i = 0;
	while (i < map->rows)
	{
		if (map->grid[i][0] == '1' && map->grid[i][map->cols - 1] == '1')
			i++;
		else
			return (ft_printf("%s", errme->map6), false);
	}
	return (true);
}

/*	this functions checks if the given row contains only valid map components.
	It returns 'true' if it does and 'false' if it doesn't

	y = map.rows, x = i (als component gevonden is, opslaan in struct)
	array [count - 1]

*/
static bool	mapcomponents_check(char *row, t_map_info *map, t_error *errme)
{
	int	i;

	i = 0;
	while (i < map->cols - 1)
	{
		if (ft_strchr("01CEP", row[i]) != NULL)
		{
			if (row[i] == '0')
				map->empty.count++;
			else if (row[i] == '1')
				map->wall.count++;
			else if (row[i] == 'C')
				map->collect.count++;
			else if (row[i] == 'E')
				map->exit.count++;
			else if (row[i] == 'P')
				map->player.count++;
			if (map->exit.count > 1 || map->player.count > 1)
				return (ft_printf("%s", errme->map4), false);
			i++;
		}
		else
			return (ft_printf("%s", errme->map5), false);
	}
	return (true);
}

/*	this function checks if the map has a valid shape. It first checks if it's
	empty, then it checks if there's at least 3 columns. After that it compares
	the length of every row to check if it's rectangular and then it checks if
	there's at least 3 rows.

	Free the strings allocated by GNL

	The row is then put into a function that checks the map components */

bool	mapshape_check(int fd, t_map_info *map, t_error *errme)
{
	char	*row;

	map->rows = 0;
	map->cols = 0;
	row = get_next_line(fd);
	if (row == NULL)
		return (ft_printf("%s", errme->map0), false);
	map->cols = ft_strlen(row) - 1;
	if (map->cols < 3)
		return (ft_printf("%s", errme->map1), my_freestr(&row), false);
	while (row != NULL)
	{
		if (mapcomponents_check(row, map, errme) == false)
			break ;
		if ((int) ft_strlen(row) - 1 != map->cols)
			return (ft_printf("%s", errme->map2), my_freestr(&row), false);
		my_freestr(&row);
		map->rows++;
		row = get_next_line(fd);
	}
	if (map->rows < 3)
		return (ft_printf("%s", errme->map3), my_freestr(&row), false);
	return (my_freestr(&row), true);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_map_info	test;
	t_error		errme;
	bool		res;
	char		*ptr;

	ptr = NULL;
	error_message(&errme);
	if (argc != 2)
		return (ft_printf("%s", errme.file0), 0);
	if (my_strendstr(argv[1], ".ber") == NULL)
		return (ft_printf("%s", errme.file1), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), close(fd), 0);
/* map validation */
	res = mapshape_check(fd, &test, &errme);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (res == true)
	{
		ptr = allocate_map(&test);
		if (ptr != NULL)
		{
			save_map(fd, &test);
			res = mapwalled_check(&test, &errme);
		}
	}
	// if (res == true)
	// 	res = path_check(&test, )


/* map saving */
/* window handling */

	close(fd);
	return (0);
}
