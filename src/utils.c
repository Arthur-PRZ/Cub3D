/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:24:25 by ctravers          #+#    #+#             */
/*   Updated: 2025/06/25 11:53:54 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	exit_error(char *msg)
{
    ft_putstr_fd(msg, 2);
    exit(1);
}

double	get_time()
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec + t.tv_usec / 1000000.0);
}

char	*skip_space(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (line + i);
}

bool	is_alpha(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if ((ft_isalpha(line[i]) && line[i] != ' '
				&& line[i] != 'W' && line[i] != 'N'
				&& line[i] != 'S' && line[i] != 'E') || line[i] == '\t')
			return (true);
		i++;
	}
	return (false);
}

char	*skip_figure_and_comma(char	*tmp, char *line, t_data *data, int fd)
{
	int	i;

	i = 0;
	while (tmp[i] && (tmp[i] >= '0' && tmp[i] <= '9'))
		i++;
	while (tmp[i] && tmp[i] == ' ')
		i++;
	if (tmp[i] == ',' && ((tmp[i + 1] >= '0' && tmp[i + 1] <= '9')
			|| tmp[i + 1] == '\0' || tmp[i + 1] == ' '))
	{
		i++;
		return (skip_space(tmp + i));
	}
	else
		exit_and_free(line, "Error: Rgb, invalid format", data, fd);
	return (NULL);
}
