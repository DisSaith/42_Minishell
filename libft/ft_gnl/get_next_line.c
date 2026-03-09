/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:46:54 by acohaut           #+#    #+#             */
/*   Updated: 2026/02/13 11:35:31 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	while (s1 && s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	if (s1)
		free(s1);
	return (result);
}

char	*take_line(char *file)
{
	char	*line;
	size_t	size;
	size_t	i;

	if (!file)
		return (NULL);
	size = 0;
	i = 0;
	while (file[size] && file[size] != '\n')
		size++;
	line = malloc(sizeof(char) * (size + 2));
	if (!line)
		return (NULL);
	while (file[i] && file[i] != '\n')
	{
		line[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_file(int fd, char *file)
{
	char	*buffer;
	ssize_t	nb_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	nb_read = 1;
	while (!(ft_strchr(file, '\n')) && nb_read > 0)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(buffer);
			free(file);
			return (NULL);
		}
		buffer[nb_read] = '\0';
		file = ft_strjoin(file, buffer);
	}
	free(buffer);
	return (file);
}

char	*sup_line_static(char *file)
{
	char	*nw_file;
	size_t	i;

	i = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (!file[i])
	{
		free(file);
		return (NULL);
	}
	nw_file = ft_strdup(&file[i + 1]);
	free(file);
	return (nw_file);
}

char	*get_next_line(int fd)
{
	static char	*file[FD_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	file[fd] = read_file(fd, file[fd]);
	if (!file[fd])
		return (NULL);
	if (file[fd][0] == '\0')
	{
		free(file[fd]);
		file[fd] = NULL;
		return (NULL);
	}
	line = take_line(file[fd]);
	file[fd] = sup_line_static(file[fd]);
	return (line);
}
