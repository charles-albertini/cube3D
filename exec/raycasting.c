/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:41:13 by axburin-          #+#    #+#             */
/*   Updated: 2025/03/20 21:02:01 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_calc_delta_dist(t_ray *ray, t_player *player)
{
	ray->map_x =(int)player->pos_x;
	ray->map_y = (int)player->pos_y;

	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

void	ft_calc_step_and_side_dist(t_ray *ray, t_player *player)
{
	if(ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x =(ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if(ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

void	perf_dda(t_ray *ray, t_data *data)
{
	while(1)
	{
		if(ray->sidedist_x < ray->deltadist_y)
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
		if(data->map[ray->map_x][ray->map_y] == '1')
			break;
	}
}

void	calc_wall_height(t_ray *ray, t_player *player)
{
	if(ray->side == 0)
	{
		ray->wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	}
	else
		ray->wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if(ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if(ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist *ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);	// FLOOR ?
}

// ca c est chat gpt j sais pas si a marche

void	ft_cast_rays(t_data *data, t_player *player)
{
	int x;  // Pour chaque colonne de l'écran
	t_ray ray;  // Structure de données pour le rayon

	x = 0;
	while (x < WIN_WIDTH)
	{

		ray.camera_x = 2 * x / (double)WIN_WIDTH -1; 
		ray.dir_x = player->dir_x + player->plane_x * ray.camera_x;
		ray.dir_y = player->dir_y + player->plane_y * ray.camera_x;

		ft_calc_delta_dist(&ray, player);

		ft_calc_step_and_side_dist(&ray, player);

		perf_dda(&ray, data);

		calc_wall_height(&ray, player);

		// 6. Dessiner ou afficher le mur (cette étape serait généralement dans une fonction de rendu)
		// Ici, vous pouvez dessiner le mur avec les calculs effectués pour chaque rayon
		// Exemple d'affichage (vous devrez remplacer par votre propre méthode de rendu)
		//draw_wall(&ray, x);  // La fonction draw_wall doit dessiner le mur pour la colonne x
		x++;
	}
}
