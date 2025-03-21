/*
Maintenant que je vois ces fonctions, je comprends mieux pourquoi vous rencontrez des problèmes de performance. Voici les principales causes et des solutions :
Problèmes identifiés

Création répétée d'images - Dans render_frame(), vous créez une nouvelle image à chaque frame avec mlx_new_image(). C'est très coûteux en mémoire et en performances.
Accumulation d'images - Vous n'effacez jamais les anciennes images, mais ajoutez simplement de nouvelles images à la fenêtre avec mlx_image_to_window().
Raycasting inefficace - Vous effectuez tous les calculs de raycasting pour chaque pixel de l'écran à chaque frame, même quand rien ne bouge.
Résolution élevée - 1920x1080 signifie 2 millions de pixels à traiter à chaque frame, ce qui est énorme sans optimisation.*/

// Variables globales à ajouter dans votre struct t_config
mlx_image_t *render_img; // Image persistante pour le rendu

// Modifiez init_all pour créer l'image une seule fois
void init_all(t_config *config)
{
    // Autres initialisations...
    
    // Créer l'image de rendu une seule fois
    config->render_img = mlx_new_image(config->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!config->render_img)
    {
        fprintf(stderr, "Error: Failed to create render image\n");
        exit(EXIT_FAILURE);
    }
    
    // L'ajouter à la fenêtre une seule fois
    mlx_image_to_window(config->mlx, config->render_img, 0, 0);
}

// Modifiez render_frame pour utiliser l'image existante
void render_frame(t_config *config)
{
    mlx_image_t *img = config->render_img;
    
    // Effacer l'image en remplissant avec une couleur (optionnel)
    // memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
    
    // Structure player et data pour le raycasting
    config->data->map = config->map.grid;
    
    // Cast des rayons et dessiner pour chaque colonne de l'écran
    for (int x = 0; x < WIN_WIDTH; x += 1) // Vous pouvez même essayer x += 2 pour tester
    {
        // Calculer la direction du rayon pour cette colonne
        config->data->ray.camera_x = 2 * x / (double)WIN_WIDTH - 1;
        config->data->ray.dir_x = config->data->player.dir_x + config->data->player.plane_x * config->data->ray.camera_x;
        config->data->ray.dir_y = config->data->player.dir_y + config->data->player.plane_y * config->data->ray.camera_x;
        
        // Calcul de delta_dist
        config->data->ray.map_x = (int)config->data->player.pos_x;
        config->data->ray.map_y = (int)config->data->player.pos_y;
        config->data->ray.deltadist_x = fabs(1 / config->data->ray.dir_x);
        config->data->ray.deltadist_y = fabs(1 / config->data->ray.dir_y);
        
        // Calcul de step et side_dist
        ft_calc_step_and_side_dist(config);
        
        // DDA Algorithm
        perf_dda(config);
        
        // Calcul de la hauteur du mur
        calc_wall_height(config);
        
        // Dessiner le mur
        draw_wall(x, config, img);
    }
}

// Optimisez continuous_render pour limiter le framerate
void continuous_render(void *param)
{
    static double last_time = 0;
    double current_time;
    t_config *config = (t_config *)param;
    t_player *player = &config->data->player;
    
    // Limiter le framerate à ~60 FPS
    current_time = mlx_get_time();
    if (current_time - last_time < 0.016) // ~60 FPS (1/60 ≈ 0.016)
        return;
    
    last_time = current_time;
    
    // Mettre à jour la position du joueur et rendre la frame
    update_player_position(config);
    render_frame(config);
}

/*
Autres optimisations suggérées

Réduisez temporairement la résolution - Changez WIN_WIDTH à 960 et WIN_HEIGHT à 540 pour les tests.
Optimisez draw_wall - Précalculez certaines valeurs et évitez les multiplications/divisions répétées.
Limitez les vérifications de collision - Ne vérifiez que les cases adjacentes au joueur.
Implémentez une technique de "frame skip" - Ne rendez pas toutes les frames si le système est trop lent.
Optimisez les textures - Utilisez des textures plus petites ou préchargez-les dans un format plus efficace.
Utilisez des distances manhattaniennes pour les collisions à distance, plutôt que des calculs de distances euclidiennes.

En implémentant ces changements, vous devriez constater une amélioration significative des performances. Si le problème persiste, vous pourriez envisager de profiler votre code pour identifier d'autres goulets d'étranglement.
*/