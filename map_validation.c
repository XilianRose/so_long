/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:39:27 by mstegema      #+#    #+#                 */
/*   Updated: 2023/04/28 16:13:18 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/* this functions checks if the given row contains only valid map components.
	It returns 'true' if it does and 'false' if it doesn't */

bool	mapcomponents_check(char *row, t_map_info map)
{
	int	i;

	i = 0;
	while (i <= map.cols)
	{
		if (ft_strchr("01CEP", row[i]) != NULL)
		{
			if (row[i] == '0')
				map.empty++;
			else if (row[i] == '1')
				map.wall++;
			else if (row[i] == 'C')
				map.collect++;
			else if (row[i] == 'E')
				map.exit++;
			else if (row[i] == 'P')
				map.player++;
			if (map.exit > 1 || map.player > 1)
				return (ft_printf("\nERROR\ntoo many exits or starts\n"), false);
			i++;
		}
		else
			return (ft_printf("\nERROR\ncontains invalid components\n"), false);
	}
	return (true);
}

/*	this function checks if the map has a valid shape. It first checks if it's
	empty, then it checks if there's at least 3 columns. After that it compares
	the length of every row to check if it's rectangular and then it checks if
	there's at least 3 rows.

	The row is then put into a function that checks the map components */

void	mapshape_check(int fd, t_map_info map)
{
	char	*row;

	map.rows = 0;
	map.cols = 0;
	row = get_next_line(fd);
	if (row == NULL)
		return (ft_printf("\nERROR\nmap is empty\n"));
	map.cols = ft_strlen(row);
	if (map.cols < 3)
		return (ft_printf("\nERROR\nmap is too narrow\n"), ft_freestr(row));
	while (row != NULL)
	{
		if (mapcomponents_check(row, map) == false)
			break ;
		if (ft_strlen(row) != map.cols)
			return (ft_printf("\nERROR\nmap is not a rectangle\n"), ft_freestr(row));
		ft_freestr(row);
		map.rows++;
		row = get_next_line(fd);
	}
	if (map.rows < 3)
		return (ft_printf("\nERROR\nmap is too short\n"), ft_freestr(row));
	return (ft_freestr(row));
}
