/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:53:33 by unadoroz          #+#    #+#             */
/*   Updated: 2025/05/30 11:37:11 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned long n, char format)
{
	char	*hex;
	int		count;
	int		result;

	count = 0;
	if (format == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (n >= 16)
	{
		result = ft_puthex(n / 16, format);
		if (result < 0)
			return (-1);
		count += result;
	}
	result = ft_putchar_fd(hex[n % 16], 1);
	if (result < 0)
		return (-1);
	count += result;
	return (count);
}