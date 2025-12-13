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
	thread(&data->ref, NULL, NULL, JOIN);
	clean(data);
}

void	*run(void *arg)
{
	t_philos	*philo;
	int			i;

	philo = (t_philos *)arg;
	i = 0;
	while (is_alive(philo) && !is_full(philo))
	{
		if (is_alive(philo) && !is_full(philo)
			&& (has_right_fork(philo) || (!has_right_fork(philo) && !i)))
			take_forks(philo);
		if (is_alive(philo) && !is_full(philo))
			eat(philo);
		check_times_ate(philo);
		drop_forks(philo);
		if (is_alive(philo) && !is_full(philo))
			_sleep(philo);
		if (is_alive(philo) && !is_full(philo))
			think(philo);
		i++;
	}
	if (!has_right_fork(philo))
		pthread_mutex_unlock(&philo->left_fork->mtx);
	return (NULL);
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
			kill_all(data);
		else
			data->ended_sim = check_if_all_full(data);
	}
	pthread_mutex_unlock(&data->mtx);
	return (NULL);
}

int	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (check_if_hungry(data->philos[i]))
			return (1);
		i++;
	}
	return (0);
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
