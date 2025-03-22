/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:11:22 by calberti          #+#    #+#             */
/*   Updated: 2025/03/22 14:42:07 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void draw_wall(int x, t_config *config, mlx_image_t *img)
{
	t_ray *ray = &config->data->ray;
    int y;
    int tex_x;
    int tex_y;
    uint32_t color;
    mlx_texture_t *texture;

    // Déterminer quelle texture utiliser selon la direction du mur
    if (ray->side == 0 && ray->dir_x > 0)
        texture = config->textu->east;
    else if (ray->side == 0 && ray->dir_x <= 0)
        texture = config->textu->west;
    else if (ray->side == 1 && ray->dir_y > 0)
        texture = config->textu->south;
    else
        texture = config->textu->north;

    // Calculer la position x sur la texture
    tex_x = (int)(ray->wall_x * texture->width);
    if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
        tex_x = texture->width - tex_x - 1;

    // Pour chaque pixel de la colonne de mur
    double step = 1.0 * texture->height / ray->line_height;
    double tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;

    // Dessiner le plafond
    y = 0;
    while (y < ray->draw_start)
    {
        mlx_put_pixel(img, x, y, config->ceiling.value);
        y++;
    }

    // Dessiner le mur avec texture
    while (y < ray->draw_end)
    {
        tex_y = (int)tex_pos & (texture->height - 1);
        tex_pos += step;

        // Obtenir la couleur du pixel de la texture
        uint8_t *pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
        color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
        
        // Assombrir légèrement si c'est un mur côté Y (effet d'ombre)
        if (ray->side == 1)
            color = ((color >> 1) & 0x7F7F7F7F) | (color & 0xFF);
        
        mlx_put_pixel(img, x, y, color);
        y++;
    }

    // Dessiner le sol
    while (y < WIN_HEIGHT)
    {
        mlx_put_pixel(img, x, y, config->floor.value);
        y++;
    }
}

void render_frame(t_config *config)
{
    // Vérifier si une image existe déjà
    if (config->current_image)
    {
        // Supprimer l'image existante
        mlx_delete_image(config->mlx, config->current_image);
        config->current_image = NULL; // Réinitialiser le pointeur
    }

    // Créer une nouvelle image
    mlx_image_t *img = mlx_new_image(config->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!img)
        return;

    // Stocker la nouvelle image dans config
    config->current_image = img;

    config->data->map = config->map.grid;

    for (int x = 0; x < WIN_WIDTH; x++)
    {
        config->data->ray.camera_x = 2 * x / (double)WIN_WIDTH - 1;
        config->data->ray.dir_x = config->data->player.dir_x + config->data->player.plane_x * config->data->ray.camera_x;
        config->data->ray.dir_y = config->data->player.dir_y + config->data->player.plane_y * config->data->ray.camera_x;

        config->data->ray.map_x = (int)config->data->player.pos_x;
        config->data->ray.map_y = (int)config->data->player.pos_y;
        config->data->ray.deltadist_x = fabs(1 / config->data->ray.dir_x);
        config->data->ray.deltadist_y = fabs(1 / config->data->ray.dir_y);

        ft_calc_step_and_side_dist(config);
        perf_dda(config);
        calc_wall_height(config);
        draw_wall(x, config, img);
    }

    // Afficher l'image
    mlx_image_to_window(config->mlx, img, 0, 0);
}