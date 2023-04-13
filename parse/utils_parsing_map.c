/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 00:34:42 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/13 02:54:08 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_x_y(t_game *game, size_t y, size_t x)
{
	size_t		count;

	count = 0;
	if (game->map[y][x + 1] && (game->map[y][x + 1] == '1'
		|| game->map[y][x + 1] == '0'
		|| game->map[y][x + 1] == game->player_dir))
		count++;
	if (game->map[y][x - 1] && (game->map[y][x - 1] == '1'
		|| game->map[y][x - 1] == '0'
		|| game->map[y][x - 1] == game->player_dir))
		count++;
	if (game->map[y + 1] && (game->map[y + 1][x] == '1'
		|| game->map[y + 1][x] == '0'
		|| game->map[y + 1][x] == game->player_dir))
		count++;
	if (game->map[y - 1] && (game->map[y - 1][x] == '1'
		|| game->map[y - 1][x] == '0'
		|| game->map[y - 1][x] == game->player_dir))
		count++;
	if (count < 4)
		return (FAILURE);
	return (SUCCESS);
}

void	set_player_pos(t_game *game, size_t y, size_t x)
{
	game->player_dir = game->map[y][x];
	game->player_pos_i.x = x;
	game->player_pos_i.y = y;
	game->player_pos_f.x = x + 0.5;
	game->player_pos_f.y = y + 0.5;
}

int	size_of_map(t_game *game)
{
	size_t	x;
	size_t	y;
	size_t	big_x;

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

int	set_line(t_game *game, char **line, int y)
{
	size_t	i;
	char	c;

	i = -1;
	*line = ft_strjoin(*line, "X");
	if (*line == NULL)
		return (FAILURE);
	while (game->map[y][++i])
	{
		c = game->map[y][i + 1];
		game->map[y][i + 1] = '\0';
		*line = ft_strjoin(*line, &game->map[y][i]);
		game->map[y][i + 1] = c;
		if (c == '\n')
			break ;
		if (*line == NULL)
			return (free(*line), FAILURE);
	}
	while (++i <= game->map_size[WIDTH] + 1)
	{
		*line = ft_strjoin(*line, "X");
		if (*line == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	set_limiter(char **line, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
	{
		*line = ft_strjoin(*line, "X");
		if (*line == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}
