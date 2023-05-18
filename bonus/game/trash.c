/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:17:26 by alvina            #+#    #+#             */
/*   Updated: 2023/05/17 20:21:36 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	img_destroyer(t_game *game)
{
	if (game->texture[0].img.img)
		mlx_destroy_image(game->mlx, game->texture[0].img.img);
	if (game->texture[1].img.img)
		mlx_destroy_image(game->mlx, game->texture[1].img.img);
	if (game->texture[2].img.img)
		mlx_destroy_image(game->mlx, game->texture[2].img.img);
	if (game->texture[3].img.img)
		mlx_destroy_image(game->mlx, game->texture[3].img.img);
	if (game->win && game->mlx)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
	}
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	cleaner(t_game *game, int code)
{
	int	i;

	i = 0;
	if (game->tab)
	{
		while (game->tab[i])
			free(game->tab[i++]);
		free(game->tab);
	}
	img_destroyer(game);
	ft_free(game->info_map->map_info, 0);
	ft_free(game->info_map->texture, 0);
	if (code == MLX_ERROR)
		ft_putstr_fd("MLX FAILED : Did you try to fool me ?\n", 2);
	if (code == MALLOC_ERROR)
		ft_putstr_fd("MALLOC FAILED : too bad . . . \n", 2);
	if (code == MAP_ERROR)
		ft_putstr_fd("MAP FAILED : You tried a too big map !\n", 2);
	if (code == IMG_ERROR)
		ft_putstr_fd("IMG FAILED : Your image is too small . . .\n", 2);
	exit(code);
}

void	tab_clean(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	checking(t_game *game, int orient)
{
	if (!game->texture[orient].img.img)
		cleaner(game, MLX_ERROR);
	if (game->texture[orient].width < 200 || game->texture[orient].height < 200)
		cleaner(game, IMG_ERROR);
}
