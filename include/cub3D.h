/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:03:46 by artperez          #+#    #+#             */
/*   Updated: 2025/06/11 12:27:42 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../libft/include/libft.h"
#include "../libft/include/ft_printf.h"
#include "../libft/include/get_next_line_bonus.h"
#include "../minilibx-linux/mlx.h"

# define SCREEN_HEIGHT 1080
# define SCREEN_WIDTH 1920
# define PLANE_Y 0.66

typedef struct	s_map
{
	int		y;
	char **grid;
}		t_map;

typedef struct s_map_data
{
		char	*path_no_text;
		char	*path_so_text;
		char	*path_we_text;
		char	*path_ea_text;
		int		floor;
		int		ceiling;
		t_map	map;
}		t_map_data;

typedef struct	s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_dir
{
	int x;
	int	y;
}	t_dir;


typedef struct s_player
{
	t_pos	player_pos;
	t_dir	dir_pos;
}		t_player;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}			t_img;

typedef struct s_raycast
{
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	perpwalldist;
	bool	is_wall;
	int		map_y;
	int		map_x;
	int		dir_x;
	int		dir_y;
	int		side;
	int		step_x;
	int		step_y;
	int		lineheight;
	int		drawstart;
	int		drawend;
}		t_raycast;

typedef struct	s_textures
{
	void	*so_text;
	void	*no_text;
	void	*we_text;
	void	*ea_text;	
}	t_textures;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		offset;
	t_raycast raycast;
	t_map_data	map_data;
	t_textures	textures;
	t_img	scene;
}		t_data;

void	check_input(int args_nbr, char *input);
void	check_map_name(char *map_name);
void	init_map_data(char *map_name, t_data *data);
void	exit_error(char *msg);
char	*skip_space(char *line);
void    init_data(t_data *data);
void	exit_and_free(char *line, char *msg, t_data *data, int fd);
void    raycast(t_data *data);

#endif