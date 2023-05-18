/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brasenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:38:10 by alvina            #+#    #+#             */
/*   Updated: 2023/05/14 16:06:08 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	going_up(t_data img, t_forthenorme point, float pente, int color)
{
	int	x;

	x = point.curr.x;
	if (x < point.next.x)
	{
		if (pente >= 1)
			second(img, point.curr, point.next, color);
		else
			first(img, point.curr, point.next, color);
	}
	else if (x == point.next.x)
		vertical(img, point.curr, point.next, color);
	else
	{
		if (pente < 1)
			fifth(img, point.curr, point.next, color);
		else
			sixth(img, point.curr, point.next, color);
	}
}

static void	going_down(t_data img, t_forthenorme point, float pente, int color)
{
	int	x;

	x = point.curr.x;
	if (x < point.next.x)
	{
		if (pente >= -1)
			eight(img, point.curr, point.next, color);
		else
			seventh(img, point.curr, point.next, color);
	}
	else
	{
		if (pente < -1)
			third(img, point.curr, point.next, color);
		else
			fourth(img, point.curr, point.next, color);
	}
}

void	bresenham(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int				dy;
	int				dx;
	float			pente;
	t_forthenorme	point;

	dy = next.y - curr.y;
	dx = next.x - curr.x;
	if (dx != 0)
		pente = (float)dy / (float)dx;
	else
	{
		pente = (float)dy;
		if (dy < 0)
			pente = -pente;
	}
	point.curr = curr;
	point.next = next;
	if (pente >= 0)
		going_up(img, point, pente, color);
	else
		going_down(img, point, pente, color);
}
