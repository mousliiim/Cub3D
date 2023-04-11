/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:34:49 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/11 20:10:21 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_x_y(t_game *game, size_t y, size_t x)
{
	size_t		count;

	count = 0;
	if (game->map[y][x + 1] && (game->map[y][x + 1] == '1' || game->map[y][x + 1] == '0' || game->map[y][x + 1] == game->player_dir))
		count++;
	if (game->map[y][x - 1] && (game->map[y][x - 1] == '1' || game->map[y][x - 1] == '0' || game->map[y][x - 1] == game->player_dir))
		count++;
	if (game->map[y + 1] && (game->map[y + 1][x] == '1' || game->map[y + 1][x] == '0' || game->map[y + 1][x] == game->player_dir))
		count++;
	if (game->map[y - 1] && (game->map[y - 1][x] == '1' || game->map[y - 1][x] == '0' || game->map[y - 1][x] == game->player_dir))
		count++;
	if (count < 4)
		return (FAILURE);
	return (SUCCESS);
}

// static int	check_map_border(t_game *game, t_info_map *info)
// {
// 	size_t	y;
// 	size_t	x;

// 	y = -1;
// 	while (game->map[++y])
// 	{
// 		x = -1;
// 		while (game->map[y][++x])
// 		{
// 			if (game->map[y][x] == '0' || game->map[y][x] == 'N')
// 			{
// 				if (!check_x_y(game, y, x))
// 					return (info->error = MAP_ERROR, FAILURE);
// 			}
// 		}
// 	}
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
	size_t	big_x;

	x = 0;
	y = 0;
	big_x = 0;
	if (!game->map || !*game->map)
		return (FAILURE);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x] && game->map[y][x] != '\n')
			x++;
		if (x > big_x)
			big_x = x;
		y++;
	}
	if (big_x < 3 || y < 3)
		return (FAILURE);
	game->map_size[HEIGHT] = y;
	game->map_size[WIDTH] = big_x;
	return (SUCCESS);
}

int	set_line(t_game *game, t_info_map *info, char **line, int y)
{
	size_t	i;
	char	c;

	i = -1;
	*line = ft_strjoin(NULL, "X");
	if (*line == NULL)
		return (info->error = MAP_ERROR, FAILURE);
	while (game->map[y][++i])
	{
		c = game->map[y][i + 1];
		game->map[y][i + 1] = '\0';
		*line = ft_strjoin(*line, &game->map[y][i]);
		game->map[y][i + 1] = c;
		if (c == '\n')
			break ;
		if (*line == NULL)
			return (info->error = MAP_ERROR, FAILURE);
	}
	printf("Line value : %ld Size: value : %zu\n", ft_strlen(*line), game->map_size[WIDTH]);
	while (++i < game->map_size[WIDTH])
		*line = ft_strjoin(*line, "X");
	*line = ft_strjoin(*line, "X");
	return (SUCCESS);
}

int	set_limiter(t_info_map *info, char **line, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
	{
		*line = ft_strjoin(*line, "X");
		if (*line == NULL)
			return (info->error = MAP_ERROR, FAILURE);
	}
	return (SUCCESS);
}

int	map_to_square(t_game *game, t_info_map *info)
{
	size_t	y;
	char	**new_map;

	new_map = ft_calloc(game->map_size[HEIGHT] + 3, sizeof(char *));
	if (!new_map)
		return (FAILURE);
	y = 0;
	while (y < (game->map_size[HEIGHT] + 2))
	{
		if (y == 0)
			set_limiter(info, &new_map[y], game->map_size[WIDTH] + 2);
		else if ((y > 0 && y < game->map_size[HEIGHT] + 1))
		{
			if (!set_line(game, info, &new_map[y], y - 1))
				return (info->error = MAP_ERROR, FAILURE);
		}
		else if (y == game->map_size[HEIGHT] + 1)
			set_limiter(info, &new_map[y], game->map_size[WIDTH] + 2);
		y++;
	}
	new_map[game->map_size[HEIGHT] + 2] = NULL;
	for (size_t i = 0; new_map[i]; i++)
		printf("%s\n", new_map[i]);
	printf("\n");
	return (SUCCESS);
}

int	check_map(t_game *game, t_info_map *info)
{
	if (!size_of_map(game))
		return (info->error = MAP_ERROR, FAILURE);
	if (!check_map_content(game, -1, -1, 0))
		return (info->error = MAP_ERROR, FAILURE);
	if (!map_to_square(game, info))
		return (info->error = MALLOC_ERROR, FAILURE);
	// if (!check_map_border(game, info)) // A FAIRE
	// 	return (FAILURE);
	return (SUCCESS);
}

int	get_map(const char *map_name, t_game *game, t_info_map *info)
{
	display(info->map_info);
	ft_free_double_array(info->map_info);
	if (!ft_read_map(map_name, game, info))
		return (FAILURE);
	if (!check_map(game, info))
		return (FAILURE);
	display(game->map); // AFFICHAGE MAP A SUPPRIMER
		ft_free_double_array(info->texture); // free texture
		ft_free_double_array(game->map); // free map
		free(game->map); // free map
		get_next_line(-1, 1); // free get
	return (SUCCESS);
}

	// A FREE POUR LE PARSING DE LA MAP
	// ft_free_double_array(info->texture); // free texture
	// 	ft_free_double_array(game->map); // free map
	// 	free(game->map); // free map
	// 	get_next_line(-1, 1); // free get