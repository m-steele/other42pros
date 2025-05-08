/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:40:54 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/08 11:34:21 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

int	main(int ac,char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("%s\n%s maps/map.ber\n", LOAD_ERROR, av[0]));
	
}
