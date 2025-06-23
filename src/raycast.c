/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:55:08 by artperez          #+#    #+#             */
/*   Updated: 2025/06/23 13:39:15 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	get_current_bpp(t_data *data)
{
	if (data->raycast.side == 0)
	{
		if (data->raycast.step_x > 0)
			return (data->textures.ea_bpp);
		else
			return (data->textures.we_bpp);
	}
	else
	{
		if (data->raycast.step_y > 0)
			return (data->textures.so_bpp);
		else
			return (data->textures.no_bpp); 
	}
}

static void draw_ceiling_and_floor_column(t_data *data, int x, int wall_start, int wall_end)
{
    int y;
    int bpp_x_calc;
	
    y = 0;
	bpp_x_calc = x * (data->scene.bpp / 8);
    while (y < wall_start)
    {
        *(int *)(data->scene.addr + (y * data->scene.size_line + bpp_x_calc)) = data->map_data.ceiling;
        y++;
    }
    y = wall_end + 1;
    while (y < SCREEN_HEIGHT)
    {
        *(int *)(data->scene.addr + (y * data->scene.size_line + bpp_x_calc)) = data->map_data.floor;
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

}

// void	draw_wall_all(t_data *data)
// {
// 	int *img;

// 	img = (int *)data->scene.img;

// 	*img = 0;
// 	img++;
// }

static char	*which_texture(t_data *data)
{
	if (data->raycast.side == 0)
	{
		if (data->raycast.step_x > 0)
			return (data->textures.ea_addr);
		else 
			return (data->textures.we_addr);
	}
	else
	{
		if (data->raycast.step_y > 0)
			return (data->textures.so_addr);
		else
			return (data->textures.no_addr); 
	}
}

static int	get_current_ll(t_data *data)
{
	if (data->raycast.side == 0)
	{
		if (data->raycast.step_x > 0)
			return (data->textures.ea_size_line);
		else 
			return (data->textures.we_size_line);
	}
	else
	{
		if (data->raycast.step_y > 0)
			return (data->textures.so_size_line);
		else
			return (data->textures.no_size_line);
	}
}

static void draw_vertical_line(t_data *data, int x, int y_start, int y_end, int color)
{
	int	y;
	double	wall_x;
	int		tex_y;
	int		tex_x;
	int		d;
    int bpp_x_calc;

	y = 0;
	bpp_x_calc = x * (data->scene.bpp / 8);
	data->which_tex = which_texture(data);
	data->current_bpp = get_current_bpp(data);
	data->current_line_length = get_current_ll(data);
    if (y_start < 0)
		y_start = 0;
    if (y_end >= SCREEN_HEIGHT)
		y_end = SCREEN_HEIGHT - 1;
    y = y_start;
	if (data->raycast.side == 0)
    	wall_x = data->raycast.pos_y + data->raycast.perpwalldist * data->raycast.raydir_y;
	else
    	wall_x = data->raycast.pos_x + data->raycast.perpwalldist * data->raycast.raydir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)64);
	if ((data->raycast.side == 0 && data->raycast.raydir_x > 0) ||
    	(data->raycast.side == 1 && data->raycast.raydir_y < 0))
    	tex_x = 64 - tex_x - 1;
    while (y <= y_end)
    {
		d = y * 256 - SCREEN_HEIGHT * 128 + data->raycast.lineheight * 128;
		tex_y = ((d * 64) / data->raycast.lineheight) / 256;
		color = *(int *)(data->which_tex + (tex_y * data->current_line_length + tex_x * (data->current_bpp / 8)));
		*(int *)(data->scene.addr + (y * data->scene.size_line + bpp_x_calc)) = color;
		y++;
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
	draw_ceiling_and_floor_column(data, x, data->raycast.drawstart, data->raycast.drawend);
	draw_vertical_line(data, x, data->raycast.drawstart, data->raycast.drawend, color);
}

static void	memcpy_column(t_data *data, int dst_x, int src_x)
{
	int	y;
	char	*dst;
	char	*src;
	
	y = 0;
	while(y < SCREEN_HEIGHT)
	{
		src = data->scene.addr + (y * data->scene.size_line + src_x * (data->scene.bpp / 8));
		dst = data->scene.addr + (y * data->scene.size_line + dst_x * (data->scene.bpp / 8));
		*(int *)dst = *(int *)src;
		y++;
	}
	
}

void    raycast(t_data *data)
{
	int	x;
	int color;
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