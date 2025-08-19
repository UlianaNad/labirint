/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:32:07 by unadoroz          #+#    #+#             */
/*   Updated: 2025/05/03 14:32:44 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp_dest;
	unsigned char	*temp_src;
	size_t			i;

	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	temp_dest = (unsigned char *) dest;
	temp_src = (unsigned char *) src;
	i = 0;
	if (temp_dest > temp_src)
	{
		while (n-- > 0)
		{
			temp_dest[n] = temp_src[n];
		}
	}
	else
	{
		while (n-- > 0)
		{
			temp_dest[i] = temp_src[i];
			i++;
		}
	}
	return (dest);
}
