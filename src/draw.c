/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:58:21 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 14:15:06 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_texture_data(t_data *data)
{
	data->which_tex = which_texture(data);
	data->current_bpp = get_current_bpp(data);
	data->current_line_length = get_current_ll(data);
}

static double	calculate_wall_x(t_data *data)
{
	double	wall_x;

	if (data->raycast.side == 0)
		wall_x = data->raycast.pos_y + data->raycast.perpwalldist
			* data->raycast.raydir_y;
	else
		wall_x = data->raycast.pos_x + data->raycast.perpwalldist
			* data->raycast.raydir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	calculate_tex_x(t_data *data, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)64);
	if ((data->raycast.side == 0 && data->raycast.raydir_x > 0)
		|| (data->raycast.side == 1 && data->raycast.raydir_y < 0))
		tex_x = 64 - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_pixels(t_data *data, int x, int y_start, int y_end)
{
	int	y;
	int	tex_y;
	int	tex_x;
	int	d;
	int	color;

	tex_x = calculate_tex_x(data, calculate_wall_x(data));
	y = y_start;
	while (y <= y_end)
	{
		d = y * 256 - SCREEN_HEIGHT * 128 + data->raycast.lineheight * 128;
		tex_y = ((d * 64) / data->raycast.lineheight) / 256;
		color = *(int *)(data->which_tex + (tex_y * data->current_line_length
					+ tex_x * (data->current_bpp / 8)));
		*(int *)(data->scene.addr + (y * data->scene.size_line
					+ x * (data->scene.bpp / 8))) = color;
		y++;
	}
}

void	draw_vertical_line(t_data *data, int x, int color)
{
	int	y_start;
	int	y_end;

	(void)color;
	y_start = data->raycast.drawstart;
	y_end = data->raycast.drawend;
	if (y_start < 0)
		y_start = 0;
	if (y_end >= SCREEN_HEIGHT)
		y_end = SCREEN_HEIGHT - 1;
	init_texture_data(data);
	draw_wall_pixels(data, x, y_start, y_end);
}
