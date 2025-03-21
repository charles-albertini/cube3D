/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:41:13 by axburin-          #+#    #+#             */
/*   Updated: 2025/03/21 15:36:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_calc_delta_dist(t_config *config)
{
	config->data->ray.map_x =(int)config->data->player.pos_x;
	config->data->ray.map_y = (int)config->data->player.pos_y;

	config->data->ray.deltadist_x = fabs(1 / config->data->ray.dir_x);
	config->data->ray.deltadist_y = fabs(1 / config->data->ray.dir_y);
}

void	ft_calc_step_and_side_dist(t_config *config)
{
	if(config->data->ray.dir_x < 0)
	{
		config->data->ray.step_x = -1;
		config->data->ray.sidedist_x = (config->data->player.pos_x - config->data->ray.map_x) * config->data->ray.deltadist_x;
	}
	else
	{
		config->data->ray.step_x = 1;
		config->data->ray.sidedist_x =(config->data->ray.map_x + 1.0 - config->data->player.pos_x) * config->data->ray.deltadist_x;
	}
	if(config->data->ray.dir_y < 0)
	{
		config->data->ray.step_y = -1;
		config->data->ray.sidedist_y = (config->data->player.pos_y - config->data->ray.map_y) * config->data->ray.deltadist_y;
	}
	else
	{
		config->data->ray.step_y = 1;
		config->data->ray.sidedist_y = (config->data->ray.map_y + 1.0 - config->data->player.pos_y) * config->data->ray.deltadist_y;
	}
}

void perf_dda(t_config *config)
{
    int hit = 0;
    t_ray *ray = &config->data->ray;
    char **map = config->data->map;
    int map_height = config->map.height;
    int map_width = config->map.width;

    while (!hit)
    {
        if (ray->sidedist_x < ray->sidedist_y)
        {
            ray->sidedist_x += ray->deltadist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->sidedist_y += ray->deltadist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        
        // Vérifier si on est hors des limites de la carte
        if (ray->map_y < 0 || ray->map_y >= map_height || 
            ray->map_x < 0 || ray->map_x >= map_width)
        {
            hit = 1;
            break;
        }
        
        // Vérifier si le pointeur de ligne existe et si on a touché un mur
        if (map && ray->map_y >= 0 && ray->map_y < map_height &&
            ray->map_x >= 0 && ray->map_x < map_width &&
            map[ray->map_y][ray->map_x] == '1')
        {
            hit = 1;
        }
    }
}

void calc_wall_height(t_config *config)
{
    if (config->data->ray.side == 0)
        config->data->ray.wall_dist = (config->data->ray.map_x - config->data->player.pos_x + (1 - config->data->ray.step_x) / 2) / config->data->ray.dir_x;
    else
        config->data->ray.wall_dist = (config->data->ray.map_y - config->data->player.pos_y + (1 - config->data->ray.step_y) / 2) / config->data->ray.dir_y;
    
    config->data->ray.line_height = (int)(WIN_HEIGHT / config->data->ray.wall_dist);
    config->data->ray.draw_start = -config->data->ray.line_height / 2 + WIN_HEIGHT / 2;
    
    // Définir draw_end aussi
    config->data->ray.draw_end = config->data->ray.line_height / 2 + WIN_HEIGHT / 2;
    
    if (config->data->ray.draw_start < 0)
        config->data->ray.draw_start = 0;
    if (config->data->ray.draw_end >= WIN_HEIGHT)
        config->data->ray.draw_end = WIN_HEIGHT - 1;
    
    if (config->data->ray.side == 0)
        config->data->ray.wall_x = config->data->player.pos_y + config->data->ray.wall_dist * config->data->ray.dir_y;
    else
        config->data->ray.wall_x = config->data->player.pos_x + config->data->ray.wall_dist * config->data->ray.dir_x;
    
    config->data->ray.wall_x -= floor(config->data->ray.wall_x);
}

// ca c est chat gpt j sais pas si a marche

void	ft_cast_rays(t_config *config)
{
	int x;  // Pour chaque colonne de l'écran

	x = 0;
	while (x < WIN_WIDTH)
	{

		config->data->ray.camera_x = 2 * x / (double)WIN_WIDTH -1; 
		config->data->ray.dir_x = config->data->player.dir_x + config->data->player.plane_x * config->data->ray.camera_x;
		config->data->ray.dir_y = config->data->player.dir_y + config->data->player.plane_y * config->data->ray.camera_x;

		ft_calc_delta_dist(config);

		ft_calc_step_and_side_dist(config);

		perf_dda(config);

		calc_wall_height(config);

		// 6. Dessiner ou afficher le mur (cette étape serait généralement dans une fonction de rendu)
		// Ici, vous pouvez dessiner le mur avec les calculs effectués pour chaque rayon
		// Exemple d'affichage (vous devrez remplacer par votre propre méthode de rendu)
		//draw_wall(&ray, x);  // La fonction draw_wall doit dessiner le mur pour la colonne x
		x++;
	}
}
