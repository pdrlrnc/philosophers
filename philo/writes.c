/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:21:05 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/09 17:21:06 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mtx	*write_lock(void)
{
	static t_mtx	mtx;

	return (&mtx);
}

void	_write(long time, t_philos *philo, char *str, int strlen)
{
	pthread_mutex_lock(write_lock());
	if (is_alive(philo))
	{
		ft_putnbr_fd(time, STDOUT_FILENO);
		write(STDOUT_FILENO, " ", 1);
		ft_putnbr_fd(get_id(philo) + 1, STDOUT_FILENO);
		write(STDOUT_FILENO, str, strlen);
	}
	pthread_mutex_unlock(write_lock());
}

void	_write_debug_forks(long time, t_philos *philo, t_fork *fork)
{
	pthread_mutex_lock(write_lock());
	if (is_alive(philo))
	{
		ft_putnbr_fd(time, STDOUT_FILENO);
		write(STDOUT_FILENO, " ", 1);
		ft_putnbr_fd(get_id(philo) + 1, STDOUT_FILENO);
		write(STDOUT_FILENO, " took fork with id: ", 20);
		ft_putnbr_fd(fork->id, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
	pthread_mutex_unlock(write_lock());

}
