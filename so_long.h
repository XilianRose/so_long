/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 12:46:26 by mstegema      #+#    #+#                 */
/*   Updated: 2023/04/21 14:21:45 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include "libft.h"
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_component {
	int		count;
	char	*position;
}	t_component;

typedef struct s_map_info {
	int			rows;
	int			cols;
	char		**grid;
	t_component	player;
	t_component	collectible;
	t_component	exit;
}	t_map_info;

#endif
