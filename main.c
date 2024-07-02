/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:39:43 by mresch            #+#    #+#             */
/*   Updated: 2024/07/02 14:12:36 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing/parsing.h"
#include "cube.h"

int	main(int ac, char **av)
{
  t_game  game;
	int     fd;

	if (ac != 2)
		return (ft_putendl_fd("Need 2 arguments", STDERR_FILENO), 1);
	name_check(av);
	init_game(&game);
	fd = open(av[1], O_RDONLY);
	get_textures(fd, &game.tex);
	game.map = getMap(fd, &game); // we could height and width of map
	if (!game.map)
		ft_error(&game, "Map isnt valid");	
	printf("%d : %d\n", game.map_height, game.map_width);
	if (validate_map(game.map, &game))
		ft_error(&game, "ERRONIOUS MAP\n");
	init_rest(&game);
	print_map(game.map);
	delete_map(game.map);
	print_tex(&game.tex);
	delete_tex(&game.tex);
	mlx_loop(game.minilibx.mlx);
	printf("hop");
	return (0);
}
