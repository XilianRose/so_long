/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 12:46:26 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/09 15:40:15 by mstegema      ########   odam.nl         */
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
# include "libft/inc/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

// typedef struct s_queue {
// 	struct s_list	*front;
// 	struct s_list	*rear;
// }	t_queue;

typedef struct s_coordinates {
	int	x;
	int	y;
}	t_coordinates;

typedef struct s_component {
	int						count;
	struct s_coordinates	position[42];
}	t_component;

typedef struct s_map_info {
	int					rows;
	int					cols;
	char				**grid;
	struct s_component	player;
	struct s_component	collect;
	struct s_component	exit;
	struct s_component	wall;
	struct s_component	empty;
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
	char	*no25;
}	t_error;

void	free_map(char **map);
void	allocate_map(t_map_info *map);

#endif
