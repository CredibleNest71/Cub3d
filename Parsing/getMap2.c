/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMap2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:18:26 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/24 17:18:42 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	**get_map(int fd, t_game *g)
{
	char	*temp;
	char	*oneline;
	char	**map;

	oneline = read_map(fd);
	if (!oneline)
		return (NULL);
	if (oneline[ft_strlen(oneline) - 1] != '\n')
	{
		temp = ft_strjoin(oneline, "\n");
		free_and_null((void **)&oneline);
		oneline = temp;
	}
	map = make_map(oneline, g);
	free_and_null((void **)&oneline);
	return (map);
}
