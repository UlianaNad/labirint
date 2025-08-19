/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:45:55 by unadoroz          #+#    #+#             */
/*   Updated: 2025/05/03 12:47:26 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	result;

	if (!s)
		s = "(null)";
	i = 0;
	while (s[i])
	{
		result = write(fd, &s[i], 1);
		if (result < 0)
			return (-1);
		i++;
	}
	return (i);
}
