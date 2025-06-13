/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:31:00 by artperez          #+#    #+#             */
/*   Updated: 2025/06/13 15:14:15 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int    handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        exit_and_free(NULL, "", data, -1);
    if (keysym == 100) // D
        data->keys.d_pressed = true;
    if (keysym == 97)  // A
        data->keys.a_pressed = true;
    if (keysym == 115) // S
        data->keys.s_pressed = true;
    if (keysym == 119) // W
        data->keys.w_pressed = true;
    if (keysym == XK_Left)
        data->keys.left_pressed = true;
    if (keysym == XK_Right)
        data->keys.right_pressed = true;
    return (0);
}

static int    handle_keyrelease(int keysym, t_data *data)
{
    if (keysym == 100)
        data->keys.d_pressed = false;
    if (keysym == 97)
        data->keys.a_pressed = false;
    if (keysym == 115)
        data->keys.s_pressed = false;
    if (keysym == 119)
        data->keys.w_pressed = false;
    if (keysym == XK_Left)
        data->keys.left_pressed = false;
    if (keysym == XK_Right)
        data->keys.right_pressed = false;
    return (0);
}

void handle_movement(t_data *data)
{
    double	old_dir_x;
	double	old_plane_x;
    
    if (data->keys.d_pressed)
    {
        data->raycast.pos_x += data->raycast.dir_y * data->move_speed;
        data->raycast.pos_y -= data->raycast.dir_x * data->move_speed;
    }
    if (data->keys.a_pressed)
    {
        data->raycast.pos_x -= data->raycast.dir_y * data->move_speed;
        data->raycast.pos_y += data->raycast.dir_x * data->move_speed;
    }
    if (data->keys.s_pressed)
    {
        data->raycast.pos_x -= data->raycast.dir_x * data->move_speed;
        data->raycast.pos_y -= data->raycast.dir_y * data->move_speed;
    }
    if (data->keys.w_pressed)
    {
        data->raycast.pos_x += data->raycast.dir_x * data->move_speed;
        data->raycast.pos_y += data->raycast.dir_y * data->move_speed;
    }
    if (data->keys.right_pressed)
    {
        old_dir_x = data->raycast.dir_x;
        old_plane_x = data->raycast.plane_x;
        data->raycast.dir_x = old_dir_x * cos(-data->rot_speed) - data->raycast.dir_y * sin(-data->rot_speed);
        data->raycast.dir_y = old_dir_x * sin(-data->rot_speed) + data->raycast.dir_y * cos(-data->rot_speed);
        data->raycast.plane_x = old_plane_x * cos(-data->rot_speed) - data->raycast.plane_y * sin(-data->rot_speed);
        data->raycast.plane_y = old_plane_x * sin(-data->rot_speed) + data->raycast.plane_y * cos(-data->rot_speed);
    }
    if (data->keys.left_pressed)
    {
        old_dir_x = data->raycast.dir_x;
        old_plane_x = data->raycast.plane_x;
        data->raycast.dir_x = old_dir_x * cos(data->rot_speed) - data->raycast.dir_y * sin(data->rot_speed);
        data->raycast.dir_y = old_dir_x * sin(data->rot_speed) + data->raycast.dir_y * cos(data->rot_speed);
        data->raycast.plane_x = old_plane_x * cos(data->rot_speed) - data->raycast.plane_y * sin(data->rot_speed);
        data->raycast.plane_y = old_plane_x * sin(data->rot_speed) + data->raycast.plane_y * cos(data->rot_speed);
    }
}

static int	exit_cross(t_data *data)
{
	exit_and_free(NULL, "", data, -1);
	return (0);
}

void movements(t_data *data)
{
    data->keys.w_pressed = false;
    data->keys.a_pressed = false;
    data->keys.s_pressed = false;
    data->keys.d_pressed = false;
    data->keys.left_pressed = false;
    data->keys.right_pressed = false;
	mlx_hook(data->win, 2, 1L<<0, handle_keypress, data);
	mlx_hook(data->win, 3, 1L<<1, handle_keyrelease, data);
    mlx_hook(data->win, 17, 0, exit_cross, data);
}