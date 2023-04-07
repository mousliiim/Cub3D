/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:34:49 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/07 04:03:12 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_key(char *str)
{
	char	*tmp;

	if (!str)
		return (-1);
	tmp = ft_strtrim(str, " ");
	if (ft_strncmp(str, "NO", ft_strlen(tmp)) == SAME)
		return (free(tmp), 0);
	else if (ft_strncmp(str, "SO", ft_strlen(tmp)) == SAME)
		return (free(tmp), 1);
	else if (ft_strncmp(str, "WE", ft_strlen(tmp)) == SAME)
		return (free(tmp), 2);
	else if (ft_strncmp(str, "EA", ft_strlen(tmp)) == SAME)
		return (free(tmp), 3);
	else if (ft_strncmp(str, "F", ft_strlen(tmp)) == SAME)
		return (free(tmp), 4);
	else if (ft_strncmp(str, "C", ft_strlen(tmp)) == SAME)
		return (free(tmp), 5);
	else
		return (free(tmp), -1);
}

int	check_tab_value(int *tab)
{
	size_t	i;

	i = 0;
	while (i < 6)
	{
		if (tab[i] == 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	take_value_texture(char **array, t_info_map *info_parse)
{
	char	*path;
	size_t	i;
	size_t	j;

	if (!array || !*array)
		return (FAILURE);
	if (check_key(array[0]) == 4 || check_key(array[0]) == 5)
		return (1);
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
	return (PARSING_OK);
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
			return (ft_free_split(array), ft_free(info_parse->texture, i),
				info_parse->type_error = MAP_ERROR, FAILURE);
		if (check_key(array[0]) != -1)
		{
			if (tab_check[check_key(array[0])] == 1)
				return (ft_free_split(array),
					info_parse->type_error = MAP_ERROR, PARSING_KO);
			else if (tab_check[check_key(array[0])] == 0)
				tab_check[check_key(array[0])] = 1;
		}
		if (!take_value_texture(array, info_parse))
			return (info_parse->type_error = MAP_ERROR, PARSING_KO);
		ft_free_split(array);
	}
	if (!check_tab_value(tab_check))
		return (info_parse->type_error = MAP_ERROR, PARSING_KO);
	info_parse->texture[4] = NULL;
	// ft_free_double_array(info_parse->texture); // FREE POUR TEST TEXTURE
	return (PARSING_OK);
}

int	key_and_value_check(t_info_map *info_parse)
{
	size_t	i;

	i = 0;
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
	display(info_parse->map_info);
	return (PARSING_OK);
}

// PENSER A FREE MAP_INFO A LA FIN DU PROGRAMME OU SI ERREUR.
