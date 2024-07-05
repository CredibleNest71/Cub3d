/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:28:23 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/05 15:15:02 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#include <mlx.h>

int	handle_mouse(int button, int x, int y, void *game)
{
	// int	x;
	// int	y;
	t_game	*g = (t_game *) game;
	y++;
	button++;
	// mlx_mouse_get_pos(g->minilibx.mlx, g->minilibx.window, &x, &y);
	g->player.rad += (500 - x);
	mlx_mouse_move(g->minilibx.mlx, g->minilibx.window, 500, 500);
	return (0);
}
int		main_display_loop(t_game *g)
{
	t_info	*info;
	void	*oldimg;

	oldimg = g->minilibx.img;
	info = create_buffer(g);
	vision(g, info);
	mlx_put_image_to_window(g->minilibx.mlx, g->minilibx.window, info->image, 0, 0);
	if (oldimg)
	{
		mlx_destroy_image(g->minilibx.mlx, oldimg);
		free(oldimg);
	}
	char str[60];
	sprintf(str, "ANGLE: %f\nX:%f\nY:%f", g->player.rad, g->player.px, g->player.py);
	mlx_string_put(g->minilibx.mlx, g->minilibx.window, 40, 40, 0, str);
	free(info);
	return (0);
}

void	move_and_draw(t_game *game, int dir)
{
	if (dir == 1)
	{
		move_forward(&game->player, game);
		draw_player(game, 5);    
    }
	if (dir == 2)
	{	
        move_left(&game->player, game);
        draw_player(game, 5);    
    }
	if (dir  == 3)
    {
		move_backwards(&game->player, game);
        draw_player(game, 5);
    }
	if (dir == 4)
    {
		move_right(&game->player, game);
        draw_player(game, 5);
    }
}
int	handle_keyboard(int button, t_game *game)
{
	//printf("%d\n", button);
	if (button == ESC)
		clean_everything(game, 0);
	else if (button == W)
		move_and_draw(game, 1);
	else if (button == A)
		move_and_draw(game, 2);
	else if (button == S)
   		move_and_draw(game, 3);
	else if (button == D)
    	move_and_draw(game, 4);
	else if (button == LEFT)
		turn_left(&game->player);
	else if (button == RIGHT)
		turn_right(&game->player);
	else if (button == Q)
		game->player.fov -= 2;
	else if (button == E)
		game->player.fov += 2;
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
	mlx_mouse_move(game->minilibx.mlx, game->minilibx.window, 500, 500);
	mlx_mouse_hook(game->minilibx.window, handle_mouse, game);
	// mlx_loop_hook(game->minilibx.mlx, draw_player, game);
	mlx_loop_hook(game->minilibx.mlx, main_display_loop, game);
}
