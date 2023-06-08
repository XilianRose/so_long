/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 11:41:05 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/08 13:48:42 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*	this function allocates the memory for the map. */
void	allocate_map(t_map_info map)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_calloc(map.rows + 1, sizeof(char *));
	if (!arr)
		return (perror("Error\n"));
	while (i <= map.rows)
	{
		arr[i] = ft_calloc(map.cols + 1, sizeof(char));
		if (!arr[i])
		{
			ft_free_map(arr);
			return (perror("Error\n"));
		}
		i++;
	}
	map.grid = arr;
	return ;
}

/*	this function copies the map from the file to the allocated memory */
void	save_map(int fd, t_map_info map)
{
	int	i;

	i = 0;
	while (i <= map.rows)
	{
		map.grid[i] = get_next_line(fd);
		i++;
	}
	return ;
}

/*	the main checks if there's a ".ber" file given as input and opens it if
	possible it then calls on the function to read the map */

void	main(int argc, char **argv)
{
	int			fd;
	t_map_info	map;
	t_error		file_err;
	t_error		map_err;

	error_output(file_err, map_err);
	if (argc != 2)
		return (ft_printf("%s", file_err.no00));
	if (ft_strendstr(argv[1], ".ber") == NULL)
		return (ft_printf("%s", file_err.no01));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error\n");
		return (close(fd));
	}

/* map validation */
/* map saving */
/* window handling */

	close(fd);
	return ;
}
