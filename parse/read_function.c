/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:32:16 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/13 02:30:41 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static char	*str_without_space(char *str)
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

static int	ft_empty_line(const char *line)
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

int	ft_read_map_info(const char *map_path, t_info_map *info)
{
	size_t		i;
	char		*line;
	int			fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (info->error = MAP_ERROR, FAILURE);
	i = 0;
	line = get_next_line(fd, 0);
	while (line && i < 6)
	{
		if (!ft_empty_line(line))
			info->map_info[i++] = str_without_space(line);
		else
			free(line);
		if (i == 6)
			break ;
		line = get_next_line(fd, 0);
	}
	info->map_info[i] = NULL;
	if (i != 6)
		return (free(line), close(fd), info->error = MAP_ERROR, 0);
	info->fd = fd;
	return (SUCCESS);
}

int	loop_in_read_map(char **line, int *flag, size_t *i, t_game *game)
{
	if (*flag && !ft_empty_line(*line))
		game->map[(*i)++] = *line;
	else if (!*flag && !ft_empty_line(*line))
	{
		game->map[(*i)++] = *line;
		*flag = 1;
	}
	else if (*flag && ft_empty_line(*line))
		return (FAILURE);
	else
		free(*line);
	*line = get_next_line(game->info_map->fd, 0);
	return (SUCCESS);
}

int	ft_read_map(const char *map_path, t_game *game, t_info_map *info)
{
	int		fd_tmp;
	int		fd;
	int		flag;
	char	*line;
	size_t	i;

	fd_tmp = open(map_path, O_RDONLY);
	fd = info->fd;
	if (fd_tmp == -1 || fd == -1)
		return (close(info->fd), close(fd_tmp),
			info->error = FILE_ERROR, FAILURE);
	game->map = ft_calloc(ft_count_line_of_file(fd_tmp) + 1, sizeof(char *));
	if (!game->map)
		return (close(fd_tmp), close(fd), info->error = MALLOC_ERROR, FAILURE);
	close(fd_tmp);
	i = 0;
	flag = 0;
	line = get_next_line(fd, 0);
	while (line)
		if (!loop_in_read_map(&line, &flag, &i, game))
			return (ft_free(info->map_info, 0), free(line), close(fd), FAILURE);
	game->map[i] = NULL;
	free(line);
	close (fd);
	return (SUCCESS);
}
