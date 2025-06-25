/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:31:44 by ctravers          #+#    #+#             */
/*   Updated: 2025/06/25 14:32:40 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	move_for_back(t_data *data, char pressed)
{
	double	new_x;
	double	new_y;

	if (pressed == 'w')
	{
		new_x = data->raycast.pos_x + data->raycast.dir_x * data->move_speed;
		new_y = data->raycast.pos_y + data->raycast.dir_y * data->move_speed;
		if (!check_collision(data, new_x, data->raycast.pos_y))
			data->raycast.pos_x = new_x;
		if (!check_collision(data, data->raycast.pos_x, new_y))
			data->raycast.pos_y = new_y;
	}
	if (pressed == 's')
	{
		new_x = data->raycast.pos_x - data->raycast.dir_x * data->move_speed;
		new_y = data->raycast.pos_y - data->raycast.dir_y * data->move_speed;
		if (!check_collision(data, new_x, data->raycast.pos_y))
			data->raycast.pos_x = new_x;
		if (!check_collision(data, data->raycast.pos_x, new_y))
			data->raycast.pos_y = new_y;
	}
}

static void	move_left_right(t_data *data, char pressed)
{
	double	new_x;
	double	new_y;

	if (pressed == 'a')
	{
		new_x = data->raycast.pos_x - data->raycast.dir_y * data->move_speed;
		new_y = data->raycast.pos_y + data->raycast.dir_x * data->move_speed;
		if (!check_collision(data, new_x, data->raycast.pos_y))
			data->raycast.pos_x = new_x;
		if (!check_collision(data, data->raycast.pos_x, new_y))
			data->raycast.pos_y = new_y;
	}
	if (pressed == 'd')
	{
		new_x = data->raycast.pos_x + data->raycast.dir_y * data->move_speed;
		new_y = data->raycast.pos_y - data->raycast.dir_x * data->move_speed;
		if (!check_collision(data, new_x, data->raycast.pos_y))
			data->raycast.pos_x = new_x;
		if (!check_collision(data, data->raycast.pos_x, new_y))
			data->raycast.pos_y = new_y;
	}
}

static void	look_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->raycast.dir_x;
	old_plane_x = data->raycast.plane_x;
	data->raycast.dir_x = old_dir_x * cos(-data->rot_speed)
		- data->raycast.dir_y * sin(-data->rot_speed);
	data->raycast.dir_y = old_dir_x * sin(-data->rot_speed)
		+ data->raycast.dir_y * cos(-data->rot_speed);
	data->raycast.plane_x = old_plane_x * cos(-data->rot_speed)
		- data->raycast.plane_y * sin(-data->rot_speed);
	data->raycast.plane_y = old_plane_x * sin(-data->rot_speed)
		+ data->raycast.plane_y * cos(-data->rot_speed);
}

static void	look_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->raycast.dir_x;
	old_plane_x = data->raycast.plane_x;
	data->raycast.dir_x = old_dir_x * cos(data->rot_speed)
		- data->raycast.dir_y * sin(data->rot_speed);
	data->raycast.dir_y = old_dir_x * sin(data->rot_speed)
		+ data->raycast.dir_y * cos(data->rot_speed);
	data->raycast.plane_x = old_plane_x * cos(data->rot_speed)
		- data->raycast.plane_y * sin(data->rot_speed);
	data->raycast.plane_y = old_plane_x * sin(data->rot_speed)
		+ data->raycast.plane_y * cos(data->rot_speed);
}

void	handle_movement(t_data *data)
{
	if (data->keys.d_pressed)
		move_left_right(data, 'd');
	if (data->keys.a_pressed)
		move_left_right(data, 'a');
	if (data->keys.s_pressed)
		move_for_back(data, 's');
	if (data->keys.w_pressed)
		move_for_back(data, 'w');
	if (data->keys.right_pressed)
		look_right(data);
	if (data->keys.left_pressed)
		look_left(data);
}
