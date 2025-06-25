/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:31:00 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 14:42:44 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		exit_and_free(NULL, "", data, -1);
	if (keysym == 100)
		data->keys.d_pressed = true;
	if (keysym == 97)
		data->keys.a_pressed = true;
	if (keysym == 115)
		data->keys.s_pressed = true;
	if (keysym == 119)
		data->keys.w_pressed = true;
	if (keysym == XK_Left)
		data->keys.left_pressed = true;
	if (keysym == XK_Right)
		data->keys.right_pressed = true;
	return (0);
}

static int	handle_keyrelease(int keysym, t_data *data)
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

static int	is_valid_position(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (data->map_data.map.grid[map_y][map_x] == '1')
		return (0);
	return (1);
}

int	check_collision(t_data *data, double new_x, double new_y)
{
	double	margin;

	margin = 0.1;
	if (!is_valid_position(data, new_x - margin, new_y - margin)
		|| !is_valid_position(data, new_x + margin, new_y - margin)
		|| !is_valid_position(data, new_x - margin, new_y + margin)
		|| !is_valid_position(data, new_x + margin, new_y + margin))
		return (1);
	return (0);
}

void	movements(t_data *data)
{
	data->keys.w_pressed = false;
	data->keys.a_pressed = false;
	data->keys.s_pressed = false;
	data->keys.d_pressed = false;
	data->keys.left_pressed = false;
	data->keys.right_pressed = false;
	mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->win, 17, 0, exit_cross, data);
}
