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
	if (get_id(philo) % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mtx);
		if (!sim_has_ended(philo))
			_write(now(), philo, ACT_2, 18);
		pthread_mutex_lock(&philo->left_fork->mtx);
		if (!sim_has_ended(philo))
			_write(now(), philo, ACT_2, 18);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mtx);
		if (!sim_has_ended(philo))
			_write(now(), philo, ACT_2, 18);
		pthread_mutex_lock(&philo->right_fork->mtx);
		if (!sim_has_ended(philo))
			_write(now(), philo, ACT_2, 18);
	}
}

void	eat(t_philos *philo)
{
	long	time_now;
	long	time_to_eat;
	
	if (!is_full(philo))
	{
		time_now = now();
		pthread_mutex_lock(&philo->mtx);
		if (!(*philo->ended_sim))
		{
			pthread_mutex_unlock(&philo->mtx);
			_write(time_now, philo, ACT_1, 11);
			pthread_mutex_lock(&philo->mtx);
		}
		philo->times_ate++;
		philo->time_last_meal = philo->time_this_meal;
		philo->time_this_meal = time_now;
	       	time_to_eat = philo->time_to_eat;
		pthread_mutex_unlock(&philo->mtx);
		smart_usleep(philo, ms_to_us(time_to_eat));
	}
}

void	drop_forks(t_philos *philo)
{	
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
	if (!sim_has_ended(philo))
		_write(now(), philo, ACT_3, 13);
	smart_usleep(philo, ms_to_us(get_time_to_sleep(philo)));
}

void	think(t_philos *philo)
{
	if (!sim_has_ended(philo))
		_write(now(), philo, ACT_4, 13);
}
