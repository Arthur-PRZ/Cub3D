/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_text_and_rgb.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:59:36 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 13:00:50 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	get_rgb(char *line, t_data *data, int fd)
{
	int		red;
	int		green;
	int		blue;
	int		rgb;
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
	if ((red < 0 || red > 255 || green < 0 || green > 255
			|| blue < 0 || blue > 255))
	{
		close(fd);
		exit_and_free(line, "Error: Rgb, invalid format", data, fd);
	}
	rgb = (red << 16) + (green << 8) + blue;
	return (rgb);
}

static int	check_line_text(t_data *data, char *line)
{
	if (!data->map_data.path_no_text && !ft_strncmp(skip_space(line), "NO", 2))
	{
		data->map_data.path_no_text = get_path(line);
		free(line);
		return (1);
	}
	if (!data->map_data.path_so_text && !ft_strncmp(skip_space(line), "SO", 2))
	{
		data->map_data.path_so_text = get_path(line);
		free(line);
		return (1);
	}
	if (!data->map_data.path_we_text && !ft_strncmp(skip_space(line), "WE", 2))
	{
		data->map_data.path_we_text = get_path(line);
		free(line);
		return (1);
	}
	if (!data->map_data.path_ea_text && !ft_strncmp(skip_space(line), "EA", 2))
	{
		data->map_data.path_ea_text = get_path(line);
		free(line);
		return (1);
	}
	return (0);
}

static int	check_line_rgb(t_data *data, char *line, int fd)
{
	char	*temp;

	if (data->map_data.floor == -1 && !ft_strncmp(skip_space(line), "F", 1))
	{
		temp = get_path(line);
		free(line);
		data->map_data.floor = get_rgb(temp, data, fd);
		free(temp);
		return (1);
	}
	if (data->map_data.ceiling == -1 && !ft_strncmp(skip_space(line), "C", 1))
	{
		temp = get_path(line);
		free(line);
		data->map_data.ceiling = get_rgb(temp, data, fd);
		free(temp);
		return (1);
	}
	return (0);
}

void	check_line(char *line, t_data *data, int fd)
{
	if (!line)
		return ;
	if (check_line_text(data, line) == 1 || check_line_rgb(data, line, fd) == 1)
		return ;
	if ((!ft_strncmp(skip_space(line), "1", 1)
			|| !ft_strncmp(skip_space(line), "0", 1))
		&& !is_alpha(line) && is_data_init(&data->map_data))
	{
		get_map(line, &data->map_data);
		free(line);
		return ;
	}
	else if (is_alpha(line) && is_data_init(&data->map_data))
		exit_and_free(line, "Error: Invalid character detected", data, fd);
	else if (!ft_strncmp(skip_space(line), "1", 1)
		&& !is_data_init(&data->map_data))
		exit_and_free(line, "Error: Missing data", data, fd);
	if (line[0] != '\n')
		exit_and_free(line, "Error: Invalid character detected", data, fd);
	free(line);
}
