/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 12:46:26 by mstegema      #+#    #+#                 */
/*   Updated: 2023/06/29 12:28:29 by mstegema      ########   odam.nl         */
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

typedef struct s_dimensions {
	int	width;
	int	height;
}	t_dimensions;

typedef struct s_game_info {
	int					tilesize;
	struct s_dimensions	window;

}	t_game_info;

void	error_message(t_error *errme);
void	save_map(int fd, t_map_info *map);
void	save_mapcomponents(t_map_info *map, int x, int y, char c);

bool	check_mapshape(int fd, t_map_info *map, t_error *errme);
bool	check_mapwalls(t_map_info *map, t_error *errme);
bool	check_path(t_map_info *map, int x, int y, bool **visited);
int		start(t_map_info *map);

#endif
