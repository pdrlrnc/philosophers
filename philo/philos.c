/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 14:34:51 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/06 14:34:52 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	**init_philos(t_data *data)
{
	int	i;

	if (!create_philos(data))
		return (NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		(*(data->philos + i))->id = i;
		(*(data->philos + i))->times_ate = 0;
		if (!i)
			(*(data->philos + i))->left_fork = *(data->forks + data
					->number_of_philosophers - 1);
		else
			(*(data->philos + i))->left_fork = *(data->forks + i - 1);
		(*(data->philos + i))->right_fork = *(data->forks + i);
		if (mutex((*(data->philos + i))->mtx, CREATE))
			return (free(*(data->philos + i)), philos_err(data, i));
		if (mutex((*(data->referees + i))->mtx, CREATE))
		{
			mutex((*(data->philos + i))->mtx, DESTROY);
			return (free(*(data->philos + i)), philos_err(data, i));
		}
		i++;
	}
	return (data->philos);
}

t_philos	**philos_err(t_data *data, int i)
{
	while (--i >= 0)
	{
		mutex((*(data->philos + i))->mtx, DESTROY);
		if (*(data->referees + i))
			mutex((*(data->referees + i))->mtx, DESTROY);
		free(*(data->philos + i));
		if (*(data->referees + i))
			free(*(data->referees + i));
	}
	free(data->referees);
	fork_err(data, data->number_of_philosophers);
	return (NULL);
}

int	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(data->number_of_philosophers * sizeof(t_philos *));
	data->referees = malloc(data->number_of_philosophers * sizeof(t_referee *));
	if (!data->philos)
		return (fork_err(data, data->number_of_philosophers), 0);
	if (!data->referees)
	{
		free(data->philos);
		return (fork_err(data, data->number_of_philosophers), 0);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		*(data->philos + i) = malloc(sizeof(t_philos));
		if (!*(data->philos + i))
			return (philos_err(data, i), 0);
		*(data->referees + i) = malloc(sizeof(t_referee));
		if (!*(data->referees + i))
			return (philos_err(data, i + 1), 0);
		(*(data->referees + i))->id = i;
		i++;
	}	
	return (1);
}
