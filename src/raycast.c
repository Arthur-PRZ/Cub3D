/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:55:08 by artperez          #+#    #+#             */
/*   Updated: 2025/06/13 13:51:04 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void put_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;
    dst = data->scene.addr + (y * data->scene.size_line + x * (data->scene.bpp / 8));
    *(unsigned int*)dst = color;
}

static void draw_vertical_line(t_data *data, int x, int y_start, int y_end, int color)
{
	int	y;

	y = 0;
    if (y_start < 0)
		y_start = 0;
    if (y_end >= SCREEN_HEIGHT)
		y_end = SCREEN_HEIGHT - 1;
    y = y_start;
    while (y <= y_end)
    {
        put_pixel(data, x, y, color);
		y++;
    }
}

static void draw_ceiling_and_floor_column(t_data *data, int x, int wall_start, int wall_end)
{
    int y;
    
    y = 0;
    while (y < wall_start)
    {
        put_pixel(data, x, y, data->map_data.ceiling);
        y++;
    }
    y = wall_end + 1;
    while (y < SCREEN_HEIGHT)
    {
        put_pixel(data, x, y, data->map_data.floor);
        y++;
    }
}

static void	init_ray_params(t_data *data, int x)
{
	data->raycast.camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
	data->raycast.raydir_x = data->raycast.dir_x + data->raycast.plane_x * data->raycast.camera_x;
	data->raycast.raydir_y = data->raycast.dir_y + data->raycast.plane_y * data->raycast.camera_x;
	data->raycast.map_x = (int)data->raycast.pos_x;
	data->raycast.map_y = (int)data->raycast.pos_y;
	data->raycast.is_wall = false;
}

static void	find_delta_dist(t_data *data)
{
	if (data->raycast.raydir_x == 0)
		data->raycast.deltadist_x = 1e30;
	else
		data->raycast.deltadist_x = fabs(1 / data->raycast.raydir_x);
	if (data->raycast.raydir_y == 0)
		data->raycast.deltadist_y = 1e30;
	else
		data->raycast.deltadist_y = fabs(1 / data->raycast.raydir_y);
}

static void	find_step_and_sidedist(t_data *data)
{
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
		if (data->map_data.map.grid[data->raycast.map_y][data->raycast.map_x] == '1')
			data->raycast.is_wall = true;
	}
}

static void	find_wall_dist(t_data *data)
{			
	if (data->raycast.side == 0)
		data->raycast.perpwalldist = (data->raycast.sidedist_x - data->raycast.deltadist_x);
	else
		data->raycast.perpwalldist = (data->raycast.sidedist_y - data->raycast.deltadist_y);
}

static void	find_draw_coords(t_data *data)
{
	data->raycast.lineheight = (int)(SCREEN_HEIGHT / data->raycast.perpwalldist);
	data->raycast.drawstart = -data->raycast.lineheight / 2 + SCREEN_HEIGHT / 2;
	if (data->raycast.drawstart < 0)
		data->raycast.drawstart = 0;
	data->raycast.drawend = data->raycast.lineheight / 2 + SCREEN_HEIGHT / 2;
	if (data->raycast.drawend >= SCREEN_HEIGHT)
		data->raycast.drawend = SCREEN_HEIGHT - 1;
}

static int	get_wall_color(t_data *data)
{
	if (data->raycast.side == 0)
	{
		if (data->raycast.step_x > 0)
			return (0x00FF0000); 
		else
			return (0x0000FF00);
	}
	else
	{
		if (data->raycast.step_y > 0)
			return (0x00808080);
		else
			return (0x000000FF); 
	}
}

static void	process_raycast_column(t_data *data, int x)
{
	int color;

	init_ray_params(data, x);
	find_delta_dist(data);
	find_step_and_sidedist(data);
	dda_algo(data);
	find_wall_dist(data);
	find_draw_coords(data);
	draw_ceiling_and_floor_column(data, x, data->raycast.drawstart, data->raycast.drawend);
	color = get_wall_color(data);
	draw_vertical_line(data, x, data->raycast.drawstart, data->raycast.drawend, color);
}

static void	init_scene_img(t_data *data)
{
	data->scene.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->scene.addr = mlx_get_data_addr(data->scene.img, &data->scene.bpp, &data->scene.size_line, &data->scene.endian);
}
void    raycast(t_data *data)
{
	int	x;

	x = 0;

    if (data->scene.img)
        mlx_destroy_image(data->mlx, data->scene.img);
    init_scene_img(data);
	while (x < SCREEN_WIDTH)
	{
		process_raycast_column(data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img, 0, 0);
}