/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:40:32 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/09 21:50:38 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	this function gets the x and y position from the mapcomponents_check function
	(the current position) and saves it to the corresponding map components in the
	map struct, indicated by the character at the current position.

	arguments	: the map data struct, x & y coordinates and the character at that
				position
	returns		: nothing
*/
void	save_mapcomponents(t_map_info *map, int x, int y, char c)
{
	if (c == 'C')
	{
		map->collect.position[map->collect.count - 1].x = x;
		map->collect.position[map->collect.count - 1].y = y;
	}
	else if (c == 'E')
	{
		map->exit.position[map->exit.count - 1].x = x;
		map->exit.position[map->exit.count - 1].y = y;
	}
	else if (c == 'P')
	{
		map->player.position[map->player.count - 1].x = x;
		map->player.position[map->player.count - 1].y = y;
	}
	else if (c == '1')
	{
		map->wall.position[map->wall.count - 1].x = x;
		map->wall.position[map->wall.count - 1].y = y;
	}
	return ;
}

/*	this function copies the map from the file to the allocated memory
	it does this by calling on the GNL function and setting the pointer to
	the row it returns.

	the pointer that was previously stored in the grid array is freed

	arguments	: the file descriptor & the map data struct
	returns		: nothing
*/
void	save_map(int fd, t_map_info *map)
{
	int		i;
	char	*row;
	char	*temp;

	i = 0;
	row = NULL;
	temp = NULL;
	while (i < map->rows)
	{
		row = get_next_line(fd);
		if (row != NULL)
		{
			temp = map->grid[i];
			map->grid[i] = row;
			my_freestr(temp);
		}
		else
			break ;
		i++;
	}
	return ;
}

/*	this is a wrapper i made for exit so it prints the error messages
	and exits in one line

	arguments	: the error message string
	returns		: it exits with 0
*/
void	exit_wrapper(char *str)
{
	ft_printf("%s", str);
	exit(0);
}

/*	this function simply initializes some of the variables in the map
	struct for ease

	arguments	: the map data struct
	returns		: nothing
*/
void	initialize_map_info(t_map_info *map)
{
	map->player.count = 0;
	map->collect.count = 0;
	map->exit.count = 0;
	map->wall.count = 0;
	map->empty.count = 0;
	map->moves = 0;
	map->collected = 0;
	map->status = LOSE;
}

/*	this function's sole reason for existance is the fact that there's a
	character limit per line. So i decided to save the strings, to be
	printed when an error occurs, in a struct. That's it

	arguments	: the error message struct
	returns		: nothing
*/
void	error_message(t_error *errme)
{
	errme->file0 = "Error\nplease give one filename as argument\n";
	errme->file1 = "Error\nnot a '.ber' map description file\n";
	errme->file2 = "Error\nencountered problem while opening the file\n";
	errme->map0 = "Error\nmap is empty\n";
	errme->map1 = "Error\nmap is too narrow\n";
	errme->map2 = "Error\nmap is not a rectangle\n";
	errme->map3 = "Error\nmap is too short\n";
	errme->map4 = "Error\nmap has more than 1 exit or starting position\n";
	errme->map5 = "Error\nmap contains invalid map components\n";
	errme->map6 = "Error\nmap is not completely walled\n";
	errme->map7 = "Error\nmap doesn't have a valid path\n";
	errme->map8 = "Error\nmap doesn't contain all the neccesary components\n";
	return ;
}
