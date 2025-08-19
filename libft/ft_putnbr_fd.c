/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:43:58 by unadoroz          #+#    #+#             */
/*   Updated: 2025/05/03 12:45:26 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		res;
	int		temp;

	res = 0;
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		temp = ft_putchar_fd('-', fd);
		if (temp < 0)
			return (-1);
		res += temp;
		n = -n;
	}
	if (n > 9)
	{
		temp = ft_putnbr_fd(n / 10, fd);
		if (temp < 0)
			return (-1);
		res += temp;
	}
	temp = ft_putchar_fd((n % 10 + '0'), fd);
	if (temp < 0)
		return (-1);
	return (res + temp);
}
