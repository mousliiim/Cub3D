/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:34:22 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/08 17:08:24 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include "../libft/libft.h"
# include "../mlx/mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

# define GREEN "\033[0;32m"
# define BLUE "\033[1;34m"
# define RED "\033[0;31m"
# define END "\033[0m"

# define W_WIDTH	1280
# define W_HEIGHT	720

# define ARG_ERROR -1
# define FILE_ERROR -2
# define MAP_ERROR -3
# define MALLOC_ERROR -4
# define MLX_ERROR -5
# define ENV_ERROR -6
# define PARSING_OK 1
# define PARSING_KO 0
# define FREE_SR_GNL -1
# define SUCCESS 1
# define FAILURE 0
# define SAME 0
# define NO 0
# define SO 0
# define WE 0
# define EA 0
# define F 0
# define C 0

# define ESC 65307
# define W 119
# define A 97
# define D 100
# define S 115

typedef enum e_texture
{
	T_NO,
	T_SO,
	T_WE,
	T_EA,
	RGB_F,
	RGB_C
}	t_texture;

typedef struct s_info_map
{
	char	*texture[5];
	char	*map_info[7];
	int		type_error;
	int		floor_color[3];
	int		ceil_color[3];
}	t_info_map;

typedef struct s_start_game
{
	void		*mlx;
	void		*win;
	void		*img;
	int			width;
	int			height;
	t_info_map	*info_map;
}	t_start_game;

/**************** IN DIRECTORY PARSE *****************/
				/** IN FILE READ_MAP.C **/
int		ft_read_map_info(const char *map_path, t_info_map *info_parse);
				/** IN FILE UTILS.C **/
void	ft_print_error(const int type_error);
int		ft_isspace(char c);
void	ft_free_double_array(char **array);
				/** IN FILE PARSING_MAP.C **/
int		get_info_map(const char *map_name, t_info_map *info_parse);

/**************** IN DIRECTORY FREE *****************/
				/** IN FILE FREE.C **/
void	ft_free_double_array(char **array);
void	ft_free_split(char **array);
void	ft_free(char **str, int i);


/************ TMP UTILS NEED TO DELETE **************/
void	display(char **map);
#endif