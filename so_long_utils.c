/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:40:32 by mstegema      #+#    #+#                 */
/*   Updated: 2023/04/28 16:13:16 by mstegema      ########   odam.nl         */
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

	file_err.no00 = "\nERROR\nplease give one filename as argument\n";
	return ;
}
