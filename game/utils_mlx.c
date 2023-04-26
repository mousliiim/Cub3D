/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:03:50 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/25 14:19:59 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	close_x(t_game *game)
{
	fprintf(stderr, "FIN DU JEUX AVEC LA CROIX\n");
	mlx_loop_end(game->mlx);
	exit (0);
	return (1);
}
