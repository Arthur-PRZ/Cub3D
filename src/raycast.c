/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:55:08 by artperez          #+#    #+#             */
/*   Updated: 2025/06/11 12:32:44 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void put_pixel(t_data *data, int x, int y, int color)
{
    if (x < 0 || x >= 1920 || y < 0 || y >= 1920)
        return;

    char *dst = data->wall.addr + (y * data->wall.size_line + x * (data->wall.bpp / 8));
    *(unsigned int*)dst = color;
}

static void draw_vertical_line(t_data *data, int x, int y_start, int y_end, int color)
{
    if (y_start < 0)
		y_start = 0;
    if (y_end >= 1080)
		y_end = 1080 - 1;
    for (int y = y_start; y <= y_end; y++)
    {
        put_pixel(data, x, y, color);
    }
}

static void init_raycast(t_data *data)
{
	int	x;

	x = 0;
	data->raycast.plane_x = 0;
	data->raycast.plane_y = 0.66;
	while (x < 1920)
	{
		data->raycast.camera_x = 2 * x / 1920 - 1;
		data->raycast.raydir_x = data->raycast.dir_x + data->raycast.plane_x * data->raycast.camera_x;
		data->raycast.raydir_y = data->raycast.dir_y + data->raycast.plane_y * data->raycast.camera_x;
		data->raycast.map_x = (int)data->raycast.pos_x;
		data->raycast.map_y = (int)data->raycast.pos_y;
		if (data->raycast.raydir_x == 0)
			data->raycast.deltadist_x = 1e30;
		else
			data->raycast.deltadist_x = fabs(1 / data->raycast.raydir_x);
		if (data->raycast.raydir_y == 0)
			data->raycast.deltadist_y = 1e30;
		else
			data->raycast.deltadist_y = fabs(1 / data->raycast.raydir_y);
		data->raycast.is_wall = false;
		if (data->raycast.raydir_x < 0)
		{
			data->raycast.step_x = -1;
			data->raycast.sidedist_x = (data->raycast.pos_x - data->raycast.map_x) * data->raycast.deltadist_x;
		}
		else
		{
			data->raycast.step_x = 1;
			data->raycast.sidedist_x = (data->raycast.map_x + 1.0 - data->raycast.pos_x) * data->raycast.deltadist_x;
		}
		if (data->raycast.raydir_y < 0)
		{
			data->raycast.step_y = -1;
			data->raycast.sidedist_y = (data->raycast.pos_y - data->raycast.map_y) * data->raycast.deltadist_y;
		}
		else
		{
			data->raycast.step_y = 1;
			data->raycast.sidedist_y = (data->raycast.map_y + 1.0 - data->raycast.pos_y) * data->raycast.deltadist_y;
		}
		while (data->raycast.is_wall == false)
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
			if (data->map_data.map.grid[data->raycast.map_y][data->raycast.map_x] > 0)
				data->raycast.is_wall = true;
			if (data->raycast.side == 0)
				data->raycast.perpwalldist = (data->raycast.sidedist_x - data->raycast.deltadist_x);
			else
				data->raycast.perpwalldist = (data->raycast.sidedist_y - data->raycast.deltadist_y);
			data->raycast.lineheight = (int)(1080 / data->raycast.perpwalldist);
			data->raycast.drawstart = -data->raycast.lineheight / 2 + 1080 / 2;
			if (data->raycast.drawstart < 0)
				data->raycast.drawstart = 0;
			data->raycast.drawend = data->raycast.lineheight / 2 + 1080 / 2;
			if (data->raycast.drawend >= 1080)
				data->raycast.drawend = 1080 - 1;
			data->wall.img = mlx_new_image(data->mlx, 1920, 1080);
			data->wall.addr = mlx_get_data_addr(data->wall.img, &data->wall.bpp, &data->wall.size_line, &data->wall.endian);
			int color;
			switch (data->map_data.map.grid[data->raycast.map_y][data->raycast.map_x])
			{
    			case 1:  color = 0xFF0000; break; // rouge
    			case 2:  color = 0x00FF00; break; // vert
    			case 3:  color = 0x0000FF; break; // bleu
    			case 4:  color = 0xFFFFFF; break; // blanc
    			default: color = 0xFFFF00; break; // jaune
			}
			draw_vertical_line(data, x, data->raycast.drawstart, data->raycast.drawend, color);
		}
	}

}

void    raycast(t_data *data)
{
    init_raycast(data);
}