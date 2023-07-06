/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 12:46:26 by mstegema      #+#    #+#                 */
/*   Updated: 2023/07/06 15:34:02 by mstegema      ########   odam.nl         */
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
# include "../libft/inc/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define MAP_OK 1
# define MAP_NV 0

# define FILE_OK 1
# define FILE_NV 0

# define WIN 1
# define LOSE 0

typedef struct s_coordinates {
	int				x;
	int				y;
}	t_coordinates;

typedef struct s_component {
	int				count;
	t_coordinates	position[126];
	mlx_image_t		*image[10];
}	t_component;

typedef struct s_map_info {
	int				rows;
	int				cols;
	char			**grid;
	t_component		player;
	t_component		collect;
	t_component		exit;
	t_component		wall;
	t_component		empty;
	mlx_t			*mlx;
	int				moves;
	int				collected;
	int				status;
}	t_map_info;

typedef struct s_file_info {
	int				argc;
	char			**argv;
	int				fd;
}	t_file_info;

typedef struct s_error {
	char	*file0;
	char	*file1;
	char	*file2;
	char	*map0;
	char	*map1;
	char	*map2;
	char	*map3;
	char	*map4;
	char	*map5;
	char	*map6;
	char	*map7;
}	t_error;

int			file_validation(t_file_info *file, t_error *errme);
int			map_validation(t_file_info *file, t_map_info *map, t_error *errme);
void		initialize_map_info(t_map_info *map);

int			check_mapshape(int fd, t_map_info *map, t_error *errme);
int			check_mapwalls(t_map_info *map, t_error *errme);
bool		check_path(t_map_info *map, int x, int y, bool **visited);

int32_t		window_management(t_map_info *map);
int32_t		error(mlx_t	*mlx);

int32_t		load_all(t_map_info *map, mlx_t *mlx);
mlx_image_t	*load_asset(char *str, mlx_t *mlx);

int32_t		render_all(t_map_info *map, mlx_t *mlx);
int32_t		render_img(mlx_t *mlx, mlx_image_t *img, int x, int y);

void		move_up(t_map_info *map);
void		move_down(t_map_info *map);
void		move_left(t_map_info *map);
void		move_right(t_map_info *map);

void		error_message(t_error *errme);
void		exit_wrapper(char *str);
void		free_boolarray(bool **array);
void		save_map(int fd, t_map_info *map);
void		save_mapcomponents(t_map_info *map, int x, int y, char c);
#endif
