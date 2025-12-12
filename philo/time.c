/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:54:19 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/09 10:54:23 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	start(void)
{
	struct timeval	tv;
	static long	now;

	if (now == 0)
	{
		if (gettimeofday(&tv, NULL) != 0)
			return (-1);
		now = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	}
	return (now);
}

long	now(void)
{
	struct timeval tv;
	long	now;
	
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	now = tv.tv_sec * 1000L + tv.tv_usec/ 1000L;
	return (now - start());
}

long	ms_to_us(long ms)
{
	return (ms * 1000);
}

void	smart_usleep(t_philos *philo, long us)
{
	long	increment;
	long	mini_sleep;
	long	target;

	increment = 0;
	mini_sleep = 1000;
	target = ms_to_us(now()) + us;
	while (increment < us)
	{
		if (check_if_hungry(philo))
			break ;
		if ((us - increment) < mini_sleep)
			mini_sleep = us - increment;
		usleep(mini_sleep);
		increment += mini_sleep;
	}
	pthread_mutex_lock(&philo->mtx);
	philo->debt = ms_to_us(now()) - target;
	pthread_mutex_unlock(&philo->mtx);
}
