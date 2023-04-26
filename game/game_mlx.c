/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:08:03 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/26 19:38:37 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	deal_key(int key_symbole, t_game *game)
{
	if (key_symbole == XK_Escape)
	{
		mlx_loop_end(game->mlx);
		exit(0);
	}
	if (key_symbole == W)
		printf("W\n");
	if (key_symbole == S)
		printf("S\n");
	if (key_symbole == A)
		printf("A\n");
	if (key_symbole == D)
		printf("D\n");
	if (key_symbole == LEFT)
		printf("GAUCHE\n");
	if (key_symbole == RIGHT)
		printf("DROITE\n");
	return (0);
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (FAILURE);
	game->win = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "Cub3D");
	if (!game->win)
		return (free(game->mlx), FAILURE);
	game->planeX = 0;
	game->planeY = 0.66;
	mlx_hook(game->win, KeyPress, KeyPressMask, &deal_key, &game);
	mlx_hook(game->win, 17, (1L << 17), &close_x, &game);
	mlx_loop(game->mlx);
	return (SUCCESS);
}
