/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:59:05 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/06 15:59:06 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ended_sim(t_data *data)
{
	int	ended_sim;

	pthread_mutex_lock(&data->mtx);
	ended_sim = data->ended_sim;
	pthread_mutex_unlock(&data->mtx);
	return (ended_sim);
}

void	simulate(t_data *data)
{
	int		i;

	data->started_sim_time = start();
	i = 0;
	thread(&data->ref, ref, data, CREATE);
	while (i < data->number_of_philosophers)
	{
		thread(&data->philos[i]->thread, run, data->philos[i], CREATE);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		thread(&data->philos[i]->thread, NULL, NULL, JOIN);
		i++;
	}
}

void	*ref(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->mtx);
	while (!data->ended_sim)
	{
		data->ended_sim = check_if_dead(data);
		pthread_mutex_unlock(&data->mtx);
		usleep(100);
		pthread_mutex_lock(&data->mtx);
	}
	pthread_mutex_unlock(&data->mtx);
	return (NULL);
}

int	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (data->philos[i])
	{
		if (!is_alive(data->philos[i]))
		{
			kill_all(data);
			return (1);
		}
		i++;
	}
	return (0);
}

void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (data->philos[i])
	{
		kill_philo(data->philos[i]);
		i++;
	}
}


void	*run(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!is_full(philo) && is_alive(philo))
	{
		if (is_alive(philo))
			take_forks(philo);
		if (is_alive(philo))
			check_if_hungry(philo);
		if (is_alive(philo))
			eat(philo);
		if (is_alive(philo))
			check_times_ate(philo);
		drop_forks(philo);
		if (!is_full(philo))
		{
			if (is_alive(philo))
				_sleep(philo);
			if (is_alive(philo))
				think(philo);
		}
	}
	return (NULL);
}

void	check_times_ate(t_philos *philo)
{
	pthread_mutex_lock(&philo->mtx);
	if (philo->number_of_eats > 0)
	{
		if (philo->number_of_eats == philo->times_ate)
		{
			_write(now(), philo->id, ACT_5, 9);
			philo->full = 1;
		}
	}
	pthread_mutex_unlock(&philo->mtx);
}

void	check_if_hungry(t_philos *philo)
{
	pthread_mutex_lock(&philo->mtx);
	if (philo->alive && !philo->full)
	{
		pthread_mutex_lock(write_lock());
		pthread_mutex_unlock(write_lock());
		if ((philo->time_this_meal - philo->time_last_meal) > philo->time_to_die)
		{
			_write(now(), philo->id, ACT_6, 9);
			philo->alive = 0;
		}
	}
	pthread_mutex_unlock(&philo->mtx);
}

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

	usleep(1000);
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

void	kill_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->mtx);
	philo->alive = 0;
	pthread_mutex_unlock(&philo->mtx);
}
