/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 03:13:05 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/13 00:55:04 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	display_all(char **array, char **array2)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		printf("%s", array[i]);
		i++;
	}
	i = 0;
	while (array2[i])
	{
		printf("%s\n", array2[i]);
		i++;
	}
}

void	display(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		printf("%s", array[i]);
		i++;
	}
}

void	display_nl(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}
