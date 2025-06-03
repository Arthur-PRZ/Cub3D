/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:11:32 by ctravers          #+#    #+#             */
/*   Updated: 2025/06/03 14:21:03 by artperez         ###   ########.fr       */
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

static void	get_map(char *line, map_data_t *map_data)
{
	static int	i;

	map_data->map.grid[i] = ft_strdup(line);
	map_data->map.grid[i][ft_strlen(line) - 1] = '\0';
	i++;
}

static bool	is_data_init(map_data_t *map_data)
{
	if (map_data->ceiling && map_data->so_text 
		&& map_data->no_text && map_data->ea_text && map_data->we_text && map_data->floor)
		return (true);
	return (false);
}

static bool	is_alpha(char *line)
{
	int	i;

	i = 0;
	while(line[i] && line[i] != '\n')
	{
		if (ft_isalpha(line[i]) && line[i] != ' ' && line[i] != 'W' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E')
			return (true);
		i++;
	}
	return (false);
}

static void	exit_and_free(char *line, char *msg)
{
	(void)line;
	(void)msg;
	ft_printf("%s\n", msg);
	exit(1);
}
static void	check_line(char *line, map_data_t *map_data)
{
	if (!line)
		return ;
	if (!map_data->no_text && !ft_strncmp(skip_space(line), "NO", 2))
	{
		map_data->no_text = get_path(line);
		return ;
	}
	if (!map_data->so_text && !ft_strncmp(skip_space(line), "SO", 2))
	{
		map_data->so_text = get_path(line);
		return ;
	}
	if (!map_data->we_text && !ft_strncmp(skip_space(line), "WE", 2))
	{
		map_data->we_text = get_path(line);
		return ;
	}
	if (!map_data->ea_text && !ft_strncmp(skip_space(line), "EA", 2))
	{
		map_data->ea_text = get_path(line);
		return ;
	}
	if (!map_data->floor && !ft_strncmp(skip_space(line), "F", 1))
	{
		map_data->floor = ft_atoi(get_path(line));
		return ;
	}	
	if (!map_data->ceiling && !ft_strncmp(skip_space(line), "C", 1))
	{
		map_data->ceiling = ft_atoi(get_path(line));
		return ;
	}
	if (!ft_strncmp(skip_space(line), "1", 1) && !is_alpha(line) && is_data_init(map_data))
	{
		get_map(line, map_data);
		return ;
	}
	else if (is_alpha(line) && is_data_init(map_data))
		exit_and_free(line, "Error: Invalid character detected");
	else if (!ft_strncmp(skip_space(line), "1", 1) && !is_data_init(map_data))
		exit_and_free(line, "Error: Missing data");
	if (line[0] != '\n')
		exit_and_free(line, "Error: Invalid character detected");
}


static void	get_map_data(map_data_t *map_data, int fd)
{
	char	*read_file;

	read_file = get_next_line(fd);
	if (!read_file)
		exit_error("Error: file is empty\n");
	while (read_file != NULL)
	{
		check_line(read_file, map_data);
		read_file = get_next_line(fd);
	}
	map_data->map.grid[map_data->map.y + 1] = NULL;
}

static void	check_eof(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (line && line[0] != '\n')
			exit_and_free(line, "Error: Invalid map");
		free(line);
	}
}

static int	count_map_height(char *map_name)
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
			break ;
		map_line = false;
		if ((!ft_strncmp(skip_space(line), "1", 1)
			|| !ft_strncmp(skip_space(line), "0", 1)))
		{
			height++;
			map_line = true;
		}
		free(line);
	}
	check_eof(fd);
	close(fd);
	return (height);
}

void	check_map(map_data_t *map_data, int x, int y)
{
	char left;
	char right;
	char top;
	char bot;
	char curr;
	
	if (!map_data->map.grid[y][x])
		return ;
	left = '\0';
	right = '\0';
	bot = '\0';
	top = '\0';
	curr = map_data->map.grid[y][x];
	if (x - 1 > 0)
		left = map_data->map.grid[y][x - 1];
	if (x + 1 < (int)ft_strlen(map_data->map.grid[y]))
		right = map_data->map.grid[y][x + 1];
	if (y - 1 > 0)
		top = map_data->map.grid[y - 1][x];
	if (y + 1 < map_data->map.y)
		bot = map_data->map.grid[y + 1][x];
	if (curr == ' ')
	{
		if ((left && left == '0') || (right && right == '0') || (top && top == '0') || (bot && bot == '0'))
			exit_and_free(NULL, "Error: Unclosed map");
		check_map(map_data, x + 1, y);
		check_map(map_data, x - 1, y);
		check_map(map_data, x, y + 1);
		check_map(map_data, x, y - 1);
	}
	
}

void	init_map_data(char *map_name, map_data_t *map_data)
{
	int		fd;
	
	map_data->ceiling = 0;
	map_data->floor = 0;
	map_data->map.y = 0;
	map_data->map.x = 0;
	map_data->map.z = 0;
	map_data->no_text = NULL;
	map_data->so_text = NULL;
	map_data->we_text = NULL;
	map_data->ea_text = NULL;
	map_data->map.grid = NULL;
	map_data->map.y = count_map_height(map_name);
	map_data->map.grid = malloc((map_data->map.y + 1) * sizeof(char *));
	ft_printf("%i\n", map_data->map.y);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exit_error("Error: Can't open fd\n");
	get_map_data(map_data, fd);
	ft_printf("North: %s South: %s West: %s East: %s Floor: %i Ceiling: %i\n", map_data->no_text, map_data->so_text, map_data->we_text, map_data->ea_text, map_data->floor, map_data->ceiling);
	check_map(map_data, 0, 0);
	int i = 0;
	while (map_data->map.grid[i] != NULL)
	{
		ft_printf("%s\n", map_data->map.grid[i]);
		i++;
	}
}
