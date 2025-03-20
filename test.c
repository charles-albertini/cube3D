#include "cub3d.h"

/**
 * Initialise les paramètres du rayon pour le raycasting
 * @param data Structure principale
 * @param x Position x de la colonne actuelle
 */
static void	init_ray_params(t_data *data, int x)
{
	data->ray.camera_x = 2 * x / (double)data->win_width - 1;
	data->ray.dir_x = data->player.dir_x + data->player.plane_x 
		* data->ray.camera_x;
	data->ray.dir_y = data->player.dir_y + data->player.plane_y 
		* data->ray.camera_x;
	data->ray.map_x = (int)data->player.pos_x;
	data->ray.map_y = (int)data->player.pos_y;
	if (data->ray.dir_x == 0)
		data->ray.deltadist_x = 1e30;
	else
		data->ray.deltadist_x = fabs(1 / data->ray.dir_x);
	if (data->ray.dir_y == 0)
		data->ray.deltadist_y = 1e30;
	else
		data->ray.deltadist_y = fabs(1 / data->ray.dir_y);
}

/**
 * Calcule les distances initiales et les pas pour le DDA
 * @param data Structure principale
 */
static void	calc_step_and_sidedist(t_data *data)
{
	if (data->ray.dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.sidedist_x = (data->player.pos_x - data->ray.map_x) 
			* data->ray.deltadist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.sidedist_x = (data->ray.map_x + 1.0 - data->player.pos_x) 
			* data->ray.deltadist_x;
	}
	if (data->ray.dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.sidedist_y = (data->player.pos_y - data->ray.map_y) 
			* data->ray.deltadist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.sidedist_y = (data->ray.map_y + 1.0 - data->player.pos_y) 
			* data->ray.deltadist_y;
	}
}

/**
 * Exécute l'algorithme DDA pour trouver l'intersection avec un mur
 * @param data Structure principale
 */
static void	perform_dda(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->ray.sidedist_x < data->ray.sidedist_y)
		{
			data->ray.sidedist_x += data->ray.deltadist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.sidedist_y += data->ray.deltadist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->map[data->ray.map_y][data->ray.map_x] == '1')
			hit = 1;
	}
}

/**
 * Calcule la hauteur de la ligne à dessiner et les positions de début et de fin
 * @param data Structure principale
 */
static void	calc_line_height(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.wall_dist = (data->ray.map_x - data->player.pos_x 
				+ (1 - data->ray.step_x) / 2) / data->ray.dir_x;
	else
		data->ray.wall_dist = (data->ray.map_y - data->player.pos_y 
				+ (1 - data->ray.step_y) / 2) / data->ray.dir_y;
	data->ray.line_height = (int)(data->win_height / data->ray.wall_dist);
	data->ray.draw_start = -data->ray.line_height / 2 + data->win_height / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height / 2 + data->win_height / 2;
	if (data->ray.draw_end >= data->win_height)
		data->ray.draw_end = data->win_height - 1;
}

/**
 * Détermine quelle texture utiliser en fonction de l'orientation du mur
 * @param data Structure principale
 * @return Index de la texture à utiliser
 */
static int	get_texture_index(t_data *data)
{
	if (data->ray.side == 0)
	{
		if (data->ray.step_x > 0)
			return (2);  // East
		else
			return (3);  // West
	}
	else
	{
		if (data->ray.step_y > 0)
			return (1);  // South
		else
			return (0);  // North
	}
}

/**
 * Calcule les coordonnées de la texture à utiliser
 * @param data Structure principale
 * @param tex_idx Index de la texture
 */
static void	calc_texture_coords(t_data *data, int tex_idx)
{
	mlx_texture_t	*texture;

	if (tex_idx == 0)
		texture = data->texinfo.north;
	else if (tex_idx == 1)
		texture = data->texinfo.south;
	else if (tex_idx == 2)
		texture = data->texinfo.east;
	else
		texture = data->texinfo.west;
	
	if (data->ray.side == 0)
		data->ray.wall_x = data->player.pos_y + data->ray.wall_dist 
			* data->ray.dir_y;
	else
		data->ray.wall_x = data->player.pos_x + data->ray.wall_dist 
			* data->ray.dir_x;
	data->ray.wall_x -= floor(data->ray.wall_x);
	
	data->texinfo.x = (int)(data->ray.wall_x * (double)texture->width);
	if ((data->ray.side == 0 && data->ray.dir_x > 0) 
		|| (data->ray.side == 1 && data->ray.dir_y < 0))
		data->texinfo.x = texture->width - data->texinfo.x - 1;
	
	data->texinfo.step = 1.0 * texture->height / data->ray.line_height;
	data->texinfo.pos = (data->ray.draw_start - data->win_height / 2 
		+ data->ray.line_height / 2) * data->texinfo.step;
}

/**
 * Dessine une colonne de pixels du mur avec la texture appropriée
 * @param data Structure principale
 * @param image Image MLX42 à modifier
 * @param x Position x de la colonne
 * @param tex_idx Index de la texture
 */
static void	draw_textured_wall(t_data *data, mlx_image_t *image, 
							int x, int tex_idx)
{
	int				y;
	int				tex_y;
	uint32_t		color;
	mlx_texture_t	*texture;

	if (tex_idx == 0)
		texture = data->texinfo.north;
	else if (tex_idx == 1)
		texture = data->texinfo.south;
	else if (tex_idx == 2)
		texture = data->texinfo.east;
	else
		texture = data->texinfo.west;
	
	y = data->ray.draw_start;
	while (y < data->ray.draw_end)
	{
		tex_y = (int)data->texinfo.pos & (texture->height - 1);
		data->texinfo.pos += data->texinfo.step;
		
		color = ((uint32_t *)texture->pixels)[(tex_y * texture->width) 
			+ data->texinfo.x];
		
		mlx_put_pixel(image, x, y, color);
		y++;
	}
}

/**
 * Dessine le plafond et le sol pour une colonne
 * @param data Structure principale
 * @param image Image MLX42 à modifier
 * @param x Position x de la colonne
 */
static void	draw_floor_ceiling(t_data *data, mlx_image_t *image, int x)
{
	int	y;

	y = 0;
	while (y < data->ray.draw_start)
	{
		mlx_put_pixel(image, x, y, data->texinfo.hex_ceiling);
		y++;
	}
	
	y = data->ray.draw_end;
	while (y < data->win_height)
	{
		mlx_put_pixel(image, x, y, data->texinfo.hex_floor);
		y++;
	}
}

/**
 * Effectue le raycasting pour une colonne
 * @param data Structure principale
 * @param image Image MLX42 à modifier
 * @param x Position x de la colonne
 */
static void	cast_ray(t_data *data, mlx_image_t *image, int x)
{
	int	tex_idx;

	init_ray_params(data, x);
	calc_step_and_sidedist(data);
	perform_dda(data);
	calc_line_height(data);
	
	tex_idx = get_texture_index(data);
	calc_texture_coords(data, tex_idx);
	
	draw_floor_ceiling(data, image, x);
	draw_textured_wall(data, image, x, tex_idx);
}

/**
 * Fonction principale de rendu qui est appelée à chaque frame
 * @param param Pointeur vers les données (cast en t_data *)
 */
void	render_frame(void *param)
{
	t_data		*data;
	mlx_image_t	*image;
	int			x;

	data = (t_data *)param;
	
	// Si le joueur n'a pas bougé, pas besoin de redessiner
	if (!data->player.has_moved)
		return ;
	
	// Créer une nouvelle image pour ce frame
	image = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!image)
		return ;
	
	// Effectuer le raycasting pour chaque colonne de l'écran
	x = 0;
	while (x < data->win_width)
	{
		cast_ray(data, image, x);
		x++;
	}
	
	// Afficher l'image
	if (mlx_image_to_window(data->mlx, image, 0, 0) < 0)
	{
		mlx_delete_image(data->mlx, image);
		return ;
	}
	
	data->player.has_moved = 0;
}

/**
 * Initialise les paramètres du joueur selon sa direction initiale
 * @param data Structure principale
 */
void	init_player_direction(t_data *data)
{
	if (data->player.dir == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (data->player.dir == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
	else if (data->player.dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (data->player.dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

/**
 * Configure les hooks MLX42 pour les mouvements et la fermeture de fenêtre
 * @param data Structure principale
 */
void	setup_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &render_frame, data);
	// Ajoutez ici vos hooks pour les mouvements et la fermeture de la fenêtre
}

/**
 * Initialise le raycasting
 * @param data Structure principale
 * @return 0 en cas de succès, -1 en cas d'erreur
 */
int	init_raycasting(t_data *data)
{
	// Initialiser les dimensions de la fenêtre
	data->win_width = WIN_WIDTH;
	data->win_height = WIN_WEIGHT;
	
	// Initialiser la position et la direction du joueur
	init_player_direction(data);
	
	// Initialiser les couleurs du sol et du plafond
	data->texinfo.hex_floor = (data->texinfo.floor[0] << 24) | 
							(data->texinfo.floor[1] << 16) | 
							(data->texinfo.floor[2] << 8) | 0xFF;
	data->texinfo.hex_ceiling = (data->texinfo.ceiling[0] << 24) | 
							(data->texinfo.ceiling[1] << 16) | 
							(data->texinfo.ceiling[2] << 8) | 0xFF;
	
	// Indiquer que le joueur a bougé pour forcer le premier rendu
	data->player.has_moved = 1;
	
	// Configurer les hooks
	setup_hooks(data);
	
	return (0);
}