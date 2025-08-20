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

int	ft_putptr(void *ptr)
{
	unsigned long	address;
	int				count;
	int				result;

	address = (unsigned long) ptr;
	count = 0;
	if (address == 0)
	{
		result = ft_putstr_fd("(nil)", 1);
		if (result < 0)
			return (-1);
		return (result);
	}
	result = ft_putstr_fd("0x", 1);
	if (result < 0)
		return (-1);
	count += result;
	result = ft_puthex(address, 'x');
	if (result < 0)
		return (-1);
	count += result;
	return (count);
}