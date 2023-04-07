/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:32:16 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/06 23:39:43 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*str_without_space(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

static int	ft_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (EXIT_FAILURE);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_read_map_info(const char *map_path, t_info_map *info_parse)
{
	size_t		i;
	char		*line;
	int			fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (info_parse->type_error = MAP_ERROR, PARSING_KO);
	i = 0;
	line = get_next_line(fd, 0);
	while (line && i < 6)
	{
		if (!ft_empty_line(line))
			info_parse->map_info[i++] = str_without_space(line);
		else
			free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(FREE_SR_GNL, 1);
	info_parse->map_info[i] = NULL;
	if (i != 6)
		return (free(line), close(fd), info_parse->type_error = MAP_ERROR, 0);
	close(fd);
	free(line);
	return (PARSING_OK);
}
