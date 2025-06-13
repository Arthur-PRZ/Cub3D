/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:31:00 by artperez          #+#    #+#             */
/*   Updated: 2025/06/13 14:05:59 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int    handle_input(int keysym, t_data *data)
{
	double old_dir_x;
	double old_plane_x;

    if (keysym == XK_Escape)
		exit_and_free(NULL, "", data, -1);
	if (keysym == 100)
	{
		data->raycast.pos_x += data->raycast.dir_y * data->move_speed;
		data->raycast.pos_y -= data->raycast.dir_x * data->move_speed;
	}
	if (keysym == 97)
	{
		data->raycast.pos_x -= data->raycast.dir_y * data->move_speed;
		data->raycast.pos_y += data->raycast.dir_x * data->move_speed;
	}
	if (keysym == 115)
	{
		data->raycast.pos_x -= data->raycast.dir_x * data->move_speed;
		data->raycast.pos_y -= data->raycast.dir_y * data->move_speed;
	}
	if (keysym == 119)
	{
		data->raycast.pos_x += data->raycast.dir_x * data->move_speed;
		data->raycast.pos_y += data->raycast.dir_y * data->move_speed;
	}
    if (keysym == XK_Left)
    {
        old_dir_x = data->raycast.dir_x;
        old_plane_x = data->raycast.plane_x;
        data->raycast.dir_x = data->raycast.dir_x * cos(data->rot_speed) - data->raycast.dir_y * sin(data->rot_speed);
        data->raycast.dir_y = old_dir_x * sin(data->rot_speed) + data->raycast.dir_y * cos(data->rot_speed);
        data->raycast.plane_x = data->raycast.plane_x * cos(data->rot_speed) - data->raycast.plane_y * sin(data->rot_speed);
        data->raycast.plane_y = old_plane_x * sin(data->rot_speed) + data->raycast.plane_y * cos(data->rot_speed);
    }
	return (0);
}

static int	exit_cross(t_data *data)
{
	exit_and_free(NULL, "", data, -1);
	return (0);
}

void movements(t_data *data)
{
    mlx_key_hook(data->win, handle_input, data);
    mlx_hook(data->win, 17, 0, exit_cross, data);
}