/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:32:16 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/04 20:05:21 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	read_file(int fd, char *buffer, char **tmp)
{
	size_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read < 0)
		{
			free(*tmp);
			return (FAILURE);
		}
		buffer[bytes_read] = '\0';
		*tmp = NULL;
		if (!*tmp)
		{
			close(fd);
			free(buffer);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

char	*ft_read_map(const char *map_path)
{
	char	*buffer;
	char	*tmp;
	int		fd;

	buffer = malloc(sizeof(char) * 2);
	if (!buffer)
		return (NULL);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	tmp = NULL;
	if (!read_file(fd, buffer, &tmp))
		return (FAILURE);
	close(fd);
	free(buffer);
	return (tmp);
}

int	get_info_map(const char *map_name, t_info_map *info_parse)
{
	char	*map;

	(void)info_parse;
	map = ft_read_map(map_name);
	if (!map)
		return (FAILURE);
	// if (!parse_map(map, info_parse))
	// 	return (FAILURE);
	return (SUCCESS);
}

// METTRE DANS LA STRUCT UN CODE ERREUR POUR AFFICHER LE BON MESSAGE D'ERREUR

