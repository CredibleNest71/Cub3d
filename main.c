/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:39:43 by mresch            #+#    #+#             */
/*   Updated: 2024/06/27 14:55:58 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int main(int ac, char **av){
    t_game game;
    if (ac != 2)
		return (ft_putendl_fd("Need 2 arguments", STDERR_FILENO), 1);
    name_check(av);
    init_game(&game);
    t_game g;
    char **map;
    memset(&game.tex, 0, sizeof(game.tex));

    int fd = open("testfile.cub", O_RDONLY);
    get_textures(fd, &game.tex);
    map = getMap(fd, &g);
    if (validate_map(map, &g))
        printf("ERRONIOUS MAP\n");
    print_map(map);
    delete_map(map);
    print_tex(&game.tex);
    delete_tex(&game.tex);
    mlx_loop(game.minilibx.mlx);
    return (0);
}
