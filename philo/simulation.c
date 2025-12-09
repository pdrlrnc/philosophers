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

	mutex(data->mtx, LOCK);
	ended_sim = data->ended_sim;
	mutex(data->mtx, UNLOCK);
	return (ended_sim);
}

void	simulate(t_data *data)
{
	int		i;
	long	time;

	time = now();
	i = 0;
	while (i < data->number_of_philosophers)
	{
		mutex(data->philos[i]->mtx, LOCK);
		//eating
		usleep(data->time_to_eat);
		data->philos[i]->time_this_meal = time;
		data->philos[i]->times_ate++;
		//sleep
		usleep(data->time_to_sleep);
		mutex(data->philos[i]->mtx, UNLOCK);
		i++;
	}
}
