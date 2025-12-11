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

void	take_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mtx);
		_write(now(), philo->id, ACT_2, 18);
		pthread_mutex_lock(&philo->left_fork->mtx);
		_write(now(), philo->id, ACT_2, 18);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mtx);
		_write(now(), philo->id, ACT_2, 18);
		pthread_mutex_lock(&philo->right_fork->mtx);
		_write(now(), philo->id, ACT_2, 18);
	}
}

void	eat(t_philos *philo)
{
	long	time_now;

	time_now = now();
	pthread_mutex_lock(&philo->mtx);
	_write(time_now, philo->id, ACT_1, 11);
	philo->times_ate++;
	philo->time_last_meal = philo->time_this_meal;
	philo->time_this_meal = time_now;
	pthread_mutex_unlock(&philo->mtx);
	usleep(philo->time_to_eat);
}

void	drop_forks(t_philos *philo)
{	
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->left_fork->mtx);
		pthread_mutex_unlock(&philo->right_fork->mtx);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->mtx);
		pthread_mutex_unlock(&philo->left_fork->mtx);
	}
}

void	_sleep(t_philos *philo)
{
	_write(now(), philo->id, ACT_3, 13);
	usleep(philo->time_to_sleep);
}

void	think(t_philos *philo)
{
	_write(now(), philo->id, ACT_4, 13);
}
