/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:21:00 by mresch            #+#    #+#             */
/*   Updated: 2024/07/02 12:17:38 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
//contains PATH to matching texture

# include <stdbool.h>

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
void	print_map(char **map);
void	print_tex(t_tex *tex);
bool    name_check(char **av);
void	delete_map(char **map);
void	delete_tex(t_tex *tex);

#endif