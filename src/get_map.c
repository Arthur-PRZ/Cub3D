/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:11:32 by ctravers          #+#    #+#             */
/*   Updated: 2025/06/02 12:52:24 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static char	*get_path(char *line)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	line = skip_space(line);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[a] && line[a] != '\n')
		a++;
	if (line[a] == '\n')
		line[a] = '\0';
	return (skip_space(line + i + 1));
}

static void	check_line(char *line, map_data_t *map_data)
{
	if (!line)
		return ;
	if (!map_data->no_text && ft_strncmp(skip_space(line), "NO", 2))
		map_data->no_text = get_path(line);
	if (!map_data->so_text && ft_strncmp(skip_space(line), "SO", 2))
		map_data->so_text = get_path(line);
	if (!map_data->we_text && ft_strncmp(skip_space(line), "WE", 2))
		map_data->we_text = get_path(line);
	if (!map_data->ea_text && ft_strncmp(skip_space(line), "EA", 2))
		map_data->ea_text = get_path(line);
	if (!map_data->floor && ft_strncmp(skip_space(line), "F", 1))
		map_data->floor = ft_atoi(get_path(line));
	if (!map_data->ceiling && ft_strncmp(skip_space(line), "C", 1))
		map_data->ceiling = ft_atoi(get_path(line));
}

static void	get_map(map_data_t *map_data, int fd)
{
	char	*read_file;

	read_file = get_next_line(fd);
	if (!read_file)
		exit_error("Error: file is empty\n");
	while (read_file != NULL)
	{
		read_file = get_next_line(fd);
		check_line(read_file, map_data);
	}
}

void	init_map_data(char *map_name, map_data_t *map_data)
{
	int		fd;
	
	map_data->ceiling = 0;
	map_data->floor = 0;
	map_data->no_text = NULL;
	map_data->so_text = NULL;
	map_data->we_text = NULL;
	map_data->ea_text = NULL;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exit_error("Error: Can't open fd\n");
	get_map(map_data, fd);
	ft_printf("North: %s South: %s West: %s East: %s Floor: %i Ceiling: %i\n", map_data->no_text, map_data->so_text, map_data->we_text, map_data->ea_text, map_data->floor, map_data->ceiling);
}