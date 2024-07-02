/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:39:43 by mresch            #+#    #+#             */
/*   Updated: 2024/07/02 14:45:28 by mresch           ###   ########.fr       */
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
    memset(&game.tex, 0, sizeof(game.tex));

    int fd = open("testfile.cub", O_RDONLY);
    get_textures(fd, &game.tex);
    game.map = getMap(fd, &game);
    if (validate_map(game.map, &game))
        printf("ERRONIOUS MAP\n");
    print_map(game.map);
    print_tex(&game.tex);
    vision(&game);
    display(&game, vision(&game));
    mlx_loop(game.minilibx.mlx);
    return (0);
}
