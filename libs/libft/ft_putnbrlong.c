/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrlong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:14:37 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/06 11:38:15 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrlong(unsigned int n, int fd)
{
	char	c;
	int		counter;

	counter = 0;
	if (n >= 10)
	{
		counter = ft_putnbr_fd(n / 10, fd);
	}
	c = n % 10 + '0';
	counter++;
	write (fd, &c, 1);
	return (counter);
}
