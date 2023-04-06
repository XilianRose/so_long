/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 11:41:05 by mstegema      #+#    #+#                 */
/*   Updated: 2023/04/05 16:21:39 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/* this function */
static char	*save_map(int fd, int rows, int cols)
{
	char	**map;
	int		i;

	i = 0;
	map = ft_calloc(rows + 1, sizeof(char	*));
	if (!map)
		return(ft_printf("\nERROR\nmalloc failed\n"), NULL);
	while (i < rows)
	{
		map[i] = ft_calloc(cols + 1, sizeof(char));
		if (!map[i])
			return(ft_free_map(map), ft_printf("\nERROR\nmalloc failed\n"), NULL);
	}

}

/* this functions checks if the given row contains only valid map components.
	It returns 'true' if it does and 'false' if it doesn't */

bool	mapcomponents_check(char *row, int len)
{
	int	i;

	i = 0;
	while(i < len)
	{
		if (row[i] == '0' || row[i] == '1' || row[i] == 'C' || row[i] == 'E' || row[i] == 'P')
			i++;
		else
			return(false);
	}
	if (row[i] == '0' || row[i] == '1' || row[i] == 'C' || row[i] == 'E' || row[i] == 'P')
		return (true);
	else
			return(false);
}

/* this function checks if the map has a valid shape */

char	*mapshape_check(int fd)
{
	int		rows;
	int		cols;
	char	*row;

	rows = 1;
	cols = 0;
	row = get_next_line(fd);
	if (row == NULL)
		return(ft_printf("\nERROR\nmap is empty\n"), NULL);
	cols = ft_strlen(row);
	while ((row = get_next_line(fd)) != NULL)
	{
		if (ft_strlen(row) != cols)
			return(ft_printf("\nERROR\nmap is not rectangular\n"), ft_freestr(row), NULL);
		ft_freestr(row);
		rows++;
	}
	if (rows < 3)
		return(ft_printf("\nERROR\nmap is too small\n"), ft_freestr(row), NULL);
}

/*	the main checks if there's a ".ber" file given as input and opens it if possible
	it then calls on the function to read the map */

void	main(int argc, char **argv)
{
	int fd;

	if (argc != 2)
		return(ft_printf("\nERROR\nplease give one filename as argument\n"));
	if (ft_strendstr(argv[1], ".ber") == NULL)
		return(ft_printf("\nERROR\nnot a '.ber' map description file\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return(close(fd), ft_printf("\nERROR\nencountered problem while opening the file\n"));
/* insert fuction to read map */
	close(fd);
	return ;
}
