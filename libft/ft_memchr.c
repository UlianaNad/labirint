/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:25:50 by unadoroz          #+#    #+#             */
/*   Updated: 2025/05/03 12:21:50 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		i;
	unsigned char		b;

	i = 0;
	b = (unsigned char)c;
	ptr = (const unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == b)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}
