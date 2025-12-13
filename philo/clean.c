/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:34:44 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/12 15:34:45 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->philos[i]->mtx);
		pthread_mutex_destroy(&data->forks[i]->mtx);
		free(data->forks[i]);
		free(data->philos[i]);
		i++;
	}
	pthread_mutex_destroy(write_lock());
	pthread_mutex_destroy(&data->mtx);
	free(data->forks);
	free(data->philos);
	free(data);
}
