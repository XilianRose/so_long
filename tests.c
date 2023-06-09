/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 14:12:24 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/09 15:22:57 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// test main for destinations check
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

