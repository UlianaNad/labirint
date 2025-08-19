/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:12:14 by unadoroz          #+#    #+#             */
/*   Updated: 2025/05/22 15:27:05 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_line(char *str)
{
	char	*line;
	char	*new_line;

	if (!str)
		return (NULL);
	new_line = ft_strchr(str, '\n');
	if (new_line)
		line = ft_substr(str, 0, ft_strlen(str) - ft_strlen(new_line) + 1);
	else
		line = ft_substr(str, 0, ft_strlen(str));
	return (line);
}

char	*update_saved(char *str)
{
	char	*rest;
	char	*temp;

	if (!str)
		return (NULL);
	temp = ft_strchr(str, '\n');
	if (temp && *(temp + 1))
		rest = ft_strdup(temp + 1);
	else
		rest = NULL;
	free (str);
	return (rest);
}

char	*ft_strjoin_line(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

char	*read_untill_nl(char *saved, int fd, char *buffer)
{	
	ssize_t		bytes_to_read;
	char		*temp;

	bytes_to_read = 1;
	while (!ft_strchr(saved, '\n') && bytes_to_read > 0)
	{
		bytes_to_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_to_read >= 0)
			buffer[bytes_to_read] = '\0';
		else
		{
			free (buffer);
			free(saved);
			return (NULL);
		}
		temp = ft_strjoin_line(saved, buffer);
		if (!temp)
		{
			free(buffer);
			return (NULL);
		}
		free (saved);
		saved = temp;
	}
	return (free(buffer), saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;
char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!saved)
		saved = ft_strdup("");
	saved = read_untill_nl(saved, fd, buffer);
	if (!saved || saved[0] == '\0')
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	line = get_line(saved);
	saved = update_saved(saved);
	return (line);
}