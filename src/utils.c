/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:40:32 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/06 12:18:20 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	this function gets the x and y position from the mapcomponents_check function
	(the current position) and saves it to the corresponding map components in the
	map struct, indicated by the character at the current position. */
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

/*	this function copies the map from the file to the allocated memory */
void	save_map(int fd, t_map_info *map)
{
	int		i;
	char	*row;

	i = 0;
	row = NULL;
	while (i < map->rows)
	{
		row = get_next_line(fd);
		if (row != NULL)
			map->grid[i] = row;
		else
			break ;
		i++;
	}
	return ;
}

void	exit_wrapper(char *str)
{
	ft_printf("%s", str);
	exit(0);
}

/*	this function's sole reason for existance is the fact that there's a
	character limit per line. So i decided to save the strings, to be
	printed when an error occurs, in a struct. That's it*/
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
	errme->win0 = "Error\n";
	errme->win1 = "Error\n";
	errme->win2 = "Error\n";
	errme->win3 = "Error\n";
	return ;
}
