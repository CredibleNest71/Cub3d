/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:40:56 by mresch            #+#    #+#             */
/*   Updated: 2024/06/24 16:08:26 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

static	char **identify(t_tex *tex, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (&tex->NO);
	if (!ft_strncmp(line, "SO", 2))
		return (&tex->SO);
	if (!ft_strncmp(line, "EA", 2))
		return (&tex->EA);
	if (!ft_strncmp(line, "WE", 2))
		return (&tex->WE);
	// if (!ft_strncmp(line, "F", F))
	// 	return (&tex->NO);
	// if (!ft_strncmp(line, "C", C))
		return (&tex->NO);
	return (NULL);
}

static	int	add_to_textures(t_tex *tex, char *line)
{
	char	**curr;
	char	*path;
	
	curr = identify(tex, line);
	if (!curr)
		return (0);
	path = ft_strchr(line, '.');
	if (!path)
		return (0);
}


int    get_textures(int fd, t_tex *tex)
{
    char    *line;
    int     progress;

    progress = 1;
    while (progress)
    {
        line = get_next_line(fd);
        if (!line)
            return (1);
        add_to_textures(tex, line);
    }
}
