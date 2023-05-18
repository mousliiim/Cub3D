/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:08:03 by mmourdal          #+#    #+#             */
/*   Updated: 2023/05/18 15:49:01 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	exec_move(t_game *game, int c)
{
	int	speed;

	speed = 2;
	if (c == W && game->press_maj == 1)
		speed = 4;
	game->next_pos = game->player_pos;
	setting_next_pos(c, game, speed);
	seeing_in_the_futur_bro(c, game, speed + 3);
	if (!is_wall(game, game->next_next_pos))
		game->player_pos = game->next_pos;
}

static int	move(t_game *game)
{
	if (game->press_w == 1)
		exec_move(game, W);
	if (game->press_s == 1)
		exec_move(game, S);
	if (game->press_a == 1)
		exec_move(game, A);
	if (game->press_d == 1)
		exec_move(game, D);
	if (game->press_left == 1)
	{
		game->pa -= 0.05;
		if (game->pa < 0)
			game->pa += (2 * PI);
		game->pd.x = (cos(game->pa)) * 5;
		game->pd.y = (sin(game->pa)) * 5;
	}
	if (game->press_right == 1)
	{
		game->pa += 0.05;
		if (game->pa >= (2 * PI))
			game->pa -= 2 * PI;
		game->pd.x = cos(game->pa) * 5;
		game->pd.y = sin(game->pa) * 5;
	}
	return (display_(game), 0);
}

int	display_(t_game *game)
{
	grey_screen(game);
	raycasting(game);
	draw_wall(game);
	draw_player(game);
	draw_pov(game);
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
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &release_key, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &press_key, game);
	mlx_hook(game->win, 17, (1L << 17), &close_x, game);
	mlx_loop_hook(game->mlx, move, game);
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
