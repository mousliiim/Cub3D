/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:24:04 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/14 16:06:17 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_ray_minimap(t_game *game, t_raycast *rc)
{
	t_moh2f	curr;
	t_moh2f	next;

	curr.x = game->player_pos.x / 20;
	curr.y = game->player_pos.y / 20;
	next.x = rc->draw.next.x / 20;
	next.y = rc->draw.next.y / 20;
	bresenham(game->img, curr, next, 0x0000FF00);
}

void	draw_cube(t_game *game, t_moh2f pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++j < size)
	{
		while (i < size)
		{
			if (i && j)
				img_pixel_put((&game->img), pos.x + j - 1, pos.y + i - 1,
					color);
			else
				img_pixel_put((&game->img), pos.x + j, pos.y + i, color);
			i++;
		}
		i = 0;
	}
}

void	draw_player(t_game *game)
{
	t_moh2f	pos;

	pos.x = game->player_pos.x / 20;
	pos.y = game->player_pos.y / 20;
	draw_cube(game, pos, 2, 0x00FFFF00);
}

void	draw_wall(t_game *game)
{
	int		x;
	int		y;
	t_moh2f	o;
	int		color;

	x = 0;
	y = 0;
	while (y < game->map.height)
	{
		while (x < game->map.length)
		{
			if (game->tab[y][x] == '1')
				color = 0x00FFFFFF;
			else if (game->tab[y][x] == 'X')
				color = game->color_ceil;
			else
				color = 0x00000000;
			o.x = x * (SIZE / 20);
			o.y = y * (SIZE / 20);
			draw_cube(game, o, SIZE / 20, color);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_pov(t_game *game)
{
	t_moh2f	next;
	t_moh2f	curr;

	next.x = game->player_pos.x / 20 - game->pd.x;
	next.y = game->player_pos.y / 20 - game->pd.y;
	curr.x = game->player_pos.x / 20;
	curr.y = game->player_pos.y / 20;
	bresenham(game->img, curr, next, 0X00FFFF00);
}
