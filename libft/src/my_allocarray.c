/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_allocarray.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:05:59 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/29 11:18:15 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*	this function allocates memory for an array of character pointers */
char	**my_allocarray(char **array, int x, int y)
{
	char	**temp;
	int		i;

	i = 0;
	temp = calloc(y + 1, sizeof(char *));
	if (!temp)
		return (perror("Error\n"), NULL);
	while (i < y + 1)
	{
		temp[i] = calloc(x + 1, sizeof(char));
		if (!temp[i])
		{
			my_freearray(temp);
			return (perror("Error\n"), NULL);
		}
		i++;
	}
	array = temp;
	return (array);
}
