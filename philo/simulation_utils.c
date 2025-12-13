/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:21:08 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/13 12:21:11 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_all_full(t_data *data)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->philos[i]->mtx);
		full = data->philos[i]->full;
		pthread_mutex_unlock(&data->philos[i]->mtx);
		if (!full)
			return (0);
		i++;
	}
	return (1);
}

int	has_right_fork(t_philos *philo)
{
	t_fork	*right_fork;

	pthread_mutex_lock(&philo->mtx);
	right_fork = philo->right_fork;
	pthread_mutex_unlock(&philo->mtx);
	if (right_fork)
		return (1);
	return (0);
}

void	check_times_ate(t_philos *philo)
{
	pthread_mutex_lock(&philo->mtx);
	if (philo->number_of_eats > 0)
	{
		if (philo->number_of_eats == philo->times_ate)
		{
			pthread_mutex_unlock(&philo->mtx);
			_write(now(), philo, ACT_5, 9);
			pthread_mutex_lock(&philo->mtx);
			philo->full = 1;
		}
	}
	pthread_mutex_unlock(&philo->mtx);
}

int	check_if_hungry(t_philos *philo)
{
	pthread_mutex_lock(&philo->mtx);
	if (!philo->alive)
		return (pthread_mutex_unlock(&philo->mtx), 1);
	if (!philo->full)
	{
		if ((now() - philo->time_this_meal) >= philo->time_to_die)
		{
			pthread_mutex_unlock(&philo->mtx);
			_write(now(), philo, ACT_6, 9);
			pthread_mutex_lock(&philo->mtx);
			philo->alive = 0;
			pthread_mutex_unlock(&philo->mtx);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->mtx);
	return (0);
}
