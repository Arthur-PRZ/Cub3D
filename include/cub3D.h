/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:03:46 by artperez          #+#    #+#             */
/*   Updated: 2025/06/05 09:28:18 by artperez         ###   ########.fr       */
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

typedef struct	s_map
{
	int		y;
	char **grid;
}		t_map;

typedef struct s_map_data
{
		char	*no_text;
		char	*so_text;
		char	*we_text;
		char	*ea_text;
		int		floor;
		int		ceiling;
		t_map	map;
}		t_map_data;

void	check_input(int args_nbr, char *input);
void	check_map_name(char *map_name);
void	init_map_data(char *map_name, t_map_data *map_data);
void	exit_error(char *msg);
char	*skip_space(char *line);

#endif