/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 12:46:26 by mstegema      #+#    #+#                 */
/*   Updated: 2023/04/28 16:10:22 by mstegema      ########   odam.nl         */
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
	t_component	collect;
	t_component	exit;
	t_component	wall;
	t_component	empty;
}	t_map_info;

typedef struct s_error {
	char	*no00;
	char	*no01;
	char	*no02;
	char	*no03;
	char	*no04;
	char	*no05;
	char	*no06;
	char	*no07;
	char	*no08;
	char	*no09;
	char	*no10;
	char	*no11;
	char	*no12;
	char	*no13;
	char	*no14;
	char	*no15;
	char	*no16;
	char	*no17;
	char	*no18;
	char	*no19;
	char	*no20;
	char	*no21;
	char	*no22;
	char	*no23;
	char	*no24;
}	t_error;

#endif
