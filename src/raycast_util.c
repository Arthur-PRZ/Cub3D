/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:17:12 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 14:18:25 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	find_delta_dist(t_data *data)
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

void	find_step_and_sidedist(t_data *data)
{
	if (data->raycast.raydir_x < 0)
	{
		data->raycast.step_x = -1;
		data->raycast.sidedist_x = (data->raycast.pos_x
				- data->raycast.map_x) * data->raycast.deltadist_x;
	}
	else
	{
		data->raycast.step_x = 1;
		data->raycast.sidedist_x = (data->raycast.map_x
				+ 1.0 - data->raycast.pos_x) * data->raycast.deltadist_x;
	}
	if (data->raycast.raydir_y < 0)
	{
		data->raycast.step_y = -1;
		data->raycast.sidedist_y = (data->raycast.pos_y
				- data->raycast.map_y) * data->raycast.deltadist_y;
	}
	else
	{
		data->raycast.step_y = 1;
		data->raycast.sidedist_y = (data->raycast.map_y
				+ 1.0 - data->raycast.pos_y) * data->raycast.deltadist_y;
	}
}

void	find_wall_dist(t_data *data)
{
	if (data->raycast.side == 0)
		data->raycast.perpwalldist = (data->raycast.sidedist_x
				- data->raycast.deltadist_x);
	else
		data->raycast.perpwalldist = (data->raycast.sidedist_y
				- data->raycast.deltadist_y);
}

void	find_draw_coords(t_data *data)
{
	data->raycast.lineheight = (int)(SCREEN_HEIGHT
			/ data->raycast.perpwalldist);
	data->raycast.drawstart = -data->raycast.lineheight / 2 + SCREEN_HEIGHT / 2;
	if (data->raycast.drawstart < 0)
		data->raycast.drawstart = 0;
	data->raycast.drawend = data->raycast.lineheight / 2 + SCREEN_HEIGHT / 2;
}

void	memcpy_column(t_data *data, int dst_x, int src_x)
{
	int		y;
	char	*dst;
	char	*src;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		src = data->scene.addr + (y * data->scene.size_line
				+ src_x * (data->scene.bpp / 8));
		dst = data->scene.addr + (y * data->scene.size_line
				+ dst_x * (data->scene.bpp / 8));
		*(int *)dst = *(int *)src;
		y++;
	}
}
