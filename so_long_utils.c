/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:40:32 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/25 14:13:20 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*	this function gets the x and y position from the mapcomponents_check function
	(the current position) and saves it to the corresponding map components in the
	map struct, indicated by the character at the current position. */
void	mapcomponents_save(t_map_info *map, int x, int y, char c)
{
	int	i;

	if (c == 'C')
	{
		i = map->collect.count - 1;
		map->collect.position[i].x = x;
		map->collect.position[i].y = y;
	}
	else if (c == 'E')
	{
		i = map->exit.count - 1;
		map->exit.position[i].x = x;
		map->exit.position[i].y = y;
	}
	else if (c == 'P')
	{
		i = map->player.count - 1;
		map->player.position[i].x = x;
		map->player.position[i].y = y;
	}
}

/*	this function allocates the memory for the map. */
char	*allocate_map(t_map_info *map)
{
	char	**arr;
	int		i;

	i = 0;
	arr = calloc(map->rows + 1, sizeof(char *));
	if (!arr)
		return (perror("Error\n"), NULL);
	while (i <= map->rows + 1)
	{
		arr[i] = calloc(map->cols + 1, sizeof(char));
		if (!arr[i])
		{
			free_map(arr);
			return (perror("Error\n"), NULL);
		}
		i++;
	}
	map->grid = arr;
	return (arr[0]);
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
		my_freestr(&row);
		i++;
	}
	my_freestr(&row);
	return ;
}

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

/*	this function's sole reason for existance is the fact that there's a
	character limit per line. So i decided to save the strings, to be
	printed when an error occurs, in a struct. That's it*/
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
