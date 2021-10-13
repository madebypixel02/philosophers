/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:52:44 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/13 11:55:00 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft_tools.h"

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (count);
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

int	ft_putchar_fd(char c, int fd)
{
	return ((int)write(fd, &c, 1));
}

int	ft_putnbr_fd(long unsigned n, int fd)
{
	int	count;

	count = 0;
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		count += ft_putchar_fd(n + '0', fd);
	return (count);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		return ((int)write(fd, s, ft_strlen(s)));
	return (0);
}

int	ft_putnchar_fd(char c, int fd, int n)
{
	int	count;

	count = 0;
	while (n-- > 0)
		count += (int)write(fd, &c, 1);
	return (count);
}
