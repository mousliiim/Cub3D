/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 00:34:42 by mmourdal          #+#    #+#             */
/*   Updated: 2023/05/15 19:19:19 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_x_y(t_game *game, size_t y, size_t x)
{
	size_t		count;

	count = 0;
	if (game->tab[y][x + 1] && (game->tab[y][x + 1] == '1'
		|| game->tab[y][x + 1] == '0'
		|| game->tab[y][x + 1] == game->player_dir))
		count++;
	if (game->tab[y][x - 1] && (game->tab[y][x - 1] == '1'
		|| game->tab[y][x - 1] == '0'
		|| game->tab[y][x - 1] == game->player_dir))
		count++;
	if (game->tab[y + 1] && (game->tab[y + 1][x] == '1'
		|| game->tab[y + 1][x] == '0'
		|| game->tab[y + 1][x] == game->player_dir))
		count++;
	if (game->tab[y - 1] && (game->tab[y - 1][x] == '1'
		|| game->tab[y - 1][x] == '0'
		|| game->tab[y - 1][x] == game->player_dir))
		count++;
	if (count < 4)
		return (FAILURE);
	return (SUCCESS);
}

void	set_player_pos(t_game *game, size_t y, size_t x)
{
	game->player_dir = game->tab[y][x];
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
	if (!game->tab || !*game->tab)
		return (FAILURE);
	while (game->tab[y])
	{
		x = 0;
		while (game->tab[y][x] && game->tab[y][x] != '\n')
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
	int		i;
	char	c;

	i = -1;
	*line = ft_strjoin(*line, "X");
	if (*line == NULL)
		return (FAILURE);
	while (game->tab[y][++i])
	{
		c = game->tab[y][i + 1];
		game->tab[y][i + 1] = '\0';
		*line = ft_strjoin(*line, &game->tab[y][i]);
		game->tab[y][i + 1] = c;
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
