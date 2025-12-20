/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:10:31 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/13 12:10:32 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philos *philo)
{
	if (get_id(philo) % 2 == 0)
	{
		usleep(500);
		if (has_right_fork(philo))
		{
			pthread_mutex_lock(&philo->right_fork->mtx);
			_write(now(), philo, ACT_2, 18);
		}
		pthread_mutex_lock(&philo->left_fork->mtx);
		if (!has_right_fork(philo))
			philo->pickd_frk = 1;
		_write(now(), philo, ACT_2, 18);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mtx);
		_write(now(), philo, ACT_2, 18);
		pthread_mutex_lock(&philo->right_fork->mtx);
		_write(now(), philo, ACT_2, 18);
	}
}

void	eat(t_philos *philo)
{
	long	time_to_eat;

	if (!is_full(philo) && has_right_fork(philo))
	{
		_write(now(), philo, ACT_1, 11);
		pthread_mutex_lock(&philo->mtx);
		philo->times_ate++;
		time_to_eat = philo->time_to_eat;
		pthread_mutex_unlock(&philo->mtx);
		usleep(ms_to_us(time_to_eat));
		pthread_mutex_lock(&philo->mtx);
		philo->time_last_meal = philo->time_this_meal;
		philo->time_this_meal = now();
		pthread_mutex_unlock(&philo->mtx);
	}
}

void	drop_forks(t_philos *philo)
{
	if (get_id(philo) % 2 == 0)
	{
		if (has_right_fork(philo))
		{
			pthread_mutex_unlock(&philo->left_fork->mtx);
			pthread_mutex_unlock(&philo->right_fork->mtx);
		}
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->mtx);
		pthread_mutex_unlock(&philo->left_fork->mtx);
	}
}

void	_sleep(t_philos *philo)
{
	if (has_right_fork(philo))
	{
		_write(now(), philo, ACT_3, 13);
		usleep(ms_to_us(get_time_to_sleep(philo)));
	}
}

void	think(t_philos *philo)
{
	int	delay;

	pthread_mutex_lock(&philo->mtx);
	if (philo->number_of_philosophers % 2 != 0)
	{
		delay = (philo->time_to_eat - philo->time_to_sleep);
		pthread_mutex_unlock(&philo->mtx);
		if (delay > 0)
			usleep(ms_to_us(delay));
	}
	else
		pthread_mutex_unlock(&philo->mtx);
	if (has_right_fork(philo))
		_write(now(), philo, ACT_4, 13);
}
