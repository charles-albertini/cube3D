#include "../cub3D.h"

void continuous_render(void *param)
{
    t_config *config = (t_config *)param;
    
    // S'assurer que config->data est initialisé
    if (!config || !config->data)
        return;
        
    t_player *player = &config->data->player;
    
    // Si le joueur a bougé ou si des touches de mouvement sont activées
    if (player->has_moved || player->move_x != 0 || player->move_y != 0 || player->rotate != 0)
    {
        move_player(config);
        player->has_moved = 0;
        
        // Rafraîchir l'affichage
        render_frame(config);
    }
}

// Ajouter cette fonction pour initialiser le moteur de jeu
void start_game_engine(t_config *config)
{
    // Allouer et initialiser la structure data si ce n'est pas déjà fait
    if (!config->data)
    {
        config->data = malloc(sizeof(t_data));
        if (!config->data)
            return;
        
        // Initialisation des valeurs par défaut
        memset(config->data, 0, sizeof(t_data));
    }
    
    // Initialiser le joueur
    init_player_from_config(config);
    
    // Configurer le hook pour la fonction de rendu continu
    mlx_loop_hook(config->mlx, &continuous_render, config);
    
    // Configurer le hook pour les touches
    mlx_key_hook(config->mlx, &my_key_hook, config);
    
    // Faire un premier rendu
    render_frame(config);
}

void init_data(t_config *config)
{
    if (!config->data)
    {
        config->data = malloc(sizeof(t_data));
        if (!config->data)
            return;
            
        memset(config->data, 0, sizeof(t_data));
    }
    
    // Initialiser la carte
    config->data->map = config->map.grid;
    
    // Initialiser les dimensions de la fenêtre
    config->data->win_width = WIN_WIDTH;
    config->data->win_height = WIN_HEIGHT;
    
    // Initialiser le joueur
    config->data->player.pos_x = config->map.player_x + 0.5;
    config->data->player.pos_y = config->map.player_y + 0.5;
    config->data->player.has_moved = 0;
    config->data->player.move_x = 0;
    config->data->player.move_y = 0;
    config->data->player.rotate = 0;
    
    // Initialiser la direction et le plan de caméra selon l'orientation du joueur
    init_player_from_config(config);
    
    // Initialiser les données du rayon
    init_ray(config);
}

void init_ray(t_config *config)
{
    memset(&config->data->ray, 0, sizeof(t_ray));
}

int main(int argc, char **argv)
{
    t_config config;
    
    // Vérifier les arguments
    if (argc != 2)
    {
        printf("Error: Usage: %s <map.cub>\n", argv[0]);
        return (1);
    }
    
    // Initialiser la configuration
    init_config(&config);
    
    // Parser le fichier de configuration
    if (!parse_cub_file(argv[1], &config))
    {
        clean_config(&config);
        return (1);
    }
    
    // Initialiser la fenêtre MLX
    config.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
    if (!config.mlx)
    {
        clean_config(&config);
        return (1);
    }
    
    // Initialiser les données
    init_data(&config);
    
    // Charger les textures
    get_textures(&config);
    
    // Démarrer le moteur de jeu
    start_game_engine(&config);
    
    // Lancer la boucle principale
    mlx_loop(config.mlx);
    
    // Nettoyer et quitter
    clean_config(&config);
    return (0);
}