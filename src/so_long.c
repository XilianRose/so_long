/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 11:41:05 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/06 16:40:39 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	initialize_map_info(t_map_info *map)
{
	map->player.count = 0;
	map->collect.count = 0;
	map->exit.count = 0;
	map->wall.count = 0;
	map->empty.count = 0;
	map->moves = 0;
}

int	map_validation(t_file_info *file, t_map_info *map, t_error *errme)
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
	// my_freearray((char **) visited);
	// free_boolarray(visited);
	return (MAP_OK);
}

int	file_validation(t_file_info *file, t_error *errme)
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

void	end_game(t_map_info *map)
{
	if (map->collect.count == map->collected)
	{
		if (map->status == WIN)
			ft_printf("Congratulations! You won the game in %i moves.\n",
				map->moves);
		else
			ft_printf("Oh no! You failed to offer the mice :(\n");
	}
	else
		ft_printf("You didn't catch all the mice. Better luck next time.\n");
	exit(EXIT_SUCCESS);
}

static void	check_leaks(void)
{
	system("leaks -q so_long");
}

// /*	the main checks if there's a ".ber" file given as input and opens it if
// 	possible it then calls on the function to read the map */

int	main(int argc, char **argv)
{
	t_file_info	file;
	t_map_info	map;
	t_error		errme;

	atexit(check_leaks);
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
