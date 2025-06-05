/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:02 by artperez          #+#    #+#             */
/*   Updated: 2025/06/05 09:29:08 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int main(int argc, char **argv)
{
	t_map_data map;
	
    check_input(argc, argv[1]);
	init_map_data(argv[1], &map);
}