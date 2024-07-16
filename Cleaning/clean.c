/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:56:58 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/16 13:39:35 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#include <mlx.h>

void    clean_everything(t_game *game, int ret)
{
    int i;
    
    i = 0;
    if (!game)
        return ;
   
    while (i < game->map_height)
    {
        free_and_null((void **)&game->map[i]);
        i++;
    }
    if (game->map)
        free_and_null((void **)&game->map);
    free_game_tex(game);
    if (game->info && game->info->image)
    {
        mlx_destroy_image(game->minilibx.mlx, game->info->image);
        free_and_null((void **)&game->info->image);
    }
    if (game->minilibx.window)
        mlx_destroy_window(game->minilibx.mlx, game->minilibx.window);
    if (game->minilibx.mlx)
    {
        mlx_destroy_display(game->minilibx.mlx);
        free_and_null((void **)&game->minilibx.mlx);
    }
    exit(ret);
}

int ft_error(t_game *game, char *s)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    if (s)
		ft_putendl_fd(s, STDERR_FILENO);
    free_game_tex(game);
    clean_everything(game, 1);
	exit(1);
}

void	free_game_tex(t_game *game)
{
	if (game->tex.C)
		free_and_null((void **)&game->tex.C);
	if (game->tex.F)
		free_and_null((void **)&game->tex.F);
	if (game->tex.NO)
		free_and_null((void **)&game->tex.NO);
	if (game->tex.SO)
		free_and_null((void **)&game->tex.SO);
	if (game->tex.WE)
		free_and_null((void **)&game->tex.WE);
	if (game->tex.EA)
		free_and_null((void **)&game->tex.EA);
}