/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:54:19 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/09 10:54:23 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	curr_timestamp(void)
{
	struct timeval	tv;
	long	now;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	now = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (now);
}

long	_now(void)
{
	struct timeval tv;
	long	now;
	
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	now = tv.tv_sec * 1000L + tv.tv_usec/ 1000L;
	return (now - (*_data(NULL))->started_sim_time);
}

long	elapsed_time(long first_event, long second_event)
{
	return (second_event - first_event);
}
