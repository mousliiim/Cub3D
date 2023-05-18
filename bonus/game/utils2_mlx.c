/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:38:20 by alvina            #+#    #+#             */
/*   Updated: 2023/05/18 13:41:54 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	release_key(int key_symbole, t_game *game)
{
	if (key_symbole == MAJ)
		game->press_maj = 2;
	if (key_symbole == W)
		game->press_w = 2;
	if (key_symbole == S)
		game->press_s = 2;
	if (key_symbole == D)
		game->press_d = 2;
	if (key_symbole == A)
		game->press_a = 2;
	if (key_symbole == LEFT)
		game->press_left = 2;
	if (key_symbole == RIGHT)
		game->press_right = 2;
	return (0);
}

int	press_key(int key_symbole, t_game *game)
{
	if (key_symbole == XK_Escape)
	{
		mlx_loop_end(game->mlx);
		cleaner(game, 0);
	}
	if (key_symbole == MAJ)
		game->press_maj = 1;
	if (key_symbole == W)
		game->press_w = 1;
	if (key_symbole == S)
		game->press_s = 1;
	if (key_symbole == D)
		game->press_d = 1;
	if (key_symbole == A)
		game->press_a = 1;
	if (key_symbole == LEFT)
		game->press_left = 1;
	if (key_symbole == RIGHT)
		game->press_right = 1;
	return (0);
}
