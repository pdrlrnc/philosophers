/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:47:24 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/09 14:47:26 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philos *philo)
{
	t_fork	*first;
	t_fork	*second;
	long	now;

	now = _now();
	if (philo->right_fork->id > philo->left_fork->id )
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(&first->mtx);
	_write(now, philo->id, ACT_2, 18);
	pthread_mutex_lock(&second->mtx);
	_write(now, philo->id, ACT_2, 18);
}

void	eat(t_philos *philo)
{
	long	timestamp;
	long	now;

	timestamp = curr_timestamp();
	now = _now();
	pthread_mutex_lock(&philo->mtx);
	_write(now, philo->id, ACT_1, 11);
	philo->times_ate++;
	philo->time_last_meal = philo->time_this_meal;
	philo->time_this_meal = timestamp;
	if (philo->time_last_meal != -1 && philo->time_this_meal != -1)
	{
		if (elapsed_time(philo->time_last_meal, philo->time_this_meal) > (*_data(NULL))->started_sim_time)
			philo->alive = 0;
	}
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->mtx);
}

void	drop_forks(t_philos *philo)
{	
	t_fork	*first;
	t_fork	*second;

	if (philo->right_fork->id > philo->left_fork->id )
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	pthread_mutex_unlock(&first->mtx);
	pthread_mutex_unlock(&second->mtx);


}

void	_sleep(t_philos *philo)
{
	_write(_now(), philo->id, ACT_3, 13);
	usleep(philo->time_to_sleep);
}
void	think(t_philos *philo)
{
	_write(_now(), philo->id, ACT_4, 13);
}
