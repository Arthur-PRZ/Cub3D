/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:11:32 by ctravers          #+#    #+#             */
/*   Updated: 2025/06/04 12:50:13 by artperez         ###   ########.fr       */
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
	return (ft_strdup(skip_space(line + i + 1)));
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
		if ((ft_isalpha(line[i]) && line[i] != ' ' && line[i] != 'W' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E') || line[i] == '\t')
			return (true);
		i++;
	}
	return (false);
}

static void	exit_and_free(char *line, char *msg, map_data_t *map_data)
{
	int i;

	i = 0;
	if (line)
		free(line);
	if (map_data->map.grid)
	{
		while(i < map_data->map.y)
		{
			free(map_data->map.grid[i]);
			i++;
		}
		free(map_data->map.grid);
	}
	if (map_data->so_text)
		free(map_data->so_text);
	if (map_data->no_text)
		free(map_data->no_text);
	if (map_data->we_text)
		free(map_data->we_text);	
	if (map_data->ea_text)
		free(map_data->ea_text);
	ft_printf("%s\n", msg);
	exit(1);
}
static void	check_line(char *line, map_data_t *map_data)
{
	char	*temp;

	if (!line)
		return ;
	if (!map_data->no_text && !ft_strncmp(skip_space(line), "NO", 2))
	{
		map_data->no_text = get_path(line);
		free(line);
		return ;
	}
	if (!map_data->so_text && !ft_strncmp(skip_space(line), "SO", 2))
	{
		map_data->so_text = get_path(line);
		free(line);
		return ;
	}
	if (!map_data->we_text && !ft_strncmp(skip_space(line), "WE", 2))
	{
		map_data->we_text = get_path(line);
		free(line);
		return ;
	}
	if (!map_data->ea_text && !ft_strncmp(skip_space(line), "EA", 2))
	{
		map_data->ea_text = get_path(line);
		free(line);
		return ;
	}
	if (!map_data->floor && !ft_strncmp(skip_space(line), "F", 1))
	{
		temp = get_path(line);
		map_data->floor = ft_atoi(temp);
		free(line);
		free(temp);
		return ;
	}	
	if (!map_data->ceiling && !ft_strncmp(skip_space(line), "C", 1))
	{
		temp = get_path(line);
		map_data->ceiling = ft_atoi(temp);
		free(line);
		free(temp);
		return ;
	}
	if ((!ft_strncmp(skip_space(line), "1", 1) || !ft_strncmp(skip_space(line), "0", 1)) && !is_alpha(line) && is_data_init(map_data))
	{
		get_map(line, map_data);
		free(line);
		return ;
	}
	else if (is_alpha(line) && is_data_init(map_data))
		exit_and_free(line, "Error: Invalid character detected", map_data);
	else if (!ft_strncmp(skip_space(line), "1", 1) && !is_data_init(map_data))
		exit_and_free(line, "Error: Missing data", map_data);
	if (line[0] != '\n')
		exit_and_free(line, "Error: Invalid character detected", map_data);
	free(line);
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
}

static void	check_eof(int fd, map_data_t *map_data)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (line && line[0] != '\n')
			exit_and_free(line, "Error: Invalid map", map_data);
		free(line);
	}
}

static int	count_map_height(char *map_name, map_data_t *map_data)
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
		map_line = false;
		if ((!ft_strncmp(skip_space(line), "1", 1)
			|| !ft_strncmp(skip_space(line), "0", 1)))
		{
			height++;
			map_line = true;
		}
		free(line);
	}
	check_eof(fd, map_data);
	close(fd);
	return (height);
}

static bool	check_neighbor(map_data_t *map_data, int x, int y)
{
	char top;
	char bot;
	char left;
	char right;
	
	top = '\0';
	bot = '\0';
	right = '\0';
	left = '\0';
	if (y - 1 >= 0 && x < (int)ft_strlen(map_data->map.grid[y - 1]))
		top = map_data->map.grid[y - 1][x];
	if (y + 1 < map_data->map.y && x < (int)ft_strlen(map_data->map.grid[y + 1]))
		bot = map_data->map.grid[y + 1][x];
	if (x + 1 < (int)ft_strlen(map_data->map.grid[y]))
		left = map_data->map.grid[y][x + 1];
	if (x - 1 >= 0)
		right = map_data->map.grid[y][x - 1];
	if (map_data->map.grid[y][x] == '0' && ((top == ' ' || top == '\0') || (bot == '\0' || bot == ' ')
		|| (left == '\0' || left == ' ') || (right == '\0' || right == ' ')))
	{
		ft_printf("Top: %c, Bot: %c, Right: %c, Left: %c, pos x: %i, pos y: %i, char: %c\n", top, bot, right, left, x, y, map_data->map.grid[y][x]);
		return (false);
	}
	return (true);
}

void	check_map(map_data_t *map_data)
{
	int	x;
	int	y;
	int height;
	int	len;

	y = 0;
	len = 0;
	height = map_data->map.y;
	while (y < height)
	{
		x = 0;
		len = (int)ft_strlen(map_data->map.grid[y]);
		while (x < len)
		{
			if (!check_neighbor(map_data, x, y))
				exit_and_free(NULL, "Error: Unclosed map", map_data);
			if ((y == 0 && map_data->map.grid[0][x] == '0') || (y == height - 1 && map_data->map.grid[height - 1][x] == '0'))
				exit_and_free(NULL, "Error: Unclosed map", map_data);
			if ((x == 0 && map_data->map.grid[y][0] == '0') || (x == len - 1 && map_data->map.grid[y][len - 1] == '0'))
				exit_and_free(NULL, "Error: Unclosed map", map_data);
			x++;
		}
		y++;
	}
}


void	init_map_data(char *map_name, map_data_t *map_data)
{
	int		fd;
	
	map_data->ceiling = 0;
	map_data->floor = 0;
	map_data->map.y = 0;
	map_data->no_text = NULL;
	map_data->so_text = NULL;
	map_data->we_text = NULL;
	map_data->ea_text = NULL;
	map_data->map.grid = NULL;
	map_data->map.y = count_map_height(map_name, map_data);
	map_data->map.grid = malloc((map_data->map.y + 1) * sizeof(char *));
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exit_error("Error: Can't open fd\n");
	get_map_data(map_data, fd);
	ft_printf("North:%s South:%s West:%s East:%s", map_data->no_text, map_data->so_text, map_data->we_text, map_data->ea_text);
	check_map(map_data);
	int i = 0;
	while (i < map_data->map.y)
	{
		ft_printf("%s\n", map_data->map.grid[i]);
		i++;
	}
	exit_and_free(NULL, "", map_data);
}
