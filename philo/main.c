/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:31:24 by pedde-so          #+#    #+#             */
/*   Updated: 2025/11/20 11:31:25 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	data = parser(argc, argv);
	free(data);
	return (0);
}

void	*thread_func(void *arg)
{
	t_shared *shared;
	int	i;
	
	shared = (t_shared *)arg;
	i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&shared->lock);
		shared->counter++;
		pthread_mutex_unlock(&shared->lock);
		i++;
	}
	return (NULL);
}
