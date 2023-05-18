/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:34:49 by mmourdal          #+#    #+#             */
/*   Updated: 2023/05/15 19:19:04 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	check_map_border(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->tab[++y])
	{
		x = -1;
		while (game->tab[y][++x])
		{
			if (game->tab[y][x] == '0' || game->tab[y][x] == game->player_dir)
			{
				if (!check_x_y(game, y, x))
					return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

static int	check_map_content(t_game *game, int y, int x, int pos)
{
	static char	tab[4] = {NORTH, SOUTH, EAST, WEST};

	while (game->tab[++y])
	{
		x = -1;
		while (game->tab[y][++x])
		{
			if (ft_strchr(tab, game->tab[y][x]))
			{
				if (!pos)
				{
					pos = 1;
					set_player_pos(game, y, x);
				}
				else
					return (FAILURE);
			}
			if (!ft_strchr(" 01NSEW\n", game->tab[y][x]))
				return (FAILURE);
		}
	}
	if (!pos)
		return (FAILURE);
	return (SUCCESS);
}

int	map_to_square(t_game *game)
{
	int		y;
	char	**new_map;

	new_map = ft_calloc(game->map_size[HEIGHT] + 3, sizeof(char *));
	if (!new_map)
		return (FAILURE);
	y = -1;
	while (++y < (game->map_size[HEIGHT] + 2))
	{
		if (y == 0)
		{
			if (!set_limiter(&new_map[y], game->map_size[WIDTH] + 2))
				return (free(new_map), FAILURE);
		}
		else if ((y > 0 && y < game->map_size[HEIGHT] + 1))
		{
			if (!set_line(game, &new_map[y], y - 1))
				return (ft_free(new_map, 1), FAILURE);
		}
		else if (y == game->map_size[HEIGHT] + 1)
			if (!set_limiter(&new_map[y], game->map_size[WIDTH] + 2))
				return (FAILURE);
	}
	new_map[game->map_size[HEIGHT] + 2] = NULL;
	return (ft_free(game->tab, 1), game->tab = new_map, SUCCESS);
}

int	check_map(t_game *game, t_info_map *info)
{
	if (!size_of_map(game))
		return (ft_free(info->map_info, 0), info->error = MAP_ERROR, FAILURE);
	if (!check_map_content(game, -1, -1, 0))
		return (ft_free(info->map_info, 0), info->error = MAP_ERROR, FAILURE);
	if (!map_to_square(game))
		return (info->error = MALLOC_ERROR, FAILURE);
	if (!check_map_border(game))
		return (ft_free(info->map_info, 0), info->error = MAP_ERROR, FAILURE);
	return (SUCCESS);
}

int	get_map(const char *map_name, t_game *game, t_info_map *info)
{
	if (!ft_read_map(map_name, game, info))
		return (FAILURE);
	if (!check_map(game, info))
		return (FAILURE);
	return (SUCCESS);
}
