/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:22:32 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/18 13:30:36 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init(t_game *game)
{
	game->texture[0].img.img = NULL;
	game->texture[1].img.img = NULL;
	game->texture[2].img.img = NULL;
	game->texture[3].img.img = NULL;
	game->win = NULL;
	game->img.img = NULL;
	game->mlx = NULL;
	game->press_w = 2;
	game->press_a = 2;
	game->press_s = 2;
	game->press_d = 2;
	game->press_left = 2;
	game->press_right = 2;
	game->press_maj = 2;
}

void	init_player_orientation(t_game *game, int i, int j)
{
	game->player_pos.x = j * SIZE + (SIZE / 2);
	game->player_pos.y = i * SIZE + (SIZE / 2);
	if (game->tab[i][j] == 'N')
		game->pa = P2;
	if (game->tab[i][j] == 'E')
		game->pa = PI;
	if (game->tab[i][j] == 'W')
		game->pa = 0;
	if (game->tab[i][j] == 'S')
		game->pa = P3;
}

void	init_player(t_game *game, int i, int j)
{
	game->pa = -1;
	while (game->tab[i])
	{
		while (game->tab[i][j])
		{
			if (game->tab[i][j] == 'N' || game->tab[i][j] == 'E'
				|| game->tab[i][j] == 'W' || game->tab[i][j] == 'S')
			{
				init_player_orientation(game, i, j);
				break ;
			}
			j++;
		}
		if (game->pa != -1)
			break ;
		j = 0;
		i++;
	}
	game->pd.x = cos(game->pa) * 5;
	game->pd.y = sin(game->pa) * 5;
}

void	init_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->tab[i])
	{
		while (game->tab[i][j])
			j++;
		game->map.length = j;
		j = 0;
		i++;
	}
	game->map.height = i;
	game->map.size = game->map.length * game->map.height;
	if (game->map.height * (SIZE / 20) >= W_HEIGHT || game->map.length * (SIZE
			/ 20) >= W_WIDTH)
		cleaner(game, MAP_ERROR);
}

void	init_color(t_game *game)
{
	game->color_ceil = convert_hexa_color(game->info_map->ceil_color[0],
			game->info_map->ceil_color[1], game->info_map->ceil_color[2]);
	game->color_floor = convert_hexa_color(game->info_map->floor_color[0],
			game->info_map->floor_color[1], game->info_map->floor_color[2]);
}
