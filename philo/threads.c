/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:31:48 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/09 14:31:49 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread(pthread_t *thread, void *(*f)(void *), t_philos *philo, t_ops op)
{
	if (op == CREATE)
		return (pthread_create(thread, NULL, f, philo)); 
	else if (op == JOIN)
		return (pthread_join(*thread, NULL));
	else if (op == DETACH)
		return (pthread_detach(*thread));
	return (1);
}
