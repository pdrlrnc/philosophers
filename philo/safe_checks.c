/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:24:09 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/13 12:24:09 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_id(t_philos *philo)
{
	int	id;

	pthread_mutex_lock(&philo->mtx);
	id = philo->id;
	pthread_mutex_unlock(&philo->mtx);
	return (id);
}

int	is_full(t_philos *philo)
{
	int	full;

	pthread_mutex_lock(&philo->mtx);
	full = philo->full;
	pthread_mutex_unlock(&philo->mtx);
	return (full);
}

int	is_alive(t_philos *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->mtx);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->mtx);
	return (alive);
}

int	get_time_to_sleep(t_philos *philo)
{
	int	time_to_sleep;

	pthread_mutex_lock(&philo->mtx);
	time_to_sleep = philo->time_to_sleep;
	pthread_mutex_unlock(&philo->mtx);
	return (time_to_sleep);
}
