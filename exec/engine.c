/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:11:35 by calberti          #+#    #+#             */
/*   Updated: 2025/03/21 15:39:58 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void continuous_render(void *param)
{
    t_config *config = (t_config *)param;
    t_player *player = &config->data->player;
    
    // Si le joueur a bougé, mettre à jour sa position
    if (player->has_moved || player->move_x != 0 || player->move_y != 0 || player->rotate != 0)
    {
		
        move_player(config);
		// Mettre à jour la position du joueur
    	update_player_position(config);
        player->has_moved = 0;
        
        // Rafraîchir l'affichage
        render_frame(config);
    }
}