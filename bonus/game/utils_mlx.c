/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:03:50 by mmourdal          #+#    #+#             */
/*   Updated: 2023/05/17 17:20:51 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	close_x(t_game *game)
{
	ft_putstr_fd("Did you have fun ?\n", 1);
	mlx_loop_end(game->mlx);
	cleaner(game, 0);
	return (1);
}

static void	sizing(t_game *game)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	i = 0;
	j = 0;
	while (game->tab[i])
	{
		while (game->tab[i][j])
			j++;
		if (j > size)
			size = j;
		j = 0;
		i++;
	}
	game->map_size[0] = i - 1;
	game->map_size[1] = size - 1;
}

void	modify(t_game *game, int i, int j)
{
	char	**tab;

	sizing(game);
	tab = malloc((sizeof(char *) * (game->map_size[0] + 1)));
	if (!tab)
		cleaner(game, MALLOC_ERROR);
	while (++i < (int)game->map_size[0])
	{
		tab[i - 1] = malloc(sizeof(char) * game->map_size[1]);
		if (!tab[i - 1])
			return (tab_clean(tab, i - 1), cleaner(game, MALLOC_ERROR));
		while (j < (int)game->map_size[1] - 1)
		{
			if (game->tab[i][j] == '\0' || game->tab[i][j] == ' ')
				tab[i - 1][j - 1] = 'X';
			else
				tab[i - 1][j - 1] = game->tab[i][j];
			j++;
		}
		tab[i - 1][j - 1] = 0;
		j = 1;
	}
	tab[i - 1] = NULL;
	tab_clean(game->tab, (int)game->map_size[0] + 1);
	game->tab = tab;
}

void	seeing_in_the_futur_bro(int key_symbole, t_game *game, int speed)
{
	if (key_symbole == W)
	{
		game->next_next_pos.y = game->next_pos.y - (game->pd.y * speed);
		game->next_next_pos.x = game->next_pos.x - (game->pd.x * speed);
	}
	if (key_symbole == S)
	{
		game->next_next_pos.y = game->next_pos.y + (game->pd.y * speed);
		game->next_next_pos.x = game->next_pos.x + (game->pd.x * speed);
	}
	if (key_symbole == A)
	{
		game->next_next_pos.x = game->next_pos.x - (game->pd.y * speed);
		game->next_next_pos.y = game->next_pos.y + (game->pd.x * speed);
	}
	if (key_symbole == D)
	{
		game->next_next_pos.x = game->next_pos.x + (game->pd.y * speed);
		game->next_next_pos.y = game->next_pos.y - (game->pd.x * speed);
	}
}

void	setting_next_pos(int key_symbole, t_game *game, int speed)
{
	if (key_symbole == W)
	{
		game->next_pos.y -= (game->pd.y * speed);
		game->next_pos.x -= (game->pd.x * speed);
	}
	if (key_symbole == S)
	{
		game->next_pos.y += (game->pd.y * speed);
		game->next_pos.x += (game->pd.x * speed);
	}
	if (key_symbole == A)
	{
		game->next_pos.x -= (game->pd.y * speed);
		game->next_pos.y += (game->pd.x * speed);
	}
	if (key_symbole == D)
	{
		game->next_pos.x += (game->pd.y * speed);
		game->next_pos.y -= (game->pd.x * speed);
	}
}
