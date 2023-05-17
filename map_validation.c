/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:39:27 by mstegema      #+#    #+#                 */
/*   Updated: 2023/05/17 16:04:34 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*	this functions checks if the map is surrounded by walls or not.
	it first compares the chars in the first and last row at the same time, then
	it compares the chars in the first and last column at the same time. If, at
	any time, the char is not '1' it wil return an error message and false. */
bool	mapwalled_check(t_map_info map, t_error map_err)
{
	int		i;

	i = 0;
	while (i < map.cols)
	{
		if (map.grid[0][i] == '1' && map.grid[map.rows][i] == '1')
			i++;
		else
			return (ft_printf("%s", map_err.no08), false);
	}
	i = 0;
	while (i < map.rows)
	{
		if (map.grid[i][0] == '1' && map.grid[i][map.cols] == '1')
			i++;
		else
			return (ft_printf("%s", map_err.no08), false);
	}
	return (true);
}

/*	this functions checks if the given row contains only valid map components.
	It returns 'true' if it does and 'false' if it doesn't */
bool	mapcomponents_check(char *row, t_map_info map, t_error map_err)
{
	int	i;

	i = 0;
	while (i <= map.cols)
	{
		if (ft_strchr("01CEP", row[i]) != NULL)
		{
			if (row[i] == '0')
				map.empty.count++;
			else if (row[i] == '1')
				map.wall.count++;
			else if (row[i] == 'C')
				map.collect.count++;
			else if (row[i] == 'E')
				map.exit.count++;
			else if (row[i] == 'P')
				map.player.count++;
			if (map.exit.count > 1 || map.player.count > 1)
				return (ft_printf("%s", map_err.no05), false);
			i++;
		}
		else
			return (ft_printf("%s", map_err.no07), false);
	}
	return (true);
}

/*	this function checks if the map has a valid shape. It first checks if it's
	empty, then it checks if there's at least 3 columns. After that it compares
	the length of every row to check if it's rectangular and then it checks if
	there's at least 3 rows.

	The row is then put into a function that checks the map components */

void	mapshape_check(int fd, t_map_info map, t_error map_err)
{
	char	*row;

	map.rows = 0;
	map.cols = 0;
	row = get_next_line(fd);
	if (row == NULL)
		return (ft_printf("%s", map_err.no01));
	map.cols = ft_strlen(row);
	if (map.cols < 3)
		return (ft_printf("%s", map_err.no02), ft_freestr(row));
	while (row != NULL)
	{
		if (mapcomponents_check(row, map, map_err) == false)
			break ;
		if (ft_strlen(row) != map.cols)
			return (ft_printf("%s", map_err.no03), ft_freestr(row));
		ft_freestr(row);
		map.rows++;
		row = get_next_line(fd);
	}
	if (map.rows < 3)
		return (ft_printf("%s", map_err.no04), ft_freestr(row));
	return (ft_freestr(row));
}


