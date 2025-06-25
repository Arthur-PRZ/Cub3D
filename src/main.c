/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:02 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 14:44:30 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	game_loop(t_data *data)
{
	double	current_time;
	double	frame_time;

	current_time = get_time();
	if (data->old_time == 0)
	{
		data->old_time = current_time;
		return (0);
	}
	frame_time = current_time - data->old_time;
	data->old_time = current_time;
	data->move_speed = frame_time * 2.0;
	data->rot_speed = frame_time * 2.5;
	handle_movement(data);
	raycast(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_input(argc, argv[1]);
	init_map_data(argv[1], &data);
	init_data(&data);
	movements(&data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
}
