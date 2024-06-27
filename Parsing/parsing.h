/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:21:00 by mresch            #+#    #+#             */
/*   Updated: 2024/06/27 08:07:08 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../cube.h"

//contains PATH to matching texture
typedef struct s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
}	t_tex;

int    get_textures(int fd, t_tex *tex);
char	**getMap(int fd);
void	print_map(char **map);
void	print_tex(t_tex *tex);
bool    name_check(char **av);


#endif