/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:03:44 by artperez          #+#    #+#             */
/*   Updated: 2025/06/25 14:15:34 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	get_current_bpp(t_data *data)
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

char	*which_texture(t_data *data)
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

int	get_current_ll(t_data *data)
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
