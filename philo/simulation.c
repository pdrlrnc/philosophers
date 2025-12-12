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

	print_data_vars(data);
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
	thread(&data->ref, NULL, NULL, JOIN);
}

void	*ref(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->mtx);
	while (!data->ended_sim)
	{
		data->ended_sim = check_if_dead(data);
		if (data->ended_sim)
		{
			kill_all(data);
			pthread_mutex_unlock(write_lock());
		}
		else
			data->ended_sim = check_if_all_full(data);
	}
	pthread_mutex_unlock(&data->mtx);
	return (NULL);
}

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

void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->philos[i]->mtx);
		data->philos[i]->alive = 0;
		pthread_mutex_unlock(&data->philos[i]->mtx);
		i++;
	}
}

int	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (data->philos[i])
	{
		if (check_if_hungry(data->philos[i]))
		{
			data->ended_sim = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	*run(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!is_full(philo) && is_alive(philo))
	{
		if (!sim_has_ended(philo))
			take_forks(philo);
		if (!sim_has_ended(philo))
			check_if_hungry(philo);
		if (!sim_has_ended(philo))
			eat(philo);
		if (!sim_has_ended(philo))
			check_times_ate(philo);
		drop_forks(philo);
		if (!is_full(philo))
		{
			if (!sim_has_ended(philo))
				_sleep(philo);
			if (!sim_has_ended(philo))
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
		if ((philo->time_this_meal - philo->time_last_meal) > philo->time_to_die)
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

int	sim_has_ended(t_philos *philo)
{
	int	ended_sim;

	pthread_mutex_lock(&philo->mtx);
	ended_sim = *(philo->ended_sim);
	pthread_mutex_unlock(&philo->mtx);
	return (ended_sim);
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

long	get_debt(t_philos *philo)
{
	int	debt;

	pthread_mutex_lock(&philo->mtx);
	debt = philo->debt;
	pthread_mutex_unlock(&philo->mtx);
	return (debt);
}

void	kill_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->mtx);
	philo->alive = 0;
	pthread_mutex_unlock(&philo->mtx);
}
