/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:46:28 by ctravers          #+#    #+#             */
/*   Updated: 2025/06/06 14:14:29 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_texture(t_data *data)
{
	int	i;

	i = 64;
	data->textures.so_text = NULL;
	data->textures.ea_text = NULL;
	data->textures.no_text = NULL;
	data->textures.we_text = NULL;
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
}

static void	display_ceiling_and_floor(t_data *data)
{
	int	x;
	int	y;
	
	y = 0;
	data->ceiling.img = mlx_new_image(data->mlx, 1920, 1080 / 2);
	data->floor.img = mlx_new_image(data->mlx, 1920, 1080 / 2);
	data->ceiling.addr = mlx_get_data_addr(data->ceiling.img, &data->ceiling.bpp, &data->ceiling.size_line, &data->ceiling.endian);
	data->floor.addr = mlx_get_data_addr(data->floor.img, &data->floor.bpp, &data->floor.size_line, &data->floor.endian);
	while(y < (1080 / 2))
	{
		x = 0;
		while(x < 1920)
		{
			data->offset = y * data->ceiling.size_line + x * (data->ceiling.bpp / 8);
			data->ceiling.addr[data->offset + 0] = (data->map_data.ceiling & 0x0000FF);
			data->ceiling.addr[data->offset + 1] = (data->map_data.ceiling & 0x00FF00) >> 8;
			data->ceiling.addr[data->offset + 2] = (data->map_data.ceiling & 0xFF0000) >> 16;
			x++;
		}
		y++;
	}
	y = 0;
	while(y < (1080 / 2))
	{
		x = 0;
		while(x < 1920)
		{
			data->offset = y * data->floor.size_line + x * (data->ceiling.bpp / 8);
			data->floor.addr[data->offset + 0] = (data->map_data.floor & 0x0000FF);
			data->floor.addr[data->offset + 1] = (data->map_data.floor & 0x00FF00) >> 8;
			data->floor.addr[data->offset + 2] = (data->map_data.floor & 0xFF0000) >> 16;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->ceiling.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->floor.img, 0, 1080 / 2);
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_and_free(NULL, "Error: Failed to init MLX", data, -1);
	data->win = mlx_new_window(data->mlx, 1920, 1080, "cub3D");
	if (!data->mlx)
		exit_and_free(NULL, "Error: Failed to init MLX", data, -1);
	init_texture(data);
	display_ceiling_and_floor(data);
	mlx_loop(data->mlx);
}