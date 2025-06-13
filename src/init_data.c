/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:46:28 by ctravers          #+#    #+#             */
/*   Updated: 2025/06/13 15:48:12 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"



static void	init_texture(t_data *data)
{
	int	i;
	int	bpp;
	int	size_line;
	int	endian;

	i = 64;
	data->textures.so_text = mlx_xpm_file_to_image(data->mlx, data->map_data.path_so_text, &i, &i);
	if (!data->textures.so_text)
		exit_and_free(NULL, "Failed to load south texture", data, -1);
	data->textures.we_text = mlx_xpm_file_to_image(data->mlx, data->map_data.path_we_text, &i, &i);
	if (!data->textures.we_text)
		exit_and_free(NULL, "Failed to load west texture", data, -1);
	data->textures.no_text = mlx_xpm_file_to_image(data->mlx, data->map_data.path_no_text, &i, &i);
	if (!data->textures.no_text)
		exit_and_free(NULL, "Failed to load north texture", data, -1);
	data->textures.ea_text = mlx_xpm_file_to_image(data->mlx, data->map_data.path_ea_text, &i, &i);
	if (!data->textures.ea_text) 
		exit_and_free(NULL, "Failed to load east texture", data, -1);
	data->textures.no_data = (int *)mlx_get_data_addr(data->textures.no_text, &bpp, &size_line, &endian);
	data->textures.so_data = (int *)mlx_get_data_addr(data->textures.so_text, &bpp, &size_line, &endian);
	data->textures.ea_data = (int *)mlx_get_data_addr(data->textures.ea_text, &bpp, &size_line, &endian);
	data->textures.we_data = (int *)mlx_get_data_addr(data->textures.we_text, &bpp, &size_line, &endian);
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->old_time = 0;
	data->scene.img = NULL;
	if (!data->mlx)
		exit_and_free(NULL, "Error: Failed to init MLX", data, -1);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!data->mlx)
		exit_and_free(NULL, "Error: Failed to init MLX", data, -1);
	init_texture(data);
    raycast(data);
}