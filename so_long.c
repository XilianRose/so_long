/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 11:41:05 by mstegema      #+#    #+#                 */
/*   Updated: 2023/03/23 13:55:57 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"



void	main(int argc, char **argv)
{
	int fd;

	if (argc != 2)
		return(ft_printf("\nERROR\nplease give one filename as argument\n"));
	if (ft_strendstr(argv[1], ".ber") == NULL)
		return(ft_printf("\nERROR\nnot a '.ber' map description file\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return(ft_printf("\nERROR\nencountered problem while opening the file\n"));

	close(fd);
	return ;
}
