/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 11:41:05 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/09 14:14:07 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	this function weaves all the map validation functions together to check if
	the given map is valid.

	this is also the place where the memory for the map and the boolean array,
	used in check_path, is validated.

	arguments	: the file data struct, the map data struct and the error message\
				struct
	returns		: MAP_NV and errno message when allocation fails, MAP_OK when
				all the map validation functions return MAP_OK, else exit_wrapper
*/
static int	map_validation(t_file_info *file, t_map_info *map, t_error *errme)
{
	bool		**visited;

	check_mapshape(file->fd, map, errme);
	close(file->fd);
	file->fd = open(file->argv[1], O_RDONLY);
	map->grid = my_allocarray(map->cols, map->rows);
	if (!map->grid)
		return (perror("Error\n"), close(file->fd), MAP_NV);
	save_map(file->fd, map);
	check_mapwalls(map, errme);
	visited = (bool **)my_allocarray(map->cols, map->rows);
	if (!visited)
		return (perror("Error\n"), close(file->fd), MAP_NV);
	if (check_path(map, map->player.position[0].x,
			map->player.position[0].y, visited) == false)
		exit_wrapper(errme->map7);
	my_freearray((char **) visited);
	return (MAP_OK);
}

/*	this function is where the file validation checks are done. i check if there's
	one argument given, if it's a '.ber' file and if it can be opened.

	arguments	: the file data struct and the error message struct
	returns		: FILE_NV and errno message if the file can't be opened, FILE_OK
				if everything is ok, else exit_wrapper
*/
static int	file_validation(t_file_info *file, t_error *errme)
{
	if (file->argc != 2)
		exit_wrapper(errme->file0);
	if (my_strendstr(file->argv[1], ".ber") == NULL)
		exit_wrapper(errme->file1);
	file->fd = open(file->argv[1], O_RDONLY);
	if (file->fd < 0)
		return (perror("Error\n"), close(file->fd), FILE_NV);
	return (FILE_OK);
}

// static void	check_leaks(void)
// {
// 	system("leaks -q so_long");
// }
// atexit(check_leaks);

/*	the main is where all the data structs get declared. it initializes
	the error data struct and some of the map data struct. it calls on
	all the major functions like file_validation & map_validation.

	arguments	: argument count, argument vector
	returns		: 0 or 1 depending on the definition
*/
int	main(int argc, char **argv)
{
	t_file_info	file;
	t_map_info	map;
	t_error		errme;

	error_message(&errme);
	file.argc = argc;
	file.argv = argv;
	if (file_validation(&file, &errme) == FILE_NV)
		exit (FILE_NV);
	initialize_map_info(&map);
	if (map_validation(&file, &map, &errme) == MAP_NV)
		exit(MAP_NV);
	close(file.fd);
	if (window_management(&map) == EXIT_SUCCESS)
		end_game(&map);
	exit(EXIT_FAILURE);
}
