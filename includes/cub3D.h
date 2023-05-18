/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:34:22 by mmourdal          #+#    #+#             */
/*   Updated: 2023/05/17 20:26:58 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <float.h>
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

# define W_WIDTH 960
# define W_HEIGHT 800

# define ARG_ERROR -1
# define FILE_ERROR -2
# define MAP_ERROR -3
# define MALLOC_ERROR -4
# define MLX_ERROR -5
# define ENV_ERROR -6
# define IMG_ERROR -7
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

# define PI 3.14159265
# define P2 1.570796327
# define P3 4.712388981
# define DR16 0.00109083078
# define SIZE 200
# define VERTICAL 0
# define HORIZONTAL 1
# define UP 0
# define DOWN 1
# define RIGHTT 2
# define LEFTT 3

typedef enum e_texture
{
	T_NO,
	T_SO,
	T_WE,
	T_EA,
	RGB_F,
	RGB_C
}				t_texture;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_moh2f
{
	double		x;
	double		y;
}				t_moh2f;

typedef struct s_moh2i
{
	int			x;
	int			y;
}				t_moh2i;

typedef struct s_map
{
	int			length;
	int			height;
	int			size;
}				t_map;

typedef struct s_forthenorme
{
	t_moh2f		curr;
	t_moh2f		next;
}				t_forthenorme;

typedef struct s_txt
{
	t_data		img;
	int			*tab;
	int			height;
	int			width;
}				t_txt;

typedef struct s_info_map
{
	char		*texture[5];
	char		*map_info[7];
	int			floor_color[3];
	int			ceil_color[3];
	int			fd;
	int			error;
}				t_info_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	double		planex;
	double		planey;
	t_moh2f		player_pos_f;
	t_moh2i		player_pos_i;
	char		player_dir;
	t_data		img;
	char		**tab;
	t_map		map;
	double		pa;
	int			map_size[2];
	t_moh2f		player_pos;
	t_moh2f		next_pos;
	t_moh2f		next_next_pos;
	t_moh2f		pd;
	t_info_map	*info_map;
	int			color_floor;
	int			color_ceil;
	int			*curr_txt;
	t_txt		texture[4];
}				t_game;

typedef struct s_dda
{
	t_moh2f		ray;
	t_moh2f		pas;
	float		rot_angle;
	float		ntan;
	float		atan;
}				t_dda;

typedef struct s_ray
{
	float		dis;
	t_moh2f		point;
}				t_ray;

typedef struct s_draw
{
	int			line_h;
	int			line_o;
	float		ca;
	int			color;
	int			orient;
	int			h_facing;
	int			v_facing;
	t_moh2i		next;
	t_moh2i		depart;
	t_moh2i		fin;
	t_moh2i		ceil;
	t_moh2i		floor;
}				t_draw;

typedef struct s_raycast
{
	t_dda		dda;
	float		dist;
	t_ray		ray_v;
	t_ray		ray_h;
	t_moh2i		map;
	int			ray;
	int			dof;
	t_draw		draw;
}				t_raycast;

/**************** IN DIRECTORY PARSE *****************/

/** IN FILE READ_MAP.C **/
int				ft_read_map_info(const char *map_path, t_info_map *info);
int				ft_read_map(const char *map_path, t_game *game,
					t_info_map *info);

/** IN FILE UTILS.C **/
void			ft_print_error(const int error);
int				ft_isspace(char c);
int				rgb_color_check(char *str, t_info_map *info, int choice, int j);
int				check_tab_value(int *tab);
int				check_key(char *str);

/** IN FILE PARSING_MAP_INFO.C **/
int				get_info_map(const char *map_name, t_info_map *info);
int				ft_count_line_of_file(int fd);

/** IN FILE PARSING_MAP.C **/
int				get_map(const char *map_name, t_game *game, t_info_map *info);

/** IN FILE UTILS_PARSING_MAP.C **/
int				check_x_y(t_game *game, size_t y, size_t x);
void			set_player_pos(t_game *game, size_t y, size_t x);
int				size_of_map(t_game *game);
int				set_line(t_game *game, char **line, int y);
int				set_limiter(char **line, size_t len);

/**************** IN DIRECTORY FREE *****************/

/** IN FILE FREE.C **/
void			ft_free(char **array, int free_array);
void			ft_free_split(char **array);
void			ft_free_texture(char **texture);
void			ft_free_error_map(t_info_map *info, t_game *game);

/**************** IN DIRECTORY GAME *****************/

/** IN FILE GAME_MLX.C **/

/**	MLX.C	**/
void			deplacement_key(int key_symbole, t_game *game);
int				deal_key(int key_symbole, t_game *game);
int				display_(t_game *game);
void			mlx(t_game *game);
int				blood_link(t_game *game);

/*	INIT.C	*/
void			init_player_orientation(t_game *game, int i, int j);
void			init_player(t_game *game, int i, int j);
void			init_map(t_game *game);
void			init_color(t_game *game);
void			init(t_game *game);

/*	DRAW MINIMAP.C	*/
void			grey_screen(t_game *game);

/*	RAYCASTING.C	*/
void			raycasting(t_game *game);
void			dda_vert(t_game *game, t_raycast *rc);
void			spawn_vert(t_game *game, t_raycast *rc);
void			dda_horiz(t_game *game, t_raycast *rc);
void			spawn_horiz(t_game *game, t_raycast *rc);

/*	RAYCAST_UTILS.C	*/
void			draw_3d(t_game *game, t_raycast *rc);
void			shorter_ray(t_raycast *rc);
void			ray_init(t_game *game, t_raycast *rc, int ray);
int				deter_tox(t_game *game, t_raycast *rc);
void			build_wall(t_game *game, t_moh2i start, t_moh2i end,
					t_raycast *rc);

/*	UTILS.C	*/
void			img_pixel_put(t_data *img, int x, int y, int color);
int				is_wall(t_game *game, t_moh2f pos);
int				around(float nb);
float			shorter_dist(float ax, float ay, float bx, float by);
void			simply_line(t_game *game, t_moh2i start, t_moh2i end,
					int color);

/*	TRASH.C	*/
void			cleaner(t_game *game, int code);
void			tab_clean(char **tab, int size);
void			checking(t_game *game, int orient);

/*	TEXTURE.C */
void			init_texture(t_game *game);
int				convert_hexa_color(int red, int green, int blue);

/*	UTILS_MLX.C	*/
int				close_x(t_game *game);
void			modify(t_game *game, int i, int j);
void			setting_next_pos(int key_symbole, t_game *game, int speed);
void			seeing_in_the_futur_bro(int key_symbole, t_game *game,
					int speed);

#endif