/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:12:06 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/09 18:21:59 by mmourdal         ###   ########.fr       */
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

int	rgb_color_check(char *str, t_info_map *info_parse, int choice)
{
	char	**array;
	int		i;
	int		j;

	array = ft_split(str, ',', &i);
	if (!array)
		return (FAILURE);
	if (i != 3)
		return (ft_free_split(array), FAILURE);
	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (!ft_isdigit(array[i][j]))
				return (ft_free_split(array), FAILURE);
			j++;
		}
		if (ft_atoi(array[i]) > 255 || ft_atoi(array[i]) < 0)
			return (ft_free_split(array), FAILURE);
		if (choice == FLOOR)
			info_parse->floor_color[i] = ft_atoi(array[i]);
		else if (choice == CEIL)
			info_parse->ceil_color[i] = ft_atoi(array[i]);
		i++;
	}
	ft_free_split(array);
	return (SUCCESS);
}

void	ft_print_error(const int type_error)
{
	if (type_error == ARG_ERROR)
		ft_printf("%sError:%s Correct usage : ./cub3D <map.cub> \n", RED, END);
	else if (type_error == FILE_ERROR)
		ft_printf("%sError:%s File not found\n", RED, END);
	else if (type_error == MAP_ERROR)
		ft_printf("%sError:%s Map not valid\n", RED, END);
	else if (type_error == ENV_ERROR)
		ft_printf("%sError:%s Environment not valid\n", RED, END);
	else if (type_error == MALLOC_ERROR)
		ft_printf("%sError:%s Malloc failed\n", RED, END);
	else if (type_error == MLX_ERROR)
		ft_printf("%sError:%s Mlx failed\n", RED, END);
	else
		ft_printf("%sError:%s Unknown error\n", RED, END);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}
