/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 11:41:05 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/28 15:46:13 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	map_validation(t_file_info *file, t_map_info *map, t_error *errme)
{
	bool		**visited;

	visited = NULL;
	if (check_mapshape(file->fd, map, errme) == false)
		return (false);
	visited = (bool **)my_allocarray((char **)visited, map->cols, map->rows);
	if (!visited)
		return (perror("Error\n"), close(file->fd), false);
	close(file->fd);
	file->fd = open(file->argv[1], O_RDONLY);
	if (my_allocarray(map->grid, map->cols, map->rows) == NULL)
		return (perror("Error\n"), close(file->fd), false);
	save_map(file->fd, map);
	if (check_mapwalls(map, errme) == false)
		return (false);
	check_path(map, map->player.position[0].x,
		map->player.position[0].y, visited);
	return (true);
}

bool	file_validation(t_file_info *file, t_error *errme)
{
	if (file->argc != 2)
		return (ft_printf("%s", errme->file0), false);
	if (my_strendstr(file->argv[1], ".ber") == NULL)
		return (ft_printf("%s", errme->file1), false);
	file->fd = open(file->argv[1], O_RDONLY);
	if (file->fd < 0)
		return (perror("Error\n"), close(file->fd), false);
	return (true);
}

// /*	the main checks if there's a ".ber" file given as input and opens it if
// 	possible it then calls on the function to read the map */

int	main(int argc, char **argv)
{
	t_file_info	file;
	t_map_info	map;
	t_error		errme;

	error_message(&errme);
	file.argc = argc;
	file.argv = argv;
	if (file_validation(&file, &errme) == false)
		return (0);
	if (map_validation(&file, &map, &errme) == false)
		return (0);
	close(file.fd);
	return (0);
}
