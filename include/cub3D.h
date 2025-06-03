/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:03:46 by artperez          #+#    #+#             */
/*   Updated: 2025/06/03 12:50:47 by artperez         ###   ########.fr       */
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

typedef struct	map_s
{
	int	x;
	int	y;
	int	z;
	char **grid;
}		map_t;

typedef struct map_data_s
{
		char	*no_text;
		char	*so_text;
		char	*we_text;
		char	*ea_text;
		int		floor;
		int		ceiling;
		map_t	map;
}		map_data_t;

void	check_input(int args_nbr, char *input);
void	check_map_name(char *map_name);
void	init_map_data(char *map_name, map_data_t *map_data);
void	exit_error(char *msg);
char	*skip_space(char *line);

#endif