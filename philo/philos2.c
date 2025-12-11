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
	check_if_hungry(philo);
	if (get_id(philo) % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mtx);
		_write(now(), get_id(philo), ACT_2, 18);
		pthread_mutex_lock(&philo->left_fork->mtx);
		_write(now(), get_id(philo), ACT_2, 18);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mtx);
		_write(now(), get_id(philo), ACT_2, 18);
		pthread_mutex_lock(&philo->right_fork->mtx);
		_write(now(), get_id(philo), ACT_2, 18);
	}
}

void	eat(t_philos *philo)
{
	long	time_now;
	
	check_if_hungry(philo);
	if (!is_full(philo))
	{
		time_now = now();
		pthread_mutex_lock(&philo->mtx);
		_write(time_now, philo->id, ACT_1, 11);
		philo->times_ate++;
		philo->time_last_meal = philo->time_this_meal;
		philo->time_this_meal = time_now;
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->mtx);
	}
}

void	drop_forks(t_philos *philo)
{	
	check_if_hungry(philo);
	if (get_id(philo) % 2 == 0)
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
	check_if_hungry(philo);
	_write(now(), get_id(philo), ACT_3, 13);
	usleep(get_time_to_sleep(philo));
}

void	think(t_philos *philo)
{
	check_if_hungry(philo);
	_write(now(), get_id(philo), ACT_4, 13);
}
