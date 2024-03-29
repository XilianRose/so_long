/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 14:12:24 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/06 14:19:48 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

// 												test main for destinations check
int	main(void)
{
	t_map_info	testmap;
	bool		**visited;
	int			i;
	int			j;
	bool		res;

	testmap.rows = 5;
	testmap.cols = 5;
	visited = calloc(testmap.rows + 1, sizeof(bool *));
	if (!visited)
		return (printf("malloc failed\n"), 0);
	i = 0;
	while (i <= testmap.rows)
	{
		visited[i] = calloc(testmap.cols + 1, sizeof(bool));
		if (!visited[i])
			return (free_map((char **) visited), 0);
		i++;
	}
	i = 0;
	res = false;
	printf("res = %d\n", res);
	testmap.exit.count = 1;
	testmap.exit.position[0].x = 2;
	testmap.exit.position[0].y = 2;
	testmap.collect.count = 2;
	testmap.collect.position[0].x = 3;
	testmap.collect.position[0].y = 3;
	testmap.collect.position[1].x = 4;
	testmap.collect.position[1].y = 4;
	i = 0;
	j = 0;
	printf("visited:\n");
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			visited[i][j] = false;
			printf("[%d] ", visited[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("check 1\n");
	res = destinations_check(testmap, visited);
	printf("check 2\n");
	printf("res = %d\n", res);
	return (0);
}

// 															test for path check
bool	path_check(t_map_info *map, int x, int y, bool **visited)
{
	int i = 0;
	int j = 0;
	if (destinations_check(map, visited) == true)
		return (true);
	printf("char: %c\n", map->grid[x][y]);
	// if (x < 0 || x > map->cols || y < 0 || y > map->rows
	// 	|| map->grid[x][y] != '0' || map->grid[x][y] != 'C'
	// 	|| map->grid[x][y] != 'E' || map->grid[x][y] != 'P')
	if (x < 0 || x > map->cols || y < 0 || y > map->rows
		|| ft_strchr("0CEP", map->grid[x][y]) == NULL)
		return (false);
	if (visited[x][y] == true)
		return (false);
	visited[x][y] = true;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			printf("[%d] ", visited[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
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
	test.collect.position[1].x = 3;
	test.collect.position[1].y = 2;
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
	test.grid[3] = "1CCE1";
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

// 															test main for map walled check
int	main(void)
{
	t_map_info	test;
	int			i;
	int			j;
	bool		res;
	t_error		errme;

	test.cols = 5;
	test.rows = 5;
	allocate_map(&test);
	test.grid[0] = "11111";
	test.grid[1] = "1P0C0";
	test.grid[2] = "10101";
	test.grid[3] = "1CCE1";
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
	error_message(&errme);
	res = mapwalled_check(&test, &errme);
	printf("Result: %i\n", res);
	return (0);
}

//													test main for map components check
int	main(void)
{
	t_map_info	test;
	int			i;
	int			j;
	bool		res;
	t_error		errme;

	test.cols = 5;
	test.rows = 5;
	allocate_map(&test);
	test.grid[0] = "11111";
	test.grid[1] = "1P0C0";
	test.grid[2] = "10101";
	test.grid[3] = "1CEE1";
	test.grid[4] = "11111";
	i = 3;
	j = 0;
	while (j < test.cols)
	{
		printf("[%c] ", test.grid[i][j]);
		j++;
	}
	error_message(&errme);
	res = mapcomponents_check(test.grid[i], &test, &errme);
	printf("\nResult: %i\n", res);
	return (0);
}

//													main for testing mapshape check
int	main(int argc, char **argv)
{
	int			fd;
	t_map_info	test;
	t_error		errme;
	bool		res;

	error_message(&errme);
	if (argc != 2)
		return (ft_printf("%s", errme.file0), 0);
	if (my_strendstr(argv[1], ".ber") == NULL)
		return (ft_printf("%s", errme.file1), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), close(fd), 0);
	res = mapshape_check(fd, &test, &errme);

	close(fd);
	return (0);
}
*/

// static void	check_leaks(void)
// {
// 	system("leaks so_long");
// }
// atexit(check_leaks);
