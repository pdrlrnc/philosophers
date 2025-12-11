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
		//maybe usleep(1000)??
	return (NULL);
}

//mudar para data
//passsar o gajo para dead caso seja
int	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->philos[i]->mtx);
	while (data->philos[i] && !data->ended_sim)
	{
		if ((data->philos[i]->time_this_meal - data->philos[i]->time_this_meal) > data->time_to_die)
		{
			data->philos[i]->alive = 0;
			data->ended_sim = 1;
			pthread_mutex_unlock(&data->philos[i]->mtx);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i]->mtx);
		usleep(100);
		pthread_mutex_lock(&data->philos[i]->mtx);
	}
	return (0);
}

void	*run(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		//maybe if i % 2 != 0 usleep(1000)??
		take_forks(philo);
		//checkar
		eat(philo);
		//checkar
		drop_forks(philo);
		//checkar
		_sleep(philo);
		//checkar
		think(philo);
	}
	return (NULL);
}
