/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:56:58 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/01 12:28:32 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#include <mlx.h>

void    clean_everything(t_game *game, int ret)
{
    if (!game)
        return ;
    if (game->minilibx.window)
        mlx_destroy_window(game->minilibx.mlx, game->minilibx.window);
    if (game->minilibx.mlx)
        free_and_null((void **)&game->minilibx.mlx); 
    exit(ret);
}

int ft_error(t_game *game, char *s)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    if (s)
		ft_putendl_fd(s, STDERR_FILENO);
    clean_everything(game, 1);
	exit(1);
}

void    free_and_null(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        ptr = NULL;
    }
}
