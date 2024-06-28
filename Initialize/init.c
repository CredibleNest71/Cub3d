/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:28:23 by mesenyur          #+#    #+#             */
/*   Updated: 2024/06/28 18:28:57 by mesenyur         ###   ########.fr       */
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

void	get_player_location(t_game *game, double *x, double *y)
{
	int		column;
	int		row;

	column = 0;
	printf("%d\n", game->map_width);
	printf("%d\n", game->map_height);
	while (column < game->map_width)
	{
		row = 0;
		while (row < game->map_height)
		{
			if ((game->map[row][column] == 'N' || game->map[row][column] == 'E'
			|| game->map[row][column] == 'W' || game->map[row][column] == 'S'))
			{
				*x = row;
				*y = column;
				printf("x is: %lf y is: %lf\n", game->player.px, game->player.py);
				return ;
			}
			row++;
		}
		column++;
	}
	*x = -1;
	*y = -1;
}

void	init_player(t_game *game)
{
	get_player_location(game, &game->player.px, &game->player.py);
	game->player.px = (double)game->minilibx.screen_width / 2;
	game->player.py = (double)game->minilibx.screen_height / 2;
	draw_player(game, 5);
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
	// init_player(game);
	mlx_hook(game->minilibx.window, 2, 1L << 0, handle_keyboard, game);
	mlx_loop_hook(game->minilibx.mlx, draw_player, game);
}

// int wall_check(t_game *game, int x, int y, char **map)
// {
// 	if ((x == 0 || y == 0 || x == game->map_width - 1 || y == game->map_height - 1) && map[x][y] != '1')
// 		return (1);
// 	return (0);
// }

// static void	control_map(t_game *game, char **map)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	while (map[x])
// 	{
// 		y = 0;
// 		while (map[x][y])
// 		{
// 			if (ft_strchr("01NSEW ", map[x][y]) == NULL)
// 				ft_error(game, "Invalid character in map.");
// 			if (wall_check(game, x, y, map) == 1)
// 				ft_error(game, "Map is not closed");
// 			y++;
// 		}
// 		x++;
// 	}
// }