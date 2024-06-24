/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:40:56 by mresch            #+#    #+#             */
/*   Updated: 2024/06/24 16:54:15 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

static	char **identify(t_tex *tex, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && !tex->NO)
		return (&tex->NO);
	if (!ft_strncmp(line, "SO", 2) && !tex->SO)
		return (&tex->SO);
	if (!ft_strncmp(line, "EA", 2) && !tex->EA)
		return (&tex->EA);
	if (!ft_strncmp(line, "WE", 2) && !tex->WE)
		return (&tex->WE);
	if (!ft_strncmp(line, "F", 1) && !tex->F)
		return (&tex->F);
	if (!ft_strncmp(line, "C", 1) && !tex->C)
		return (&tex->C);
	write(2, "Error: couldnt identify!", 24);
	return (NULL);
}

static	int	add_to_textures(t_tex *tex, char *line)
{
	char	**curr;
	char	*found;
	char	*path;
	
	curr = identify(tex, line);
	if (!curr)
		return (free(line), 0);
	found = ft_strchr(line, '.');
	if (!found)
		return (free(line), 0);
	path = ft_strdup(found);
	if (!path)
		return (free(line), 0);
	*curr = path;
	return (1);
}


int    get_textures(int fd, t_tex *tex)
{
    char    *line;

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            return (1);
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
        if (!add_to_textures(tex, line))
			return (write(2, "An Error occurred\n", 18));
    }
	return 0;
}
