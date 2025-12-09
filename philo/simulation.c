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

	data->started_sim_time = now();
	i = 0;
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

void	*run(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->mtx);
		eat(philo);
		pthread_mutex_unlock(&philo->mtx);
		_sleep(philo);
	}
	return (NULL);
}
