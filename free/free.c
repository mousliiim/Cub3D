/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 03:15:30 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/10 01:21:40 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_free_error_map(t_info_map *info, t_game *game)
{
	ft_free_double_array(info->texture);
	ft_free_double_array(game->map);
	free(game->map);
	get_next_line(-1, 1);
}

void	ft_free(char **str, int i)
{
	while (--i >= 0)
		free(str[i]);
}

void	ft_free_texture(char **texture)
{
	size_t	i;

	i = 0;
	while (i < 5)
	{
		if (texture[i])
			free(texture[i]);
		i++;
	}
}

void	ft_free_double_array(char **array)
{
	int	i;

	i = 0;
	if (!*array || !array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
}

void	ft_free_split(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
