/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 11:41:05 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/28 13:39:15 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	map_validation(t_file_info *file, t_map_info *map, t_error *errme)
{
	bool		res;
	bool		**visited;
	int			i;

	res = mapshape_check(file->fd, map, &errme);
	visited = calloc(map->rows + 1, sizeof (bool *));
	if (!visited)
		return (perror("Error\n"), 0);
	i = 0;
	while (i <= map->rows)
	{
		visited[i] = calloc(map->cols + 1, sizeof(bool));
		if (!visited[i])
			return (my_freearray((char **) visited), perror("Error\n"), 0);
		i++;
	}
	close(file->fd);
	file->fd = open(file->argv[1], O_RDONLY);
	if (my_allocarray(map->grid, map->cols, map->rows) == NULL)
		return (perror("Error\n"), close(file->fd), false);
	save_map(file->fd, map);
	if (mapwalled_check(map, &errme) == 1)
		path_check(map, map->player.position[0].x,
			map->player.position[0].y, visited);
	return (true);
}

int	file_validation(t_file_info *file, t_map_info *map, t_error *errme)
{
	if (file->argc != 2)
		return (ft_printf("%s", errme->file0), 0);
	if (my_strendstr(file->argv[1], ".ber") == NULL)
		return (ft_printf("%s", errme->file1), 0);
	file->fd = open(file->argv[1], O_RDONLY);
	if (file->fd < 0)
		return (perror("Error\n"), close(file->fd), 0);
}

// /*	the main checks if there's a ".ber" file given as input and opens it if
// 	possible it then calls on the function to read the map */

int	main(int argc, char **argv)
{
	t_file_info	file;
	t_map_info	test;
	t_error		errme;

	error_message(&errme);

/* window handling */

	close(file.fd);
	return (0);
}
