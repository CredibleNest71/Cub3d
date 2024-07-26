/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:39:43 by mresch            #+#    #+#             */
/*   Updated: 2024/07/26 15:28:35 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_game(t_game *game)
{
	*game = (t_game){0};
	game->minilibx.mlx = mlx_init();
	if (!game->minilibx.mlx)
		ft_error(game, "Mlx initialization failed");
}

int	main(int ac, char **av)
{
	t_game	game;
	int		fd;

	if (ac != 2)
		return (ft_putendl_fd("Need 2 arguments", STDERR_FILENO), 1);
	name_check(av);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(NULL, "File not found"));
	game.fd = fd;
	init_game(&game);
	if (get_textures(fd, &game.tex, &game))
		return (ft_error(&game, "ERROR IN TEXTURES\n"));
	game.map = get_map(fd, &game);
	if (!game.map)
		return (ft_error(&game, "ERROR IN MAP\n"));
	if (validate_map(game.map, &game))
		return (ft_error(&game, "ERRONIOUS MAP\n"));
	init_rest(&game);
	mlx_loop(game.minilibx.mlx);
	clean_everything(&game, 0);
	close(fd);
	return (0);
}
