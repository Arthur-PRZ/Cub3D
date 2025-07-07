/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:51:59 by artperez          #+#    #+#             */
/*   Updated: 2025/07/07 09:45:44 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	free_data(t_data *data)
{
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
}

static void	free_gnl_and_fd(int fd)
{
	char	*cleanup_line;

	while (1)
	{
		cleanup_line = get_next_line(fd);
		if (cleanup_line == NULL)
			break ;
		free(cleanup_line);
	}
	close(fd);
}

void	exit_and_free(char *line, char *msg, t_data *data, int fd)
{
	int	i;

	i = 0;
	if (line)
		free(line);
	if (fd >= 0)
		free_gnl_and_fd(fd);
	if (data && data->map_data.map.grid)
	{
		while (i < data->map_data.map.y)
		{
			if (data && data->map_data.map.grid[i])
				free(data->map_data.map.grid[i]);
			i++;
		}
		free(data->map_data.map.grid);
	}
	free_data(data);
	if (msg && msg[0] != '\0')
		ft_printf("%s\n", msg);
	exit(1);
}
