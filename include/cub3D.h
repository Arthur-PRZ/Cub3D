/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:03:46 by artperez          #+#    #+#             */
/*   Updated: 2025/06/06 14:09:29 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include "../libft/include/libft.h"
#include "../libft/include/ft_printf.h"
#include "../libft/include/get_next_line_bonus.h"
#include <stdbool.h>
#include "../minilibx-linux/mlx.h"

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
	t_map_data	map_data;
	t_textures	textures;
	t_img	ceiling;
	t_img	floor;
	int		offset;
}		t_data;

void	check_input(int args_nbr, char *input);
void	check_map_name(char *map_name);
void	init_map_data(char *map_name, t_data *data);
void	exit_error(char *msg);
char	*skip_space(char *line);
void    init_data(t_data *data);
void	exit_and_free(char *line, char *msg, t_data *data, int fd);

#endif