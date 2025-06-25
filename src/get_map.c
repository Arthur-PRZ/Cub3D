/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:11:32 by ctravers          #+#    #+#             */
/*   Updated: 2025/06/25 12:59:48 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*get_path(char *line)
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
	return (ft_strdup(skip_space(line + i + 1)));
}

void	get_map(char *line, t_map_data *map_data)
{
	static int	i;
	int			j;

	if (map_data->map.grid == NULL)
	{
		map_data->map.grid = malloc((map_data->map.y + 1) * sizeof(char *));
		j = 0;
		while (j <= map_data->map.y)
		{
			map_data->map.grid[j] = NULL;
			j++;
		}
	}
	map_data->map.grid[i] = ft_strdup(line);
	map_data->map.grid[i][ft_strlen(line) - 1] = '\0';
	i++;
}

static void	get_map_data(t_data *data, int fd)
{
	char	*read_file;

	read_file = get_next_line(fd);
	if (!read_file)
		exit_error("Error: file is empty\n");
	while (read_file != NULL)
	{
		check_line(read_file, data, fd);
		read_file = get_next_line(fd);
	}
	if (!is_data_init(&data->map_data))
		exit_and_free(NULL, "Error: Missing data", data, fd);
}

void	init_map_data(char *map_name, t_data *data)
{
	int		fd;

	data->map_data.ceiling = -1;
	data->map_data.floor = -1;
	data->map_data.map.y = 0;
	data->scene.img = NULL;
	data->map_data.path_no_text = NULL;
	data->map_data.path_so_text = NULL;
	data->map_data.path_we_text = NULL;
	data->map_data.path_ea_text = NULL;
	data->map_data.map.grid = NULL;
	data->textures.so_text = NULL;
	data->textures.ea_text = NULL;
	data->textures.no_text = NULL;
	data->textures.we_text = NULL;
	data->win = NULL;
	data->mlx = NULL;
	data->map_data.map.y = count_map_height(map_name, data);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exit_error("Error: Can't open fd\n");
	get_map_data(data, fd);
	check_map(data, fd);
	close(fd);
}
