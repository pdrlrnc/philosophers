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

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	t_shared	shared;

	shared.counter = 0;
	pthread_mutex_init(&shared.lock, NULL);

	pthread_create(&t1, NULL, thread_func, &shared);
	pthread_create(&t2, NULL, thread_func, &shared);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&shared.lock);

	printf("counter: %d\n", shared.counter);
	
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
