/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 03:15:30 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/07 03:59:01 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_free(char **str, int i)
{
	while (--i >= 0)
		free(str[i]);
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
