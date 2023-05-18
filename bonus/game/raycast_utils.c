/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:17:22 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/15 19:26:56 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ray_init(t_game *game, t_raycast *rc, int ray)
{
	rc->dof = 0;
	if (ray == VERTICAL)
	{
		rc->ray_v.dis = 1000000;
		rc->ray_v.point.x = game->player_pos.x;
		rc->ray_v.point.y = game->player_pos.y;
		rc->dda.ntan = -tan(rc->dda.rot_angle);
	}
	else
	{
		rc->ray_h.dis = 1000000;
		rc->ray_h.point.x = game->player_pos.x;
		rc->ray_h.point.y = game->player_pos.y;
		rc->dda.atan = (float)-1 / tan(rc->dda.rot_angle);
	}
}

int	deter_tox(t_game *game, t_raycast *rc)
{
	if (rc->draw.orient == VERTICAL)
	{
		if (rc->draw.v_facing == RIGHTT)
			game->curr_txt = game->texture[3].tab;
		else
			game->curr_txt = game->texture[2].tab;
		return ((int)rc->dda.ray.y % SIZE);
	}
	else
	{
		if (rc->draw.h_facing == UP)
			game->curr_txt = game->texture[NO].tab;
		else
			game->curr_txt = game->texture[1].tab;
		return ((int)rc->dda.ray.x % SIZE);
	}
}

void	build_wall(t_game *game, t_moh2i start, t_moh2i end, t_raycast *rc)
{
	int	y;
	int	dft;
	int	toy;
	int	tox;

	tox = deter_tox(game, rc);
	y = start.y;
	while (y < end.y)
	{
		dft = y + (((int)round((SIZE * W_HEIGHT) / rc->dist)) / 2)
			- round(W_HEIGHT / 2);
		toy = dft * (SIZE / ((float)round((SIZE * W_HEIGHT) / rc->dist)));
		if (toy > SIZE - 1)
			toy = SIZE - 1;
		if (toy < 0)
			toy = 0;
		rc->draw.color = game->curr_txt[toy * SIZE + tox];
		img_pixel_put((&game->img), start.x, y, rc->draw.color);
		y++;
	}
}

void	draw_3d(t_game *game, t_raycast *rc)
{
	rc->draw.ca = game->pa - rc->dda.rot_angle;
	if (rc->draw.ca < 0)
		rc->draw.ca += 2 * PI;
	else if (rc->draw.ca > 2 * PI)
		rc->draw.ca -= 2 * PI;
	rc->dist = rc->dist * cos(rc->draw.ca);
	rc->draw.line_h = round((SIZE * W_HEIGHT) / rc->dist);
	if (rc->draw.line_h > W_HEIGHT)
		rc->draw.line_h = W_HEIGHT;
	rc->draw.line_o = 400.0f - (float)rc->draw.line_h / 2.0f;
	rc->draw.depart.x = rc->ray * 1;
	rc->draw.depart.y = rc->draw.line_o;
	rc->draw.ceil.x = rc->ray * 1;
	rc->draw.ceil.y = 0;
	simply_line(game, rc->draw.ceil, rc->draw.depart, game->color_ceil);
	rc->draw.fin.x = rc->ray * 1;
	rc->draw.fin.y = rc->draw.line_h + rc->draw.line_o;
	build_wall(game, rc->draw.depart, rc->draw.fin, rc);
	rc->draw.floor.x = rc->ray * 1;
	rc->draw.floor.y = W_HEIGHT;
	simply_line(game, rc->draw.fin, rc->draw.floor, game->color_floor);
}

void	shorter_ray(t_raycast *rc)
{
	if (rc->ray_v.dis < rc->ray_h.dis)
	{
		rc->dda.ray.x = rc->ray_v.point.x;
		rc->dda.ray.y = rc->ray_v.point.y;
		rc->dist = rc->ray_v.dis;
		rc->draw.orient = VERTICAL;
	}
	else if (rc->ray_h.dis <= rc->ray_v.dis)
	{
		rc->dda.ray.x = rc->ray_h.point.x;
		rc->dda.ray.y = rc->ray_h.point.y;
		rc->dist = rc->ray_h.dis;
		rc->draw.orient = HORIZONTAL;
	}
	rc->draw.next.x = rc->dda.ray.x;
	rc->draw.next.y = rc->dda.ray.y;
}
