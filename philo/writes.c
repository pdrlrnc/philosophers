/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:21:05 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/09 17:21:06 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mtx	*write_lock(void)
{
	static t_mtx	mtx;
	return (&mtx);
}

void	_write(long time, long id, char *str, int strlen)
{
	pthread_mutex_lock(write_lock());
	ft_putnbr_fd(time, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	ft_putnbr_fd(id + 1, STDOUT_FILENO);
	write(STDOUT_FILENO, str, strlen);
	pthread_mutex_unlock(write_lock());
}

t_data	**_data(char **argv)
{
	static t_data *data;

	if (!data && argv)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (write(STDERR_FILENO, ERR_5, 29), NULL);
		if (pthread_mutex_init(&data->mtx, NULL))
		{
			free(data);
			return (write(STDERR_FILENO, ERR_6, 26), NULL);
		}
		atoi_input(data, argv);
		if (!init_forks(data))
			return (write(STDERR_FILENO, "Error creating forks\n", 21), NULL);
		if (!init_philos(data))
			return (write(STDERR_FILENO, "Error creating philosophers\n", 28), NULL);
	}
	return (&data);
}
