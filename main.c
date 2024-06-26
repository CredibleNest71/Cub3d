/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:39:43 by mresch            #+#    #+#             */
/*   Updated: 2024/06/26 16:17:36 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int main(){
    t_tex t;
    t_game g;
    char **map;
    memset(&t, 0, sizeof(t));

    int fd = open("testfile.txt", O_RDONLY);
    get_textures(fd, &t);
    map = getMap(fd, &g);
    if (validate_map(map, &g))
        printf("ERRONIOUS MAP\n");
    print_map(map);
    print_tex(&t);

    
    return (0);
}
