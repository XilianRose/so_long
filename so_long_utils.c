/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:40:32 by mstegema      #+#    #+#                 */
/*   Updated: 2023/05/11 15:01:57 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
		map == NULL;
	}
}

void	error_output(void)
{
	t_error	file_err;
	t_error	map_err;

	file_err.no00 = "Error\nplease give one filename as argument\n";
	file_err.no01 = "Error\nnot a '.ber' map description file\n";
	file_err.no02 = "Error\nencountered problem while opening the file\n";
	map_err.no00 = "";
	map_err.no01 = "Error\nmap is empty\n";
	map_err.no02 = "Error\nmap is too narrow\n";
	map_err.no03 = "Error\nmap is not a rectangle\n";
	map_err.no04 = "Error\nmap is too short\n";
	map_err.no05 = "Error\nmap has more than 1 exit or starting position\n";
	map_err.no06 = "";
	map_err.no07 = "Error\nmap contains invalid map components\n";
	map_err.no08 = "Error\nmap is not completely walled\n";
	return ;
}
