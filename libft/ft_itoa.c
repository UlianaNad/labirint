/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:12:02 by unadoroz          #+#    #+#             */
/*   Updated: 2025/05/03 12:18:46 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	num_len(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
		n = -n;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb_len;
	long	num;
	char	*num_res;

	nb_len = num_len(n);
	num = n;
	num_res = (char *)ft_calloc(nb_len + 1, sizeof(char));
	if (!num_res)
		return (NULL);
	if (num == 0)
		num_res[0] = '0';
	if (num < 0)
	{
		num_res[0] = '-';
		num = -num;
	}
	while (nb_len > 0 && num != 0)
	{
		nb_len--;
		num_res[nb_len] = (num % 10) + '0';
		num /= 10;
	}
	return (num_res);
}
