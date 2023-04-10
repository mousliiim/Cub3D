/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:32:16 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/10 01:27:02 by mmourdal         ###   ########.fr       */
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

int	ft_count_line_of_file(int fd)
{
	int		i;
	int		readret;
	int		flag;
	char	character;

	readret = 1;
	i = 0;
	flag = 0;
	while (readret != 0)
	{
		readret = read(fd, &character, 1);
		if (readret < 0)
			return (FAILURE);
		if (!flag && character == '1')
			flag = 1;
		if (flag && character == '\n')
			i++;
	}
	return (i);
}

int	ft_read_map_info(const char *map_path, t_info_map *info_parse)
{
	size_t		i;
	char		*line;
	int			fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (info_parse->type_error = MAP_ERROR, FAILURE);
	i = 0;
	line = get_next_line(fd, 0);
	while (line && i < 6)
	{
		if (!ft_empty_line(line))
			info_parse->map_info[i++] = str_without_space(line);
		else
			free(line);
		if (i == 6)
			break ;
		line = get_next_line(fd, 0);
	}
	info_parse->map_info[i] = NULL;
	if (i != 6)
		return (free(line), close(fd), info_parse->type_error = MAP_ERROR, 0);
	info_parse->fd = fd;
	return (SUCCESS);
}

int	ft_read_map(const char *map_path, t_game *game, t_info_map *info_parse)
{
	int		fd_tmp;
	int		fd;
	int		flag;
	char	*line;
	size_t	i;

	fd_tmp = open(map_path, O_RDONLY);
	fd = info_parse->fd;
	if (fd == -1 || fd_tmp == -1)
		return (info_parse->type_error = MAP_ERROR, FAILURE);
	game->map = ft_calloc(ft_count_line_of_file(fd_tmp) + 1, sizeof(char *));
	close(fd_tmp);
	if (!game->map)
		return (FAILURE);
	i = 0;
	flag = 0;
	line = get_next_line(fd, 0);
	while (line)
	{
		if (flag && !ft_empty_line(line))
			game->map[i++] = line;
		else if (!flag && !ft_empty_line(line))
		{
			game->map[i++] = line;
			flag = 1;
		}
		else if (flag && ft_empty_line(line))
			return (free(line), close(fd), info_parse->type_error = MAP_ERROR, FAILURE);
		else
			free(line);
		line = get_next_line(fd, 0);
	}
	// get_next_line(FREE_SR_GNL, 1);
	game->map[i] = NULL;
	free(line);
	close (fd);
	// display(game->map);
	return (SUCCESS);
}
