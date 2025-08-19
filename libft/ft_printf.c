/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:12:07 by unadoroz          #+#    #+#             */
/*   Updated: 2025/06/12 14:27:17 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_conversion(char specifier, va_list args)
{
	int	result;

	if (specifier == 'c')
		result = ft_putchar_fd(va_arg(args, int), 1);
	else if (specifier == 's')
		result = ft_putstr_fd(va_arg(args, char *), 1);
	else if (specifier == 'p')
		result = ft_putptr(va_arg(args, void *));
	else if (specifier == 'd' || specifier == 'i')
		result = ft_putnbr_fd(va_arg(args, int), 1);
	else if (specifier == 'u')
		result = ft_putuns(va_arg(args, unsigned int));
	else if (specifier == 'X' || specifier == 'x')
		result = ft_puthex (va_arg (args, unsigned int), specifier);
	else if (specifier == '%')
		result = ft_putchar_fd('%', 1);
	else
		result = 0;
	return (result);
}

static int	helper_func(const char **format, va_list *args)
{
	int	result;

	if (**format == '%' && *(*format + 1))
	{
		(*format)++;
		result = check_conversion(**format, *args);
		if (result < 0)
			return (-1);
	}
	else
	{
		result = write(1, *format, 1);
		if (result < 0)
			return (-1);
	}
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		result;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		result = helper_func(&format, &args);
		if (result < 0)
		{
			va_end(args);
			return (-1);
		}
		count += result;
		format++;
	}
	va_end(args);
	return (count);
}