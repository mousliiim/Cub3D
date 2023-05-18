/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:31:22 by mmourdal          #+#    #+#             */
/*   Updated: 2023/05/18 23:52:35 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

static int	file_name_check(const char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (!(ft_strcmp(map_name + (ft_strlen(map_name) - 4), ".cub") == 0)
		|| !ft_strcmp(map_name, ".cub"))
		return (close(fd), FAILURE);
	else if (ft_strcmp(map_name + (ft_strlen(map_name) - 5), "/.cub") == 0)
		return (close(fd), FAILURE);
	else if (fd == -1)
	{
		ft_print_error(FILE_ERROR);
		exit (EXIT_FAILURE);
	}
	else
	{
		close (fd);
		return (SUCCESS);
	}
}

static int	start_parsing(const char *map_name, t_info_map *info, t_game *game)
{
	if (!get_info_map(map_name, info))
		return (FAILURE);
	if (!get_map(map_name, game, info))
		return (ft_free_error_map(info, game), FAILURE);
	return (SUCCESS);
}

static int	start_game(t_game *game)
{
	if (!blood_link(game))
		return (ft_free_error_map(game->info_map, game), FAILURE);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	static t_info_map	info = {0};
	static t_game		game = {0};

	game.info_map = &info;
	if (!env || !*env)
		return (ft_print_error(ENV_ERROR), FAILURE);
	if (argc != 2 || !file_name_check(argv[1]))
		return (ft_print_error(ARG_ERROR), FAILURE);
	if (!start_parsing(argv[1], &info, &game))
		return (ft_print_error(info.error), FAILURE);
	if (!start_game(&game))
		return (ft_print_error(MALLOC_ERROR), FAILURE);
	return (SUCCESS);
}
