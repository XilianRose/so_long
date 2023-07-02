/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_freestr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 13:31:39 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/02 13:13:02 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/* frees the string and sets it to NULL */

void	my_freestr(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}
