/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:39:43 by mresch            #+#    #+#             */
/*   Updated: 2024/06/27 08:10:59 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int main(int ac, char **av){
    t_game game;
    if (ac != 2)
		return (ft_putendl_fd("Need 2 arguments", STDERR_FILENO), 1);
    name_check(av);
    init_game(&game);
    char **map;
    memset(&game.tex, 0, sizeof(game.tex));

    int fd = open("testfile.txt", O_RDONLY);
    get_textures(fd, &game.tex);
    map = getMap(fd);

    print_map(map);
    print_tex(&game.tex);
    mlx_loop(game.minilibx.mlx);

    return (0);
}
