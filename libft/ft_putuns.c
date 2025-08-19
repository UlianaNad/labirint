/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:54:32 by unadoroz          #+#    #+#             */
/*   Updated: 2025/06/13 17:05:10 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putuns(unsigned int n)
{
	int		count;
	char	digit;
	int		result;

	count = 0;
	result = 0;
	if (n > 9)
	{
		result = ft_putuns(n / 10);
		if (result < 0)
			return (-1);
		count += result;
	}
	digit = n % 10 + '0';
	result = ft_putchar_fd(digit, 1);
	if (result < 0)
		return (-1);
	count += result;
	return (count);
}