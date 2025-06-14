/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:03:46 by artperez          #+#    #+#             */
/*   Updated: 2025/06/13 15:47:05 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <X11/keysym.h>
#include <sys/time.h>
#include "../libft/include/libft.h"
#include "../libft/include/ft_printf.h"
#include "../libft/include/get_next_line_bonus.h"
#include "../minilibx-linux/mlx.h"
#include <stdio.h>

# define SCREEN_HEIGHT 1080
# define SCREEN_WIDTH 1920
# define PLANE 0.66

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

typedef struct s_keys
{
	bool	w_pressed;
	bool	a_pressed;
	bool	d_pressed;
	bool	s_pressed;
	bool	left_pressed;
	bool	right_pressed;
}		t_keys;

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
	double		dir_x;
	double		dir_y;
	bool	is_wall;
	int		map_y;
	int		map_x;
	int		side;
	int		step_x;
	int		step_y;
	int		lineheight;
	int		drawstart;
	int		drawend;
}		t_raycast;

typedef struct s_textures
{
	void	*so_text;
	void	*no_text;
	void	*we_text;
	void	*ea_text;
	int		*so_data;
	int		*no_data;
	int		*we_data;
	int		*ea_data;
	int		width;
	int		height;
}	t_textures;


typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		offset;
	double	move_speed;
	double	rot_speed;
	double	old_time;
	t_raycast raycast;
	t_map_data	map_data;
	t_textures	textures;
	t_img	scene;
	t_keys	keys;
}		t_data;

void	check_input(int args_nbr, char *input);
void	check_map_name(char *map_name);
void	init_map_data(char *map_name, t_data *data);
void	exit_error(char *msg);
char	*skip_space(char *line);
void    init_data(t_data *data);
void	exit_and_free(char *line, char *msg, t_data *data, int fd);
void    raycast(t_data *data);
void	movements(t_data *data);
double	get_time();
int		game_loop(t_data *data);
void	handle_movement(t_data *data);

#endif