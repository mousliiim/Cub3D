/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:12:06 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/06 03:29:38 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
