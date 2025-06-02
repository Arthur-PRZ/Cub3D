/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_magement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:01:13 by artperez          #+#    #+#             */
/*   Updated: 2025/06/02 10:21:17 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void check_input(int args_nbr, char *input)
{
    if (args_nbr <= 1)
    {
        write(2, "file .cub is needed\n", 21);
        exit (1);
    }
    if (args_nbr >= 3)
    {
        write(2, "Only one file .cub is needed\n", 30);
        exit (1);
    }
    check_map_name(input);
}

int	check_map_name(char *map_name)
{
	int	i;
	int	len;

	i = ft_strlen(map_name);
	len = ft_strlen(map_name);
	while (i > 0)
	{
		if (map_name[i] == '.')
		{
			if (ft_strncmp(ft_strnstr(map_name + i, ".cub", 4), ".cub",
					len) == 0)
				return (0);
		}
		i--;
	}
    write(2, "file .cub is needed\n", 21);
    exit (1);
}
