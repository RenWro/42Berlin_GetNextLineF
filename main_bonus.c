/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwrobles <rwrobles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:23:39 by rwrobles          #+#    #+#             */
/*   Updated: 2025/01/09 17:21:19 by rwrobles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	main(void)
{
	char	*line;
	int		fd1;
	int		fd2;
	int		i;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("Error opening files");
		return (1);
	}
	printf("\nReading from test1.txt:\n");
	i = 5;
	while (i-- > 0)
	{
		line = get_next_line(fd1);
		if (line)
		{
			printf("File 1: |%s", line);
			free(line);
		}
	}
	printf("\nReading from test2.txt:\n");
	i = 5;
	while (i-- > 0)
	{
		line = get_next_line(fd2);
		if (line)
		{
			printf("File 2: |%s", line);
			free(line);
		}
	}
	close(fd1);
	close(fd2);
	return (0);
}
