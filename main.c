/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:31:22 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/07 04:01:39 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

static int	file_name_check(char *map_name)
{
	if (!(ft_strcmp(map_name + (ft_strlen(map_name) - 4), ".cub") == 0)
		|| !ft_strcmp(map_name, ".cub"))
		return (FAILURE);
	else
		return (SUCCESS);
}

static int	start_parsing(const char *map_name, t_info_map *info_parse)
{
	if (!get_info_map(map_name, info_parse))
		return (PARSING_KO);
	return (PARSING_OK);
}

int	main(int argc, char **argv, char **env)
{
	t_info_map		info_parse;
	t_start_game	game;

	(void)game;
	if (!env || !*env)
		return (ft_print_error(ENV_ERROR), FAILURE);
	if (argc != 2 || !file_name_check(argv[1]))
		return (ft_print_error(ARG_ERROR), FAILURE);
	if (!start_parsing(argv[1], &info_parse))
		return (ft_print_error(info_parse.type_error), FAILURE);
	// ft_free_double_array(info_parse.map_info); // free map_info
}
