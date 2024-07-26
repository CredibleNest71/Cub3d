/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:28:23 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/26 15:21:47 by mesenyur         ###   ########.fr       */
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
	else if (button == SHIFT)
		game->keys.shift = 0;
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
	else if (button == SHIFT)
		game->keys.shift = 1;
	else if (button == E)
		game->keys.e = 1;
	return (0);
}

int	handle_mouse(int x, int y, void *game)
{
	t_game	*g;
	double	diff;

	g = (t_game *)game;
	(void)y;
	if (x == g->minilibx.screen_width / 2 || y == g->minilibx.screen_height / 2)
		return (1);
	diff = (double)g->minilibx.screen_width / 2 - x;
	diff = diff * fabs(diff);
	g->player.rad += map((t_m){diff, -pow((double)g->minilibx.screen_width / 2,
				2), pow((double)g->minilibx.screen_width / 2, 2), 1, -1});
	mlx_mouse_move(g->minilibx.mlx, g->minilibx.window, g->minilibx.screen_width
		/ 2, g->minilibx.screen_height / 2);
	return (0);
}

// call vision with 1 for fisheye 0 for without
int	main_display_loop(t_game *g)
{
	t_info	*info;
	void	*oldimg;

	move(g);
	oldimg = g->minilibx.img;
	info = create_buffer(g);
	if (!info)
		ft_error(g, "Buffer creation failed");
	vision(g, info, 1);
	mlx_put_image_to_window(g->minilibx.mlx, g->minilibx.window, info->image, 0,
		0);
	if (oldimg)
	{
		mlx_destroy_image(g->minilibx.mlx, oldimg);
		free_and_null((void **)&oldimg);
	}
	destroy_buffer(g, info);
	return (0);
}

void	init_rest(t_game *game)
{
	mlx_get_screen_size(game->minilibx.mlx, &game->minilibx.screen_width,
		&game->minilibx.screen_height);
	game->minilibx.window = mlx_new_window(game->minilibx.mlx,
			game->minilibx.screen_width, game->minilibx.screen_height, "Cub3D");
	if (!game->minilibx.window)
		ft_error(game, "Window creation failed");
	mlx_hook(game->minilibx.window, 17, 0L, ft_close, game);
	mlx_hook(game->minilibx.window, 6, 1L << 6, handle_mouse, game);
	mlx_hook(game->minilibx.window, 2, 1L << 0, key_down, game);
	mlx_hook(game->minilibx.window, 3, 1L << 1, key_up, game);
	// mlx_mouse_hide(game->minilibx.mlx, game->minilibx.window);
	mlx_mouse_move(game->minilibx.mlx, game->minilibx.window,
		game->minilibx.screen_height / 2, 500);
	mlx_loop_hook(game->minilibx.mlx, main_display_loop, game);
}
