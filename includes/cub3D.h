/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:34:22 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/25 20:24:32 by mmourdal         ###   ########.fr       */
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
# include <math.h>
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
# define FREE_SR_GNL -1
# define SUCCESS 1
# define FLOOR 4
# define CEIL 5
# define FAILURE 0
# define SAME 0
# define NO 0
# define SO 0
# define WE 0
# define EA 0
# define F 0
# define C 0
# define HEIGHT 0
# define WIDTH 1
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

# define ESC 65307
# define W 119
# define A 97
# define D 100
# define S 115
# define LEFT 65361
# define RIGHT 65363

typedef enum e_texture
{
	T_NO,
	T_SO,
	T_WE,
	T_EA,
	RGB_F,
	RGB_C
}	t_texture;

typedef double	t_moh2f	__attribute__((ext_vector_type(2)));
typedef int		t_moh2i	__attribute__((ext_vector_type(2)));

typedef struct s_info_map
{
	char	*texture[5];
	char	*map_info[7];
	int		floor_color[3];
	int		ceil_color[3];
	int		fd;
	int		error;
}	t_info_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		**map;
	char		player_dir;
	size_t		map_size[2];
	double		planeX;
	double		planeY;
	t_moh2f		player_pos_f;
	t_moh2i		player_pos_i;
	t_info_map	*info_map;
}	t_game;

/**************** IN DIRECTORY PARSE *****************/
				/** IN FILE READ_MAP.C **/
int		ft_read_map_info(const char *map_path, t_info_map *info);
int		ft_read_map(const char *map_path, t_game *game, t_info_map *info);
				/** IN FILE UTILS.C **/
void	ft_print_error(const int error);
int		ft_isspace(char c);
int		rgb_color_check(char *str, t_info_map *info, int choice, int j);
int		check_tab_value(int *tab);
int		check_key(char *str);
				/** IN FILE PARSING_MAP_INFO.C **/
int		get_info_map(const char *map_name, t_info_map *info);
int		ft_count_line_of_file(int fd);
				/** IN FILE PARSING_MAP.C **/
int		get_map(const char *map_name, t_game *game, t_info_map *info);
				/** IN FILE UTILS_PARSING_MAP.C **/
int		check_x_y(t_game *game, size_t y, size_t x);
void	set_player_pos(t_game *game, size_t y, size_t x);
int		size_of_map(t_game *game);
int		set_line(t_game *game, char **line, int y);
int		set_limiter(char **line, size_t len);
/**************** IN DIRECTORY FREE *****************/
				/** IN FILE FREE.C **/
void	ft_free(char **array, int free_array);
void	ft_free_split(char **array);
void	ft_free_texture(char **texture);
void	ft_free_error_map(t_info_map *info, t_game *game);
/**************** IN DIRECTORY GAME *****************/
				/** IN FILE GAME_MLX.C **/
int		init_mlx(t_game *game);
int		close_x(t_game *game);
int		deal_key(int key_symbole, t_game *game);

/************ TMP UTILS NEED TO DELETE **************/
void	display(char **map);
void	display_nl(char **array);
void	display_all(char **array, char **array2);
#endif