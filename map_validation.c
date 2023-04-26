/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:39:27 by mstegema      #+#    #+#                 */
/*   Updated: 2023/04/26 15:44:07 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/* this functions checks if the given row contains only valid map components.
	It returns 'true' if it does and 'false' if it doesn't */

bool	mapcomponents_check(char *row, int len, t_map_info map)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (row[i] == '0' || row[i] == '1' || row[i] == 'C' || row[i] == 'E'
			|| row[i] == 'P')
			i++;
		else
			return (false);
	}
	if (row[i] == '0' || row[i] == '1' || row[i] == 'C' || row[i] == 'E'
		|| row[i] == 'P')
		return (true);
	else
		return (false);
}

/*	this function checks if the map has a valid shape. It first checks if it's
	empty, then it checks if there's at least 3 columns. After that it compares
	the length of every row to check if it's rectangular and then it checks if
	there's at least 3 rows.

	The row is then put into a function that checks the map components */

t_map_info	mapshape_check(int fd, t_map_info map)
{
	char	*row;

	map.rows = 0;
	map.cols = 0;
	row = get_next_line(fd);
	if (row == NULL)
		return (ft_printf("\nERROR\nmap is empty\n"), NULL);
	map.cols = ft_strlen(row);
	if (map.cols < 3)
		return (ft_printf("\nERROR\nmap is too narrow\n"), ft_freestr(row), NULL);
	while (row != NULL)
	{
		if (ft_strlen(row) != map.cols)
		{
			ft_printf("\nERROR\nmap is not rectangular\n");
			return (ft_freestr(row), NULL);
		}
		ft_freestr(row);
		map.rows++;
		row = get_next_line(fd);
	}
	if (map.rows < 3)
		return (ft_printf("\nERROR\nmap is too short\n"), ft_freestr(row), NULL);
	return (ft_freestr(row), map);
}
