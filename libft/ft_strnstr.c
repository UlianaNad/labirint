/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:22 by unadoroz          #+#    #+#             */
/*   Updated: 2025/05/03 14:34:04 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	const unsigned char	*big_str;
	const unsigned char	*lit_str;
	size_t				i;
	size_t				r;

	i = 0;
	big_str = (const unsigned char *)big;
	lit_str = (const unsigned char *)little;
	if (lit_str[i] == '\0')
	{
		return ((char *)(big_str));
	}
	while (big_str[i] && i < n)
	{
		r = 0;
		while (big_str[i + r] && lit_str[r]
			&& big_str[i + r] == lit_str[r] && (i + r) < n)
			r++;
		if (lit_str[r] == '\0')
			return ((char *)(big_str + i));
		i++;
	}
	return (0);
}
