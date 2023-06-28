/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 12:46:26 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/28 12:47:30 by mstegema      ########   odam.nl         */
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

typedef struct s_file_info {
	int					argc;
	char				**argv;
	int					fd;
}	t_file_info;

typedef struct s_error {
	char	*file0;
	char	*file1;
	char	*file2;
	char	*file3;
	char	*file4;
	char	*map0;
	char	*map1;
	char	*map2;
	char	*map3;
	char	*map4;
	char	*map5;
	char	*map6;
	char	*map7;
	char	*map8;
	char	*map9;

}	t_error;

void	free_map(char **map);
void	save_map(int fd, t_map_info *map);
char	*allocate_map(t_map_info *map);
void	error_message(t_error *errme);
void	mapcomponents_save(t_map_info *map, int x, int y, char c);

bool	mapshape_check(int fd, t_map_info *map, t_error *errme);
bool	mapwalled_check(t_map_info *map, t_error *errme);
bool	path_check(t_map_info *map, int x, int y, bool **visited);

#endif
