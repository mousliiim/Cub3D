/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:25:56 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/15 17:27:00 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

float	shorter_dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	simply_line(t_game *game, t_moh2i start, t_moh2i end, int color)
{
	int	y;

	y = start.y;
	while (y <= end.y)
	{
		img_pixel_put((&game->img), start.x, y, color);
		y++;
	}
}

void	img_pixel_put(t_data *img, int x, int y, int color)
{
	char	*px;

	px = img->addr + (int)(y * img->line_length + x * (img->bits_per_pixel
				/ 8));
	*(unsigned int *)px = color;
}

int	is_wall(t_game *game, t_moh2f pos)
{
	int	x;
	int	y;

	x = (int)(pos.x / SIZE);
	y = (int)(pos.y / SIZE);
	if (game->tab[y][x] == '1' || game->tab[y][x] == 'X')
		return (1);
	else
		return (0);
}

int	around(float nb)
{
	if (nb - (int)nb > 0.5)
		return ((int)ceil(nb));
	else
		return ((int)floor(nb));
}
