/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:28:23 by mesenyur          #+#    #+#             */
/*   Updated: 2024/06/27 08:26:55 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#include <mlx.h>

int	handle_keyboard(int button, t_game *game)
{
	if (button == ESC)
		clean_everything(game, 0);
	if (button == W)
    {
		move_forward(&game->player);
        draw_player(game, 5);    
    }
	if (button == A)
	{	
        move_left(&game->player);
        draw_player(game, 5);    
    }
	if (button == S)
    {
		move_backwards(&game->player);
        draw_player(game, 5);
    }
	if (button == D)
    {
		move_right(&game->player);
        draw_player(game, 5);
    }
	if (button == LEFT)
    {
		turn_left(&game->player);
    }
	if (button == RIGHT)
    {
		turn_right(&game->player);
    }
	return (0);
}

int	draw_player(t_game *game, double size)
{
	int	x;
	int	y;

    y = game->player.py - size / 2;
	while (y < game->player.py + size / 2)
	{
        x = game->player.px - size / 2;
		while ( x < game->player.px + size / 2)
		{
			mlx_pixel_put(game->minilibx.mlx, game->minilibx.window, x, y,
							0xFFFFFF);
            x++;
		}
        y++;
	}
    return (0);
}

void	init_game(t_game *game)
{
	*game = (t_game){0};
	game->minilibx.mlx = mlx_init();
	if (!game->minilibx.mlx)
		ft_error(game, "Mlx initialization failed");
	mlx_get_screen_size(game->minilibx.mlx, &game->minilibx.screen_width,
		&game->minilibx.screen_height);
	game->minilibx.window = mlx_new_window(game->minilibx.mlx,
			game->minilibx.screen_width, game->minilibx.screen_height, "Cub3D");
	if (!game->minilibx.window)
		ft_error(game, "Window creation failed");
	// player movement initialization for now
	game->player.px = (double)game->minilibx.screen_width / 2;
	game->player.py = (double)game->minilibx.screen_height / 2;
	draw_player(game, 5);
	mlx_hook(game->minilibx.window, 2, 1L << 0, handle_keyboard, game);
	mlx_loop_hook(game->minilibx.mlx, draw_player, game);
	// mlx_mouse_hook(game->minilibx.window, handle_no_event, &game);
	// mlx_loop(game->minilibx.mlx);
}
