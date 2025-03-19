/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:55:35 by calberti          #+#    #+#             */
/*   Updated: 2025/03/19 21:38:56 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <memory.h>
# include <fcntl.h>
# include <stdint.h>
# include <errno.h>

# define BUFFER_SIZE 50



typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;


typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;


typedef struct s_mapinf
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_mapinf;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texinfo;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_mapinf	mapinf;
	char		**map;
	t_player	player;
	t_ray		ray;
	int			**texture_pixels;
	int			**textures;
	t_texinfo	texinfo;
	// t_img		minimap;
}	t_data;




typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;


// parsing

typedef struct s_texture
{
	char	*path;
	void	*img;
	int		width;
	int		height;
}		t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	value;
}		t_color;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}		t_map;

typedef struct s_config
{
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
}		t_config;

//PARSING
int		is_empty_line(char *line);
int		ft_arrlen(char **arr);
void	free_array(char **arr);
int		parse_file(char *filename, t_config *config);
int		parse_line(char *line, t_config *config);
int		parse_texture(char *path, t_texture *texture);
int		parse_color(char *str, t_color *color);
int		parse_cub_file(char *filename, t_config *config);
int		is_all_num(char *str);
char	*trim_left(char *str);
void	flood_fill_mark(char **map, int x, int y, t_config *config);
void	mark_outer_spaces(char **map, t_config *config);
int		ft_strlen_width(char *str);
int		pars_position(char *line, t_config *config);
int		find_player(t_config *config, int j, int i, char c);
char	**make_normalize(t_config *config, char **normalize, int i, int j);
char	*ft_strdup_tab_to_space(char *src);

//MAP
int		is_map_line(char *line);
int		start_map_parsing(char *first_line, t_config *config);
int		parse_map_line(char *line, t_config *config);
int		validate_config(t_config *config);

//CLEAN
void	clean_config(t_config *config);
void	clean_line(char *line);
int		clean_copy(char **copy, int i);

//INIT
void	init_config(t_config *config);

//VALID_MAP
int		validate_map(t_config *config);
int		normalize_map(t_config *config);
int		find_player_position(t_config *config);
int		check_map_borders(t_config *config);
int		flood_fill(char **map, int x, int y, t_config *config);

//init exec

void	init_ray(t_ray *ray);
void	init_player(t_player *player);

// a revoir 
void	init_map(t_mapinf *mapinfo);
void	init_img_clean(t_img *img);
void	init_data(t_data *data);


#endif