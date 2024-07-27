/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:39:43 by mresch            #+#    #+#             */
/*   Updated: 2024/07/27 15:17:25 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_game(t_game *game)
{
	*game = (t_game){0};
	game->minilibx.mlx = mlx_init();
	if (!game->minilibx.mlx)
		ft_error(game, "Mlx initialization failed", true);
	game->fd = -1;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (ft_putendl_fd("Need 2 arguments", STDERR_FILENO), 1);
	name_check(av);
	init_game(&game);
	game.fd = open(av[1], O_RDONLY);
	if (game.fd < 0)
		return (ft_error(&game, "File not found", true));
	if (get_textures(game.fd, &game.tex, &game))
		return (ft_error(&game, "Error in textures", true));
	game.map = get_map(game.fd, &game);
	if (!game.map)
		return (ft_error(&game, "Error in map", true));
	if (validate_map(game.map, &game))
		return (ft_error(&game, "Erroneous map", true));
	init_rest(&game, false);
	mlx_loop(game.minilibx.mlx);
	clean_everything(&game, 0);
	if (game.fd != -1)
		close(game.fd);
	return (0);
}
