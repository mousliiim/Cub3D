/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:34:49 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/06 03:34:45 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_key(char *str)
{
	if (ft_strncmp(str, "NO", 2) == SAME)
		return (0);
	else if (ft_strncmp(str, "SO", 2) == SAME)
		return (1);
	else if (ft_strncmp(str, "WE", 2) == SAME)
		return (2);
	else if (ft_strncmp(str, "EA", 2) == SAME)
		return (3);
	else if (ft_strncmp(str, "F", 1) == SAME)
		return (4);
	else if (ft_strncmp(str, "C", 1) == SAME)
		return (5);
	else
		return (-1);
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

int	cut_key_value(t_info_map *info_parse)
{
	size_t		i;
	size_t		j;
	static int	tab_check[6] = {NO, SO, WE, EA, F, C};
	char		**array;

	i = 0;
	j = 0;
	while (info_parse->map_info[i])
	{
		array = ft_split(info_parse->map_info[i], ' ');
		if (!array)
			return (FAILURE);
		if (check_key(array[0]) != -1)
		{
			if (tab_check[check_key(array[0])] == 1)
			{
				ft_free_split(array);
				return (info_parse->type_error = MAP_ERROR, PARSING_KO);
			}
			else if (tab_check[check_key(array[0])] == 0)
				tab_check[check_key(array[0])] = 1;
		}
		ft_free_split(array);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		printf("tab_check[%zu] = %d\n", i, tab_check[i]);
		i++;
	}
	return (SUCCESS);
}

int	check_first_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'F' || c == 'C')
		return (SUCCESS);
	return (FAILURE);
}

int	key_and_value_check(t_info_map *info_parse)
{
	size_t	i;

	i = 0;
	if (!cut_key_value(info_parse))
		return (FAILURE);
	return (SUCCESS);
}

void	display_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

int	get_info_map(const char *map_name, t_info_map *info_parse)
{
	if (!ft_read_map_info(map_name, info_parse))
		return (ft_free_double_array(info_parse->map_info), FAILURE);
	if (!key_and_value_check(info_parse))
		return (ft_free_double_array(info_parse->map_info), FAILURE);
	// display_map(info_parse->map_info);
	return (PARSING_OK);
}

// PENSER A FREE MAP_INFO A LA FIN DU PROGRAMME OU SI ERREUR.
