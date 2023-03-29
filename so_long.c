/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 11:41:05 by mstegema      #+#    #+#                 */
/*   Updated: 2023/03/29 14:19:07 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map != NULL && map[i] != '\0')
	{
		free(map[i]);
		map[i] = NULL;
	}
	free(map);
	map == NULL;
}

static char	*ft_save_map(int fd, int rows, int cols)
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

static char	*ft_read_map(int fd)
{
	int		rows;
	int		cols;
	char	*line;

	rows = 1;
	cols = 0;
	line = get_next_line(fd);
	if (line == NULL)
		return(ft_printf("\nERROR\nmap is empty\n"), NULL);
	cols = ft_strlen(line);
	while ((line = get_next_line(fd)) > 0)
	{
		rows++;
		if (ft_strlen(line) != cols)
			return(ft_printf("\nERROR\nmap is not rectangular\n"), NULL);
		free(line);
		line = NULL;
	}
}

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

	close(fd);
	return ;
}
