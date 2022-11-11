/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgingast <jgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:16:32 by jgingast          #+#    #+#             */
/*   Updated: 2022/02/08 20:36:15 by jgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *temp)
{
	char	*buffer;
	int	len;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	len = 1;
	while (!ft_strchr(temp, '\n') && len != 0)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[len] = '\0';
		temp = ft_strjoin(temp, buffer);
	}
	free(buffer);
	return (temp);
}

char	*get_line(char *temp)
{
	int	i;
	char	*line;

	i = 0;
	if (!temp[i])
		return (NULL);
	while (temp[i] && temp[i] != '\n')
		i++;
	line = (char*)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*save(char *temp)
{
	int	i;
	int	c;
	char	*line;

	i = 0;
	c = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
	{
		free(temp);
		return (NULL);
	}
	line = (char*)malloc(sizeof(char) * (ft_strlen(temp) - i + 1));
	if (!line)
		return (NULL);
	i++;
	while (temp[i])
		line[c++] = temp[i++];
	line[c] = '\0';
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	temp = ft_read(fd, temp);
	if (!temp)
		return (NULL);
	line = get_line(temp);
	temp = save(temp);
	return (line);
}
