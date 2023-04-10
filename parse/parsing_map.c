/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:34:49 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/10 02:11:22 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	take_value_texture(char **array, t_info_map *info_parse)
{
	char	*path;
	size_t	i;
	size_t	j;

	if (!array || !*array)
		return (FAILURE);
	if (check_key(array[0]) == 4 || check_key(array[0]) == 5)
		return (rgb_color_check(array[1], info_parse, check_key(array[0])));
	path = NULL;
	i = 0;
	while (array[++i])
	{
		path = ft_strjoin(path, array[i]);
		if (!path)
			return (FAILURE);
		j = -1;
		while (path[++j])
		{
			if (path[j] == '\v' || path[j] == '\f'
				|| path[j] == '\r')
				return (free(path), FAILURE);
		}
	}
	info_parse->texture[check_key(array[0])] = path;
	return (SUCCESS);
}

int	cut_key_value(t_info_map *info_parse)
{
	static int	tab_check[6] = {NO, SO, WE, EA, F, C};
	char		**array;
	size_t		i;
	int			j;

	i = -1;
	while (info_parse->map_info[++i])
	{
		array = ft_split(info_parse->map_info[i], ' ', &j);
		if (!array)
			return (FAILURE);
		if (j != 2)
			return (ft_free_texture(info_parse->texture), ft_free_split(array),
				info_parse->type_error = MAP_ERROR, FAILURE);
		if (check_key(array[0]) != -1)
		{
			if (tab_check[check_key(array[0])] == 1)
				return (ft_free_texture(info_parse->texture), ft_free_split(array),
					info_parse->type_error = MAP_ERROR, FAILURE);
			else if (tab_check[check_key(array[0])] == 0)
				tab_check[check_key(array[0])] = 1;
		}
		if (!take_value_texture(array, info_parse))
			return (ft_free_texture(info_parse->texture), ft_free_split(array),
				info_parse->type_error = MAP_ERROR, FAILURE);
		ft_free_split(array);
	}
	if (!check_tab_value(tab_check))
		return (info_parse->type_error = MAP_ERROR, FAILURE);
	info_parse->texture[4] = NULL;
	return (SUCCESS);
}

int	size_of_map(t_game *game)
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
	game->map_size[HEIGHT] = x;
	game->map_size[WIDTH] = y;
	return (SUCCESS);
}

int	check_map(t_game *game, t_info_map *info_parse)
{
	if (!size_of_map(game))
		return (info_parse->type_error = MAP_ERROR, FAILURE);
	// if (!check_map_char(game)) // A FAIRE POUR LA MAP
	// 	return (FAILURE);
	return (SUCCESS);
}

int	key_and_value_check(t_info_map *info_parse)
{
	if (!cut_key_value(info_parse))
		return (FAILURE);
	return (SUCCESS);
}

int	get_info_map(const char *map_name, t_info_map *info_parse)
{
	if (!ft_read_map_info(map_name, info_parse))
		return (ft_free_double_array(info_parse->map_info), FAILURE);
	if (!key_and_value_check(info_parse))
		return (ft_free_double_array(info_parse->map_info), FAILURE);
	return (SUCCESS);
}

int	get_map(const char *map_name, t_game *game, t_info_map *info_parse)
{
	// display(info_parse->map_info); // AFFICHAGE INFO A SUPPRIMER
	ft_free_double_array(info_parse->map_info);
	if (!ft_read_map(map_name, game, info_parse))
		return (FAILURE);
	if (!check_map(game, info_parse))
		return (FAILURE);
	display(game->map); // AFFICHAGE MAP A SUPPRIMER
	return (SUCCESS);
}

	// A FREE POUR LE PARSING DE LA MAP
	// ft_free_double_array(info_parse->texture); // free texture
	// 	ft_free_double_array(game->map); // free map
	// 	free(game->map); // free map
	// 	get_next_line(-1, 1); // free get