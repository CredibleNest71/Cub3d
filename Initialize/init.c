/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:28:23 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/16 10:29:26 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#include <mlx.h>

int	key_up(int button, t_game *game)
{
	if (button == W)
		game->keys.w = 0;
	else if (button == A)
		game->keys.a = 0;
	else if (button == S)
   		game->keys.s = 0;
	else if (button == D)
    	game->keys.d = 0;
	else if (button == LEFT)
		game->keys.left = 0;
	else if (button == RIGHT)
		game->keys.right = 0;
	else if (button == Q)
		game->keys.q = 0;
	else if (button == E)
		game->keys.e = 0;
	return (0);
}

int	key_down(int button, t_game *game)
{
	if (button == ESC)
		clean_everything(game, 0);
	if (button == W)
		game->keys.w = 1;
	else if (button == A)
		game->keys.a = 1;
	else if (button == S)
   		game->keys.s = 1;
	else if (button == D)
    	game->keys.d = 1;
	else if (button == LEFT)
		game->keys.left = 1;
	else if (button == RIGHT)
		game->keys.right = 1;
	else if (button == Q)
		game->keys.q = 1;
	else if (button == E)
		game->keys.e = 1;
	return (0);
}

int	handle_mouse(int x, int y, void *game)
{
	t_game	*g = (t_game *) game;
	(void) y;
	double	diff;

	if (x == g->minilibx.screen_width / 2 || y == g->minilibx.screen_height / 2)
		return (1);
	diff = (double)g->minilibx.screen_width / 2 - x;
	diff = diff * fabs(diff);
	//g->player.rad += map((t_m){x, 0, g->minilibx.screen_width, -0.06, 0.06});
	g->player.rad += map((t_m){diff, -pow((double)g->minilibx.screen_width / 2, 2), pow((double)g->minilibx.screen_width / 2, 2), 0.06, -0.06});
	mlx_mouse_move(g->minilibx.mlx, g->minilibx.window, g->minilibx.screen_width / 2, g->minilibx.screen_height / 2);
	return (0);
}
int		main_display_loop(t_game *g)
{
	t_info	*info;
	void	*oldimg;

	move(g);
	oldimg = g->minilibx.img;
	info = create_buffer(g);
	if (!info)
		ft_error(g, "Buffer creation failed");
	vision(g, info);
	mlx_put_image_to_window(g->minilibx.mlx, g->minilibx.window, info->image, 0, 0);
	if (oldimg)
	{
		mlx_destroy_image(g->minilibx.mlx, oldimg);
		free_and_null((void **)&oldimg);
	}
	// char str[60];
	// sprintf(str, "ANGLE: %f\nX:%f\nY:%f", g->player.rad, g->player.px, g->player.py);
	// mlx_string_put(g->minilibx.mlx, g->minilibx.window, 40, 40, 0, str);
	destroy_buffer(g, info);
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

void	init_game(t_game *game)
{
	*game = (t_game){0};
}

int	ft_close(t_game *game)
{
	clean_everything(game, 0);
	return (0);
}

void	init_rest(t_game *game)
{
	game->minilibx.mlx = mlx_init(); // free
	if (!game->minilibx.mlx)
		ft_error(game, "Mlx initialization failed");
	mlx_get_screen_size(game->minilibx.mlx, &game->minilibx.screen_width,
		&game->minilibx.screen_height);
	game->minilibx.window = mlx_new_window(game->minilibx.mlx,
			game->minilibx.screen_width, game->minilibx.screen_height, "Cub3D");
	if (!game->minilibx.window)
		ft_error(game, "Window creation failed");
	// mlx_hook(game->minilibx.window, 2, 1L << 0, handle_keyboard, game);
	mlx_hook(game->minilibx.window, 17, 0L, ft_close, game);
	mlx_hook(game->minilibx.window, 6, 1L << 6, handle_mouse, game);
	mlx_hook(game->minilibx.window, 2, 1L << 0, key_down, game);
	mlx_hook(game->minilibx.window, 3, 1L << 1, key_up, game);
	mlx_mouse_hide(game->minilibx.mlx, game->minilibx.window); // auskommentiert waehrend leak check
	mlx_mouse_move(game->minilibx.mlx, game->minilibx.window, game->minilibx.screen_height / 2, 500);
	// mlx_loop_hook(game->minilibx.mlx, draw_player, game);
	mlx_loop_hook(game->minilibx.mlx, main_display_loop, game);
}
