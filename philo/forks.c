/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:17:58 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/06 12:17:59 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	**init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(data->number_of_philosophers * sizeof(t_fork *));
	if (!data->forks)
		return (free(data), NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		*(data->forks + i) = malloc(sizeof(t_fork));
		if (!(*(data->forks + i)))
			return (fork_err(data, i));
		(*(data->forks + i))->id = i;
		if (pthread_mutex_init(&((*(data->forks + i))->mtx), NULL))
			return (free(*(data->forks + i)), fork_err(data, i));
		i++;
	}
	return (data->forks);
}

t_fork	**fork_err(t_data *data, int i)
{
	while (--i >= 0)
	{
		pthread_mutex_destroy(&((*(data->forks + i))->mtx));
		free(*(data->forks + i));
	}
	free(data->forks);
	free(data);
	return (NULL);
}
