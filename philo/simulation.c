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

int	ended_sim(void)
{
	int	ended_sim;

	pthread_mutex_lock(&(*_data(NULL))->mtx);
	ended_sim = (*_data(NULL))->ended_sim;
	pthread_mutex_unlock(&(*_data(NULL))->mtx);
	return (ended_sim);
}

void	end_sim(void)
{
	pthread_mutex_lock(&(*_data(NULL))->mtx);
	(*_data(NULL))->ended_sim = 1;
	pthread_mutex_unlock(&(*_data(NULL))->mtx);
}

void	simulate(t_data *data)
{
	int		i;

	data->started_sim_time = curr_timestamp();
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

int	check_if_dead(t_philos *philo)
{
	int	dead;

	dead = 0;
	if (ended_sim())
		return (1);
	pthread_mutex_lock(&philo->mtx);
	dead = philo->alive;
	if (dead)
		end_sim();
	pthread_mutex_unlock(&philo->mtx);
	return (dead);
}

void	*run(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!ended_sim())
	{
		if (!check_if_dead(philo))
			take_forks(philo);
		if (!check_if_dead(philo))
			eat(philo);
		if (!check_if_dead(philo))
			drop_forks(philo);
		if (!check_if_dead(philo))
			_sleep(philo);
		if (!check_if_dead(philo))
			think(philo);
	}
	return (NULL);
}
