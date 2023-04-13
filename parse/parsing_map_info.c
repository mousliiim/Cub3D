/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:35:56 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/13 03:24:57 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_count_line_of_file(int fd)
{
	int		i;
	int		readret;
	int		flag;
	char	character;

	readret = 1;
	i = 0;
	flag = 0;
	while (readret != 0)
	{
		readret = read(fd, &character, 1);
		if (readret < 0)
			return (FAILURE);
		if (!flag && character == '1')
			flag = 1;
		if (flag && character == '\n')
			i++;
	}
	return (i);
}

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
			return (info->error = MALLOC_ERROR, FAILURE);
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
	static int		tab_check[6] = {NO, SO, WE, EA, F, C};
	char			**array;
	static size_t	i = -1;
	int				j;

	while (info->map_info[++i])
	{
		info->error = MAP_ERROR;
		array = ft_split(info->map_info[i], ' ', &j);
		if (!array || !*array)
			return (info->error = MALLOC_ERROR, FAILURE);
		if (check_key(array[0]) != -1)
		{
			if (tab_check[check_key(array[0])] == 1 || j != 2)
				return (ft_free_texture(info->texture), ft_free(array, 1), 0);
			tab_check[check_key(array[0])] = 1;
		}
		if (!take_value_texture(array, info))
			return (ft_free_texture(info->texture), ft_free(array, 1), 0);
		ft_free(array, 1);
	}
	if (!check_tab_value(tab_check))
		return (info->error = MAP_ERROR, FAILURE);
	return (SUCCESS);
}

int	get_info_map(const char *map_name, t_info_map *info)
{
	if (!ft_read_map_info(map_name, info))
		return (ft_free(info->map_info, 0), FAILURE);
	if (!cut_key_value(info))
		return (close(info->fd), get_next_line(FREE_SR_GNL, 1),
			ft_free(info->map_info, 0), FAILURE);
	return (SUCCESS);
}
