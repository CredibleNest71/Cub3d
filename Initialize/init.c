/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:28:23 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/02 14:42:19 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#include <mlx.h>

void	move_and_draw(t_game *game, int dir)
{
	if (dir == 1)
	{
		move_forward(&game->player);
		draw_player(game, 5);    
    }
	if (dir == 2)
	{	
        move_left(&game->player);
        draw_player(game, 5);    
    }
	if (dir  == 3)
    {
		move_backwards(&game->player);
        draw_player(game, 5);
    }
	if (dir == 4)
    {
		move_right(&game->player);
        draw_player(game, 5);
    }
}

int	handle_keyboard(int button, t_game *game)
{
	if (button == ESC)
		clean_everything(game, 0);
	if (button == W)
		move_and_draw(game, 1);
	if (button == A)
		move_and_draw(game, 2);
	if (button == S)
   		move_and_draw(game, 3);
	if (button == D)
    	move_and_draw(game, 4);
	if (button == LEFT)
		turn_left(&game->player);
	if (button == RIGHT)
		turn_right(&game->player);
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

bool	valid_chars(char c)
{
	if (c != 1 && c != 0 && c != ' ' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W')
		return (false);
	return (true);
}

void	init_player(t_game *game)
{
	draw_player(game, 5);
}

void	init_game(t_game *game)
{
	*game = (t_game){0};	
}

void	init_rest(t_game *game)
{
	game->minilibx.mlx = mlx_init();
	if (!game->minilibx.mlx)
		ft_error(game, "Mlx initialization failed");
	mlx_get_screen_size(game->minilibx.mlx, &game->minilibx.screen_width,
		&game->minilibx.screen_height);
	game->minilibx.window = mlx_new_window(game->minilibx.mlx,
			game->minilibx.screen_width, game->minilibx.screen_height, "Cub3D");
	if (!game->minilibx.window)
		ft_error(game, "Window creation failed");
	init_player(game);
	mlx_hook(game->minilibx.window, 2, 1L << 0, handle_keyboard, game);
	mlx_loop_hook(game->minilibx.mlx, draw_player, game);
}
