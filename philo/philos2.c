/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:47:24 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/09 14:47:26 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mtx);
		pthread_mutex_lock(&philo->left_fork->mtx);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mtx);
		pthread_mutex_lock(&philo->right_fork->mtx);
	}
	pthread_mutex_lock(write_lock());
	ft_putnbr_fd(philo->id, STDOUT_FILENO);
	write(STDOUT_FILENO, ACT_1, 11);
	pthread_mutex_unlock(write_lock());
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork->mtx);
	pthread_mutex_unlock(&philo->left_fork->mtx);
}

void	_sleep(t_philos *philo)
{
	pthread_mutex_lock(write_lock());
	ft_putnbr_fd(philo->id, STDOUT_FILENO);
	write(STDOUT_FILENO, " is sleeping\n", 13);
	pthread_mutex_unlock(write_lock());
	usleep(philo->time_to_sleep);
}

void	think(t_philos *philo)
{
	(void)philo;
	pthread_mutex_lock(write_lock());
	ft_putnbr_fd(philo->id, STDOUT_FILENO);
	write(STDOUT_FILENO, " is thinking\n", 13);
	pthread_mutex_unlock(write_lock());
	usleep(1);
}
