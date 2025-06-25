/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:56:20 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 13:03:04 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	check_neighbor(t_map_data *map_data, int x, int y)
{
	char	top;
	char	bot;
	char	left;
	char	right;

	top = '\0';
	bot = '\0';
	right = '\0';
	left = '\0';
	if (y - 1 >= 0 && x < (int)ft_strlen(map_data->map.grid[y - 1]))
		top = map_data->map.grid[y - 1][x];
	if (y + 1 < map_data->map.y
		&& x < (int)ft_strlen(map_data->map.grid[y + 1]))
		bot = map_data->map.grid[y + 1][x];
	if (x + 1 < (int)ft_strlen(map_data->map.grid[y]))
		left = map_data->map.grid[y][x + 1];
	if (x - 1 >= 0)
		right = map_data->map.grid[y][x - 1];
	if (map_data->map.grid[y][x] == '0' && ((top == ' ' || top == '\0')
		|| (bot == '\0' || bot == ' ')
		|| (left == '\0' || left == ' ') || (right == '\0' || right == ' ')))
	{
		return (false);
	}
	return (true);
}

static void	pos_init_s_e(t_data *data, char curr)
{
	if (curr == 'S')
	{
		data->raycast.dir_x = 0.0;
		data->raycast.dir_y = 1.0;
		data->raycast.plane_x = PLANE;
		data->raycast.plane_y = 0;
	}
	if (curr == 'E')
	{
		data->raycast.dir_x = 1.0;
		data->raycast.dir_y = 0.0;
		data->raycast.plane_x = 0;
		data->raycast.plane_y = -PLANE;
	}
}

static void	pos_init(t_data *data, char curr, int x, int y)
{
	if (curr == 'W')
	{
		data->raycast.dir_x = -1.0;
		data->raycast.dir_y = 0.0;
		data->raycast.plane_x = 0;
		data->raycast.plane_y = PLANE;
	}
	if (curr == 'N')
	{
		data->raycast.dir_x = 0.0;
		data->raycast.dir_y = -1.0;
		data->raycast.plane_x = -PLANE;
		data->raycast.plane_y = 0;
	}
	pos_init_s_e(data, curr);
	data->raycast.pos_x = x + 0.5;
	data->raycast.pos_y = y + 0.5;
}

static void	check_curr(t_data *data, int fd, int x, int y)
{
	char	curr;
	int		height;
	int		len;

	height = data->map_data.map.y;
	curr = data->map_data.map.grid[y][x];
	len = (int)ft_strlen(data->map_data.map.grid[y]);
	if ((curr == 'W' || curr == 'E' || curr == 'N' || curr == 'S')
		&& data->raycast.pos_x != -1)
		exit_and_free(NULL, "Error: Too much spawn points", data, fd);
	if (curr == 'W' || curr == 'E' || curr == 'N' || curr == 'S')
		pos_init(data, curr, x, y);
	if (!check_neighbor(&data->map_data, x, y))
		exit_and_free(NULL, "Error: Unclosed map", data, fd);
	if ((y == 0 && data->map_data.map.grid[0][x] == '0')
		|| (y == height - 1
		&& data->map_data.map.grid[height - 1][x] == '0'))
		exit_and_free(NULL, "Error: Unclosed map", data, fd);
	if ((x == 0 && data->map_data.map.grid[y][0] == '0')
		|| (x == len - 1 && data->map_data.map.grid[y][len - 1] == '0'))
		exit_and_free(NULL, "Error: Unclosed map", data, fd);
}

void	check_map(t_data *data, int fd)
{
	int	x;
	int	y;
	int	height;
	int	len;

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
			check_curr(data, fd, x, y);
			x++;
		}
		y++;
	}
	if (data->raycast.pos_x == -1)
		exit_and_free(NULL, "Error: No spawn point found", data, fd);
}
