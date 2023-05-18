/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:45:54 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/17 20:07:47 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*looking down then up then horizontally*/
void	spawn_horiz(t_game *game, t_raycast *rc)
{
	if (rc->dda.rot_angle < PI)
	{
		rc->dda.ray.y = (((int)game->player_pos.y / SIZE) * SIZE) - 0.0001;
		rc->dda.ray.x = (game->player_pos.y - rc->dda.ray.y) * rc->dda.atan
			+ game->player_pos.x;
		rc->dda.pas.y = -SIZE;
		rc->dda.pas.x = -rc->dda.pas.y * rc->dda.atan;
		rc->draw.h_facing = DOWN;
	}
	if (rc->dda.rot_angle > PI)
	{
		rc->draw.h_facing = UP;
		rc->dda.ray.y = (((int)game->player_pos.y / SIZE) * SIZE) + SIZE;
		rc->dda.ray.x = (game->player_pos.y - rc->dda.ray.y) * rc->dda.atan
			+ game->player_pos.x;
		rc->dda.pas.y = SIZE;
		rc->dda.pas.x = -rc->dda.pas.y * rc->dda.atan;
	}
	if (rc->dda.rot_angle < 0 || rc->dda.rot_angle == PI)
	{
		rc->draw.h_facing = UP;
		rc->dda.ray.x = game->player_pos.x;
		rc->dda.ray.y = game->player_pos.y;
		rc->dof = game->map.height;
	}
}

void	dda_horiz(t_game *game, t_raycast *rc)
{
	while (rc->dof < game->map.height)
	{
		rc->map.x = (int)rc->dda.ray.x / SIZE;
		rc->map.y = (int)rc->dda.ray.y / SIZE;
		if (rc->map.x >= 0 && rc->map.y >= 0 && rc->map.x < game->map.length
			&& rc->map.y < game->map.height
			&& game->tab[rc->map.y][rc->map.x] == '1')
		{
			rc->ray_h.point.x = rc->dda.ray.x;
			rc->ray_h.point.y = rc->dda.ray.y;
			rc->ray_h.dis = shorter_dist(game->player_pos.x, game->player_pos.y,
					rc->ray_h.point.x, rc->ray_h.point.y);
			rc->dof = game->map.height;
		}
		else
		{
			rc->dda.ray.x += rc->dda.pas.x;
			rc->dda.ray.y += rc->dda.pas.y;
			rc->dof += 1;
		}
	}
}

/*looking right, then looking left*/
void	spawn_vert(t_game *game, t_raycast *rc)
{
	if (rc->dda.rot_angle < P2 || rc->dda.rot_angle > P3)
	{
		rc->dda.ray.x = (((int)game->player_pos.x / SIZE) * SIZE) - 0.0001;
		rc->dda.ray.y = (game->player_pos.x - rc->dda.ray.x) * rc->dda.ntan
			+ game->player_pos.y;
		rc->dda.pas.x = -SIZE;
		rc->dda.pas.y = -rc->dda.pas.x * rc->dda.ntan;
		rc->draw.v_facing = RIGHTT;
	}
	if (rc->dda.rot_angle > P2 && rc->dda.rot_angle < P3)
	{
		rc->dda.ray.x = (((int)game->player_pos.x / SIZE) * SIZE) + SIZE;
		rc->dda.ray.y = (game->player_pos.x - rc->dda.ray.x) * rc->dda.ntan
			+ game->player_pos.y;
		rc->dda.pas.x = SIZE;
		rc->dda.pas.y = -rc->dda.pas.x * rc->dda.ntan;
		rc->draw.v_facing = LEFTT;
	}
}

void	dda_vert(t_game *game, t_raycast *rc)
{
	while (rc->dof < game->map.length)
	{
		rc->map.x = (int)rc->dda.ray.x / SIZE;
		rc->map.y = (int)rc->dda.ray.y / SIZE;
		if (rc->map.x >= 0 && rc->map.y >= 0 && rc->map.x < game->map.length
			&& rc->map.y < game->map.height
			&& game->tab[rc->map.y][rc->map.x] == '1')
		{
			rc->ray_v.point.x = rc->dda.ray.x;
			rc->ray_v.point.y = rc->dda.ray.y;
			rc->ray_v.dis = shorter_dist(game->player_pos.x, game->player_pos.y,
					rc->ray_v.point.x, rc->ray_v.point.y);
			rc->dof = game->map.length;
		}
		else
		{
			rc->dda.ray.x += rc->dda.pas.x;
			rc->dda.ray.y += rc->dda.pas.y;
			rc->dof += 1;
		}
	}
}

/*Spawn horizontal rays, then verticals, then choose the shorter,
	then draw the pixel columns*/
void	raycasting(t_game *game)
{
	t_raycast	rc;

	rc.dda.rot_angle = game->pa - (DR16 * 480);
	rc.ray = 0;
	while (rc.ray < 960)
	{
		if (rc.dda.rot_angle < 0)
			rc.dda.rot_angle += 2 * PI;
		else if (rc.dda.rot_angle > 2 * PI)
			rc.dda.rot_angle -= 2 * PI;
		ray_init(game, &rc, HORIZONTAL);
		spawn_horiz(game, &rc);
		dda_horiz(game, &rc);
		ray_init(game, &rc, VERTICAL);
		spawn_vert(game, &rc);
		dda_vert(game, &rc);
		shorter_ray(&rc);
		draw_3d(game, &rc);
		draw_ray_minimap(game, &rc);
		rc.ray++;
		rc.dda.rot_angle += DR16;
	}
}
