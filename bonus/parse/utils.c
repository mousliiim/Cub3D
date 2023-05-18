/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:12:06 by mmourdal          #+#    #+#             */
/*   Updated: 2023/05/17 21:41:26 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_key(char *str)
{
	if (!str)
		return (-1);
	if (ft_strncmp(str, "NO", 3) == SAME)
		return (0);
	else if (ft_strncmp(str, "SO", 3) == SAME)
		return (1);
	else if (ft_strncmp(str, "WE", 3) == SAME)
		return (2);
	else if (ft_strncmp(str, "EA", 3) == SAME)
		return (3);
	else if (ft_strncmp(str, "F", 2) == SAME)
		return (4);
	else if (ft_strncmp(str, "C", 2) == SAME)
		return (5);
	else
		return (-1);
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

int	rgb_color_check(char *str, t_info_map *info, int choice, int j)
{
	char	**array;
	int		i;

	array = ft_split(str, ',', &i);
	if (!array)
		return (FAILURE);
	if (i != 3)
		return (ft_free(array, 1), FAILURE);
	i = -1;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
			if (!ft_isdigit(array[i][j]))
				return (ft_free(array, 1), FAILURE);
		if (ft_atoi(array[i]) > 255 || ft_atoi(array[i]) < 0)
			return (ft_free(array, 1), FAILURE);
		if (choice == FLOOR)
			info->floor_color[i] = ft_atoi(array[i]);
		else if (choice == CEIL)
			info->ceil_color[i] = ft_atoi(array[i]);
	}
	ft_free(array, 1);
	return (SUCCESS);
}

void	ft_print_error(const int error)
{
	if (error == ARG_ERROR)
		ft_printf("%sError:%s Usage : ./cub3D_bonus <map.cub> \n", RED, END);
	else if (error == FILE_ERROR)
		ft_printf("%sError:%s File FD ERROR or not found\n", RED, END);
	else if (error == MAP_ERROR)
		ft_printf("%sError:%s Map not valid\n", RED, END);
	else if (error == ENV_ERROR)
		ft_printf("%sError:%s Environment not valid\n", RED, END);
	else if (error == MALLOC_ERROR)
		ft_printf("%sError:%s Malloc failed\n", RED, END);
	else if (error == MLX_ERROR)
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
