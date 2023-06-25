/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 11:41:05 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/25 14:29:33 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// /*	the main checks if there's a ".ber" file given as input and opens it if
// 	possible it then calls on the function to read the map */

int	main(int argc, char **argv)
{
	int			fd;
	t_map_info	test;
	t_error		errme;
	bool		res;
	char		*ptr;
	bool		**visited;
	int			i;

	ptr = NULL;
	error_message(&errme);
	if (argc != 2)
		return (ft_printf("%s", errme.file0), 0);
	if (my_strendstr(argv[1], ".ber") == NULL)
		return (ft_printf("%s", errme.file1), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), close(fd), 0);
	res = mapshape_check(fd, &test, &errme);
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
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (res == true)
		ptr = allocate_map(&test);
	if (!ptr)
		return (perror("Error\n"), close(fd), 0);
	save_map(fd, &test);
	res = mapwalled_check(&test, &errme);
	if (res == true)
		path_check(&test, test.player.position[0].x, test.player.position[0].y, visited);

/* window handling */

	close(fd);
	return (0);
}
