/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:04:13 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 14:30:16 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	check_eof(int fd, t_data *data)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line && line[0] != '\n')
			exit_and_free(line, "Error: Invalid map", data, fd);
		free(line);
	}
}

bool	is_data_init(t_map_data *map_data)
{
	if (map_data->ceiling >= 0 && map_data->path_so_text
		&& map_data->path_no_text && map_data->path_ea_text
		&& map_data->path_we_text && map_data->floor >= 0)
		return (true);
	return (false);
}

int	exit_cross(t_data *data)
{
	exit_and_free(NULL, "", data, -1);
	return (0);
}
