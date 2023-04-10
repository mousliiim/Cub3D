/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:35:56 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/10 19:57:29 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	take_value_texture(char **array, t_info_map *info)
{
	char	*path;
	size_t	i;
	size_t	j;

	if (check_key(array[0]) == FLOOR || check_key(array[0]) == CEIL)
		return (rgb_color_check(array[1], info, check_key(array[0]), -1));
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
	if (check_key(array[0]) == -1)
		return (free(path), FAILURE);
	info->texture[check_key(array[0])] = path;
	return (SUCCESS);
}

static int	cut_key_value(t_info_map *info)
{
	static int	tab_check[6] = {NO, SO, WE, EA, F, C};
	char		**array;
	size_t		i;
	int			j;

	i = -1;
	while (info->map_info[++i])
	{
		array = ft_split(info->map_info[i], ' ', &j);
		if (!array || !*array)
			return (FAILURE);
		if (j != 2)
			return (ft_free_texture(info->texture), ft_free_split(array),
				info->error = MAP_ERROR, FAILURE);
		if (check_key(array[0]) != -1)
		{
			if (tab_check[check_key(array[0])] == 1)
				return (ft_free_texture(info->texture), ft_free_split(array),
					info->error = MAP_ERROR, FAILURE);
			else if (tab_check[check_key(array[0])] == 0)
				tab_check[check_key(array[0])] = 1;
		}
		if (!take_value_texture(array, info))
		{
			return (ft_free_texture(info->texture), ft_free_split(array),
				info->error = MAP_ERROR, FAILURE);
		}
		ft_free_split(array);
	}
	if (!check_tab_value(tab_check))
		return (info->error = MAP_ERROR, FAILURE);
	info->texture[4] = NULL;
	return (SUCCESS);
}

int	get_info_map(const char *map_name, t_info_map *info)
{
	if (!ft_read_map_info(map_name, info))
		return (ft_free_double_array(info->map_info), FAILURE);
	if (!cut_key_value(info))
		return (close(info->fd), get_next_line(FREE_SR_GNL, 1),
			ft_free_double_array(info->map_info), FAILURE);
	return (SUCCESS);
}

