/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:27:50 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/17 20:22:15 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#include "../includes/cub3D.h"

static void	init_adr_texture(t_game *game)
{
	game->texture[NO].tab = (int *)mlx_get_data_addr(game->texture[NO].img.img,
			&game->texture[NO].img.bits_per_pixel,
			&game->texture[NO].img.line_length, &game->texture[NO].img.endian);
	game->texture[1].tab = (int *)mlx_get_data_addr(game->texture[1].img.img,
			&game->texture[1].img.bits_per_pixel,
			&game->texture[1].img.line_length, &game->texture[2].img.endian);
	game->texture[2].tab = (int *)mlx_get_data_addr(game->texture[2].img.img,
			&game->texture[2].img.bits_per_pixel,
			&game->texture[2].img.line_length, &game->texture[2].img.endian);
	game->texture[3].tab = (int *)mlx_get_data_addr(game->texture[3].img.img,
			&game->texture[3].img.bits_per_pixel,
			&game->texture[3].img.line_length, &game->texture[3].img.endian);
}

void	init_texture(t_game *game)
{
	game->texture[NO].img.img = mlx_xpm_file_to_image(game->mlx,
			game->info_map->texture[1], &(game->texture[NO].width),
			&(game->texture[NO].height));
	checking(game, NO);
	game->texture[1].img.img = mlx_xpm_file_to_image(game->mlx,
			game->info_map->texture[NO], &(game->texture[1].width),
			&(game->texture[1].height));
	checking(game, 1);
	game->texture[2].img.img = mlx_xpm_file_to_image(game->mlx,
			game->info_map->texture[3], &(game->texture[2].width),
			&(game->texture[2].height));
	checking(game, 2);
	game->texture[3].img.img = mlx_xpm_file_to_image(game->mlx,
			game->info_map->texture[2], &(game->texture[3].width),
			&(game->texture[3].height));
	checking(game, 3);
	init_adr_texture(game);
}

void	grey_screen(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < W_HEIGHT)
	{
		while (x < W_WIDTH)
		{
			img_pixel_put((&game->img), x, y, 0x00808080);
			x++;
		}
		x = 0;
		y++;
	}
}

int	convert_hexa_color(int red, int green, int blue)
{
	int	hex_value;

	hex_value = 0;
	hex_value |= red << 16;
	hex_value |= green << 8;
	hex_value |= blue;
	return (hex_value);
}
