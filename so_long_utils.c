/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:40:32 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/23 13:37:42 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*	this function first free's the allocated rows, then the map itself and then
	set's them to NULL. This is done after checking it can be freed */

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map != NULL && map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	if (map != NULL)
	{
		free(map);
		map = NULL;
	}
}

void	error_message(t_error *errme)
{
	errme->file0 = "Error\nplease give one filename as argument\n";
	errme->file1 = "Error\nnot a '->ber' map description file\n";
	errme->file2 = "Error\nencountered problem while opening the file\n";
	errme->map0 = "Error\nmap is empty\n";
	errme->map1 = "Error\nmap is too narrow\n";
	errme->map2 = "Error\nmap is not a rectangle\n";
	errme->map3 = "Error\nmap is too short\n";
	errme->map4 = "Error\nmap has more than 1 exit or starting position\n";
	errme->map5 = "Error\nmap contains invalid map components\n";
	errme->map6 = "Error\nmap is not completely walled\n";
	return ;
}
