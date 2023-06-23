/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 11:41:05 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/23 16:23:37 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

// /*	the main checks if there's a ".ber" file given as input and opens it if
// 	possible it then calls on the function to read the map */

// void	main(int argc, char **argv)
// {
// 	int			fd;
// 	t_map_info	map;
// 	t_error		errme;

// 	error_message(&errme);
// 	if (argc != 2)
// 		return (ft_printf("%s", errme.file0));
// 	if (ft_strendstr(argv[1], ".ber") == NULL)
// 		return (ft_printf("%s", errme.file1));
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error\n");
// 		return (close(fd));
// 	}

// /* map validation */
// /* map saving */
// /* window handling */

// 	close(fd);
// 	return ;
// }
