/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:14 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/03/10 13:39:05 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		counter;

	counter = 0;
	if (n == -2147483648)
		return (write (fd, "-2147483648", 11));
	if (n < 0)
	{
		write(fd, "-", 1);
		counter++;
		n = -n;
	}
	if (n >= 10)
	{
		counter += ft_putnbr_fd(n / 10, fd);
	}
	c = n % 10 + '0';
	write (fd, &c, 1);
	counter++;
	return (counter);
}

