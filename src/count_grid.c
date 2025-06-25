/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:15 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 13:07:19 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	count_line_height(char *line, int height, bool *map_line)
{
	*map_line = false;
	if ((!ft_strncmp(skip_space(line), "1", 1)
			|| !ft_strncmp(skip_space(line), "0", 1)))
	{
		height++;
		*map_line = true;
	}
	free(line);
	return (height);
}

int	count_map_height(char *map_name, t_data *data)
{
	int		fd;
	char	*line;
	int		height;
	bool	map_line;

	map_line = false;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line || (map_line && line[0] == '\n'))
		{
			free(line);
			break ;
		}
		height = count_line_height(line, height, &map_line);
	}
	if (height == 0)
		exit_and_free(NULL, "Error: Missing data", data, fd);
	check_eof(fd, data);
	close(fd);
	return (height);
}
