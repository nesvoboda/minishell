/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:20:28 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/28 16:20:53 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_digits(int n)
{
	int digits;

	if (n == 0)
		return (1);
	digits = n < 0 ? 1 : 0;
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char		*ft_itoa(int n)
{
	char			*result;
	int				digits;
	int				i;
	int				stop;
	long long int	nbr;

	digits = count_digits(n);
	i = digits;
	stop = ((n < 0) ? 1 : 0);
	if (n < 0)
		nbr = n == -2147483648 ? 2147483648 : -n;
	else
		nbr = n;
	if (!(result = malloc(sizeof(char) * (digits + 2))))
		return (NULL);
	result[digits + 1] = '\0';
	while (i > stop)
	{
		result[i--] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (stop == 1)
		result[1] = '-';
	return (result);
}
