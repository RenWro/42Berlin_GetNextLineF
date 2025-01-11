/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwrobles <rwrobles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:41:48 by rwrobles          #+#    #+#             */
/*   Updated: 2025/01/09 17:04:08 by rwrobles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_checker(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-42);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (-42);
	return (i);
}

char	*ft_putline(char *keep)
{
	char	*r_line;
	int		size;

	if (!keep)
		return (NULL);
	size = ft_checker(keep);
	if (ft_checker(keep) == -42)
		return (ft_strdup(keep));
	r_line = (char *)malloc(sizeof(char) * (size + 2));
	if (!r_line)
		return (NULL);
	ft_memmove(r_line, keep, size);
	r_line[size] = '\n';
	r_line[size + 1] = '\0';
	return (r_line);
}

char	*ft_backup(char *keep)
{
	int	size;
	int	len;

	if (!keep)
		return (NULL);
	len = ft_strlen(keep);
	size = ft_checker(keep);
	if (size == -42 || (size - len) == -1)
		return (free(keep), NULL);
	keep = ft_substr(keep, (size + 1), (len - size - 1));
	return (keep);
}

char	*read_and_store_bonus(int fd, char *keep)
{
	char	*str;
	int		r_read;

	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	while (ft_checker(keep) == -42)
	{
		r_read = read(fd, str, BUFFER_SIZE);
		if (r_read <= 0)
			break ;
		str[r_read] = '\0';
		keep = ft_strjoin(keep, str);
	}
	free(str);
	if (r_read < 0)
	{
		free(keep);
		return (NULL);
	}
	return (keep);
}

char	*get_next_line(int fd)
{
	static char	*keep[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	keep[fd] = read_and_store_bonus(fd, keep[fd]);
	if (!keep[fd])
		return (NULL);
	line = ft_putline(keep[fd]);
	keep[fd] = ft_backup(keep[fd]);
	return (line);
}
