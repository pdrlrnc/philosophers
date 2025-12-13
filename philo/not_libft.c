/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:34:44 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/13 12:34:45 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_str_isdigit(char *str)
{
	if (*str == '-' || *str == '+')
	{
		if (ft_strlen(str) == 1)
			return (0);
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
		str++;
	return (*str == '\0');
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*(str + len))
		len++;
	return (len);
}

int	ft_check_for_overflow(char *nb)
{
	char	*max_int;
	int		i;

	max_int = "2147483647";
	if (ft_strlen(nb) > 10)
		return (1);
	if (ft_strlen(nb) < 10)
		return (0);
	i = 0;
	while (*(nb + i))
	{
		if (*(nb + i) > *(max_int + i))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
	int	minus;

	result = 0;
	minus = 1;
	i = 0;
	while (ft_isspace(*(nptr + i)))
		i++;
	if (*(nptr + i) == '+' || *(nptr + i) == '-')
	{
		if (*(nptr + i) == '-')
			minus = -1;
		i++;
	}
	while (*(nptr + i) >= '0' && *(nptr + i) <= '9')
	{
		result *= 10;
		result += (*(nptr + i) - '0');
		i++;
	}
	return (result * minus);
}

void	ft_putnbr_fd(long n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}
