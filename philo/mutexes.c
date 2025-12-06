/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 14:14:59 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/06 14:15:00 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex(t_mtx mut, t_ops op)
{
	if (op == CREATE)
		return (pthread_mutex_init(&mut, NULL));
	if (op == DESTROY)
		return (pthread_mutex_destroy(&mut));
	return (1);
}

t_mtx	write_lock(void)
{
	static t_mtx	mtx;

	return (mtx);
}
