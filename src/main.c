/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctravers <ctravers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:02 by artperez          #+#    #+#             */
/*   Updated: 2025/06/06 12:47:07 by ctravers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int main(int argc, char **argv)
{
	t_data	data;
	
    check_input(argc, argv[1]);
	init_map_data(argv[1], &data);
	init_data(&data);
}