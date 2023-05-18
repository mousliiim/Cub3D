/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:08:03 by mmourdal          #+#    #+#             */
/*   Updated: 2023/05/18 11:59:29 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	deplacement_key(int key_symbole, t_game *game)
{
	game->next_pos = game->player_pos;
	if (key_symbole == W)
	{
		setting_next_pos(key_symbole, game, 5);
		seeing_in_the_futur_bro(key_symbole, game, 5);
	}
	if (key_symbole == S)
	{
		setting_next_pos(key_symbole, game, 5);
		seeing_in_the_futur_bro(key_symbole, game, 5);
	}
	if (key_symbole == A)
	{
		setting_next_pos(key_symbole, game, 5);
		seeing_in_the_futur_bro(key_symbole, game, 5);
	}
	if (key_symbole == D)
	{
		setting_next_pos(key_symbole, game, 5);
		seeing_in_the_futur_bro(key_symbole, game, 5);
	}
	if (!is_wall(game, game->next_next_pos))
		game->player_pos = game->next_pos;
}

int	deal_key(int key_symbole, t_game *game)
{
	if (key_symbole == XK_Escape)
	{
		mlx_loop_end(game->mlx);
		cleaner(game, 0);
	}
	if (key_symbole == W || key_symbole == A || key_symbole == S
		|| key_symbole == D)
		deplacement_key(key_symbole, game);
	if (key_symbole == LEFT)
	{
		game->pa -= 0.1;
		if (game->pa < 0)
			game->pa += (2 * PI);
		game->pd.x = (cos(game->pa)) * 5;
		game->pd.y = (sin(game->pa)) * 5;
	}
	if (key_symbole == RIGHT)
	{
		game->pa += 0.1;
		if (game->pa >= (2 * PI))
			game->pa -= 2 * PI;
		game->pd.x = cos(game->pa) * 5;
		game->pd.y = sin(game->pa) * 5;
	}
	return (0);
}

int	display_(t_game *game)
{
	grey_screen(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		cleaner(game, 3);
	init_texture(game);
	game->win = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "Cub3D");
	if (!game->win)
		cleaner(game, 3);
	game->img.img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!game->img.img)
		cleaner(game, 3);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&(game->img.bits_per_pixel), &(game->img.line_length),
			&(game->img.endian));
	mlx_loop_hook(game->mlx, display_, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &deal_key, game);
	mlx_hook(game->win, 17, (1L << 17), &close_x, game);
	mlx_loop(game->mlx);
}

int	blood_link(t_game *game)
{
	init(game);
	modify(game, 0, 1);
	init_player(game, 0, 0);
	init_map(game);
	init_color(game);
	mlx(game);
	return (SUCCESS);
}
