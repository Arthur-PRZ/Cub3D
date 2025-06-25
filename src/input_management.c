/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:01:13 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 13:11:47 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	check_input(int args_nbr, char *input)
{
	if (args_nbr <= 1)
		exit_error("file .cub is needed\n");
	if (args_nbr >= 3)
		exit_error("Only one file .cub is needed\n");
	check_map_name(input);
}

void	check_map_name(char *map_name)
{
	int	i;
	int	len;

	i = ft_strlen(map_name);
	len = ft_strlen(map_name);
	while (i > 0)
	{
		if (map_name[i] == '.')
		{
			if (ft_strncmp(map_name + i, ".cub",
					len) == 0)
				return ;
		}
		i--;
	}
	exit_error("file .cub is needed\n");
}
