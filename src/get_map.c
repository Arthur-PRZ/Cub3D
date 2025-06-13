/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:11:32 by ctravers          #+#    #+#             */
/*   Updated: 2025/06/13 13:53:39 by artperez         ###   ########.fr       */
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

static void	get_map(char *line, t_map_data *map_data)
{
	static int	i;
	int	j;

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

static bool	is_data_init(t_map_data *map_data)
{
	if (map_data->ceiling >= 0 && map_data->path_so_text 
		&& map_data->path_no_text && map_data->path_ea_text && map_data->path_we_text && map_data->floor >= 0)
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

void	exit_and_free(char *line, char *msg, t_data *data, int fd)
{
	int i;
	char *cleanup_line;

	i = 0;
	if (line)
		free(line);
	if (fd >= 0)
	{
		while ((cleanup_line = get_next_line(fd)) != NULL)
			free(cleanup_line);
		close(fd);
	}
	if (data && data->map_data.map.grid)
	{
		while(i < data->map_data.map.y)
		{
			if (data && data->map_data.map.grid[i])
				free(data->map_data.map.grid[i]);
			i++;
		}
		free(data->map_data.map.grid);
	}
	if (data->map_data.path_so_text)
		free(data->map_data.path_so_text);
	if (data->map_data.path_no_text)
		free(data->map_data.path_no_text);
	if (data->map_data.path_we_text)
		free(data->map_data.path_we_text);	
	if (data->map_data.path_ea_text)
		free(data->map_data.path_ea_text);
	if (data && data->textures.no_text)
		mlx_destroy_image(data->mlx, data->textures.no_text);
	if (data && data->textures.so_text)
		mlx_destroy_image(data->mlx, data->textures.so_text);
	if (data && data->textures.we_text)
		mlx_destroy_image(data->mlx, data->textures.we_text);
	if (data && data->textures.ea_text)
		mlx_destroy_image(data->mlx, data->textures.ea_text);
	if (data && data->scene.img)
        mlx_destroy_image(data->mlx, data->scene.img);
	if (data && data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data && data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}	
	ft_printf("%s\n", msg);
	exit(1);
}

static char	*skip_figure_and_comma(char	*tmp, char *line, t_data *data, int fd)
{
	int	i;

	i = 0;
	while (tmp[i] && (tmp[i] >= '0' && tmp[i] <= '9'))
		i++;
	while (tmp[i] && tmp[i] == ' ')
		i++;
	if (tmp[i] == ',' && ((tmp[i + 1] >= '0' && tmp[i + 1] <= '9') || tmp[i + 1] == '\0' || tmp[i + 1] == ' '))
	{
		i++;
		return (skip_space(tmp + i));
	}
	else
		exit_and_free(line, "Error: Rgb, invalid format", data, fd);
	return (NULL);
}

int	get_rgb(char *line, t_data *data, int fd)
{
	int	red;
	int	green;
	int	blue;
	int	rgb;
	char	*tmp;

	green = -1;
	blue = -1;
	red = -1;
	tmp = line;
	red = ft_atoi(tmp);
	tmp = skip_figure_and_comma(tmp, line, data, fd);
	green = ft_atoi(tmp);
	tmp = skip_figure_and_comma(tmp, line, data, fd);
	if (!is_alpha(tmp))
		blue = ft_atoi(tmp);
	if ((red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255))
	{
		close(fd);
		exit_and_free(line, "Error: Rgb, invalid format", data, fd);
	}
	ft_printf("Red: %i, Green: %i, Blue: %i\n", red, green, blue);
	rgb = (red << 16) + (green << 8) + blue;
	return (rgb);
}

static void	check_line(char *line, t_data *data, int fd)
{
	char	*temp;

	if (!line)
		return ;
	if (!data->map_data.path_no_text && !ft_strncmp(skip_space(line), "NO", 2))
	{
		data->map_data.path_no_text = get_path(line);
		free(line);
		return ;
	}
	if (!data->map_data.path_so_text && !ft_strncmp(skip_space(line), "SO", 2))
	{
		data->map_data.path_so_text = get_path(line);
		free(line);
		return ;
	}
	if (!data->map_data.path_we_text && !ft_strncmp(skip_space(line), "WE", 2))
	{
		data->map_data.path_we_text = get_path(line);
		free(line);
		return ;
	}
	if (!data->map_data.path_ea_text && !ft_strncmp(skip_space(line), "EA", 2))
	{
		data->map_data.path_ea_text = get_path(line);
		free(line);
		return ;
	}
	if (data->map_data.floor == -1 && !ft_strncmp(skip_space(line), "F", 1))
	{
		temp = get_path(line);
		free(line);
		data->map_data.floor = get_rgb(temp, data, fd);
		ft_printf("%i\n", data->map_data.floor);
		free(temp);
		return ;
	}	
	if (data->map_data.ceiling == -1 && !ft_strncmp(skip_space(line), "C", 1))
	{
		temp = get_path(line);
		free(line);
		data->map_data.ceiling = get_rgb(temp, data, fd);
		free(temp);
		return ;
	}
	if ((!ft_strncmp(skip_space(line), "1", 1) || !ft_strncmp(skip_space(line), "0", 1)) && !is_alpha(line) && is_data_init(&data->map_data))
	{
		get_map(line, &data->map_data);
		free(line);
		return ;
	}
	else if (is_alpha(line) && is_data_init(&data->map_data))
		exit_and_free(line, "Error: Invalid character detected", data, fd);
	else if (!ft_strncmp(skip_space(line), "1", 1) && !is_data_init(&data->map_data))
		exit_and_free(line, "Error: Missing data", data, fd);
	if (line[0] != '\n')
		exit_and_free(line, "Error: Invalid character detected", data, fd);
	free(line);
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

static void	check_eof(int fd, t_data *data)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (line && line[0] != '\n')
			exit_and_free(line, "Error: Invalid map", data, fd);
		free(line);
	}
}

static int	count_map_height(char *map_name, t_data *data)
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
	check_eof(fd, data);
	close(fd);
	return (height);
}

static bool	check_neighbor(t_map_data *map_data, int x, int y)
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
		return (false);
	}
	return (true);
}

void	check_map(t_data *data, int fd)
{
	int	x;
	int	y;
	int height;
	int	len;
	char	curr;

	y = 0;
	len = 0;
	data->raycast.pos_x = -1;
	height = data->map_data.map.y;
	while (y < height)
	{
		x = 0;
		len = (int)ft_strlen(data->map_data.map.grid[y]);
		while (x < len)
		{
			curr = data->map_data.map.grid[y][x];
			if ((curr == 'W' || curr == 'E' || curr == 'N' || curr == 'S') && data->raycast.pos_x != -1)
				exit_and_free(NULL, "Error: Too much spawn points", data, fd);
			if (curr == 'W' || curr == 'E' || curr == 'N' || curr == 'S')
			{
				if (curr == 'W')
				{
					data->raycast.dir_x = -1;
					data->raycast.dir_y = 0;
					data->raycast.plane_x = 0;
					data->raycast.plane_y = -PLANE;
				}
				if (curr == 'N')
				{
					data->raycast.dir_x = 0;
					data->raycast.dir_y = -1;
					data->raycast.plane_x = -PLANE;
					data->raycast.plane_y = 0;
				}
				if (curr == 'S')
				{
					data->raycast.dir_x = 0;
					data->raycast.dir_y = 1;
					data->raycast.plane_x = PLANE;
					data->raycast.plane_y = 0;
				}
				if (curr == 'E')
				{
					data->raycast.dir_x = 1;
					data->raycast.dir_y = 0;
					data->raycast.plane_x = 0;
					data->raycast.plane_y = PLANE;
				}				
				data->raycast.pos_x = x + 0.5;
				data->raycast.pos_y = y + 0.5;
			}
			if (!check_neighbor(&data->map_data, x, y))
				exit_and_free(NULL, "Error: Unclosed map", data, fd);
			if ((y == 0 && data->map_data.map.grid[0][x] == '0') || (y == height - 1 && data->map_data.map.grid[height - 1][x] == '0'))
				exit_and_free(NULL, "Error: Unclosed map", data, fd);
			if ((x == 0 && data->map_data.map.grid[y][0] == '0') || (x == len - 1 && data->map_data.map.grid[y][len - 1] == '0'))
				exit_and_free(NULL, "Error: Unclosed map", data, fd);
			x++;
		}
		y++;
	}
	if (data->raycast.pos_x == -1)
		exit_and_free(NULL, "Error: No spawn point found", data, fd);
}


void	init_map_data(char *map_name, t_data *data)
{
	int		fd;
	
	data->map_data.ceiling = -1;
	data->map_data.floor = -1;
	data->map_data.map.y = 0;
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
	// ft_printf("North:%s South:%s West:%s East:%s\nRgb ceiling:%i Rgb floor:%i\n", map_data->no_text, map_data->so_text, map_data->we_text, map_data->ea_text, map_data->floor, map_data->ceiling);
	check_map(data, fd);
	close(fd);
	// while (i < map_data->map.y)
	// {
	// 	ft_printf("%s\n", map_data->map.grid[i]);
	// 	i++;
	// }
	// exit_and_free(NULL, "", map_data, fd);
}
