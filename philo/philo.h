/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:32:12 by pedde-so          #+#    #+#             */
/*   Updated: 2025/11/20 11:32:14 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include "libft.h"

typedef	pthread_mutex_t t_mtx;

typedef struct s_fork
{
	long	id;
	t_mtx	mtx;
}	t_fork;

typedef struct s_philos
{
	int	id;
	t_fork	*left_fork;
	t_fork	*right_fork;
	long	time_last_meal;
	long	times_ate;
	t_mtx	mtx;
}	t_philos;

typedef struct s_data
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_eats;
	t_fork	**forks;
	t_philos	**philos;
	int		philo_dead;
}	t_data;

typedef enum e_ops
{
	CREATE,
	LOCK,
	UNLOCK,
	DESTROY
}	t_ops;

void	*thread_func(void *arg);
t_data	*parser(int argc, char **argv);
int	check_if_numeric(char **argv);
int	check_nb(char *nb_str);
t_data	*final_data_check(t_data *data);

//forks.c
t_fork	**init_forks(t_data *data);
t_fork	**fork_err(t_data *data, int i);

//mutexes.c
int	mutex(t_mtx mut, t_ops op);

//philos.c
t_philos	**init_philos(t_data *data);
t_philos	**philos_err(t_data *data, int i);


#endif
