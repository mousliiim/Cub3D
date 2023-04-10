/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:34:49 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/10 20:05:14 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// static int	check_map_border(t_game *game, t_info_map *info)
// {
// 	(void)game;
// 	(void)info;
// 	return (SUCCESS);
// }

static int	check_map_content(t_game *game, size_t y, size_t x, size_t pos)
{
	static char	tab[4] = {NORTH, SOUTH, EAST, WEST};

	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (ft_strchr(tab, game->map[y][x]))
			{
				if (!pos)
				{
					pos = 1;
					game->player_dir = game->map[y][x];
				}
				else
					return (FAILURE);
			}
			if (!ft_strchr(" 01NSEW\n", game->map[y][x]))
				return (FAILURE);
		}
	}
	if (!pos)
		return (FAILURE);
	return (SUCCESS);
}

static int	size_of_map(t_game *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	if (!game->map || !*game->map)
		return (FAILURE);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x] && game->map[y][x] != '\n')
			x++;
		y++;
	}
	if (x < 3 || y < 3)
		return (FAILURE);
	game->map_size[HEIGHT] = y;
	game->map_size[WIDTH] = x;
	return (SUCCESS);
}

int	check_map(t_game *game, t_info_map *info)
{
	if (!size_of_map(game))
		return (info->error = MAP_ERROR, FAILURE);
	if (!check_map_content(game, -1, -1, 0))
		return (info->error = MAP_ERROR, FAILURE);
	// if (!check_map_border(game, info)) // A FAIRE
	// 	return (FAILURE);
	return (SUCCESS);
}

int	get_map(const char *map_name, t_game *game, t_info_map *info)
{
	// display(info->map_info); // AFFICHAGE INFO A SUPPRIMER
	ft_free_double_array(info->map_info);
	if (!ft_read_map(map_name, game, info))
		return (FAILURE);
	if (!check_map(game, info))
		return (FAILURE);
	display(game->map); // AFFICHAGE MAP A SUPPRIMER
	return (SUCCESS);
}

	// A FREE POUR LE PARSING DE LA MAP
	// ft_free_double_array(info->texture); // free texture
	// 	ft_free_double_array(game->map); // free map
	// 	free(game->map); // free map
	// 	get_next_line(-1, 1); // free get