/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:24:25 by ctravers          #+#    #+#             */
/*   Updated: 2025/06/13 11:16:27 by artperez         ###   ########.fr       */
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