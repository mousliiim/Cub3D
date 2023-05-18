/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 03:15:30 by mmourdal          #+#    #+#             */
/*   Updated: 2023/05/14 16:45:04 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_free_error_map(t_info_map *info, t_game *game)
{
	if (info->error == FILE_ERROR)
	{
		ft_free(info->map_info, 0);
		ft_free(info->texture, 0);
		get_next_line(FREE_SR_GNL, 1);
		return ;
	}
	ft_free(info->texture, 0);
	if (info->error == MAP_ERROR)
	{
		ft_free(game->tab, 0);
		free(game->tab);
	}
	if (info->error == MALLOC_ERROR)
		ft_free(info->map_info, 0);
	get_next_line(FREE_SR_GNL, 1);
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

void	ft_free(char **array, int free_array)
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
	if (free_array)
		free(array);
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
