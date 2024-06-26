/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:56:58 by mesenyur          #+#    #+#             */
/*   Updated: 2024/06/26 14:04:14 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void    clean_everything(t_game *game)
{
    if (game && game->tex)
        // free_textures();
        free_and_null((void **)&game->tex);
    if (game && game->player)
        // free_player();
        free_and_null((void **)&game->player);
    if (game)
        // free_game();
        free_and_null((void **)&game);
}

int ft_error(t_game *game, char *s)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    clean_everything(game);
    if (s)
		ft_putendl_fd(s, STDERR_FILENO);
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
