/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:55:08 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 14:18:13 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	draw_ceiling_and_floor_column(t_data *data,
	int x, int wall_start, int wall_end)
{
	int	y;
	int	bpp_x_calc;

	y = 0;
	bpp_x_calc = x * (data->scene.bpp / 8);
	while (y < wall_start)
	{
		*(int *)(data->scene.addr + (y
					* data->scene.size_line + bpp_x_calc))
			= data->map_data.ceiling;
		y++;
	}
	y = wall_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		*(int *)(data->scene.addr + (y
					* data->scene.size_line + bpp_x_calc))
			= data->map_data.floor;
		y++;
	}
}

static void	init_ray_params(t_data *data, int x)
{
	data->raycast.camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
	data->raycast.raydir_x = data->raycast.dir_x
		+ data->raycast.plane_x * data->raycast.camera_x;
	data->raycast.raydir_y = data->raycast.dir_y
		+ data->raycast.plane_y * data->raycast.camera_x;
	data->raycast.map_x = (int)data->raycast.pos_x;
	data->raycast.map_y = (int)data->raycast.pos_y;
	data->raycast.is_wall = false;
}

static void	dda_algo(t_data *data)
{
	while (!data->raycast.is_wall)
	{
		if (data->raycast.sidedist_x < data->raycast.sidedist_y)
		{
			data->raycast.sidedist_x += data->raycast.deltadist_x;
			data->raycast.map_x += data->raycast.step_x;
			data->raycast.side = 0;
		}
		else
		{
			data->raycast.sidedist_y += data->raycast.deltadist_y;
			data->raycast.map_y += data->raycast.step_y;
			data->raycast.side = 1;
		}
		if (data->map_data.map.grid[data->raycast.map_y]
			[data->raycast.map_x] == '1')
			data->raycast.is_wall = true;
	}
}

static void	process_raycast_column(t_data *data, int x)
{
	int	color;

	color = 0;
	init_ray_params(data, x);
	find_delta_dist(data);
	find_step_and_sidedist(data);
	dda_algo(data);
	find_wall_dist(data);
	find_draw_coords(data);
	draw_ceiling_and_floor_column(data, x,
		data->raycast.drawstart, data->raycast.drawend);
	draw_vertical_line(data, x, color);
}

void	raycast(t_data *data)
{
	int	x;
	int	color;
	int	step;

	step = 2;
	color = 0;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		process_raycast_column(data, x);
		if (x + 1 < SCREEN_WIDTH)
			memcpy_column(data, x + 1, x);
		x += step;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img, 0, 0);
}
